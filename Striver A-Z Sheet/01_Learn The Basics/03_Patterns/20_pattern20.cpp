// Pattern 20
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// *        *
// **      **
// ***    ***
// ****  ****
// **********
// ****  ****
// ***    ***
// **      **
// *        *
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern20(int n) {
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= i; j++){
                cout<<"*";
            }
            for(int k = 1; k <= 2*(n-i); k++){
                cout<<" ";
            }
            for(int j = 1; j <= i; j++){
                cout<<"*";
            }
            cout<<"\n";
        }
        for(int i = 4; i >= 1; i--){
            for(int j = 1; j <= i; j++){
                cout<<"*";
            }
            for(int k = 1; k <= 2*(n-i); k++){
                cout<<" ";
            }
            for(int j = 1; j <= i; j++){
                cout<<"*";
            }
            cout<<"\n";
        }

        
    }

    void patter20_2(int n){
        // Initialize spaces between star blocks
        int spaces = 2 * n - 2;

        // Loop for rows
        for (int i = 1; i <= 2 * n - 1; i++) {
            // Calculate stars for first half
            int stars = i;

            // Adjust stars for second half
            if (i > n) stars = 2 * n - i;

            // Print left stars
            for (int j = 1; j <= stars; j++) {
                cout << "*";
            }

            // Print spaces
            for (int j = 1; j <= spaces; j++) {
                cout << " ";
            }

            // Print right stars
            for (int j = 1; j <= stars; j++) {
                cout << "*";
            }

            // Move to next line
            cout << endl;

            // Adjust spaces for next row
            if (i < n) spaces -= 2;
            else spaces += 2;
        }
    }
};
int main(){
    Solution obj;
    obj.pattern20(6);
    return 0;
}