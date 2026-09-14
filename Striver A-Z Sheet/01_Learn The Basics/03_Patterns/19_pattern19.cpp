// Pattern 19
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// **********
// ****  ****
// ***    ***
// **      **
// *        *
// *        *
// **      **
// ***    ***
// ****  ****
// **********
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern19(int n) {
        for(int i = n; i >= 1; i--){
            for(int j = 1; j <= i; j++){
                cout<<"*";
            }
            for(int j = 0; j < 2*(n-i); j++){
                cout<<" ";
            }
            for(int j = 1; j <= i; j++){
                cout<<"*";
            }
            cout<<"\n";
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= i; j++){
                cout<<"*";
            }
            for(int j = 0; j < 2*(n-i); j++){
                cout<<" ";
            }
            for(int j = 1; j <= i; j++){
                cout<<"*";
            }
            cout<<"\n";
        }
    }
};

int main(){
    Solution obj;
    obj.pattern19(6);
    return 0;
}
