// Pattern 8
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// *********
//  *******
//   *****
//    ***
//     *
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern8(int n) {
        for(int i = 0;  i < n; i++){
            for(int j = 0;  j < i; j++){
                cout<<" ";
            }
            for(int k = 0; k <= 2*(n-1-i); k++){
                cout<<"*";
            }
            for(int l = 0; l < i; l++){
                cout<<" ";
            }
            cout<<"\n";
        }
    }
};

int main(){

    Solution obj;
    int n = 6;
    obj.pattern8(n);
    return 0;
}