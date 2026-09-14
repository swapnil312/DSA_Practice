// GCD of Two Numbers
// You are given two integers n1 and n2. You need find the Greatest Common Divisor (GCD) of the two given numbers. Return the GCD of the two numbers.
// The Greatest Common Divisor (GCD) of two integers is the largest positive integer that divides both of the integers.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int GCD(int n1,int n2) {
        if(n1 == 0) return n2;
        if(n2 == 0) return n1;
        int x = (n1 >= n2) ? n2:n1;
        for(int i = x; i >= 1; i--){
            if(((n1%i)==0)&&((n2%i)==0)){
                return i;
            }
        }
        return 1;
    }

    int GCD_Euclidean_recursive(int n1, int n2){
        if(n1 == 0) return n2;
        if(n2 == 0) return n1;
        if(n1 >= n2) return GCD_Euclidean_recursive(n1%n2, n2);
        else return GCD_Euclidean_recursive(n2%n1, n1);
    }

    int findGcd_Euclidean(int a, int b) {
    // Continue loop as long as both
    // a and b are greater than 0
    while(a > 0 && b > 0) {
        // If a is greater than b,
        // subtract b from a and update a
        if(a > b) {
             // Update a to the remainder
             // of a divided by b
            a = a % b;
        }
        // If b is greater than or equal
        // to a, subtract a from b and update b
        else {
            // Update b to the remainder
            // of b divided by a
            b = b % a; 
        }
    }
    // Check if a becomes 0,
    // if so, return b as the GCD
    if(a == 0) {
        return b;
    }
    // If a is not 0,
    // return a as the GCD
    return a;
    }


};

int main(){
    Solution obj;
    cout<<obj.GCD(0,60)<<endl;
    cout<<obj.GCD_Euclidean_recursive(0,60)<<endl;
    cout<<obj.findGcd_Euclidean(0,60);
    return 0;
}