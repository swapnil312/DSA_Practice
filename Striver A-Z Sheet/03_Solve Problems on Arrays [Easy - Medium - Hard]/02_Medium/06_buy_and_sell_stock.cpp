// Best Time to Buy and Sell Stock
// You are given an array prices where prices[i] is the price of a given stock on the ith day.
// You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
// Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int length = size(prices);
        int max = 0;
        for(int i = 0; i < length; i++){
            int x = prices[i];
            for(int j = i+1; j < length; j++){
                if(prices[j] > x){
                    int d = prices[j] - x;
                    if(d > max) max = d;
                }
            }
        }
        return max;
    }

    int maxProfit_optimal(vector<int> &prices){
        int minPrice = prices[0];
        int maxProfit = 0;
        int length = size(prices);
        for(int i = 1; i < length; i++){
            minPrice = min(minPrice, prices[i]);
            if((prices[i] - minPrice) > maxProfit) maxProfit = prices[i] - minPrice;
        }
        return maxProfit;
    }
};

int main(){
    Solution obj;
    vector<int> prices = {7,1,5,3,6,4};
    cout<<obj.maxProfit_optimal(prices);
    return 0;
}