// Pattern 11
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// 1 
// 0 1 
// 1 0 1 
// 0 1 0 1 
// 1 0 1 0 1
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern11(int n) {
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= i; j++){
                if(((i+j)%2) == 0) cout<<"1";
                else cout<<"0";
            }
            cout<<"\n";
        }
    }
    void pattern11_2(int n){
         // First row starts by printing a single 1.
    int start = 1;
    
    // Outer loop for the number of rows
    for (int i = 0; i < n; i++) {
        // If the row index is even, print 1 first in that row
        if (i % 2 == 0) start = 1;
        
        // If the row index is odd, print 0 first in that row
        else start = 0;
        
        // Inner loop to print alternating 1's and 0's in each row
        for (int j = 0; j <= i; j++) {
            cout << start;
            // Alternate between 1 and 0
            start = 1 - start;
        }

        // Move to the next line after each row is printed
        cout << endl;
    }
    }
};

int main(){
    Solution obj;
    int n = 6;
    obj.pattern11_2(n);
    return 0;
}