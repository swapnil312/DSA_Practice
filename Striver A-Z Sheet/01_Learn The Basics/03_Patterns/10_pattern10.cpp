// Pattern 10
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// *
// **
// ***
// ****
// *****
// ****
// ***
// **
// *
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern10(int n) {
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= i; j++){
                cout<<"*";
            }
            cout<<"\n";
        }
        for(int i = n-1; i >= 1; i--){
            for(int j = 1;  j<= i; j++){
                cout<<"*";
            }
            cout<<"\n";

        }
    }
};

int main(){
    Solution obj;
    int n = 6;
    obj.pattern10(n);
    return 0;
}