// Factorial of a given number
// You are given an integer n. Return the value of n! or n factorial.
// Factorial of a number is the product of all positive integers less than or equal to that number.
# include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int factorial(int n) {
        if((n == 1)||(n == 0)) return 1;
        return n*factorial(n-1);
    }
};

int main(){
    Solution obj;
    cout<<obj.factorial(5);
    return 0;
}