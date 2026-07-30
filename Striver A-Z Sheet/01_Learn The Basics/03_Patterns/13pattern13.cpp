// Pattern 13
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// 1 
// 2 3 
// 4 5 6 
// 7 8 9 10 
// 11 12 13 14 15
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern13(int n) {
        int x = 1;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= i; j++){
                cout<<x<<" ";
                x++;
            }
            cout<<"\n";
        }
    }
};

int main(){
    Solution obj;
    int a = 5;
    obj.pattern13(a);
    return 0;
}