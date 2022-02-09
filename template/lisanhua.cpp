#include<bits/stdc++.h>
using namespace std;


int n = 9;
int arr[10] = {0, 45, 69, 69, 45, 69, 45, 69, 49, 45};
int rk_arr[10];

inline void ranking(){
	for(int i = 1; i <= n; ++i) rk_arr[i] = arr[i];
	sort(arr + 1, arr + 1 + n);
	auto pd = unique(arr + 1, arr + n + 1);
	int cnt = 0; unordered_map<int, int> hx;
	for(auto p = arr + 1; p < pd; ++p) hx.insert({*p, ++cnt});
	for(int i = 1; i <= n; ++i) rk_arr[i] = hx[rk_arr[i]];
}

int main(){
	
	ranking();

	return 0;
}