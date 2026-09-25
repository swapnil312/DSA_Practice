// Linear Search
// Given an array of integers nums and an integer target, find the smallest index (0 based indexing) where the target appears in the array. If the target is not found in the array, return -1
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int linearSearch(vector<int>& nums, int target) {
        int l = nums.size();
        for(int i = 0; i < l; i++){
            if(target == nums[i]) return i;
        }
        return -1;
    }
};