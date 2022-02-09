#include<bits/stdc++.h>
using namespace std;

inline int rd(){
    int x = 0, f = 0;
    register char c = getchar();
    while(c < '0' || c > '9') f |= c == '-', c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar(); 
    return f ? -x : x;
}

void wt(int x){
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) wt(x / 10);
    putchar(x % 10 + '0');
}


#define N 1000005
int arr[N];

int n, k;
deque<pair<int, int>> q1, q2;

int main(){
    n = rd(), k = rd();
    for(int i = 1; i <= n; ++i) arr[i] = rd();
    for(int i = 1; i < k; ++i){
        while(q1.size() && q1.back().first >= arr[i]) q1.pop_back();
        if(q1.size() && i - q1.front().second >= k) q1.pop_front();
        q1.push_back({arr[i], i});
        while(q2.size() && q2.back().first <= arr[i]) q2.pop_back();
        if(q2.size() && i - q2.front().second >= k) q2.pop_front();
        q2.push_back({arr[i], i});
    }
    vector<int> ans;
    for(int i = k; i <= n; ++i){
        while(q1.size() && q1.back().first >= arr[i]) q1.pop_back();
        if(q1.size() && i - q1.front().second >= k) q1.pop_front();
        q1.push_back({arr[i], i});
        while(q2.size() && q2.back().first <= arr[i]) q2.pop_back();
        if(q2.size() && i - q2.front().second >= k) q2.pop_front();
        q2.push_back({arr[i], i});
        wt(q1.front().first), putchar(' ');
        ans.push_back(q2.front().first);
    }
    putchar('\n');
    for(int& x: ans) wt(x), putchar(' ');

    return 0;
}