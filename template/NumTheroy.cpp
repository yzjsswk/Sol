//-----------------NumTheroy
#include"prepare.h"
using namespace prepare;


//带模加
inline ll addm(ll a, ll b, ll p){
    a = ((a - p) + b) % p;
    return a < 0 ? a + p : a;
}

//带模乘
inline ll mulm(ll a, ll b, ll p){
    ll l = a * (b >> 25) % p * (1ll << 25) % p,
        r = a * (b & ((1ll << 25) - 1)) % p;
    l = ((l - p) + r) % p;
    return l < 0 ? l + p : l;
}

//带模幂
ll powm(ll a, ll b, ll p){
    ll ret = 1;
    while(b > 0){
        if(b & 1) ret = mulm(ret, a, p);
        a = mulm(a, a, p);
        b >>= 1;
    }
    return ret;
}



//最大公约数(欧几里德)
ll gcd(ll a, ll b){
    if(b == 0) return a;
    return gcd(b, a % b);
}

//最小公倍数
ll lcm(ll a, ll b){
    return a * b / gcd(a, b);
}

//拓展欧几里德(注意结果可能为负)
ll exgcd(ll a, ll b, ll& x, ll& y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

//逆元
ll inv(ll a, ll p){
    ll x, y;
    exgcd(a, p, x, y);
    x %= p;
    return x < 0 ? x + p : x;
}

//中国剩余定理(fc.first = rest, fc.second = mod)
ll crt(vector<pair<ll, ll>> fc){
    ll ans = 0, umod = 1;
    for(auto& x: fc) umod *= x.second;
    for(auto& x: fc){
        ll crst = x.first, cmod = x.second, cu = umod / cmod;
        ans = (ans + crst * inv(cu, cmod) * cu) % umod;
    }
    return ans;
}

//拓展中国剩余定理
ll excrt(vector<pair<ll, ll>> fc){
    ll rst = 0, mod = 1;
    for(auto& ehx: fc){
        ll r1 = rst, m1 = mod, r2 = ehx.first, m2 = ehx.second;
        ll x, y, g, k;
        g = exgcd(m1, m2, x, y);
        x %= m2, x = x < 0 ? x + m2 : x;
        k = (r2 - r1) / g, k %= m2, k = k < 0 ? k + m2 : k;
        x = mulm(x, k, m2), mod *= m2 / g;
        rst = mulm(x, m1, mod), rst = ((r1 - mod) + rst) % mod;
        rst = rst < 0 ? rst + mod : rst;
    }
    return rst;
}

//BSGS
ll BSGS(ll num, ll rst, ll mod){
    if(rst == 1 || mod == 1) return 0;
    unordered_map<ll, ll> mp;
    ll m = sqrt(mod) + 1, cur = rst;
    mp[rst] = 0;
    for(ll i = 1; i <= m; ++i)
        cur = mulm(cur, num, mod), mp[cur] = i;
    ll u = powm(num, m, mod);
    cur = 1;
    for(ll i = 1; i <= m; ++i){
        cur = mulm(cur, u, mod);
        if(mp.find(cur) != mp.end()) return m * i - mp[cur];
    }
    return -1;
}

//拓展BSGS
ll exBSGS(ll num, ll rst, ll mod){
    if(rst == 1 || mod == 1) return 0;
    ll k = 0, u = 1, g = 1;
    while((g = gcd(num, mod)) > 1){
        if(rst % g) return -1;
        ++k, rst /= g, mod /= g, u = mulm(u, (num / g), mod);
        if(u == rst) return k;
    }
    rst = mulm(rst, inv(u, mod), mod);
    ll ans = BSGS(num, rst, mod);
    return ans == -1 ? -1 : ans + k;
}

int main(){
    





    return 0;
}
