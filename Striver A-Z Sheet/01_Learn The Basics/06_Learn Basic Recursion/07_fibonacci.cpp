// Fibonacci Number
// The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,
// F(0) = 0, F(1) = 1
// F(n) = F(n - 1) + F(n - 2), for n > 1.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int fib(int n) {
        if(n==0) return 0;
        if(n==1) return 1;
        return fib(n-1) + fib(n-2);
    }
    int fib_leetcode(int n) {
        if(n <= 1) return n;
        int a = 0;
        int b = 1;
        int c;
        for(int i = 2; i <= n; i++){
            c = a+b;
            a = b;
            b = c;
        }
        return c;
    }
};

int main(){
    Solution obj;
    cout << obj.fib_leetcode(3);
    return 0;
}