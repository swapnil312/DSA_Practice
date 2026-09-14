// Reverse a number
// You are given an integer n. Return the integer formed by placing the digits of n in reverse order.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int reverseNumber(int n) {
        int rev = 0;
        while(n > 0){
            rev = (rev*10) + (n%10);
            n /= 10;
        }
        return rev;
    }

    int reverseNumberLeetCode(int n){
        int rev = 0;
        int sign = (n>0)?0:1;
        while(n != 0){
            int digit = n%10;
            if(sign == 0){
                if((rev > INT32_MAX/10)||((rev == INT32_MAX/10)&&(digit > 7))){
                    rev = 0;
                    cout<<"First";
                    break;
                }
            }
            else{
                if((rev < INT32_MIN/10)||((rev == INT32_MIN/10)&&(digit < -8))){
                    cout<<rev<<endl;
                    rev = 0;
                    cout<<"Second ";
                    break;
                }
            }
            rev = (rev * 10) + digit;
            n /= 10;
        }
        return rev;
    }
};

int main() {
    Solution s;
    int n = -1463847412;
    // cout << s.reverseNumber(n) << endl; // Output: 54321
    cout<<s.reverseNumberLeetCode(n)<<endl;
    return 0;
}