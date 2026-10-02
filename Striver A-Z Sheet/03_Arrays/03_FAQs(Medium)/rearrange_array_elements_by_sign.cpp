// Problem - Rearrange Array Elements by Sign
// Problem Link - https://leetcode.com/problems/rearrange-array-elements-by-sign/description/

# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    // 
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> positives;
        vector<int> negatives;
        int l = nums.size();
        for(int i = 0; i < l; i++){
            if(nums[i] > 0) positives.push_back(nums[i]);
            else negatives.push_back(nums[i]);
        }
        for(int i = 0; i < l/2; i++){
            nums[2*i] = positives[i];
            nums[(2*i) + 1] = negatives[i];
        }
        return nums;
    }
    // Time = O(n + n/2)
    // Space = O(n)

    // Optimal Approach
    vector<int> rearrangeArray(vector<int>& nums) {
        int l = nums.size();
        vector<int> ans(l);
        int positive_index = 0;
        int negative_index = 1;
        for(int i = 0; i < l; i++){
            if(nums[i]  > 0){
                ans[positive_index] = nums[i];
                positive_index += 2;
            }
            else{
                ans[negative_index] = nums[i];
                negative_index += 2;
            }
        }
        return ans;
    }
    // Time Complexity - O(n)
    // Space Complexity - O(n)

    
    
};