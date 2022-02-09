#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 1000000000
#define N 10000

typedef struct{int to, nxt, w;} Edge;
int n, m;
int S, T;
Edge edge[5000000];
int G[N];
int eid = 2;
inline void link(int u, int v, int w){
    //if(w) cout << u << "->" << v << ": " << w << endl;
    edge[eid] = (Edge){v, G[u], w}, G[u] = eid++;
    edge[eid] = (Edge){u, G[v], 0}, G[v] = eid++;
}

int deep[N], vis[N];
int q[N], qf, qb;
int bfs(){
	memset(deep, -1, sizeof deep);
	qf = qb = 0, deep[S] = 1; q[++qb] = S;
	while(qf != qb){
		int u = q[++qf]; vis[u] = 0;
		for(int i = G[u]; i; i = edge[i].nxt){
			int v = edge[i].to, w = edge[i].w;
			if(w > 0 && deep[v] < 0){
				if(!vis[v]) q[++qb] = v, vis[v] = 1;
				deep[v] = deep[u] + 1;
			}
		}
	}
	return deep[T] != -1;
}

int dfs(int u, int rst){
	if(u == T) return rst;
	int k, ret = 0; 
	for(int i = G[u]; i && rst; i = edge[i].nxt){
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
    while(bfs()) ans += dfs(S, inf);
    return ans;
}


int main(){

    

    return 0;
}