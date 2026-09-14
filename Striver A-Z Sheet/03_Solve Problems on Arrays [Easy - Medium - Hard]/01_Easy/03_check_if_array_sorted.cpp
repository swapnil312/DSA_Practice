// Check if the Array is Sorted II
// Given an array nums of n integers, return true if the array nums is sorted in non-decreasing order or else false.
# include <bits/stdc++.h>
using namespace std;
class Solution{	
	public:
		bool isSorted(vector<int>& nums){
			for(int i = 0; i < size(nums)-1; i++){
                if(nums[i] > nums[i+1]) return false;
            }
            return true;
		}
        bool isSortedAndRotated_leetcode(vector<int>& nums){
            int i = 0;
            int length = size(nums);
            while((i < length-1)&&(nums[i] <= nums[i+1])) i++;
            if((i == length-1)||((i+1 == length-1)&&(nums[length-1] <= nums[0]))) return true;
            for(int x = i+1; x < length-1; x++){
                if(nums[x] > nums[x+1]) return false;
            }
            if(nums[length-1] > nums[0]) return false;
            return true;
        }
};

int main(){
    Solution obj;
    vector<int> v = {1,3,2};
    cout<<obj.isSortedAndRotated_leetcode(v);
    return 0;
}