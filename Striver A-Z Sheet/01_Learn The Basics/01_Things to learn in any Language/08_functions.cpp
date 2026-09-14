// Pass by Ref
// Given an array arr of n elements. The task is to reverse the given array. The reversal of array should be inplace.
// Example 1
// Input: n=5, arr = [1,2,3,4,5]
// Output: [5,4,3,2,1]
// Explanation: The reverse of the array [1,2,3,4,5] is [5,4,3,2,1]
# include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    void reverse(vector<int>& arr){
       int l = arr.size();
       for(int i = 0; i < l/2; i++){
        int temp = arr[i];
        arr[i] = arr[l-1-i];
        arr[l-1-i] = temp;
       } 
    }
};