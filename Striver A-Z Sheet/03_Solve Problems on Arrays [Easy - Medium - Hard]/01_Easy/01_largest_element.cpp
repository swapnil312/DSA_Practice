// Largest Element
// Given an array of integers nums, return the value of the largest element in the array
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int largestElement(vector<int>& nums) {
        int largest = nums[0];
        for(int i = 1; i < size(nums)-1; i++){
            if(nums[i] > largest) largest = nums[i];
        }
        return largest;
    }
};

int main(){
    Solution obj;
    vector<int> v = {1,56,56,89,3,7,965,47};
    cout<<obj.largestElement(v);
    return 0;
}