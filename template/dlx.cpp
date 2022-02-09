#include <bits/stdc++.h>
using namespace std;

#define N 750
#define M 350
#define V N * M

int rect[N][M];
int num[10][10];
int score[9][9] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 9, 10, 9, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6}};
int ansp;

inline void p2cg(int& x, int& y, int& k, int& c, int& g0, int& g1, int& g2, int& g3){
    c = ((x - 1) * 9 + y) + (k - 1) * 81,
    g0 = (x - 1) * 9 + y,
    g1 = 81 + (x - 1) * 9 + k,
    g2 = 81 + 81 + (y - 1) * 9 + k,
    g3 = 81 + 81 + 81 + ((x - 1) / 3 * 3 + (y - 1) / 3) * 9 + k;
}

inline void c2p(int& x, int& y, int& k, int& c){
    k = c / 81 + (c % 81 == 0 ? 0 : 1),
    x = y = c - (k - 1) * 81, 
    x = x / 9 + (x % 9 == 0 ? 0 : 1),
    y -= (x - 1) * 9;
}

int n = 729, m = 324, vid, deep;                                   
int l[V], r[V], u[V], d[V], row[V], col[V], s[M];
int ans = -1, choice[N];

void init(){
    for (int i = 0; i <= m; ++i)
        r[i] = i + 1, l[i] = i - 1, u[i] = d[i] = i;
    r[m] = 0, l[0] = m, vid = m + 1;
}                
inline void link(int x, int y, int& rh, int& rt){
    row[vid] = x, col[vid] = y, ++s[y];
    u[vid] = y, d[vid] = d[y], u[d[y]] = vid, d[y] = vid;
    r[rh] = l[rt] = vid, r[vid] = rt, l[vid] = rh;
    rt = vid++;
}
void remove(int y){
    l[r[y]] = l[y], r[l[y]] = r[y];
    for (int i = d[y]; i != y; i = d[i])
        for (int j = r[i]; j != i; j = r[j])
            u[d[j]] = u[j], d[u[j]] = d[j], --s[col[j]];    
}
void resume(int y){
    for (int i = u[y]; i != y; i = u[i])
        for (int j = l[i]; j != i; j = l[j])
            u[d[j]] = j, d[u[j]] = j, ++s[col[j]];
    l[r[y]] = r[l[y]] = y;
}
void dance(){
    if (!r[0]){
        int x, y, k, cans = ansp;
        for(int i = 1; i <= deep; ++i){
            c2p(x, y, k, choice[i]);
            cans += k * score[x - 1][y - 1];
        }
        ans = max(ans, cans);
    }
    int mc = r[0];
    for (int i = r[0]; i; i = r[i]) if(s[i] < s[mc]) mc = i;
    remove(mc);
    for (int i = d[mc]; i != mc; i = d[i]){
        choice[++deep] = row[i];
        for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
        dance();
        for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
        --deep;
    }
    resume(mc);
}

int main(){
    init();
    for(int i = 1; i <= 9; ++i)
        for(int j = 1; j <= 9; ++j) cin >> num[i][j];

    int g0, g1, g2, g3, c, rh, rt;
    for(int i = 1; i <= 9; ++i)
        for(int j = 1; j <= 9; ++j){
            if(num[i][j]) continue;
            for(int k = 1; k <= 9; ++k){
                p2cg(i, j, k, c, g0, g1, g2, g3);
                rect[c][g0] = rect[c][g1] = rect[c][g2] = rect[c][g3] = 1;
            }
    }
    for(int i = 1; i <= n; ++i){
        rh = rt = vid;
        for(int j = 1; j <= m; ++j)
            if(rect[i][j]) link(i, j, rh, rt);
    }
    for(int i = 1; i <= 9; ++i)
        for(int j = 1; j <= 9; ++j){
            if(!num[i][j]) continue;
            ansp += score[i - 1][j - 1] * num[i][j];
            p2cg(i, j, num[i][j], c, g0, g1, g2, g3);
            remove(g0), remove(g1), remove(g2), remove(g3);
        }
    dance();
    cout << ans << endl;
    return 0;
}