// Pattern 22
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// 5 5 5 5 5 5 5 5 5 
// 5 4 4 4 4 4 4 4 5 
// 5 4 3 3 3 3 3 4 5 
// 5 4 3 2 2 2 3 4 5 
// 5 4 3 2 1 2 3 4 5 
// 5 4 3 2 2 2 3 4 5 
// 5 4 3 3 3 3 3 4 5 
// 5 4 4 4 4 4 4 4 5 
// 5 5 5 5 5 5 5 5 5
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern22(int n) {
        for(int i = 0; i < (2*n)-1; i++){
            for(int j = 0; j < (2*n)-1; j++){
                int top = i;
                int bottom = (2*n)-1-1-i;
                int left = j;
                int right = (2*n)-1-1-j;
                int minimum = min(min(top,bottom),min(left,right));
                cout<<n-minimum<<" ";
            }
            cout<<"\n";
        }
    }
};

int main(){
    Solution obj;
    obj.pattern22(5);
    return 0;
}