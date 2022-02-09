//-----------max_match
#include"prepare.h"
using namespace prepare;

#define MAXN 3000
vi g[MAXN];
int vis[MAXN], con[MAXN];
int p; //左部点数

void build(){
    
}

bool dfs_match(int v){
    for(auto& x: g[v]){
        if(vis[x]) continue;
        vis[x] = 1;
        if(con[x] == -1 || dfs_match(con[x])){
            con[x] = v;
            return true;
        }
    }
    return false;
}

int max_match(){
    int ans = 0; mst(con, -1);
    for(int i = 1; i <= p; ++i){
        mst(vis, 0);
        ans += dfs_match(i);
    }
    return ans;
}

int main(){
    ready();
    build();
    cout << max_match() << endl;

    return 0;
}