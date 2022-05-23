#include <bits/stdc++.h>
using namespace std;



 struct TreeNode {
      int val;
     TreeNode *left;
      TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    
    list<int> L;
    map<int, list<int>::iterator> pos;
    map<int, int> ok;
    map<int, list<int>::iterator> ll;
    map<int, list<int>::iterator> rr;
    
    void dfs(TreeNode* nd) {
        if(nd == nullptr) {
            return;
        }
        L.push_back(nd->val);
        dfs(nd->left);
        dfs(nd->right);
    }
    
    int getNumber(TreeNode* root, vector<vector<int>>& ops) {
        dfs(root);
        //sort(L.begin(), L.end());
        L.sort();
		for(auto it = L.begin(); it != L.end(); it++) {
            pos[*it] = it;
            ok[*it] = 1;
            ll[*it] = it;
            rr[*it] = it;
        }
        int ans = 0;
        int sz = ops.size();
        for(int i = sz-1; i >= 0; i--) {
            int l = ops[i][1], r = ops[i][2], col = ops[i][0];
            list<int>::iterator real_l = ok[l] ? pos[l] : ll[l], real_r = ok[r] ? pos[r] : rr[r];
            list<int>::iterator bound_l = real_l, bound_r = real_r;
            //bound_l--;
            //bound_r++;
            for(list<int>::iterator it = real_l; it != bound_r; it++) {
                ans += col;
                ok[*it] = 0;
                ll[*it] = bound_l;
                rr[*it] = bound_r;
                L.erase(it);
            }
        }
        return ans;
    } 
};


int main()
{
	
	return 0;
}
