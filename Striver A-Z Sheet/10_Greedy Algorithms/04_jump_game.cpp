// Problem - Jump Game
// Problem Link - https://leetcode.com/problems/jump-game/description/

# include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // My approach also optimal
    // I start from rightmost and then find number from where I can reach rightmost and it goes on,
    // then update the right, Even if there are multiple jump paths still approch is correct, suppose
    // there are more paths, then the second last node from where I will jump to the last node is > 1
    // So, by this algo i get the right-most second-last number and its ok because if we could jump from 
    // other second-last number to last we could also jump from this second-last to right-most second-last.
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int right = n-1;
        for(int i = n-2; i >= 0; i--){
            if(nums[i] >= right-i){
                right = i;
                i = right;
            }
        }
        if(right == 0) return true;
        else return false;
    }
    // Time Complexity = O(n)
    // Space Complexity = O(1)

    // Striver Approach
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int maxReach = 0;
        for(int i = 0; i < n; i++){
            if(i > maxReach) return false;
            maxReach = max(maxReach, i+nums[i]);
        }
        return true;
    }
    // Time Complexity = O(n)
    // Space Complexity = O(1)

};