#pragma once
#include <string>
#include <vector>
class Menu
{
public:
	/**
	display menu
	**/
	void show();

	/**
	read user input and return string representing
	chosen option
	**/
	std::string get_selected_option();
	
	Menu(std::initializer_list<std::string> list);
	~Menu();
private:
	std::vector<std::string> options;
};

