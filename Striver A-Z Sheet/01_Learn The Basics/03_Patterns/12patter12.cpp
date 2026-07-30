// Pattern 12
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// 1        1
// 12      21
// 123    321
// 1234  4321
// 1234554321
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern12(int n) {
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= i; j++){
                cout<<j;
            }
            for(int k = 1; k <= 2*(n-i); k++){
                cout<<" ";
            }
            for(int l = i; l >= 1; l--){
                cout<<l;
            }
            cout<<"\n";
        }
    }
};

int main(){
    Solution obj;
    int n = 5;
    obj.pattern12(n);
    return 0;
}