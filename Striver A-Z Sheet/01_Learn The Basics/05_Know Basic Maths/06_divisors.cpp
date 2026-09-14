// Divisors of a Number
// You are given an integer n. You need to find all the divisors of n. Return all the divisors of n as an array or list in a sorted order.
// A number which completely divides another number is called it's divisor.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> divisors_brute(int n) {
        vector<int> v;
        for(int i = 1; i <= n; i++){
            if((n%i) == 0) v.push_back(i);
        }
        return v;
    }
    vector<int> divisors_optimal(int n){
        vector<int> v;
        for(int i = 1; i*i <= n; i++){
            if((n%i)==0) v.push_back(i);
            if(i != (n/i)) v.push_back(n/i);
        }
        sort(v.begin(), v.end());
        return v;
    }
};

int main(){
    Solution obj;
    vector<int> v = obj.divisors_optimal(10);
    for(auto x: v){
        cout<<x<<endl;
    }
    return 0;
}