// Problem - Fractional Knapsack
// Problem Link - https://takeuforward.org/practice/dsa/fractional-knapsack

# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    static bool compare(pair<double, int> x, pair<double, int> y){
        return x.first>y.first;
    }
    double fractionalKnapsack(vector<long long>& val, vector<long long>& wt, long long capacity) {
        int n = val.size();
        vector<pair<double, int>> val_per_unit(n);
        for(int i = 0; i < n; i++){
            val_per_unit[i].first = (double)val[i]/wt[i];
            val_per_unit[i].second = i;
        }
        sort(val_per_unit.begin(), val_per_unit.end(), compare);
        double value = 0.0;
        long double current_capacity = capacity;
        for(int index = 0; index < n; index++){
            if(wt[val_per_unit[index].second] <= current_capacity){
                current_capacity -= wt[val_per_unit[index].second];
                value += val[val_per_unit[index].second];
            }
            else{
                value += (double)val[val_per_unit[index].second] * (current_capacity/wt[val_per_unit[index].second]);
                break;
            }
        }
        return value;

    }
    // Time Complexity = O(nlogn + n)
    // Space Complexity = O(n)
};