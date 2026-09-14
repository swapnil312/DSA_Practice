// Counting Frequencies of Array Elements
// Given an array nums of size n which may contain duplicate elements.
// Return a list of pairs where each pair contains a unique element from the array and its frequency in the array.
// You may return the result in any order, but each element must appear exactly once in the output.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> countFrequencies(vector<int>& nums) {
        unordered_map<int, int> mpp;
        vector<vector<int>> vec;
        int l = size(nums);
        for(int i = 0; i < l; i++){
            mpp[nums[i]]++;
        }
        for(auto it: mpp){
            vec.push_back({it.first, it.second});
        }
        return vec;
    }
};

int main(){
    Solution obj;
    vector<int> v = {1, 2, 2, 1, 3};
    vector<vector<int>> x = obj.countFrequencies(v);
    for(auto it: x){
        for(auto it1: it) cout<<it1<<" ";
        cout<<endl;
    }
    return 0;
}