#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

// Estrutura de um Nó de uma árvore tamanho-n
struct Node{
    string name; 
    vector <Node *> neighbors;
};
// Função utilitária para criar um novo Nó
Node *newNode(string v){
    Node *temp = new Node;
    temp->name = v;
    return temp;
}

// Função para achar cliques
int find_cliques(vector<Node*> potential_clique, vector<Node*> remaining_nodes, vector<Node*> skip_nodes, int depth=0) {
    
    //Condição só é satisfeita quando não há nenhum nó remanecente E nenhum nó ignorado
    if (remaining_nodes.size() == 0 and skip_nodes.size() == 0) {
        cout << "This is a clique: [ ";
        for (auto n : potential_clique) cout << n->name << " ";
        cout << "]" << endl << endl;
        return 1;
    }

    int found_cliques = 0;
    for (auto node : remaining_nodes) {
        vector<Node*> new_potential_clique, aux={node}, aux2, new_remaining_nodes, new_skip_list;
        
        //Faz união do clique potencial que pode existir com o nó com analisado
        new_potential_clique = potential_clique;
        new_potential_clique.push_back(node);
        
        //Faz a interseção dos nós remanecentes com os nós vizinhos do nó analisado
        for (auto n : remaining_nodes) {
            for (auto x : node->neighbors){
                if(n->name == x->name)
                    new_remaining_nodes.push_back(n);
            }
        }

        //Faz a chamada recursiva que conta a quantidade de cliques encontrados
        for (auto n : skip_nodes) {
            for (auto x : node->neighbors){
                if(n->name == x->name)
                    new_skip_list.push_back(n);
            }
        }
        
        found_cliques += find_cliques(new_potential_clique, new_remaining_nodes, new_skip_list, depth+1);
        
        //Remove o vértice dos nós remanecentes
        vector<Node*>::iterator i=remaining_nodes.begin();
        for (auto n : remaining_nodes) {
            if (n->name == node->name) {
                remaining_nodes.erase(i);
            }
            ++i;
        }

        //Adiciona o nó analisado na lista de nós ignorados
        skip_nodes.push_back({node});
    }

    return found_cliques;
}

int main(){
    // Construção do grafo
    struct Node* A = newNode("A");
    struct Node* B = newNode("B");
    struct Node* C = newNode("C");
    struct Node* D = newNode("D");
    struct Node* E = newNode("E");
    struct Node* F = newNode("F");
    vector<Node *> all_nodes = {A, B, C, D, E, F};

    A->neighbors = {B, C, E};
    B->neighbors = {A, C, D, F};
    C->neighbors = {A, B, D, F};
    D->neighbors = {C, B, E, F};
    E->neighbors = {A, D};
    F->neighbors = {B, C, D};

    int total_cliques = find_cliques({}, all_nodes, {});
    cout << "Total cliques found: " << total_cliques;

    return 0;
}