// Check if String is Palindrome or Not
// Given a string s, return true if the string is palindrome, otherwise false.
// A string is called palindrome if it reads the same forward and backward.
# include <bits/stdc++.h>
using namespace std;

class Solution{	
	public:		
		bool palindromeCheck_recursion(string& s){
			if((s.size() == 0) || (s.size() == 1)) return true;
            string x = s.substr(1,(s.size()-2));
            if(s[0] == s[s.size()-1]) return palindromeCheck_recursion(x);
            return false;
		}
        bool palindromeCheck_leetCode(string s){
            string str = "";
            for(int i = 0; i < size(s); i++){
                if(isalpha(s[i])) str += tolower(s[i]);
                else if(isdigit(s[i])) str += s[i];
                else continue;    
            }
            for(int i = 0; i < size(str)/2; i++){
                if(str[i] == str[size(str)-1-i]) continue;
                else return false;
            }
            return true;
        }
};
int main(){
    Solution obj;
    string s = "abbctfgba";
    cout<<obj.palindromeCheck_leetCode(s);
    return 0;
}
