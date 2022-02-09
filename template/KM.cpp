//---------KM
#include"prepare.h"
using namespace prepare;

#define MAXN 85

ll g[MAXN][MAXN];//邻接矩阵存图, 无边赋-INF
int n; //n = max(ln, rn) 少的补充成完全图, 添加虚边
int con[MAXN], vis[MAXN], t[MAXN];  // 右边连接的左边点序号, 右边点是否被访问过, 交替增广路
ll kl[MAXN], kr[MAXN], sla[MAXN]; //左右顶标, slack

void build(){
    read(n);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            read(g[i][j]);
}

void bfs_match(int u){
    for(int i = 1; i <= n; ++i) vis[i] = 0, t[i] = 0, sla[i] = INF;
    int i, v = 0, nxtv = 0; ll d; con[v] = u; 
    do{
        i = con[v], d = INF, vis[v] = 1;
        for(int j = 1; j <= n; ++j) if(!vis[j]){
            if(sla[j] > kl[i] + kr[j] - g[i][j])
                sla[j] = kl[i] + kr[j] - g[i][j], t[j] = v;
            if(sla[j] < d) d = sla[j], nxtv = j;
        }
        for(int j = 0; j <= n; ++j)
            if(vis[j]) kl[con[j]] -= d, kr[j] += d; 
            else sla[j] -= d;
        v = nxtv;
    }while(con[v]);
    while(v) con[v] = con[t[v]], v = t[v];
}

ll KM(){
    mst(con, 0); mst(kl, 0); mst(kr, 0);
    for(int i = 1; i <= n; ++i) bfs_match(i);
	ll ans = 0;
	for(int i = 1; i <= n; ++i)
        ans += g[con[i]][i];
	return ans;
}



int main(){
    ready();
    build();
    ll ans = KM();
    cout << ans << endl;
    
    return 0;
}