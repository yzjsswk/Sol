#define LOCAL
#define TEST 1
//#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
namespace prepare{
    #define mst(it, n) memset(it, n, sizeof it);
    #define fill(it, l, r, v) for(int i = l; i <= r; ++i) it[i] = v;
    #define see(it) for(auto& x: it) cout << x << " "; cout << endl;
    #define inf 2139062143
    #define INF 9187201950435737471ll
    #define rg register
    typedef long long ll;
    typedef pair<int, int> pii;
    typedef vector<int> vi;
    typedef vector<vector<int> > vvi;
	int test = 1;
    inline void solve();
    inline void ready(){
        //ios::sync_with_stdio(false);
        //cin.tie(0); cout.tie(0);
		#ifdef LOCAL
		test = TEST;
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
        #endif
    }
    template<class T>
    inline void read(T& x){
        x = 0; int f = 0; rg char c = 0;
        while(!isdigit(c)) f |= c == '-', c = getchar();
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        x = f ? -x : x;
    }
    template<class T1, class... Tn>
    inline void read(T1& x1, Tn&... xn){
        read(x1), read(xn...);
    }
    inline void reads(string& s){
        s = ""; rg char c = 0;
        while(!isdigit(c)) c = getchar();
        while(isdigit(c)) s += c, c = getchar();
    }
    template<class T>
    inline void write(rg T x){
        if(x < 0) putchar('-'), x = -x;
        if(x > 9) write(x / 10);
        putchar(x % 10 + 48);
    }
}
using namespace prepare;
int main(){
	ready();
	while(test--) solve();
	return 0;
}
//----------------------------------

void prepare::solve(){
    
    

}

