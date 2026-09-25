// Max Consecutive Ones
// Given a binary array nums, return the maximum number of consecutive 1's in the array.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findMaxConsecutiveOnes_myApproach(vector<int>& nums) {
        int max = 0;
        int local_count = 0;
        int l = nums.size();
        for(int k = 0; k < l; k++){
            if(nums[k] == 1){
                if(k == 0){
                    local_count++;
                    if(l==1) return 1;
                    continue;
                }
                if(nums[k-1] == 1) local_count++;
                else local_count = 1;
            }
            
            if(local_count > max) max = local_count;
        }
        return max;
    }
    int findMaxConsecutiveOnes_bestApproach(vector<int>& nums) {
        int local_count = 0;
        int maximum = 0;
        for(auto it: nums){
            if(it == 1){
                local_count++;
                maximum = max(local_count, maximum);
            }
            else local_count = 0;
        }
        return maximum;
    }
};