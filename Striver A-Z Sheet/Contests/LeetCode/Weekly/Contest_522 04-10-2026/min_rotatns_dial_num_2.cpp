// Problem - Minimum Rotations to Dial a Number II
// Problem Link - https://leetcode.com/problems/minimum-rotations-to-dial-a-number-ii/description/

# include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minRotations(int n, string s) {        
        int prefix[n];
        int suffix[n];
        int current = 0;
        int sum = 0;
        for(int i = 0; i < n; i++){
            int num = s[i] - '0';
            int diff = abs(num-current);
            int diff1 = 10 - diff;
            int minimum = min(diff, diff1);
            sum += minimum;
            prefix[i] = sum;
            current = num;
        }
        current = s[n-1] - '0';
        sum = 0;
        for(int i = n-1; i >= 0; i--){
            int num = s[i] - '0';
            int diff = abs(num-current);
            int diff1 = 10 - diff;
            int minimum = min(diff, diff1);
            sum += minimum;
            suffix[i] = sum;
            current = num;
        }
        int minimum = INT_MAX;
        for(int k = 0; k < n; k++){
            int ans = -1;
            if(k == 0){
                int diff = abs(0 - (s[n-1] - '0'));
                int diff1 = 10-diff;
                int x = min(diff,diff1);
                ans = x + suffix[k];
            }
            else{
                int diff = abs((s[k-1] - '0') - (s[n-1] - '0'));
                int diff1 = 10-diff;
                int x = min(diff,diff1);
                ans = prefix[k-1] + x + suffix[k];
            }
            if(ans < minimum) minimum = ans;
        }
        return minimum;
    }


    // Better Approach
};

