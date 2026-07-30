# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void pattern9(int n) {
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n-i; j++){
                cout<<" ";
            }
            for(int k = 1; k <= (2*(i-1))+1; k++){
                cout<<"*";
            }
            for(int l = 1; l <= n-1-i; l++){
                cout<<" ";
            }
            cout<<"\n";
        }
        
        for(int i = n; i >= 1; i--){
            for(int k = 1; k <= n-i; k++){
                cout<<" ";
            }
            for(int j = 1; j <= (2*(i-1))+1; j++){
                cout<<"*";
            }
            for(int l = 1; l <= n-i; l++){
                cout<<" ";
            }
            cout<<"\n";
        }
    }
};

int main(){
    Solution obj;
    int n = 6;
    obj.pattern9(n);
    return 0;
}