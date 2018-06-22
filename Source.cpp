#pragma warning(disable:4996)
#include <iostream>
#include <limits.h>
#include <Windows.h>
#include <time.h>
#include "Heap.h"
#include "Menu.h"

bool input_valid(std::istream& stream) {
	if (stream.fail()) {
		stream.clear();
		while (stream.get() != '\n');
		return false;
	}
	else 
		return true;
}

int main() {

	Menu main_menu({ "heap merge example", "create your own heap", "about", "quit" });
	while (true) {
		system("cls");
		main_menu.show();
		std::string option = main_menu.get_selected_option();
		
		if (option == "heap merge example") {
			Heap heap1, heap2;
			
			srand(time(NULL));
			int max_rand = 50;
			int n = rand() % 10 + 10;
			for (int i = 0; i < n; i++) {
				heap1.push(rand() % max_rand);
				heap2.push(rand() % max_rand);
			}
			heap1.pop_max();
			heap2.pop_max();
			heap2.pop_max();
			

			std::cout << "----------heap 1---------" << std::endl;
			heap1.print_structure();
			std::cout << "----------heap 2---------" << std::endl;
			heap2.print_structure();

			std::cout << "---heap 1 and 2 merged---" << std::endl;
			heap1.merge_with(&heap2);
			heap1.print_structure();
			
			system("pause");
		}

		else if(option == "create your own heap"){
			Menu sub_menu({ "add", "add random batch", "change key", "pop max", "help", "end"});
			Heap my_heap;
			while (true) {
				system("cls");

				std::cout << "========== Heap =========" << std::endl;
				my_heap.print_structure();
				sub_menu.show();
				std::string sub_option = sub_menu.get_selected_option();

				if (sub_option == "add") {
					std::cout << "enter new value to add" << std::endl;
					int val;
					std::cin >> val;
					if (input_valid(std::cin)) {
						my_heap.push(val);
						continue;
					}
					else
						std::cout << "invalid input!" << std::endl;			
				}

				else if (sub_option == "add random batch") {
					int n, r_max;
					bool err_ocurred = true;

					std::cout << "enter amount of values to add" << std::endl;
					std::cin >> n;
					if (input_valid(std::cin)) {
						
						std::cout << "enter max rand value" << std::endl;
						std::cin >> r_max;
						if (input_valid(std::cin)) {
							
							for (int i = 0; i < n; i++)
								my_heap.push(rand() % r_max + 1);							
							err_ocurred = false;
						}
					}

					if (err_ocurred) 
						std::cout << "invalid input!" << std::endl;
					else
						continue;
				}

				else if (sub_option == "change key") {
					int old_key, new_key;
					bool err_ocurred = true;

					std::cout << "enter key to change" << std::endl;
					std::cin >> old_key;
					if (input_valid(std::cin)) {

						std::cout << "enter new value" << std::endl;
						std::cin >> new_key;
						if (input_valid(std::cin)) {
							
							err_ocurred = false;
							if (my_heap.replace_key(old_key, new_key) == KEY_NOT_FOUND)
								std::cout << "entered key doesnt exist" << std::endl;			
						}
					}
					if (err_ocurred) 
						std::cout << "invalid input!" << std::endl;
					else
						continue;
					
				}

				else if (sub_option == "pop max") {
					int val = my_heap.pop_max();
					if (val != HEAP_EMPTY)
						std::cout<<"popped " << val << std::endl;
					else
						std::cout << "heap empty!" << std::endl;
				}

				else if (sub_option == "help") {

					std::cout << "------------------------- Help ------------------------" << std::endl;
					std::cout << "add - allows user to insert custom numbers into the heap" << std::endl << std::endl;
					
					std::cout << "add random batch - allows user to insert given amount of " << std::endl;
					std::cout << "random numbers into the heap" << std::endl <<std::endl;

					std::cout << "change key - allows user to change given key in the heap" << std::endl;
					std::cout << "if it exists" << std::endl << std::endl;

					std::cout << "pop max - displays highest number from the heap and" <<  std::endl;
					std::cout << "deletes it" << std::endl << std::endl;

					std::cout << "help - displays help :)" << std::endl << std::endl;

					std::cout << "end - returns to main menu" << std::endl;

					std::cout << "-------------------------------------------------------" << std::endl;
				}

				else if (sub_option == "end") {
					system("cls");
					break;
				}
				system("pause");
			}
		}
		else if (option == "about") {
			std::cout << "This program demonstrates FIBONACCI HEAP, an advanced data structure,"<<std::endl;
			std::cout << "which provides O(1) complexity for max elem search, insertion, merge," << std::endl;
			std::cout << "decrease-key and also O(Log n) for delete max" << std::endl;
			system("pause");
		}
		else if (option == "quit") {
			break;
		}
		
	}
	return 0;
}
