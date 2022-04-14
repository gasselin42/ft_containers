/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:39:43 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/14 15:55:15 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

#include <map>
#include <utility>
#include <iostream>

#define BRED	"\033[1;31m"
#define BGRN	"\033[1;32m"
#define BLUE	"\033[1;34m"
#define NC		"\033[0m"

void fill_ft_map(ft::map<int, std::string>& myMap)
{
	myMap.insert(ft::make_pair<int, std::string>(44, "root"));

	myMap.insert(ft::make_pair<int, std::string>(17, "left"));
	myMap.insert(ft::make_pair<int, std::string>(28, "left"));
	myMap.insert(ft::make_pair<int, std::string>(29, "left"));

	myMap.insert(ft::make_pair<int, std::string>(88, "right"));
	myMap.insert(ft::make_pair<int, std::string>(97, "right"));
	myMap.insert(ft::make_pair<int, std::string>(65, "right"));
	myMap.insert(ft::make_pair<int, std::string>(54, "right"));
	myMap.insert(ft::make_pair<int, std::string>(82, "right"));
	myMap.insert(ft::make_pair<int, std::string>(76, "right"));
	myMap.insert(ft::make_pair<int, std::string>(80, "right"));
	myMap.insert(ft::make_pair<int, std::string>(78, "right"));
}

void fill_std_map(std::map<int, std::string>& myMap)
{
	myMap.insert(std::make_pair<int, std::string>(44, "root"));

	myMap.insert(std::make_pair<int, std::string>(17, "left"));
	myMap.insert(std::make_pair<int, std::string>(28, "left"));
	myMap.insert(std::make_pair<int, std::string>(29, "left"));

	myMap.insert(std::make_pair<int, std::string>(88, "right"));
	myMap.insert(std::make_pair<int, std::string>(97, "right"));
	myMap.insert(std::make_pair<int, std::string>(65, "right"));
	myMap.insert(std::make_pair<int, std::string>(54, "right"));
	myMap.insert(std::make_pair<int, std::string>(82, "right"));
	myMap.insert(std::make_pair<int, std::string>(76, "right"));
	myMap.insert(std::make_pair<int, std::string>(80, "right"));
	myMap.insert(std::make_pair<int, std::string>(78, "right"));
}

void map_tests(void)
{
	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|      CONSTRUCTORS     |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       ITERATORS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|        CAPACITY       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|     ELEMENT ACCESS    |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       MODIFIERS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       OBSERVERS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       OPERATIONS      |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       ALLOCATOR       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";
}