// Print 1 to N using Recursion
// Given an integer n, write a function to print all numbers from 1 to n (inclusive) using recursion.
// You must not use any loops such as for, while, or do-while.
// The function should print each number on a separate line, in increasing order from 1 to n.
# include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    void printNumbers(int n) {
        if(n == 1) {
            cout<<n<<endl;
            return;
        }
        printNumbers(n-1);
        cout<<n<<endl;
    }
};

int main(){
    Solution obj;
    obj.printNumbers(6);
}