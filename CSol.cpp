#include<bits/stdc++.h>
using namespace std;



int main(){
    list<int> l = {1, 2, 3, 5};
    auto it = l.begin();
    it++;
    it++;
    l.emplace_back(*it);
    for(auto it = l.begin(); it != l.end(); it++){
        cout << *it << endl;
    }

    return 0;
}