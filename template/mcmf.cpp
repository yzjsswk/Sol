//--------mcmf(EK)
#include"prepare.h"
using namespace prepare;

typedef struct{int to, nxt; ll w, c;} Edge;
#define N 10000

int n, m;

int s, t;
Edge edge[5000000];
int g[N];
int eid = 2;
inline void adde(int u, int v, ll w, ll c){
    //if(w) cout << u << "->" << v << ": " << w << endl;
    edge[eid].to = v, 
    edge[eid].w = w,
    edge[eid].c = c,
    edge[eid].nxt = g[u];
    g[u] = eid++;
    edge[eid].to = u, 
    edge[eid].w = 0,
    edge[eid].c = -c,
    edge[eid].nxt = g[v];
    g[v] = eid++;
}

void build(){
    cin >> n >> m >> s >> t;
    int u, v; ll w, c;
    for(int i = 1; i <= m; ++i){
        cin >> u >> v >> w >> c;
        adde(u, v, w, c);
    }
}

int pre[N], lst[N], vis[N];
ll cst[N], flw[N];
int q[N], qf, qb;
bool spfa(){
    mst(vis, 0); mst(cst, 127); mst(flw, 127);
    qf = qb = 0; 
    q[++qb % N] = s, vis[s] = 1, cst[s] = 0, pre[t] = 0;
    while(qf != qb){
        int u = q[++qf % N]; vis[u] = 0;
        for(int i = g[u]; i; i = edge[i].nxt){
            int v = edge[i].to;
            ll w = edge[i].w, c = edge[i].c;
            if(w > 0 && cst[u] + c < cst[v]){
                cst[v] = cst[u] + c,
                pre[v] = u, lst[v] = i,
                flw[v] = min(flw[u], w);
                if(!vis[v]) q[++qb % N] = v, vis[v] = 1;
            }      
        }    
    } 
    return pre[t];
}

ll cost, flow;
void mcmf(){
    while(spfa()){
        flow += flw[t], cost += flw[t] * cst[t];
        int cur = t;
        while(cur != s){
            int e = lst[cur];
            edge[e].w -= flw[t],
            edge[e ^ 1].w += flw[t];
            cur = pre[cur];
        }
    }
}

int main(){
    ready();
    build();
    mcmf();
    cout << flow << " " << cost << endl;
    
    return 0;
}