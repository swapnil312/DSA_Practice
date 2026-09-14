// Longest subarray with sum K
// Array contains only positive numbers
// Given an array nums of size n and an integer k, find the length of the longest sub-array that sums to k. If no such sub-array exists, return 0.
# include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    int longestSubarrayBruteForce(vector<int> &nums, int k){
        int longest = 0;
        int length = size(nums);
        for(int i = 0; i < length; i++){
            int sum = 0;
            for(int j = i; j < length; j++){
                sum += nums[j];
                if(sum == k){
                    if(j-i+1 > longest) longest = j-i+1;
                }
            }
        }
        return longest;
    }
    int longestSubarray(vector<int> &nums, int k){
        int longest = 0;
        int length = size(nums);
        int sum = 0;
        unordered_map<int, int> mpp;
        for(int i = 0; i < length; i++){
            sum += nums[i];
            mpp[sum] = i;
            if(sum == k){
                int size = i+1;
                if(size > longest) longest = size;
                continue;
            }
            if(mpp.find(sum-k) != mpp.end()){
                if((i - mpp[sum-k]) > longest) longest = i - mpp[sum-k];
            }
        }
    //     for(auto it: mpp){
    //     cout<<it.first<<" "<<it.second<<endl;
    // }
        return longest;
    }

    // The below function is most optimal if the array contains non-negative numbers i.e we save on space
    // We need not put map
    int longestSubArray_nonNegative_optimal(vector<int> &nums, int k){
        int i = 0;
        int j = 0;
        int sum = nums[j];
        int longest = 0;
        int length = size(nums);
        while((i <= j)&&(j < length)){
            cout<<endl<<"First: i = "<<i<<" "<<"j = "<<j<<" "<<"Sum = "<<sum;
            if(sum == k){
                if((j-i+1) > longest) longest = j-i+1;
                j++;
                sum += nums[j];
            }
            else if(sum < k){
                j++;
                sum += nums[j];
            }
            else{
                sum -= nums[i];
                if(i == j){
                    j++;
                    sum += nums[j];
                }
                i++;
            }
            cout<<endl<<"End: i = "<<i<<" "<<"j = "<<j<<" "<<"Sum = "<<sum<<endl;
        }
        return longest;
    }

    int longestSubArray_nonNegative_optimal_striver(vector<int> &nums, int k){
        int n = nums.size();
        
        // To store the maximum length of the subarray
        int maxLen = 0;
        
        // Pointers to mark the start and end of window
        int left = 0, right = 0;
        
        // To store the sum of elements in the window
        int sum = nums[0];
        
        // Traverse all the elements
        while(right < n) {
            
            // If the sum exceeds K, shrink the window
            while(left <= right && sum > k) {
                sum -= nums[left];
                left++;
            }
            
            // store the maximum length
            if(sum == k) {
                maxLen = max(maxLen, right - left + 1);
            }
            
            right++;
            if(right < n) sum += nums[right];
        }
        
        return maxLen;
    }
    
};

int main(){
    Solution obj;
    vector<int> nums = {4,2,3,4,0,0,0,4,8,2};
    cout<<obj.longestSubArray_nonNegative_optimal(nums, 2);
    
    return 0;
}
