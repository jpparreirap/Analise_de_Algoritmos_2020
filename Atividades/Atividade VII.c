/**
Aluno: Joao Paulo Parreira Peixoto

NOTE: This code is referenced from the web page:
https://www.programiz.com/dsa/red-black-tree
It is used only as a study for the discipline Analysis of Algorithms

Nota2: Implementation of the reused hash table of the discipline Data Structure 2.
*/

// Implementing Red-Black Tree in C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum nodeColor {
  RED,
  BLACK
};

struct rbNode {
  int data, color;
  struct rbNode *link[2];
};

struct rbNode *root = NULL;

// Create a red-black tree
struct rbNode *createNode(int data) {
  struct rbNode *newnode;
  newnode = (struct rbNode *)malloc(sizeof(struct rbNode));
  newnode->data = data;
  newnode->color = RED;
  newnode->link[0] = newnode->link[1] = NULL;
  return newnode;
}

// Insert an node
void insertion(int data) {
  struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
  int dir[98], ht = 0, index;
  ptr = root;
  if (!root) {
    root = createNode(data);
    return;
  }

  stack[ht] = root;
  dir[ht++] = 0;
  while (ptr != NULL) {
    if (ptr->data == data) {
      printf("Duplicates Not Allowed!!\n");
      return;
    }
    index = (data - ptr->data) > 0 ? 1 : 0;
    stack[ht] = ptr;
    ptr = ptr->link[index];
    dir[ht++] = index;
  }
  stack[ht - 1]->link[index] = newnode = createNode(data);
  while ((ht >= 3) && (stack[ht - 1]->color == RED)) {
    if (dir[ht - 2] == 0) {
      yPtr = stack[ht - 2]->link[1];
      if (yPtr != NULL && yPtr->color == RED) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 0) {
          yPtr = stack[ht - 1];
        } else {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[1];
          xPtr->link[1] = yPtr->link[0];
          yPtr->link[0] = xPtr;
          stack[ht - 2]->link[0] = yPtr;
        }
        xPtr = stack[ht - 2];
        xPtr->color = RED;
        yPtr->color = BLACK;
        xPtr->link[0] = yPtr->link[1];
        yPtr->link[1] = xPtr;
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    } else {
      yPtr = stack[ht - 2]->link[0];
      if ((yPtr != NULL) && (yPtr->color == RED)) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 1) {
          yPtr = stack[ht - 1];
        } else {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[0];
          xPtr->link[0] = yPtr->link[1];
          yPtr->link[1] = xPtr;
          stack[ht - 2]->link[1] = yPtr;
        }
        xPtr = stack[ht - 2];
        yPtr->color = BLACK;
        xPtr->color = RED;
        xPtr->link[1] = yPtr->link[0];
        yPtr->link[0] = xPtr;
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    }
  }
  root->color = BLACK;
}

