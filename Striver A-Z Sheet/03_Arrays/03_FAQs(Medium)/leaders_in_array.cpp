// Problem - Leaders in an Array
// Problem Link - https://www.geeksforgeeks.org/problems/leaders-in-an-array-1587115620/1
# include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    // Approach - Brute Force
    vector<int> leaders(vector<int>& nums) {
        int l = nums.size();
        vector<int> ans;
        for(int i = 0; i < l; i++){
            int x = nums[i];
            if(i == l-1) ans.push_back(x);
            for(int j = i+1; j < l; j++){
                if(x >= nums[j]){
                    if(j == l-1) ans.push_back(x);
                    continue;
                }
                else break;
            }
        }
        return ans;
    }
    // Time Complexity = O(n^2)
    // Space Complexity = O(1)

    // Better Approach
    vector<int> leaders(vector<int>& nums) {
        int l = nums.size();
        vector<int> ans;
        vector<int> suffix_max(l);
        suffix_max[l-1] = nums[l-1];
        for(int i = l-2; i >= 0; i--){
            suffix_max[i] = (nums[i] > suffix_max[i+1]) ? nums[i] : suffix_max[i+1];
        }
        for(int i = 0; i < l-1; i++){
            if(nums[i] >= suffix_max[i+1]){
                ans.push_back(nums[i]);
            }
        }
        ans.push_back(nums[l-1]);
        return ans;
    }
    // Time Complexity = O(n)
    // Space Complexity = O(n)

    // Optimal Approach 
    vector<int> leaders(vector<int>& nums) {
        int l = nums.size();
        vector<int> ans;
        int max_Right = nums[l-1];
        ans.push_back(nums[l-1]);
        for(int i = l-2; i >= 0; i--){
            if(nums[i] >= max_Right) ans.push_back(nums[i]);
            max_Right = nums[i] > max_Right ? nums[i]:max_Right;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
    // Time Complexity = O(n)
    // Space COmplexity = O(1)
    
};