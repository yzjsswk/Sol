#include<bits/stdc++.h>
using namespace std;

#define N 100005


int n;
int cost[N];
int in[N], out[N];
int ok[N];
vector<int> g[N];

int main() {
    int T; cin >> T;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            g[i].clear();
            in[i] = 0;
            out[i] = 0;
            ok[i] = 0;
        }
        for(int i = 1; i <= n; i++) {
            cin >> cost[i];
            int k; cin >> k;
            while(k--) {
                int u; cin >> u;
                g[i].push_back(u);
                in[u]++;
                out[i]++;
            }
        }
        int ans = 0;
        int cnt = 0;
        while(cnt < n) {
            int cur = 9999;
            vector<int> work;
            for(int i = 1; i <= n; i++) {
                if(ok[i] == 0 && in[i] == 0) {
                    cur = min(cur, cost[i]);
                    work.push_back(i);
                }
            }
            ans += cur;
            for(int& x : work) {
                cost[x] -= cur;
                if(cost[x] == 0) {
                    ok[x] = 1;
                    cnt++;
                    for(int& v : g[x]) {
                        in[v]--;
                    }
                }
            }
        }
        cout << ans << endl;
    }
    
    
    return 0;
}