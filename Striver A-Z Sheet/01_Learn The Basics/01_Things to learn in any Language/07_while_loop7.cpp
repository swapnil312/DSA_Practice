// While Loop
// Given a digit d (0 to 9), find the sum of the first 50 positive integers (integers > 0) that end with digit d.
// A number ends with digit d if its last digit is d.
// Example 1
// Input: d = 1
// Output: 12300
// Explanation:
// The first 50 positive integers ending with 1 are: 1, 11, 21, 31, ..., 491
// Their sum is 12300.
// Approach 1: Using a while loop to iterate through positive integers and check if they end with digit d. If they do, add them to the sum until we have found 50 such integers.
class Solution {
    public:
    int whileLoop(int d) {
        int x = 50;
        int sum = 0;
        int a = 1;
        while(x > 0){
            if((a%10) == d){
                sum += a;
                x--;
            }
            a++;
            
        }
        return sum;
    }
};
// Approach 2: Using a while loop to directly calculate the first 50 positive integers that end with digit d by starting from d and incrementing by 10 each time. This avoids checking every integer and is more efficient.
class Solution {
    public:
    int whileLoop(int d) {
        int x = 50;
        int sum = 0;
        int a = d;
        while(x > 0){
            sum += a;
            a += 10;
            x--;
        }
        return sum;
    }
};

