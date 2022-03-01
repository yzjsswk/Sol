#include<bits/stdc++.h>
using namespace std;

void rankify(vector<int>& nums){
	vector<int> tmp(nums);
	sort(tmp.begin(), tmp.end());
	vector<int>::iterator p = unique(tmp.begin(), tmp.end());
	unordered_map<int, int> mp;
	int rank = 1;
	for(vector<int>::iterator it = tmp.begin(); it < p; it++){
		mp[*it] = rank;
		rank++;
	}
	for(int& x : nums){
		x = mp[x];
	}
}


int main(){
	vector<int> arr = {0, 45, 69, 69, 45, 69, 45, 69, 49, 45};
	rankify(arr);
	for(int x : arr) cout << x << " "; cout << endl; 
	

	return 0;
}