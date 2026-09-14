// Second Largest Element
// Given an array of integers nums, return the second-largest element in the array. If the second-largest element does not exist, return -1.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int secondLargestElement(vector<int>& nums) {
        int largest = nums[0];
        int second_largest = -1;
        for(int i = 1; i < size(nums); i++){
            if(nums[i] > largest){
                second_largest = largest;
                largest = nums[i];
            }
        }
        return second_largest;
    }
};

int main(){
    Solution obj;
    vector<int> v = {20};
    cout<<obj.secondLargestElement(v);
    return 0;
}