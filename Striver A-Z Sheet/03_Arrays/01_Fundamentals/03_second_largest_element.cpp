// Second Largest Element
// Given an array of integers nums, return the second-largest element in the array. If the second-largest element does not exist, return -1.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int secondLargestElement(vector<int>& nums) {
        int secondLargest = INT_MIN;
        int largest = nums[0];
        int l = nums.size();
        int flag = 0;
        for(int i = 1; i < l; i++){
            if(nums[i] > largest){
                secondLargest = largest;
                largest = nums[i];
                flag = 1;
            }
            else if((nums[i] >= secondLargest)&&(nums[i] != largest)){
                secondLargest = nums[i];
                flag = 1;
            }
        }
        if(flag == 0){
            secondLargest = -1;
        }
        return secondLargest;
    }
};