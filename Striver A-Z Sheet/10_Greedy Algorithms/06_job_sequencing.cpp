// Problem - Job sequencing Problem
// Problem Link - https://takeuforward.org/practice/dsa/job-sequencing-problem


# include <bits/stdc++.h>
using namespace std;
class Solution{  
  public:  
    
    static bool compare(vector<int> x, vector<int> y){
        return x[2] > y[2];
    }
    // Approach -> Sort by decreasing order of profit, then allocate the maximum time unit available
    // within the deadline
    vector<int> JobScheduling(vector<vector<int>>& Jobs) { 
        sort(Jobs.begin(), Jobs.end(), compare);
        vector<int> ans(2,-1);
        int deadLine = -1;
        for(auto it: Jobs){
            deadLine = max(deadLine, it[1]);
        }
        vector<int> used(deadLine+1, 0);
        int totalProfit = 0;
        int count = 0;
        for(auto it: Jobs){
            int x = it[1];
            while((used[x] == 1)&&(x >= 1)) x--;
            if(x == 0) continue;
            used[x] = 1;
            totalProfit += it[2];
            count++;
        }
        ans[0] = count;
        ans[1] = totalProfit;
        return ans;
    } 
};

// n -> no of jobs
// m -> maximum Deadline
// Time Complexity = O(nlogn + n*m)
// Space Complexity = O(m)




// Refer Later
// Disjoint Set Unit -> Graph Topic