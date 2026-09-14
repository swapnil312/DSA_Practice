// For Loop
// Given two integers low and high, return the sum of all integers from low to high inclusive.
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int forLoop(int low, int high) {
        int sum = 0;
        for(int i = low; i <= high; i++){
            sum += i;
        }
        return sum;
    }
};