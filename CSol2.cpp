//--------mcmf(EK)
#include<bits/stdc++.h>
using namespace std;
#define inf 1000000000
#define ll long long
#define N 100050
typedef struct{int to, nxt, w, c;} Edge;

template<class T>
inline void read(T& x){
    x = 0; int f = 0; register char c = 0;
    while(!isdigit(c)) f |= c == '-', c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    x = f ? -x : x;
}
template<class T1, class... Tn>
inline void read(T1& x1, Tn&... xn){
    read(x1), read(xn...);
}
int n, m;

int S, T;
Edge edge[5000000];
int G[N];
int eid = 2;
inline void link(int u, int v, int w, int c){
    edge[eid] = (Edge){v, G[u], w, c}, G[u] = eid++;
    edge[eid] = (Edge){u, G[v], 0, -c}, G[v] = eid++;
}

int pre[N], lst[N], vis[N];
int cst[N], flw[N];
int q[N], qf, qb;
bool spfa(){
    memset(vis, 0, sizeof vis); 
    memset(cst, 127, sizeof cst); 
    memset(flw, 127, sizeof flw);
    qf = qb = 0; 
    q[++qb % N] = S, vis[S] = 1, cst[S] = 0, pre[T] = 0;
    while(qf != qb){
        int u = q[++qf % N]; vis[u] = 0;
        for(int i = G[u]; i; i = edge[i].nxt){
            int v = edge[i].to;
            int w = edge[i].w, c = edge[i].c;
            if(w > 0 && cst[u] + c < cst[v]){
                cst[v] = cst[u] + c,
                pre[v] = u, lst[v] = i,
                flw[v] = min(flw[u], w);
                if(!vis[v]) q[++qb % N] = v, vis[v] = 1;
            }      
        }    
    } 
    return pre[T];
}

int cost, flow;
void mcmf(){
    while(spfa()){
        flow += flw[T], cost += flw[T] * cst[T];
        int cur = T;
        while(cur != S){
            int e = lst[cur];
            edge[e].w -= flw[T],
            edge[e ^ 1].w += flw[T];
            cur = pre[cur];
        }
    }
}
int room[N];
int cnt[N];
int main(){
    read(n, m); 
    S = n + 1, T = n + 2;
    for(int i = 2; i <= n; i++) {
        link(i, i/2, inf, 1);
        link(i/2, i, inf, 1);
    }
    for(int i = 1; i <= n; i++) {
        read(room[i]);
    }
    for(int i = 1; i <= m; i++) {
        int pos; read(pos);
        ++cnt[pos];  
    }
    for(int i = 1; i <= n; i++) {
        int w = room[i];
        if(w >= cnt[i]) {
            w -= cnt[i];
            link(i, T, w, 0);
        } else {
            cnt[i] -= w;
            link(S, i, cnt[i], 0);
        }
    }

    mcmf();
    cout << cost << endl;
    return 0;
}