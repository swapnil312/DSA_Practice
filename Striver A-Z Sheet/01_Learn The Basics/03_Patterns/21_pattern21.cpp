# include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void pattern21(int n) {
        for(int i = 1; i <= n; i++){
            if((i== 1)||(i == n)){
                for(int j = 1; j <= n; j++){
                    cout<<"*";
                }
            }
            else
            {
                for(int j = 1; j <= n; j++){
                    if((j==1)||(j==n)){
                        cout<<"*";
                    }
                    else{
                        cout<<" ";
                    }
                }
            }
            cout<<"\n";
        }
    }
    void pattern21_2(int n) {
        // Outer loop for rows
        for (int i = 0; i < n; i++) {
            // Inner loop for columns
            for (int j = 0; j < n; j++) {
                // Print star if it's a border cell
                if (i == 0 || j == 0 || i == n - 1 || j == n - 1)
                    cout << "*";
                // Print space otherwise
                else
                    cout << " ";
            }
            // Move to next line after each row
            cout << endl;
        }
    }
};

int main() {
    Solution sol;
    int n = 6; // You can change this value to test with different sizes
    sol.pattern21_2(n);
    return 0;
}