#include<bits/stdc++.h>
using namespace std;

class BigNum {
    vector<int> nums; // from 0 to size-1 
    int sign; // 1: positive, -1: negative
    static const int M = 1000000000; // save 8 decimals each int
public:
    BigNum(const string& s, int sg = 1) {
        nums.clear();
        sign = sg == 1 ? 1 : -1;
        int sum = 0, t = 1, cnt = 9;
        for(int i = s.size()-1; i >= 0; i--) {
            if(s[i] < '0' || s[i] > '9') {
                continue;
            }
            sum += (s[i] - '0') * t, t *= 10, --cnt;
            if(cnt == 0) { 
                nums.push_back(sum);    
                sum = 0, t = 1, cnt = 9;
            }
        }
        nums.push_back(sum);
    }
    BigNum(const BigNum& another) {
        nums = another.nums;
        sign = another.sign;
    }
    void print() {
        int p = nums.size() - 1;
        if(p < 0) {
            return;
        }
        printf("%d", nums[p--]);
        while(p >= 0) {
            printf("%09d", nums[p--]);
        }
    }    
};





int main() {



    return 0;
}