/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:39:43 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/14 16:44:28 by gasselin         ###   ########.fr       */
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

template <class Ta, class Tb>
bool compare_maps(std::map<Ta, Tb>& stl_map, ft::map<Ta, Tb>& ft_map)
{
	bool passed = true;
	if (stl_map.empty() != ft_map.empty())
	{
		passed = false;
		std::cout << BRED << "map::empty don't match" << NC << "\n";
	}

	if (stl_map.size() != ft_map.size())
	{
		passed = false;
		std::cout << BRED << "map::size don't match" << NC << "\n";
	}

	if (stl_map.max_size() != ft_map.max_size())
	{
		passed = false;
		std::cout << BRED << "map::max_size don't match" << NC << "\n";
	}
	
	if (!passed)
		return (passed);
	else
	{
		typename std::map<Ta, Tb>::const_iterator stl_it;
		typename ft::map<Ta, Tb>::const_iterator ft_it;

		stl_it = stl_map.begin();
		ft_it = ft_map.begin();

		while (stl_it != stl_map.end())
		{
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			{
				std::cout << BRED << "Map contents don't match" << NC << "\n";
				return (false);
			}
			stl_it++;
			ft_it++;
		}
	}

	std::cout << BGRN << "PASSED!" << NC << "\n";
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