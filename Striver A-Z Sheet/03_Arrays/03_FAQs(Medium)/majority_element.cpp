// Problem - Majority Element
// Problem Link - https://leetcode.com/problems/majority-element/description/

# include <bits/stdc++.h>
using namespace std;
class Solution {
public:

    // Approach 1- Brute force, we only need to ckeck half of the elements because
    // majority element is bound to be one of them
    int majorityElement(vector<int>& nums) {
        int l = nums.size();
        int x = l/2;
        for(int i = 0; i <= x; i++){
            int num = nums[i];
            int count = 0;
            for(int j = 0; j < l; j++){
                if(nums[j] == num) count++;
            }
            if(count > x) return num;
        }
        return -1;
    }
    // Time Complexity = O((n^2)/2)
    // Space Complexity = O(1)
    // Got Time Limit Exceeded

    // Approach 2 - Used unordered_map to store frequencies
    int majorityElement(vector<int>& nums) {
        int l = nums.size();
        unordered_map<int, int> mp;
        for(int i = 0; i < l; i++){
            mp[nums[i]]++;
            if(mp[nums[i]] > l/2) return nums[i];
        }
        return -1;
    }
    // Time Complexity = O(n) because each loopup in unordered_map takes O(1) time
    // Space Complexity = O(k) where k is the number of distinct elements
    // At worst case space complexity can go up to O(n) auxiliary space

    // Approach 3 - Used Moore's Voting Algorithm
    // Majority Element is guarenteed to exist so need not check again if candidate is the real majority element 
    int majorityElement(vector<int>& nums) {
        int l = nums.size();
        int candidate = nums[0];
        int count = 1;
        for(int i = 1; i < l; i++){
            if(count == 0){
                candidate = nums[i];
                count++;
                continue;
            }

            if(nums[i] == candidate) count++;
            else count--;
        }
        return candidate;
    }
    // Inside for loop we can write this also 
    //         if(count == 0) candidate = nums[i];
    //         if(nums[i] == candidate) count++;
    //         else count--;
    // Time Complexity = O(n)
    // Space Complexity = O(1)

};
