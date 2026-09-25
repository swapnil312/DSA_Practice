// Left Rotate Array by K Places
// Given an integer array nums and a non-negative integer k, rotate the array to the left by k steps.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void rotateArray(vector<int>& nums, int k) {
        int l = nums.size();
        vector<int> result(l);
        for(int i = 0; i < l; i++){
            result[i] = nums[(i+k)%l];
        }
        for(int i = 0; i < l; i++){
            nums[i] = result[i];
        }
    }
    void rotateArrayOptimal(vector<int>& nums, int k) {
        int l = nums.size();
        k = k%l;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+l-k);
        reverse(nums.begin()+l-k, nums.end());
    }
};