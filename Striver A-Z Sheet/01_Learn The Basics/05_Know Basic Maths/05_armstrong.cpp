// Check if the Number is Armstrong
// You are given an integer n. You need to check whether it is an armstrong number or not. Return true if it is an armstrong number, otherwise return false.
// An armstrong number is a number which is equal to the sum of the digits of the number, raised to the power of the number of digits.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isArmstrong(int n) {
        int sum = 0;
        int x = n;
        if(n == 0) return true;
        // Other way to find no of digits
        // int k = to_string(num).length(); // Get number of digits
        int noOfDigits = 0;
        while(n>0){
            noOfDigits++;
            n/=10;
        }
        n = x;
        while(x>0){
            int digit = x%10;
            sum += int(pow(digit,noOfDigits));
            x /= 10;
        }

        if(n == sum) return true;
        return false;
    }
};

int main(){
    Solution obj;
    cout<<obj.isArmstrong(153);
    return 0;
}