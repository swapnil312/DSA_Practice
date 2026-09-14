// Pattern 14
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// A
// AB
// ABC
// ABCD
// ABCDE
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern14(int n) {
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= i; j++){
                // cout<<((char)(j+65))<<" ";
                cout<<(char)('A'+j)<<" ";
            }
            cout<<"\n";
        }
    }
};

int main(){
    Solution obj;
    obj.pattern14(5);
    return 0;
}