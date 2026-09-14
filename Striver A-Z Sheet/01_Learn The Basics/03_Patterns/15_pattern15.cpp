// Pattern 15
// Given an integer n. You need to recreate the pattern given below for any value of N. Let's say for N = 5, the pattern should look like as below:
// ABCDE
// ABCD
// ABC
// AB
// A
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern15(int n) {
        for(int i = n; i >= 1; i--){
            for(int j = 0; j < i; j++){
                cout<<(char)('A'+j)<<" ";
            }
            cout<<"\n";
        }
    }
    void pattern15_2(int N) {
    // Outer loop for the number of rows
    for (int i = 0; i < N; i++) {
        
        // Inner loop to print alphabets from A to A + (N-i-1)
        for (char ch = 'A'; ch <= 'A' + (N - i - 1); ch++) {
            cout << ch << " ";  // Print the current character followed by a space
        }

        // Move to the next line after printing the current row
        cout << endl;
    }
}
};

int main(){
    Solution obj;
    obj.pattern15_2(6);
    return 0;
}