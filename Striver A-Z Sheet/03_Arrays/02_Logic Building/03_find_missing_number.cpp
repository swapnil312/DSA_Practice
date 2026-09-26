//  Find missing number
// Given an integer arrayof size n containing distinct values in the range from 0 to n (inclusive), return the only number missing from the array within this range.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int sum = (n*(n+1))/2;
        int acquired_sum = 0;
        for(auto it: nums){
            acquired_sum += it;
        }
        return sum-acquired_sum;
    }
};