// Reverse an array
// Given an array arr of n elements. The task is to reverse the given array. The reversal of array should be inplace.
# include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    void reverse(int arr[], int n){
        for(int i = 0; i < n/2; i++){
            int temp = arr[i];
            arr[i] = arr[n-1-i];
            arr[n-1-i] = temp;
        }
    }
    void reverse_recursion(int arr[], int n){
        if((n==1)||(n==0)) return;
        int temp = arr[0];
        arr[0] = arr[n-1];
        arr[n-1] = temp;
        reverse_recursion(arr+1, n-2);
    }
};

int main(){
    Solution obj;
    int arr[] = {1,2,1,1,5,1};
    obj.reverse_recursion(arr,6);
    for(int x: arr){
        cout<<x<<endl;
    }
    return 0;
}