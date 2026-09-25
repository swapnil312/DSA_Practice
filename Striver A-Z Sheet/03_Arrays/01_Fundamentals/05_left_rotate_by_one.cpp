// Left Rotate Array by One
// Given an integer array nums, rotate the array to the left by one.
// Note: There is no need to return anything, just modify the given array.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void rotateArrayByOne(vector<int>& nums) {
        int first_element = nums[0];
        int l = nums.size();
        for(int i = 1; i < l; i++){
            nums[i-1] = nums[i];
        }
        nums[l-1] = first_element;
    }
};