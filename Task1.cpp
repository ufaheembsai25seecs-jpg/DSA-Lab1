#include <iostream>
#include <string>
using namespace std;

bool ispalindrome(string user_string) {
	int start = 0;
	int end = user_string.length() -1 ;
	while(start < end) {
		if (user_string[start] != user_string[end]) {
			return false;
		}
		start++;
		end--;

	}
	return true;
}

int main() {
	string user_string;
	cout << "Enter a string to be checked: ";
	cin >> user_string;
	bool palindrome = ispalindrome(user_string);
	if (palindrome == true) {
		cout << "It is a palindrome";
	}
	else {
		cout << "It is not a palindrome";
	}
	return 0;

} 