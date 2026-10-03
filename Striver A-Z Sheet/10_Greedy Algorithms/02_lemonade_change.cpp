// Problem - Lemonade Change
// Problem Link - https://leetcode.com/problems/lemonade-change/description/


# include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Approach - Greedy
    bool lemonadeChange(vector<int>& bills) {
        int fives = 0;
        int tens = 0;
        int l = bills.size();
        for(int i = 0; i  < l; i++){
            if(bills[i] == 5) fives++;
            else if(bills[i] == 10){
                if(fives){
                    fives--;
                    tens++;
                }
                else return false;
            }
            else{
                if(tens && fives){
                    tens--;
                    fives--;
                }
                else if(fives >= 3){
                    fives -= 3;
                }
                else return false;
            }
        }
        return true;
    }

};