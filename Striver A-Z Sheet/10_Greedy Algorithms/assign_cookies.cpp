// Problem - Assign Cookies
// Problem Link - https://leetcode.com/problems/assign-cookies/description/

# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
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
};