// Print N to 1 using Recursion
// Given an integer n, write a function to print all numbers from n to 1 (inclusive) using recursion.
// You must not use any loops such as for, while, or do-while.
// The function should print each number on a separate line, in decreasing order from n to 1

# include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void printNumbers(int n) {
        cout<<n<<endl;
        if(n == 1) return;
        printNumbers(n-1);
    }
};

int main(){
    Solution obj;
    obj.printNumbers(5);
    return 0;

}