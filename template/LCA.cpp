#include<bits/stdc++.h>
using namespace std;

#define N 500005
typedef struct{int to, nxt;} Edge;

int n, S;
int lg[N];

Edge edge[N << 1];
int G[N];
int eid = 2;
void adde(int u, int v){
    edge[eid] = (Edge){v, G[u]}, G[u] = eid++;
    edge[eid] = (Edge){u, G[v]}, G[v] = eid++;
}

int fa[21][N];

int deep[N];
int Q[N], qb, qf;
void bfs(){
    for(int i = 1; i <= n; ++i) deep[i] = -1; deep[S] = 1;
    qb = qf = 0, Q[++qb] = S;
    while(qf != qb){
        int u = Q[++qf];
        for(int i = G[u]; i; i = edge[i].nxt){
            int v = edge[i].to;
            if(deep[v] < 0)
                deep[v] = deep[u] + 1, fa[0][v] = u,
                Q[++qb] = v;
        }
    }
    for(int i = 1; i < 21; ++i)
        for(int j = 1; j <= n; ++j)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
}


int lca(int u, int v){
    if(deep[u] < deep[v]) swap(u, v);
    while(deep[u] > deep[v]) u = fa[lg[deep[u] - deep[v]]][u];
    if(u == v) return u;
    for(int k = lg[deep[u]]; k >= 0; --k)
        if(fa[k][u] != fa[k][v]) u = fa[k][u], v = fa[k][v];
    return fa[0][u];
}

int main(){
    for(int i = 1; i <= n; ++i)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i), --lg[i - 1];
    


    return 0;
}