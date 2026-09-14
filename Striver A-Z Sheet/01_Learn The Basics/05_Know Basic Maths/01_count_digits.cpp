// Count all Digits of a Number
// You are given an integer n. You need to return the number of digits in the number.
// The number will have no leading zeroes, except when the number is 0 itself.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countDigit(int n) {
        if(n == 0) return 1;
        int x = 0;
        while(n>0){
            x++;
            n /= 10;
        }
        return x;
    }

    int countDigit2(int n) {
    // Initialize a variable 'cnt' to
    // store the count of digits.
        if(n == 0) return 1; // Handle the case when n is 0
        int cnt = (int)(log10(n)+1);

    // The expression (int)(log10(n)+1)
    // calculates the number of digits in 'n'
    // and casts it to an integer.
    
    // Adding 1 to the result accounts
    // for the case when 'n' is a power of 10,
    // ensuring that the count is correct.
   
    // Finally, the result is cast
    // to an integer to ensure it is rounded
    // down to the nearest whole number.
    
    // Return the count of digits in 'n'.
        return cnt;
    }
};

int main() {
    Solution s;
    int n = 0;
    cout << s.countDigit2(n) << endl;
    return 0;
}


