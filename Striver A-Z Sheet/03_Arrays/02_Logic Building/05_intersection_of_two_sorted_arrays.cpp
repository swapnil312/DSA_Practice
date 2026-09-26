// Intersection of two sorted arrays
// Given two sorted arrays, nums1 and nums2, return an array containing the intersection of these two arrays. Each element in the result must appear as many times as it appears in both arrays; that is, if an element appears x times in nums1 and y times in nums2, it should appear min(x, y) times in the result.
// The intersection of two arrays is an array where all values are present in both arrays.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> intersectionArray(vector<int>& nums1, vector<int>& nums2) {
        int i = 0;
        int j = 0;
        int l1 = nums1.size();
        int l2 = nums2.size();
        vector<int> ans;
        while((i < l1)&&(j < l2)){
            if(nums1[i] < nums2[j]) i++;
            else if(nums1[i] > nums2[j]) j++;
            else{
                ans.push_back(nums1[i]);
                i++;
                j++;
            }
        }
        return ans;
    }
};