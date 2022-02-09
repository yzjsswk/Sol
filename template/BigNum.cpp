//--------------------BigNum
//just for positive number, sub and div(/ Bignum) need a >= b
//make sure the result array be clear before function and pay attention to what rds reads
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

const int M = 1000000000;

inline void setlen(int* a, int p){
    a[0] = p;
    while(!a[a[0]] && a[0] > 1) --a[0];
}

inline void copyto(int* a, int* b){
    memset(a, 0, sizeof(int) * (a[0] + 1));
    memcpy(a, b, sizeof(int) * (b[0] + 1));
}

void ini(int* a, string& str){
    int p = str.size();
    if(p == 0) return;
    a[0] = (p + 8) / 9;
    int sum = 0, t = 1, cnt = 9, nxt = 0;
    while(--p, p >= 0){
        sum += (str[p] - '0') * t, t *= 10, --cnt;
        if(!cnt) a[++nxt] = sum, sum = 0, t = 1, cnt = 9;
    }
    a[++nxt] = sum;
}

void pnt(int* a){
    int p = a[0];
    printf("%d", a[p]);
    while(--p, p > 0) printf("%09d", a[p]);
}

int cmp(int* a, int* b){
    if(a[0] > b[0]) return 1;
    if(a[0] < b[0]) return -1;
    int p = a[0] + 1;
    while(--p, p > 0){
        if(a[p] > b[p]) return 1;
        if(a[p] < b[p]) return -1;
    }
    return 0;
}

void add(int* a, int* b){
    int ml = max(a[0], b[0]);
    for(int i = 1; i <= ml; ++i){
        a[i] += b[i];
        if(a[i] >= M) a[i] -= M, ++a[i + 1];
    }
    a[0] = a[ml + 1] ? ml + 1 : ml;
}

void sub(int* a, int* b){
    for(int i = 1; i <= a[0]; ++i){
        a[i] -= b[i];
        if(a[i] < 0) a[i] += M, --a[i + 1];
    }
    setlen(a, a[0]);
}

void mul(int* a, int* b, int* res){
    for(int i = 1; i <= a[0]; ++i)
        for(int j = 1; j <= b[0]; ++j){
            ll m = 1ll * a[i] * b[j] + res[i + j - 1];
            res[i + j] += m / M, res[i + j - 1] = m % M;
        }
    setlen(res, a[0] + b[0]);
}

void mul(int* a, int b){
    ll cf = 0;
    for(int i = 1; i <= a[0]; ++i){
        cf += 1ll * a[i] * b;
        a[i] = cf % M, cf /= M;
    }
    if(cf) a[++a[0]] = cf; 
}

int mod(int* a, int b){
    int ret = 0;
    for(int i = a[0]; i > 0; --i)
        ret = (1ll * ret * M + a[i]) % b;
    return ret;
}

void div(int* a, int b, int* div){
    int res = 0;
    for(int i = a[0]; i > 0; --i){
        ll cur = 1ll * M * res + a[i];
        div[i] = cur / b, res = cur - div[i] * b;
    }
    setlen(div, a[0]);
}

void div(int* a, int* b, int* div, int* rst){
    int mt[a[0] + 5], nxt = a[0] - b[0] + 1; 
    mst(mt, 0);  rst[0] = b[0] - 1;
    for(int i = 1; i < b[0]; ++i) rst[i] = a[i + nxt];
    while(nxt){
        for(int i = rst[0] + 1; i > 1; --i) rst[i] = rst[i - 1];
        rst[1] = a[nxt]; setlen(rst, rst[0] + 1);
        int l = 0, r = M;
        while(l <= r){
            int mid = (l + r) >> 1;
            copyto(mt, b), mul(mt, mid);
            int chk = cmp(rst, mt);
            if(chk > 0) l = mid + 1;
            if(chk < 0) r = mid - 1;
            if(chk == 0){r = mid; break;}
        }
        copyto(mt, b), mul(mt, r), sub(rst, mt);
        div[nxt--] = r;
    }
    setlen(div, a[0]);
}

#define MAXL 2500

int a[MAXL], b[MAXL], d[MAXL], r[MAXL];
string s1, s2;

void prepare::solve(){
    for(int i = 1; i <= 10; ++i){
        cin >> s1 >> s2;
        ini(a, s1), ini(b, s2);
        div(a, b, d, r);
        pnt(r);
        putchar('\n');
    }
    

}


