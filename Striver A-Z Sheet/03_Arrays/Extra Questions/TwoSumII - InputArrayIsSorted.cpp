// Problem - Two Sum II - Input Array Is Sorted
// Problem Link - https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    //Approach - Two pointer
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0;
        int j = numbers.size()-1;
        vector<int> ans = {-1, -1};
        while(i < j){
            if((numbers[i] + numbers[j]) == target){
                ans[0] = i+1;   //Accroding to question it is 1 indexed so added 1
                ans[1] = j+1;   //Accroding to question it is 1 indexed so added 1
                break;
            }
            else if((numbers[i] + numbers[j]) > target) j--;
            else i++;
        }
    return ans;
    }
    // Time Complexity - O(n)
    // Space Complexity - O(1)
};