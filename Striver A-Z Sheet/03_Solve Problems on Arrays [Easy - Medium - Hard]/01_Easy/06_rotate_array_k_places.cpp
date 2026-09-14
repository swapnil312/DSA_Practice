// Rotate Array by K Places
// Given an integer array nums and a non-negative integer k, rotate the array to the left by k steps.
// Example 
// Input: nums = [1, 2, 3, 4, 5, 6], k = 2
// Output: nums = [3, 4, 5, 6, 1, 2]
// Explanation:
// rotate 1 step to the left: [2, 3, 4, 5, 6, 1]
// rotate 2 steps to the left: [3, 4, 5, 6, 1, 2]
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void rotate_left_myfunc(vector<int>& nums, int k) {
        vector<int> x;
        int l = size(nums);
        for(int i = 0; i < l; i++){
            x.emplace_back(nums[i]);
        }
        for(int i = k; i < l; i++){
            nums[i-k] = nums[i];
        }
        int index = 0;
        for(int i = l-k; i < l; i++){
            nums[i] = x[index];
            index++;
        }
    }
    void rotate_right_k_places_leetcode(vector<int> &nums, int k){
        int length = size(nums);
        k %= length;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+k);
        reverse(nums.begin()+k, nums.end());
    }
    void rotate_left_k_places_leetcode(vector<int> &nums, int k){
        int length = size(nums);
        k %= length;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+length-k);
        reverse(nums.begin()+length-k, nums.end());
    }
    
};

int main(){
    Solution obj;
    vector<int> vec = {1,2,4,6,7,5,7,5};
    obj.rotate_left_k_places_leetcode(vec, 3);
    for(auto it: vec) cout<<it<<" ";
    return 0;
}