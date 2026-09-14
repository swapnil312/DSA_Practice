// Pattern 16
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// A
// BB
// CCC
// DDDD
// EEEEE
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern16(int n) {
        for(char i = 'A'; i <= ('A'+n-1); i++){
            for(int j = 0; j <= (int)i - 65; j++){
                cout<<i<<" ";
            }
            cout<<"\n";
        }
    }
};

int main(){
    Solution obj;
    obj.pattern16(6);
    return 0;
}