#include <iostream>
#include <vector>
#include <map>

bool check_str (std::string);

int main(int argc, char** argv)
{
	std::string test_parenthesis;

	std::cout << "Введите набор скобок" << std::endl;
	std::cin >> test_parenthesis;

	if (check_str (test_parenthesis))
		std::cout << "YES\n";
	else
		std::cout << "NO\n";
}

//Функция парсинга последовательности скобок
bool check_str (std::string test_parenthesis)
{

	std::vector<char> all_parenthesis;
	std::map<char, char> closing_parenthesis = {
		{')', '('},
		{'}', '{'},
		{']', '['},
		{'>', '<'}
	};

	all_parenthesis.clear();
	for (char temp_str : test_parenthesis) {
		if (temp_str == '(' || temp_str == '{' || 
		temp_str == '[' || temp_str == '<')
			all_parenthesis.push_back(temp_str); 
		else if (closing_parenthesis.find(temp_str) != closing_parenthesis.end()) {
			if(all_parenthesis.empty()) 
				return false;
			else if (closing_parenthesis[temp_str] == all_parenthesis.back())
				all_parenthesis.pop_back();
			else 
				return false;
		}
	}
	if (all_parenthesis.empty())
		return true;	
	else
		return false; 	
}
