#include<bits/stdc++.h>
using namespace std;
#define inf 1000000000
#define ll long long
#define N 10000



int n, m;
int S, T;
Edge edge[5000000];
int G[N];
int eid = 2;
typedef struct{int to, nxt, w, c;} Edge;
inline void link(int u, int v, int w, int c){
    edge[eid] = (Edge){v, G[u], w, c}, G[u] = eid++;
    edge[eid] = (Edge){u, G[v], 0, -c}, G[v] = eid++;
}
int vis[N], dis[N]; deque<int> q;
bool spfa(){
    memset(dis, 127, sizeof dis); dis[T] = 0, q.push_front(T);
    while(!q.empty()){
        int u = q.front(); q.pop_front(); vis[u] = 0;
        for(int i = G[u]; i; i = edge[i].nxt){
            int v = edge[i].to, w = edge[i ^ 1].w, c = edge[i ^ 1].c;
            if(w > 0 && dis[u] + c < dis[v]){
                dis[v] = dis[u] + c; if(vis[v]) continue;
                if(!q.empty() && dis[v] < dis[q.front()]) 
                    q.push_front(v); else q.push_back(v);
                vis[v] = 1;
            }      
        }    
    } 
    return dis[S] < dis[0];
}
ll cost, flow;
int dfs(int u, int rst){
	if(u == T) return rst; vis[u] = 1; int k, ret = 0; 
	for(int i = G[u]; i && rst; i = edge[i].nxt){
		int v = edge[i].to, w = edge[i].w, c = edge[i].c;
		if(!vis[v] && w > 0 && dis[u] == dis[v] + c){
			k = dfs(v, min(rst, w)); if(k == 0) dis[v] = inf; 
			edge[i].w -= k, edge[i ^ 1].w += k, 
            ret += k, rst -= k, cost += 1ll * k * c;  
		}
	}
    vis[u] = 0;
	return ret;
}
void mcmf(){
    while(spfa()) flow += dfs(S, inf);   
}


int main(){


    return 0;
}