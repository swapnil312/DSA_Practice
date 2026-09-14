// Palindrome Number
// You are given an integer n. You need to check whether the number is a palindrome number or not. Return true if it's a palindrome number, otherwise return false.
// A palindrome number is a number which reads the same both left to right and right to left.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isPalindrome(int n) {
        int rev = 0;
        int x = n;
        while(n > 0){
            rev = (rev*10) + (n%10);
            n /= 10;
        }
        if(x == rev) return true;
        else return false;

    }
    bool isPalindrome_leetcode(int n) {
        int rev = 0;
        if(n < 0) return false;
        int x = n;
        while(n != 0){
            int digit = n%10;
            if((rev > INT32_MAX/10)||((rev == INT32_MAX/10)&&(digit > 7))){
                rev = 0;
                break;
            }
            rev = (rev * 10) + digit;
            n /= 10;
        }
        if(x == rev) return true;
        else return false;
    }
};

int main() {
    Solution s;
    int n = 121;
    cout << (s.isPalindrome(n) ? "true" : "false") << endl; // Output: true
    return 0;
}