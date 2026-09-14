// Majority Element
// Given an array nums of size n, return the majority element.
// The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int majorityElement_myApproach(vector<int>& nums) {
        int n = size(nums);
        int limit = n/2;
        map<int, int> element_counter;
        for(int i =  0; i < n; i++){
                element_counter[nums[i]]++;
                if(element_counter[nums[i]] > limit) return nums[i];
        }
        return -1;
    }
    int majorityElement(vector<int>& nums) {
        int n = size(nums);
        int limit = n/2;
        int count = 0;
        int candidate;
        for(int i = 0; i < n; i++){
            if(count == 0) candidate = nums[i];
            if(nums[i] == candidate) count++;
            else count--;
        }
        //The following part is needed only when we do not know if majority element exists in the array
        int x = 0;
        for(int i = 0; i < n; i++){
            if(nums[i] == candidate) x++;
        }
        if(x > limit) return candidate;
        return -1;
    }
};

int main(){
    Solution obj;
    vector<int> nums = {2,2,2,3,2,2,2,2,4,5,64,2,9};
    cout<<obj.majorityElement(nums);
    return 0;
}