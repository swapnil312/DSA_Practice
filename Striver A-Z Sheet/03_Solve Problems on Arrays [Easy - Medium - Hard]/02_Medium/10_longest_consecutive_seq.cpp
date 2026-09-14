// Longest Consecutive Sequence
// Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
// You must write an algorithm that runs in O(n) time.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool linearSearch(int x, vector<int> &nums){
        for(auto it: nums){
            if(x==it) return true;
        }
        return false;
    }
    int longestConsecutive_bruteForce(vector<int>& nums) {
        int length = size(nums);
        if(length == 0) return 0;
        int longest = INT_MIN;
        int cnt = 0;
        for(int i = 0; i < length; i++){
            int x = nums[i];
            cnt = 1;
            while(linearSearch(x+1, nums)){
                x++;
                cnt++;
            }
            if(cnt>longest) longest = cnt;
        }
        return longest;
    }

    int longestConsecutive_optimal(vector<int> &nums){
        if(size(nums) == 0) return 0;
        unordered_set<int> st;
        for(auto it: nums) st.insert(it);
        int cnt = 0;
        int longest_count = INT_MIN;
        for(auto it: st){
            if(st.find(it-1) == st.end()){
                cnt = 1;
                int x = it;
                while(st.find(x+1) != st.end()){
                    cnt++;
                    x++;
                }
                if(cnt>longest_count) longest_count = cnt;
            }
        }
        return longest_count;
    }
};

int main(){
    Solution obj;
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout<<obj.longestConsecutive_bruteForce(nums);
    return 0;
}