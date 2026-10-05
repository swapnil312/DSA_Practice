// Problem - Shortest Job First
// Problem Link - https://takeuforward.org/practice/dsa/shortest-job-first?tab=problem

# include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    long long solve(vector<int>& bt) {
        sort(bt.begin(), bt.end());
        int n = bt.size();
        long long wt = 0;
        long long total_wt = 0;
        for(int i = 1; i < n; i++){
            wt += bt[i-1];
            total_wt += wt;
        }
        return total_wt/n;
    }
    // Time Complexity = O(nlogn + n)
    // Space Complexity = O(1)

};