#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

const int tam = 6;
int iteracoes = 0;
list<int> grafo[tam], all_nodes;

void addEdge(list<int> adj[], int v1, int v2) {
    adj[v1].push_back(v2);
    //adj[v2].push_back(v1);
}

void imprime_Grafo() {
    for (auto n : grafo) {
        cout << "["; 
        for (auto m : n) cout << ' ' << m;
        cout << " ]" << endl;
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
    iteracoes++;
    list<int> rm = remaining_nodes;
    if(remaining_nodes.size() == 0 and skip_nodes.size() == 0) {
        cout << "This is a clique: ";
        imprime_lista(potential_clique);
        cout << endl;
        return 1;
    }

    int found_cliques = 0;
    
    list<int>::iterator node;
    for (node = rm.begin(); node != rm.end(); node++) {
        list<int> new_potential_clique, new_remaining_nodes, new_skip_list, aux = {*node}, temp;
        
        set_union(potential_clique.begin(), potential_clique.end(),
                  aux.begin(), aux.end(), 
                  back_inserter(new_potential_clique));
        
        set_intersection(remaining_nodes.begin(), remaining_nodes.end(),
                         grafo[*node].begin(), grafo[*node].end(),
                         back_inserter(new_remaining_nodes));
        
        set_intersection(skip_nodes.begin(), skip_nodes.end(),
                         grafo[*node].begin(), grafo[*node].end(),
                         back_inserter(new_skip_list));

        // for (auto n : remaining_nodes) {
        //     for (auto m : grafo[*node]) {
        //         if(n == m) new_remaining_nodes.push_back(m);
        //     }
        // }
        // for (auto n : skip_nodes) {
        //     for (auto m : grafo[*node]) {
        //         if (n == m) new_skip_list.push_back(m);
        //     }
        // }


        found_cliques += find_cliques(new_potential_clique, new_remaining_nodes, new_skip_list);
        remaining_nodes.remove(*node);
        set_union(skip_nodes.begin(), skip_nodes.end(),
                  aux.begin(), aux.end(),
                  back_inserter(temp));
        skip_nodes = temp;
    }

    return found_cliques;
}

int main() {

    leitura();
    
    imprime_Grafo();
    cout << endl;

    int total_cliques = find_cliques({},all_nodes,{});
    cout << "Total cliques found: " << total_cliques << endl;
    cout << "Iteracoes: " << iteracoes << endl;

    return 0;
}