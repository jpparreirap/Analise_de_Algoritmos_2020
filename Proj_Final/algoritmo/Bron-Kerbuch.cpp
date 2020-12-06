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
        cout << "]" << endl;
        return 1;
    }

    int found_cliques = 0;
    for (auto node : remaining_nodes) {
        vector<Node*> new_potential_clique, aux={node}, aux2, new_remaining_nodes, new_skip_list;
        
        //Faz união do clique potencial que pode existir com o nó com analisado
        set_union(potential_clique.begin(), potential_clique.end(), aux.begin(), aux.end(), back_inserter(new_potential_clique));

        //Faz a interseção dos nós remanecentes com os nós vizinhos do nó analisado
        set_intersection(remaining_nodes.begin(), remaining_nodes.end(), node->neighbors.begin(), node->neighbors.end(), back_inserter(new_remaining_nodes));

        //Faz a interseção dos nós ignorados com os nós vizinhos do nó analisado
        set_intersection(skip_nodes.begin(), skip_nodes.end(), node->neighbors.begin(), node->neighbors.end(), back_inserter(new_skip_list));
        
        //Faz a chamada recursiva que conta a quantidade de cliques encontrados
        found_cliques += find_cliques(new_potential_clique, new_remaining_nodes, new_skip_list, depth+1);

        //Remove o vértice dos nós remanecentes
        set_difference(remaining_nodes.begin(), remaining_nodes.end(), aux.begin(), aux.end(), back_inserter(aux2));
        remaining_nodes = aux2;

        //Adiciona o nó analisado na lista de nós ignorados
        set_union(skip_nodes.begin(), skip_nodes.end(), aux.begin(), aux.end(), back_inserter(aux2));
        skip_nodes = aux2;
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

    //Vizinhança de cada um dos nós
    A->neighbors = {B, C, E};
    B->neighbors = {A, C, D, F};
    C->neighbors = {A, B, D, F};
    D->neighbors = {C, B, E, F};
    E->neighbors = {A, D};
    F->neighbors = {B, C, D};

    //Chamada da função
    int total_cliques = find_cliques({}, all_nodes, {});
    cout << "Total cliques found: " << total_cliques;

    return 0;
}