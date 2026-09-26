// Move Zeros to End
// Given an integer array nums, move all the 0's to the end of the array. The relative order of the other elements must remain the same.
// This must be done in place, without making a copy of the array.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int x = 0;
        int l = nums.size();
        for(int i = 0; i < l; i++){
            if(nums[i] != 0){
                nums[x] = nums[i];
                x++;
            }
        }
        while(x<l){
            nums[x] = 0;
            x++;
        }
    }
    void moveZeroesMyApproach(vector<int>& nums) {
        int i = 0;
        int j = 0;
        int l = nums.size();
        while(((i < l)&&(j < l)) && (i <= j)){
            if((nums[i] == 0)&&(nums[j] == 0)){
                j++;
            }
            else if((nums[i] == 0)&&(nums[j] != 0)){
                nums[i] = nums[j];
                nums[j] = 0;
                i++;
                j++;
            }
            else{
                i++;
                j++;
            }
        }
    }
    void moveZeroesBestClearApproach(vector<int>& nums) {
        int i = 0;
        int j = -1;
        int l = nums.size();
        for(i = 0; i < l; i++){
            if(nums[i] == 0){
                j = i;
                break;
            }
        }
        if(j == -1) return;
        for(i = j+1; i < l; i++){
            if(nums[i] != 0){
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
                j++;
            }
        }
    }
};