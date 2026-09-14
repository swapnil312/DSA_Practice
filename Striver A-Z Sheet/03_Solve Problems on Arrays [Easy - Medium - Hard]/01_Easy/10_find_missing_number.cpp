// Find missing number
// Given an integer array of size n containing distinct values in the range from 0 to n (inclusive), return the only number missing from the array within this range.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int missingNumber_myApproach(vector<int> &nums) {
        int l = size(nums);
        vector<int> arr(l+1,0);
        for(int i = 0; i < l; i++){
            arr[nums[i]] = 1;
        }
        for(int x = 0; x < l+1; x++){
            if(arr[x] == 0) return x;
        }
        return -1;
    }

    //using the formual sum of first n natural numbers is n(n+1)/2
    int missingNumber_sumApproach(vector<int> &nums){
        int length = size(nums);
        int sum = (length*(length+1))/2;
        int computed_sum = 0;
        for(auto it: nums){
            computed_sum += it;
        }
        return sum-computed_sum;
    }

    //  XOR of a number with itself is 0 i.e. x ^ x = 0 and the given array arr[] has numbers in range [1, n]. 
    //  This means that the result of XOR of first n natural numbers with the XOR of all the array elements will be the missing number.
    //  To do so, calculate XOR of first n natural numbers and XOR of all the array arr[] elements, and then our result will be the XOR of both the resultant values.
    int missingNumber_xorApproach(vector<int> &nums){
        int l = size(nums);
        int xor1 = 0;
        for(int i = 0; i <= l; i++){
            xor1 = xor1 ^ i;
        }
        int xor2 = 0;
        for(auto it: nums){
            xor2 = xor2 ^ it;
        }
        return xor1 ^ xor2;
    }

};

int main(){
    Solution obj;
    vector<int> nums = {1,2,4,5,0};
    cout<<obj.missingNumber_xorApproach(nums);
    return 0;
}