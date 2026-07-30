// Pattern 5
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// *****
// ****
// ***
// **
// *

# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern5(int n) {
        for(int i = n; i >= 1; i--){
            for(int j = 1; j <= i; j++){
                cout<<"*";
            }
            cout<<"\n";
        }
    }
};
int main() {
    Solution obj;
    int n = 5;
    obj.pattern5(n);
    return 0;
}