#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;

const int tam = 6;
list<int> grafo[tam], all_nodes;

void addEdge(list<int> adj[], int v1, int v2) {
    adj[v1].push_back(v2);
}

void imprime_Grafo() {
    for (auto n : grafo) {
        cout << "["; for (auto m : n) cout << ' ' << m; cout << " ]" << endl;
    }
}

void imprime_lista(list <int> l) { 
    cout << "["; for(auto n : l) cout << ' ' << n; cout << " ]" << endl;
} 

void leitura() {
    FILE *arq;
    arq = fopen("teste.txt", "r");
    int v1, v2, nodes = 0;

    if(arq == NULL)
        cout << "Erro, nao foi possivel abrir o arquivo";
    else {
        
        while ( (fscanf(arq, "%d %d\n", &v1,&v2))!=EOF) {
            addEdge(grafo, v1-1, v2-1);
            if(v1 != nodes){ all_nodes.push_back(nodes++); }
        }
    }
    fclose(arq);
}

int find_cliques(list<int>potential_clique, list<int>remaining_nodes, list<int>skip_nodes) {
    list<int> rm = remaining_nodes;
    if(remaining_nodes.size() == 0 and skip_nodes.size() == 0) {
        cout << "This is a clique: ";
        imprime_lista(potential_clique);
        cout << endl;
        return 1;
    }

    int found_cliques = 0;
    for (auto node : rm) {
        list<int> new_potential_clique = potential_clique, new_remaining_nodes, new_skip_list;

        new_potential_clique.push_back(node);
        for (auto n : remaining_nodes) {
            for (auto m : grafo[node]){
                if(n == m) new_remaining_nodes.push_back(m);
            }
        }
        for (auto n : skip_nodes) {
            for (auto m : grafo[node]){
                if (n == m) new_skip_list.push_back(m);
            }
        }

        found_cliques += find_cliques(new_potential_clique, new_remaining_nodes, new_skip_list);
        remaining_nodes.remove(node);
        skip_nodes.push_back(node);
    }

    return found_cliques;
}

int main() {

    leitura();
    system("pause");

    int total_cliques = find_cliques({},all_nodes,{});
    cout << "Total cliques found: " << total_cliques;

    return 0;
}