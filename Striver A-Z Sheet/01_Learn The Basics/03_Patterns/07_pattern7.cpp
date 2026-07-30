// Pattern 7
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
//     *
//    ***
//   *****
//  *******
// *********
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern7(int n) {
        int x = 1;
        for(int i = n; i >= 1; i--){
            for(int j = 1; j <= i-1; j++){
                cout<<" ";
            }
            for(int k = 1; k <= x; k++){
                cout<<"*";
            }
            x += 2;
            cout<<"\n";
        }
    }

    void pattern7_2(int n) {
        for(int i =0; i < n; i++){
            //For spaces
            for(int j = 0; j < n-i-1; j++){
                cout<<" ";
            }
            //For stars
            for(int k = 0; k < ((2*i)+1); k++){
                cout<<"*";
            }
            //For spaces
            for(int l = 0; l < n-i-1; l++){
                cout<<" ";
            }
            cout<<"\n";
        }
    }
};
int main() {
    Solution obj;
    int n = 6;
    obj.pattern7_2(n);
    return 0;
}