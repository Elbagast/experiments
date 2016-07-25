#include "iterator_properties.h"
#include <string>
#include <array>
#include <vector>
#include <map>
#include <iostream>

void iterator_properties::test()
{
	std::cout << "Iterator Properties Test" << std::endl << std::endl;

	std::cout << "Implementation Details:" << std::endl;
	std::cout << "sizeof(size_t) = " << sizeof(std::size_t) << std::endl;
	std::cout << "sizeof(void*) = " << sizeof(void*) << std::endl;
	std::cout << "sizeof(int&) = " << sizeof(int&) << std::endl;
	std::cout << std::endl;
	std::cout << "Iterator Sizes:" << std::endl;
	std::cout << "std::string::iterator = " << sizeof(std::string::iterator) << std::endl;
	std::cout << "std::string::reverse_iterator = " << sizeof(std::string::reverse_iterator) << std::endl;
	std::cout << "std::wstring::iterator = " << sizeof(std::wstring::iterator) << std::endl;
	std::cout << "std::wstring::reverse_iterator = " << sizeof(std::wstring::reverse_iterator) << std::endl;
	std::cout << "std::vector<int>::iterator = " << sizeof(std::vector<int>::iterator) << std::endl;
	std::cout << "std::vector<int>::reverse_iterator = " << sizeof(std::vector<int>::reverse_iterator) << std::endl;
	std::cout << "std::vector<bool>::iterator = " << sizeof(std::vector<bool>::iterator) << std::endl;
	std::cout << "std::vector<bool>::reverse_iterator = " << sizeof(std::vector<bool>::reverse_iterator) << std::endl;
	std::cout << "std::array<int,5>::iterator = " << sizeof(std::array<int, 5>::iterator) << std::endl;
	std::cout << "std::array<int,5>::reverse_iterator = " << sizeof(std::array<int, 5>::reverse_iterator) << std::endl;
	std::cout << "std::map<int,std::string>::iterator = " << sizeof(std::map<int, std::string>::iterator) << std::endl;
	std::cout << "std::map<int,std::string>::reverse_iterator = " << sizeof(std::map<int, std::string>::reverse_iterator) << std::endl;

	std::cout << std::is_same<std::array<int, 5>::iterator, std::array<int, 4>::iterator>::value << std::endl;

	std::cout << "Why is an array iterator bigger?..." << std::endl;


	std::cout << "----------------------------------------" << std::endl;
}