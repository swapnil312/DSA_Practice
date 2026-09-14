// Longest subarray with sum K
// Given an array nums of size n and an integer k, find the length of the longest sub-array that sums to k. If no such sub-array exists, return 0.
# include <bits/stdc++.h>
using namespace std;
class Solution{
    public:
        int longestSubArray(vector<int> &nums,int k){
        int prefix_sum = 0;
        int longest = 0;
        unordered_map<int,int> mpp;
        int length = size(nums);
        for(int i = 0; i < length; i++){
            prefix_sum += nums[i];
            if(prefix_sum == k){
                longest = max(longest, i+1);
                continue;
            }
            if(mpp.find(prefix_sum) == mpp.end()){
                mpp[prefix_sum] = i;
            }
            if(mpp.find(prefix_sum-k) != mpp.end()){
                longest = max(longest,i-mpp[prefix_sum-k]);
            }
        }
        return longest;
    }

    int longestSubArray(vector<int> &nums, int k){
        
    }
};

int main(){
    vector<int> nums = {1,2,3,4,-4,0,0,4,8,2};
    Solution obj;
    cout<<obj.longestSubArray(nums,4);
    return 0;
}