#include<bits/stdc++.h>
using namespace std;

#define N 100050

//并查集
int fa[N];
int root(int x){
	if(fa[x] == x) return x;
	return fa[x] = root(fa[x]);
}
//并: fa[root(x)] = root(y)
//查: root(x) == root(y) ?


//ST表
int st[21][N], a[N];
//预处理
inline void st_init(){
    for(int i = 1; i <= n; ++i) st[0][i] = a[i];
    for(int i = 1; i < 21; ++i)
        for(int j = 1; j + (1 << i) - 1 <= n; ++j)
    	    st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
}
//查询
inline int query(int l, int r){
    int k = log2(r - l + 1);
    return max(st[k][l], st[k][r - (1 << k) + 1]);
}


//树状数组
int n;
int a[N];
int tree[N], tree1[N], tree2[N];
void update(int i, int x){
    //前缀和
    for( ; i <= n; i += i & -i) tree[i] += x;
    //前缀最值
    for( ; i <= n; i += i & -i) tree[i] = max(tree[i], x);
    //区间修改, 区间查询
    for(int k = i; i <= n; i += i & -i) 
        tree1[i] += x, tree2[i] += k * x;
}
int query(int i){
    int ret = 0;
    //前缀和
    for( ; i > 0; i -= i & -i) ret += tree[i];
    //前缀最值
    for( ; i > 0; i -= i & -i) ret = max(ret, tree[i]);
    //区间修改, 区间查询
    for(int k = i + 1; i > 0; i -= i & -i) 
        ret += tree1[i] * k - tree2[i];
    return ret;
}

int main(){


    return 0;
}

