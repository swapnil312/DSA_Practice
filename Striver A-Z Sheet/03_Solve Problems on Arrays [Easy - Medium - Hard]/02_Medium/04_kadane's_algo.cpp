// Maximum Subarray
// Given an integer array nums, find the subarray with the largest sum, and return its sum.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxSubArrayBruteForce(vector<int>& nums) {
        int max = INT_MIN;
        int length = size(nums);
        for(int i = 0; i < length; i++){
            int sum = 0;
            for(int j = i; j < length; j++){
                sum += nums[j];
                if(sum>max) max = sum;
            }
        }
        return max;
    }

    int maxSubArray_kadane_algo(vector<int> &nums){
        int max = INT_MIN;
        int sum = 0;
        for(auto it: nums){
            sum += it;
            if(sum>max) max = sum;
            if(sum<0) sum = 0;
        }
        return max;
    }
};

int main(){
    vector<int> nums = {5,4,-1,7,8};
    Solution obj;
    cout<<obj.maxSubArrayBruteForce(nums);
    return  0;
}