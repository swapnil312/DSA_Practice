// Pattern 6
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// 12345
// 1234
// 123
// 12
// 1
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern6(int n) {
        for(int i = n; i >= 1; i--){
            for(int j = 1;  j <= i; j++){
                cout<<j;
            }
            cout<<"\n";
        }
    }
};

