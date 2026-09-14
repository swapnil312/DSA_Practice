// Sum of First N Numbers
// Given an integer N, return the sum of first N natural numbers. Try to solve this using recursion.
# include <bits/stdc++.h>
using namespace std;
class Solution{	
	public:
		int NnumbersSum(int N){
            if(N == 1) return 1;
			return N+NnumbersSum(N-1);
		}
};

int main(){
    Solution obj;
    cout<<obj.NnumbersSum(5);
    return 0;
}