//------------MinCutTree
#include"prepare.h"
using namespace prepare;

typedef struct{int to, nxt, w;} Edge;
#define N 10000

int n, m;
int tmpw[1000000];
int eeid;

int s, t;
Edge edge[1000000];
int g[N], tree[N];
int eid = 2;
inline void adde(int u, int v, int w){
    //if(w) cout << u << "->" << v << ": " << w << endl;
    edge[eid] = (Edge){v, g[u], w}, g[u] = eid++;
    edge[eid] = (Edge){u, g[v], 0}, g[v] = eid++;
}

inline void adde2(int u, int v, int w){
    //if(w) cout << u << "->" << v << ": " << w << endl;
    edge[eid] = (Edge){v, tree[u], w}, tree[u] = eid++;
    edge[eid] = (Edge){u, tree[v], w}, tree[v] = eid++;
}

void build(){
    eid = 2; mst(g, 0); mst(tree, 0);
    read(n, m);
    int u, v, w;
    for(int i = 1; i <= m; ++i){
        read(u, v, w);
        adde(u, v, w);
        adde(v, u, w);
    }
    eeid = eid;
    for(int i = 2; i < eeid; ++i) tmpw[i] = edge[i].w;
}

int deep[N], vis[N];
int q[N], qf, qb;
int bfs(){
	mst(deep, -1);
	qf = qb = 0, deep[s] = 1;
	q[++qb] = s;
	while(qf != qb){
		int u = q[++qf]; vis[u] = 0;
		for(int i = g[u]; i; i = edge[i].nxt){
			int v = edge[i].to, w = edge[i].w;
			if(w > 0 && deep[v] < 0){
				if(!vis[v]) q[++qb] = v, vis[v] = 1;
				deep[v] = deep[u] + 1;
			}
		}
	}
	return deep[t] != -1;
}

int dfs(int u, int rst){
	if(u == t) return rst;
	int k, ret = 0; 
	for(int i = g[u]; i && rst; i = edge[i].nxt){
		int v = edge[i].to, w = edge[i].w;
		if(w > 0 && (deep[v] == deep[u] + 1)){
			k = dfs(v, min(rst, w));
			if(k == 0) deep[v] = -1; 
			edge[i].w -= k, edge[i ^ 1].w += k;
			ret += k, rst -= k;
		}
	}
	return ret;
}

ll dinic(){
    ll ans = 0;
    while(bfs()) ans += dfs(s, inf);
    return ans;
}

void work(vi& vlst){
    if(vlst.size() == 1) return;
    s = vlst[0], t = vlst[1];
    int flow = (int)dinic();
    adde2(s, t, flow), adde2(t, s, flow);
    vi va, vb;
    for(auto& x: vlst) 
        if(deep[x] == -1) va.push_back(x);
        else vb.push_back(x);
    for(int i = 2; i < eeid; ++i) edge[i].w = tmpw[i];
    work(va), work(vb);
}

int fa[21][N], lg[N], mph[21][N];
void bfs2(){
    mst(deep, -1); deep[1] = 1;
    qb = qf = 0, q[++qb] = 1;
    while(qf != qb){
        int u = q[++qf];
        for(int i = tree[u]; i; i = edge[i].nxt){
            int v = edge[i].to, w = edge[i].w;
            if(deep[v] < 0){
                deep[v] = deep[u] + 1;
                q[++qb] = v;
                fa[0][v] = u, mph[0][v] = w;
            }
        }
    }
}

int mincut(int u, int v){
    if(deep[u] < deep[v]) swap(u, v);
    int ans = inf;
    while(deep[u] > deep[v]) 
        ans = min(ans, mph[lg[deep[u] - deep[v]]][u]), u = fa[lg[deep[u] - deep[v]]][u];
    if(u == v) return ans;
    for(int k = lg[deep[u]]; k >= 0; --k)
        if(fa[k][u] != fa[k][v])
            ans = min(ans, mph[k][u]), ans = min(ans, mph[k][v]),
            u = fa[k][u], v = fa[k][v];
    ans = min(ans, min(mph[0][u], mph[0][v]));
    return ans;
}

int main(){
    ready();
    int tt; read(tt);
    for(int i = 1; i <= n; ++i)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i), --lg[i - 1];
    while(tt--){
        build();
        vi vlst;
        for(int i = 1; i <= n; ++i) vlst.push_back(i);
        work(vlst);
        bfs2();
        for(int i = 1; i < 21; ++i)
            for(int j = 1; j <= n; ++j)
                fa[i][j] = fa[i - 1][fa[i - 1][j]],
                mph[i][j] = min(mph[i - 1][j], mph[i - 1][fa[i - 1][j]]);

    }
    

  

    return 0;
}