// Pattern 17
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
//     A
//    ABA
//   ABCBA
//  ABCDCBA
// ABCDEDCBA
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern17(int n) {
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n-1-i; j++){
                cout<<" ";
            }
            for(char ch = 'A'; ch <= 'A'+i; ch++){
                cout<<ch;
            }
            for(char ch = 'A'+i-1; ch >= 'A'; ch--){
                cout<<ch;
            }
            for(int j = 0; j < n-1-i; j++){
                cout<<" ";
            }
            cout<<"\n";
        }
    }

    void pattern17_2(int n){
        // Loop for each row
    for (int i = 0; i < n; i++) {

        // Print leading spaces
        for (int j = 0; j < n - i - 1; j++) {
            cout << " ";
        }

        // Initialize character to start from 'A'
        char ch = 'A';

        // Calculate midpoint of the row
        int breakpoint = (2 * i + 1) / 2;

        // Print the characters in the row
        for (int j = 1; j <= 2 * i + 1; j++) {
            cout << ch;

            // Increment character till the midpoint, then decrement
            if (j <= breakpoint) ch++;
            else ch--;
        }

        // Print trailing spaces
        for (int j = 0; j < n - i - 1; j++) {
            cout << " ";
        }

        // Newline after each row
        cout << endl;
    }
    }
};

int main(){
    Solution obj;
    obj.pattern17(6);
    return 0;
}