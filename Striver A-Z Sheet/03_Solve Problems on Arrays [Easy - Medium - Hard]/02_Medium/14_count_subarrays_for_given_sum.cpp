// Subarray Sum Equals K
// Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
// A subarray is a contiguous non-empty sequence of elements within an array.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int subarraySum_bruteForce(vector<int>& nums, int k) {
        int length = size(nums);
        int count = 0;
        for(int i = 0; i < length; i++){
            int sum = 0;
            for(int j = i; j< length; j++){
                sum += nums[j];
                if(sum == k) count++;
           }
        }
        return count;
    }
};
