// Two Sum
// You are given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
// You can return the answer in any order.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:

    static bool compare(pair<int, int> x, pair<int, int> y){
        return x.first < y.first;
    } 
    vector<int> twoSum_myApproach(vector <int>& nums, int target) {
        vector<pair<int,int>> x;
        int length = size(nums);
        for(int i = 0; i < length; i++){
            x.push_back({nums[i],i});
        }
        sort(x.begin(), x.end(), compare);  
        int i = 0;
        int j = size(nums) - 1;    
        while(i < j){
            if(x[i].first + x[j].first > target) j--;
            else if(x[i].first + x[j].first < target) i++;
            else return {x[i].second,x[j].second};
        }
        return {};
    }
    vector<int> twoSum_twopass_HashTable(vector <int>& nums, int target) {
        //We traverse the list containing n elements exactly twice.
        map<int, int> hash;
        int length = size(nums);
        for(int i = 0; i < length; i++){
            hash[nums[i]] = i;
        }
        for(auto it: hash){
            cout<<it.first<<" "<<it.second;
        }
        cout<<endl;
        for(int i = 0; i < length; i++){
            int complement = target-nums[i];
            if(hash.find(complement) != hash.end() && hash[complement] != i){
                return {i, hash[complement]};
            }
        }
        return {};
    }
    vector<int> twoSum_onepass_HashTable(vector <int>& nums, int target) {
        
        map<int, int> hash;
        int length = size(nums);
        for(int i = 0; i < length; i++){
            
            int complement = target-nums[i];
            if(hash.find(complement) != hash.end()){
                return {i, hash[complement]};
            }
            hash[nums[i]] = i;
        }
        return {};
    }



};

int main(){
    vector<int> v = {3,3};
    int target = 6;
    Solution obj;
    vector<int> ans = obj.twoSum_twopass_HashTable(v, target);
    for(auto it: ans) cout<<it<<" ";
    return 0;
}
