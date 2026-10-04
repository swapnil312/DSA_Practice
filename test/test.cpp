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
            val_per_unit[i].first = val[i]/wt[i];
            val_per_unit[i].second = i;
        }
        sort(val_per_unit.begin(), val_per_unit.end(), compare);
        double value = 0.0;
        long long current_capacity = capacity;
        for(int index = 0; index < n; index++){
            if(wt[val_per_unit[index].second] <= current_capacity){
                current_capacity -= wt[val_per_unit[index].second];
                value += val[val_per_unit[index].second];
                cout<<val[val_per_unit[index].second]<<endl;
            }
            else{
                value += ((double)val[val_per_unit[index].second] * current_capacity)/(double)wt[val_per_unit[index].second];
                cout<<((double)val[val_per_unit[index].second] * current_capacity)/(double)wt[val_per_unit[index].second]<<endl;
                break;
            }
        }
        return value;

    }
};

int main(){
    Solution obj;
    vector<long long> val = {1,2,3,4,5,6,7,8,9,10};
    vector<long long> wt = {10,9,8,7,6,5,4,3,2,1};
    long long capacity = 25;
    cout<<obj.fractionalKnapsack(val,wt,capacity);
    return 0;
}
