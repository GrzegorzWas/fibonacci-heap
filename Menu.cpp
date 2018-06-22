#include "Menu.h"
#include <iostream>

Menu::Menu(std::initializer_list<std::string> options)
{
	for (std::string option : options)
	{
		this->options.push_back(option);
	}
}

Menu::~Menu()
{
}

void Menu::show()
{
	std::cout << "========== Menu =========" << std::endl;
	for (int i = 0; i < options.size(); i++) {
		std::cout << i << ": " << options.at(i) << std::endl;
	}
	std::cout << "=========================" << std::endl;
}

std::string Menu::get_selected_option()
{
	int selected_option;
	while (true) {
		
		
		std::cin >> selected_option;

		if (std::cin.fail() || selected_option >= options.size() || selected_option < 0) {
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "invalid option" << std::endl;		
			
		}
		else {
			return options.at(selected_option);
			continue;
		}
	}
}