// Delete a node
void deletion(int data) {
  struct rbNode *stack[98], *ptr, *xPtr, *yPtr;
  struct rbNode *pPtr, *qPtr, *rPtr;
  int dir[98], ht = 0, diff, i;
  enum nodeColor color;

  if (!root) {
    printf("Tree not available\n");
    return;
  }

  ptr = root;
  while (ptr != NULL) {
    if ((data - ptr->data) == 0)
      break;
    diff = (data - ptr->data) > 0 ? 1 : 0;
    stack[ht] = ptr;
    dir[ht++] = diff;
    ptr = ptr->link[diff];
  }

  if (ptr->link[1] == NULL) {
    if ((ptr == root) && (ptr->link[0] == NULL)) {
      free(ptr);
      root = NULL;
    } else if (ptr == root) {
      root = ptr->link[0];
      free(ptr);
    } else {
      stack[ht - 1]->link[dir[ht - 1]] = ptr->link[0];
    }
  } else {
    xPtr = ptr->link[1];
    if (xPtr->link[0] == NULL) {
      xPtr->link[0] = ptr->link[0];
      color = xPtr->color;
      xPtr->color = ptr->color;
      ptr->color = color;

      if (ptr == root) {
        root = xPtr;
      } else {
        stack[ht - 1]->link[dir[ht - 1]] = xPtr;
      }

      dir[ht] = 1;
      stack[ht++] = xPtr;
    } else {
      i = ht++;
      while (1) {
        dir[ht] = 0;
        stack[ht++] = xPtr;
        yPtr = xPtr->link[0];
        if (!yPtr->link[0])
          break;
        xPtr = yPtr;
      }

      dir[i] = 1;
      stack[i] = yPtr;
      if (i > 0)
        stack[i - 1]->link[dir[i - 1]] = yPtr;

      yPtr->link[0] = ptr->link[0];

      xPtr->link[0] = yPtr->link[1];
      yPtr->link[1] = ptr->link[1];

      if (ptr == root) {
        root = yPtr;
      }

      color = yPtr->color;
      yPtr->color = ptr->color;
      ptr->color = color;
    }
  }

  if (ht < 1)
    return;

  if (ptr->color == BLACK) {
    while (1) {
      pPtr = stack[ht - 1]->link[dir[ht - 1]];
      if (pPtr && pPtr->color == RED) {
        pPtr->color = BLACK;
        break;
      }

      if (ht < 2)
        break;

      if (dir[ht - 2] == 0) {
        rPtr = stack[ht - 1]->link[1];

        if (!rPtr)
          break;

        if (rPtr->color == RED) {
          stack[ht - 1]->color = RED;
          rPtr->color = BLACK;
          stack[ht - 1]->link[1] = rPtr->link[0];
          rPtr->link[0] = stack[ht - 1];

          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          dir[ht] = 0;
          stack[ht] = stack[ht - 1];
          stack[ht - 1] = rPtr;
          ht++;

          rPtr = stack[ht - 1]->link[1];
        }

        if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
          (!rPtr->link[1] || rPtr->link[1]->color == BLACK)) {
          rPtr->color = RED;
        } else {
          if (!rPtr->link[1] || rPtr->link[1]->color == BLACK) {
            qPtr = rPtr->link[0];
            rPtr->color = RED;
            qPtr->color = BLACK;
            rPtr->link[0] = qPtr->link[1];
            qPtr->link[1] = rPtr;
            rPtr = stack[ht - 1]->link[1] = qPtr;
          }
          rPtr->color = stack[ht - 1]->color;
          stack[ht - 1]->color = BLACK;
          rPtr->link[1]->color = BLACK;
          stack[ht - 1]->link[1] = rPtr->link[0];
          rPtr->link[0] = stack[ht - 1];
          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          break;
        }
      } else {
        rPtr = stack[ht - 1]->link[0];
        if (!rPtr)
          break;

        if (rPtr->color == RED) {
          stack[ht - 1]->color = RED;
          rPtr->color = BLACK;
          stack[ht - 1]->link[0] = rPtr->link[1];
          rPtr->link[1] = stack[ht - 1];

          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          dir[ht] = 1;
          stack[ht] = stack[ht - 1];
          stack[ht - 1] = rPtr;
          ht++;

          rPtr = stack[ht - 1]->link[0];
        }
        if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
          (!rPtr->link[1] || rPtr->link[1]->color == BLACK)) {
          rPtr->color = RED;
        } else {
          if (!rPtr->link[0] || rPtr->link[0]->color == BLACK) {
            qPtr = rPtr->link[1];
            rPtr->color = RED;
            qPtr->color = BLACK;
            rPtr->link[1] = qPtr->link[0];
            qPtr->link[0] = rPtr;
            rPtr = stack[ht - 1]->link[0] = qPtr;
          }
          rPtr->color = stack[ht - 1]->color;
          stack[ht - 1]->color = BLACK;
          rPtr->link[0]->color = BLACK;
          stack[ht - 1]->link[0] = rPtr->link[1];
          rPtr->link[1] = stack[ht - 1];
          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          break;
        }
      }
      ht--;
    }
  }
}

// Print the inorder traversal of the tree
void inorderTraversal(struct rbNode *node) {
  if (node) {
    inorderTraversal(node->link[0]);
    printf("%d  ", node->data);
    inorderTraversal(node->link[1]);
  }
  return;
}

///HASH
typedef struct name{
    int data;
}DATA;

typedef struct hashstr{
    DATA *chaves;
    int tam;
}HASHStr;

HASHStr* cria_hashT(int k){
    HASHStr* no = (HASHStr*)malloc(sizeof(HASHStr));
    no->chaves= (DATA*)malloc(k * sizeof(DATA));
    for (int i = 0; i < k; i++)
        no->chaves[i].data = -1;
    no->tam = k;

    return no;
}

HASHStr* insereHash(HASHStr* h, int data){
    int i = 1;
    int pos = data % h->tam;

    while ( pos <= h->tam && h->chaves[pos].data != -1 && h->chaves[pos].data != -2 ) {
        pos = ( pos + i * ( 1+ (data % ((h->tam)-2))) )% h->tam;
        i++;
    }
    if(h->chaves[pos].data == -1 || h->chaves[pos].data == -2){
        h->chaves[pos].data = data;
    }
    else
        insertion(data);

    return h;
}

//HASHStr* removeHash(HASHStr* h, char* nome){
//    int i = 1;
//    int pos = (int)nome[0] % h->tam;
//    while (pos <= h->tam && strcmp(h->chaves[pos].nome, nome)!= 0) {
//        pos = ( pos + i * ( 1+ (((int)nome[0]) % ((h->tam)-2))) )% h->tam;
//        i++;
//    }
//    if (strcmp(h->chaves[pos].nome, nome)==0)
//        strcpy(h->chaves[pos].nome, "-2" );
//
//    return h;
//}

void imprimeHash(HASHStr* h) {
    int i;
    for (i = 0; i < h->tam; i++) {
        if (h->chaves[i].data == -1 || h->chaves[i].data == -2) {
                printf("vazia\n",i);
        } else{
            printf("%d - numero : %d \n", i, h->chaves[i].data);
        }
    }
}

void liberaHash(HASHStr* h){
        free(h->chaves);
}


void shuffle(int *arr, size_t n)
{
    time_t t;
    if (n > 1)
    {
        size_t i;
        srand(time(&t));
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}


// Driver code
int main() {

    printf("\nTabela Hash: \n\n\n");

    HASHStr *num = cria_hashT(11);
    num = insereHash(num, 10);
    num = insereHash(num, 25);
    num = insereHash(num, 30);
    num = insereHash(num, 10);

    imprimeHash(num);

    printf("\n\n\nArvore RB: \n\n\n");
    inorderTraversal(root);

    return 0;
}
