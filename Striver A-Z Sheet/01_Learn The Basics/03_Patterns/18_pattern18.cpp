// Pattern 18
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// E 
// D E 
// C D E 
// B C D E 
// A B C D E
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern18(int n) {
        for(int i = 1; i <= n; i++){
            char end = 'A' + n - 1;
            for(char ch = 'A' + n - i; ch <= end; ch++){
                cout<<ch<<" ";
            }
            cout<<"\n";
        }
    }
};

int main(){
    Solution obj;
    obj.pattern18(6);
    return 0;
}