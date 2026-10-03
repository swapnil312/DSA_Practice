// Problem - Assign Cookies
// Problem Link - https://leetcode.com/problems/assign-cookies/description/

# include <bits/stdc++.h>
using namespace std;
class Solution {
public:

    // Approach - Brute Force
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int g_l = g.size();
        int s_l = s.size();
        vector<int> used(s_l,0);
        int count = 0;
        for(int i = 0; i < g_l; i++){
            for(int j = 0; j < s_l; j++){
                if((s[j] >= g[i]) && (used[j] == 0)){
                    count++;
                    used[j] = 1;
                    break;
                }
            }
        }
        return count;
    }
    // Let |g| = m ans |s| = n
    // Time Complexity = O(m*n + mlogm + nlogn)
    // Space Complexity = O(n)



    // Approach - Greedy
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int g_l = g.size();
        int s_l = s.size();
        int i = 0;
        int j = 0;
        int count = 0;
        while((i < g_l)&&(j < s_l)){
            if(s[j] >= g[i]){
                count++;
                i++;
            }
            j++;
        }
        return count;
    }
    // Let m = size of greedy array and n = size of sizee array    
    // We can observe that while loop ends when any one of the arrays has 
    // finished traversal. Now we cannot tell anything about when will the
    // students array will finish its traversal since it depends upon how many 
    // students satisfied yet, but we can see that on every iteration we are
    // incremeting the pointer of the cookie array, so while is bound to run
    // size of cookie array no of times in worst case.
    // Time Complexity = O(mlogm + nlogn + n) = O(mlogm + nlogn)
    // Space Complexity = O(1)

};