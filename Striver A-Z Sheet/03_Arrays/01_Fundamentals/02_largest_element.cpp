// Largest Element
// Given an array of integers nums, return the value of the largest element in the array
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int largestElement(vector<int>& nums) {
        int largest = nums[0];
        for(auto it: nums){
            if(it>largest) largest = it;
        }
        return largest;
    }
};