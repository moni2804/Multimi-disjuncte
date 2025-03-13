/*
 * Make_set are complexitatea: O(1)
 * Find_set are complexitatea: O(1)
 * Union_ are complexitatea: O(1)
 * Kruskal are complexitatea: O(e lg e), e- nr de muchii
 */
#include <iostream>
#include <vector>
 ///pentru sort
#include "Profiler.h"
using namespace std;

Profiler profiler;

struct node{
    int rank,key;
};
struct edge{
    int u,v,cost;
};
///struct-ul pentru muchii are cele doua noduri intre care este muchia si costul dintre ele

node parent[10005];
///vectorul de parinti al grafului

vector <edge> edges,edges_min;
//array pentru toate muchiile grafului si array pentru muchiile arborelui de acoperire minima

void make_set(int x,Operation &op_make){
    parent[x].key=x;
    parent[x].rank=1; ///incep de la rank=1
    op_make.count(2);
}

int find_set(int x,Operation &op_find){ ///tin inaltimea constanta la 1, maxim o sa fie 3 daca nu proceseaza un nod ,,,complexitate constanta o(1), pentru unele poate ajunge la o(lg n)
    op_find.count();
    if(x != parent[x].key){
        op_find.count();
        parent[x].key= find_set(parent[x].key,op_find);
    }
    return parent[x].key;
}

void union_(int x,int y,Operation &op_union,Operation &op_find){ ///complexitate constanta o(1)
    int rootx= find_set(x,op_find);
    int rooty= find_set(y,op_find);
    op_union.count(2);

    if(rootx != rooty){
        if(parent[rootx].rank < parent[rooty].rank){
            parent[rootx].key=rooty;
            op_union.count();
        } else if(parent[rootx].rank > parent[rooty].rank){
            parent[rooty].key=rootx;
            op_union.count();
        } else{
            parent[rootx].key=rooty;
            parent[rooty].rank++;
            op_union.count(2);
        }
    }
}

void kruskal(int n,Operation &op_find,Operation &op_union){
    sort(edges.begin(),edges.end(),[](edge a,edge b){
        return a.cost<b.cost;
    }); ///sortare dupa cost

    for(edge e:edges){
       if(find_set(e.u,op_find)!=find_set(e.v,op_find)){ ///daca nu sunt deja legate
           edges_min.push_back(e); ///muchia cu cost minim
           union_(e.u,e.v,op_union,op_find);
       }
    }
}

void display(int n,Operation &op_find){
    for(int i=0;i<n;i++){
        cout<<"Element: "<<i<<"-> reprezentant: "<<find_set(i,op_find)<<endl;
    }
}

void display_k(){
    cout << "Muchiile arborelui de acoperire minimă:\n";
    for (edge e : edges_min) {
        cout << e.u << " -- " << e.v << " (cost: " << e.cost <<")"<<endl;
    }
}

void demo(){
    int n=10;
    Operation op=profiler.createOperation("Demo_op",n);
    Operation op2=profiler.createOperation("Demo2_op",n);

    for(int i=0;i<n;i++){
        make_set(i,op);
    }

    cout<<"Multimi initiale: "<<endl;
    display(n,op);

    union_(0,1,op,op2);
    union_(2,3,op,op2);
    union_(4,5,op,op2);
    union_(1,2,op,op2);
    union_(6,7,op,op2);

    cout<<"Multimile dupa union: "<<endl;
    display(n,op);

    //Kruskal
    n=5;
    edges={
            {0,1,1},
            {0,2,4},
            {1,2,2},
            {1,3,6},
            {2,3,3},
            {2,4,5},
            {3,4,7},
            {0,4,8},
            {1,4,9}
    };

    for(int i=0;i<n;i++){
        make_set(i,op);
    }

    kruskal(n,op,op2);
    display_k();
}

void perf(){
    for(int n=100;n<=10000;n+=100) {
        for(int test=0;test<5;test++) {
            ///int a[][n]={};
            vector<vector<int>> a(n, vector<int>(n, 0)); ///matricea de adiacenta
            edges.clear();
            edges_min.clear();

            Operation op_make = profiler.createOperation("Operatii_make", n);
            Operation op_find = profiler.createOperation("Operatii_find", n);
            Operation op_union = profiler.createOperation("Operatii_union", n);



            for (int i = 0; i < n; i++) {
                make_set(i, op_make);
            }

            for (int i = 0; i < n - 1; i++) { ///cream cate o muchie intre fiecare nod, in afara de primul si ultimul
                int cost = rand() % 100 + 1;  ///costul este intre 1 si 100
                edges.push_back({i, i + 1, cost});
                a[i][i + 1] = cost;
                a[i + 1][i] = cost;
            }

            while (edges.size() < 4 * n) {
                int u = rand() % n;
                int v = rand() % n;
                int cost = rand() % 100 + 1;
                if (u != v && a[u][v] == 0) {
                    a[u][v] = cost;
                    a[v][u] = cost;
                    edges.push_back({u, v, cost});
                }
            }

            kruskal(n,op_find,op_union);

            
        }

    }

    profiler.divideValues("Operatii_make",5);
    profiler.divideValues("Operatii_find",5);
    profiler.divideValues("Operatii_union",5);

    profiler.createGroup("Operatii","Operatii_make","Operatii_find","Operatii_union");
    profiler.showReport();
}


int main() {
    demo();
   //std::iota(parent.begin(), parent.end(), 0); // Each node is its own parent perf();
    return 0;
}
