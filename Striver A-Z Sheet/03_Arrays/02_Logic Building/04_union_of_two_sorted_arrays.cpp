// Union of two sorted arrays
// Given two sorted arrays nums1 and nums2, return an array that contains the union of these two arrays. The elements in the union must be in ascending order.
// The union of two arrays is an array where all values are distinct and are present in either the first array, the second array, or both.
# include <bits/stdc++.h>
using namespace std; 
class Solution {
public:
    vector<int> unionArray(vector<int>& nums1, vector<int>& nums2) {
        int i = 0;
        int j = 0;
        int l1 = nums1.size();
        int l2 = nums2.size();
        int currentElement;
        vector<int> ans;
        while((i < l1)&&(j < l2)){
            if(nums1[i] < nums2[j]){
                currentElement = nums1[i];
                i++;
            }
            else if(nums1[i] > nums2[j]){
                currentElement = nums2[j];
                j++;
            }
            else{
                currentElement = nums1[i];
                i++;
                j++;
            }

            if((ans.empty()) || (ans.back() != currentElement)){
                ans.push_back(currentElement);
            }
        }

        while(i<l1){
            if(ans.back() != nums1[i]){
                ans.push_back(nums1[i]);
            }
            i++;
            
        }
        while(j<l2){
            if(ans.back() != nums2[j]){
                ans.push_back(nums2[j]);
            }
            j++;
        }
        return ans;
    }
};