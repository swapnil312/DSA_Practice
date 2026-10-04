// Problem - Minimum Rotations to Dial a Number I
// Problem Link - https://leetcode.com/problems/minimum-rotations-to-dial-a-number-i/description/

# include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minRotations(string s) {
        int current = 0;
        int sum = 0;
        for(int i = 0; i < 10; i++){
            int num = s[i] - '0';
            int diff = abs(num-current);
            int diff1 = 10 - diff;
            int minimum = min(diff, diff1);
            sum += minimum;
            current = num;
        }
        return sum;
    }
};