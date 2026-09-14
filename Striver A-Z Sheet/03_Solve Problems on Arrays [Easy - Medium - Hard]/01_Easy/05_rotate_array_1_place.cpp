// Left/Right Rotate Array by One
// Given an integer array nums, rotate the array to the left/right by one.
// Note: There is no need to return anything, just modify the given array.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void rotateArrayByOne_left(vector<int>& nums) { 
        int length = size(nums);
        if(length == 1) return;
        int first_element = nums[0];
        for(int i = 0; i < length-1; i++){
            nums[i] = nums[i+1];
        }
        nums[length-1] = first_element;
    }
    void rotateArrayByOne_right(vector<int>& nums) { 
        int length = size(nums);
        if(length == 1) return;
        int last_element = nums[length-1];
        for(int i = length-2; i >= 0; i--){
            nums[i+1] = nums[i];
        }
        nums[0] = last_element;
    }
};

int main(){
    vector<int> v = {1,2,3,4,5,6,7,8,9};
    Solution obj;
    obj.rotateArrayByOne_right(v);
    for(auto it: v){
        cout<<it<<" ";
    }
    return 0;
}