// Remove duplicates from sorted array
// Given an integer array nums sorted in non-decreasing order, remove all duplicates in-place so that each unique element appears only once.
// Return the number of unique elements in the array.
// If the number of unique elements be k, then,
// Change the array nums such that the first k elements of nums contain the unique values in the order that they were present originally.
// The remaining elements, as well as the size of the array does not matter in terms of correctness.
// The driver code will assess correctness by printing and checking only the first k elements of the modified array.
// An array sorted in non-decreasing order is an array where every element to the right of an element is either equal to or greater in value than that element.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int length = size(nums);
        int i = 0, j = 0;
        int index = 0;
        while((i < length)&&(j < length)){
            nums[index] = nums[i];
            while((j < length)&&(nums[i] == nums[j])) j++;
            i = j;
            index++;
        }
        return index;
    }
};

int main(){
    Solution obj;
    vector<int> v = {0,0,0,1,1,1,2,2,2,3,3,3,4,4};
    cout<<obj.removeDuplicates(v)<<endl;
    for(auto i: v) cout<<i<<endl;
    return 0;
}