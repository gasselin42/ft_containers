/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:39:43 by gasselin          #+#    #+#             */
/*   Updated: 2022/05/11 16:28:44 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

#include <map>
#include <utility>
#include <iostream>
#include <exception>

#define BRED	"\033[1;31m"
#define BGRN	"\033[1;32m"
#define BLUE	"\033[1;34m"
#define NC		"\033[0m"

#define KO		"\033[1;31mKO\033[0m"
#define PASSED	"\033[1;32mPASSED!\033[0m"

class myexception: public std::exception
{
  virtual const char* what() const throw()
  {
    return "\033[1;31mKO\033[0m";
  }
} ko;

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

void test_deep_copy_ft(ft::map<int, std::string>& myMap)
{
	(*(myMap.find(29))).second = "unleft";
	(*(myMap.find(44))).second = "unroot";
	(*(myMap.find(54))).second = "unright";
	(*(myMap.find(65))).second = "unright";
	(*(myMap.find(97))).second = "unright";
}

void test_deep_copy_stl(std::map<int, std::string>& myMap)
{
	(*(myMap.find(29))).second = "unleft";
	(*(myMap.find(44))).second = "unroot";
	(*(myMap.find(54))).second = "unright";
	(*(myMap.find(65))).second = "unright";
	(*(myMap.find(97))).second = "unright";
}

template <class Ta, class Tb>
bool iterate_maps(std::map<Ta, Tb>& stl_map, ft::map<Ta, Tb>& ft_map)
{
	typename std::map<Ta, Tb>::iterator stl_it;
	typename ft::map<Ta, Tb>::iterator ft_it;

	stl_it = stl_map.begin();
	ft_it = ft_map.begin();

	while (stl_it != stl_map.end())
	{
		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			return (false);
		stl_it++;
		ft_it++;
	}
	if (ft_it != ft_map.end())
		return (false);
	return (true);
}

template <class Ta, class Tb>
bool compare_maps(std::map<Ta, Tb>& stl_map, ft::map<Ta, Tb>& ft_map)
{
	if ((stl_map.empty() != ft_map.empty()) ||
		(stl_map.size() != ft_map.size()) ||
		(stl_map.max_size() != ft_map.max_size()))
		return (false);

	return (true);
}

template <class Ta, class Tb>
bool test_empty_map_iterators(ft::map<Ta, Tb>& ft_map)
{
	typename ft::map<Ta, Tb>::iterator ft_it1;
	typename ft::map<Ta, Tb>::iterator ft_it2;

	ft_it1 = ft_map.begin();
	ft_it2 = ft_map.end();

	if (&(*ft_it1) != &(*ft_it2))
		return (false);	

	return (true);
}

void map_tests(void)
{
	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|      CONSTRUCTORS     |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Constructor - Default " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		if (!compare_maps(stl_map, ft_map) || !test_empty_map_iterators(ft_map))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Constructor - Compare " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		if (!compare_maps(stl_map, ft_map) || !test_empty_map_iterators(ft_map))
			throw ko;

		std::map<int, std::string> stl_map2(stl_map.key_comp());
		ft::map<int, std::string> ft_map2(ft_map.key_comp());

		if (!compare_maps(stl_map2, ft_map2) || !test_empty_map_iterators(ft_map2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Constructor - Range " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		std::map<int, std::string> stl_map_range(stl_map.begin(), stl_map.end());
		ft::map<int, std::string> ft_map_range(ft_map.begin(), ft_map.end());

		if (!compare_maps(stl_map_range, ft_map_range) || !iterate_maps(stl_map_range, ft_map_range))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Constructor - Copy " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		std::map<int, std::string> stl_map_cpy(stl_map);
		ft::map<int, std::string> ft_map_cpy(ft_map);

		if (!compare_maps(stl_map_cpy, ft_map_cpy) || !iterate_maps(stl_map_cpy, ft_map_cpy))
			throw ko;

		test_deep_copy_stl(stl_map);
		test_deep_copy_ft(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		if (!compare_maps(stl_map_cpy, ft_map_cpy) || !iterate_maps(stl_map_cpy, ft_map_cpy))
			throw ko;
		
		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator = " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		std::map<int, std::string> stl_map_assign = stl_map;
		ft::map<int, std::string> ft_map_assign = ft_map;

		if (!compare_maps(stl_map_assign, ft_map_assign) || !iterate_maps(stl_map_assign, ft_map_assign))
			throw ko;

		test_deep_copy_stl(stl_map);
		test_deep_copy_ft(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		if (!compare_maps(stl_map_assign, ft_map_assign) || !iterate_maps(stl_map_assign, ft_map_assign))
			throw ko;
		
		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       ITERATORS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Begin " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		if (ft_map.begin() != ft_map.end())
			throw ko;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		std::map<int, std::string>::iterator stl_it = stl_map.begin();
		ft::map<int, std::string>::iterator ft_it = ft_map.begin();

		while (stl_it != stl_map.end())
		{
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
			stl_it++;
			ft_it++;
		}
		
		if (ft_it != ft_map.end())
			throw ko;

		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Begin - Const " << NC;
	try {
		const ft::map<int, std::string> ft_map_empty;
		
		if (ft_map_empty.begin() != ft_map_empty.end())
			throw ko;
			
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		const std::map<int, std::string> stl_map_begin(stl_map);
		const ft::map<int, std::string> ft_map_begin(ft_map);

		std::map<int, std::string>::const_iterator stl_it = stl_map_begin.begin();
		ft::map<int, std::string>::const_iterator ft_it = ft_map_begin.begin();

		while (stl_it != stl_map_begin.end())
		{
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
			stl_it++;
			ft_it++;
		}
		if (ft_it != ft_map_begin.end())
			throw ko;

		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "End " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		std::map<int, std::string>::iterator stl_it = stl_map.end();
		ft::map<int, std::string>::iterator ft_it = ft_map.end();

		while (stl_it != stl_map.begin())
		{
			--stl_it;
			--ft_it;
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
		}
			
		if (ft_it != ft_map.begin())
			throw ko;
			
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "End - Const " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		const std::map<int, std::string> stl_map_end(stl_map);
		const ft::map<int, std::string> ft_map_end(ft_map);

		std::map<int, std::string>::const_iterator stl_it = stl_map_end.end();
		ft::map<int, std::string>::const_iterator ft_it = ft_map_end.end();

		while (stl_it != stl_map_end.begin())
		{
			--stl_it;
			--ft_it;
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
		}

		if (ft_it != ft_map_end.begin())
			throw ko;
			
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Rbegin " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		if (ft_map.rbegin() != ft_map.rend())
			throw ko;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		std::map<int, std::string>::reverse_iterator stl_it = stl_map.rbegin();
		ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rbegin();

		while (stl_it != stl_map.rend())
		{
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
			stl_it++;
			ft_it++;
		}

		if (ft_it != ft_map.rend())
			throw ko;
			
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }


		
	std::cout << BLUE << "Rbegin - Const " << NC;
	try {
		const ft::map<int, std::string> ft_map_empty;
		
		if (ft_map_empty.rbegin() != ft_map_empty.rend())
			throw ko;
			
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		const std::map<int, std::string> stl_map_rbegin(stl_map);
		const ft::map<int, std::string> ft_map_rbegin(ft_map);

		std::map<int, std::string>::const_reverse_iterator stl_it = stl_map_rbegin.rbegin();
		ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map_rbegin.rbegin();

		while (stl_it != stl_map_rbegin.rend())
		{
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
			stl_it++;
			ft_it++;
		}
		
		if (ft_it != ft_map_rbegin.rend())
			throw ko;
			
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Rend " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		std::map<int, std::string>::reverse_iterator stl_it = stl_map.rend();
		ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rend();

		while (stl_it != stl_map.rbegin())
		{
			--stl_it;
			--ft_it;
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
		}

		if (ft_it != ft_map.rbegin())
			throw ko;
			
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Rend - Const " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		const std::map<int, std::string> stl_map_rend(stl_map);
		const ft::map<int, std::string> ft_map_rend(ft_map);

		std::map<int, std::string>::const_reverse_iterator stl_it = stl_map_rend.rend();
		ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map_rend.rend();

		while (stl_it != stl_map_rend.rbegin())
		{
			--stl_it;
			--ft_it;
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
		}

		if (ft_it != ft_map_rend.rbegin())
			throw ko;
			
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|        CAPACITY       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";


	
	std::cout << BLUE << "Empty " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		if (stl_map.empty() != ft_map.empty())
			throw ko;

		stl_map.insert(std::make_pair(50, "root"));
		ft_map.insert(ft::make_pair(50, "root"));

		if (stl_map.empty() != ft_map.empty())
			throw ko;

		stl_map.erase(50);
		ft_map.erase(50);

		if (stl_map.empty() != ft_map.empty())
			throw ko;
		
		stl_map.insert(std::make_pair(50, "root"));
		ft_map.insert(ft::make_pair(50, "root"));

		if (stl_map.empty() != ft_map.empty())
			throw ko;

		stl_map.clear();
		ft_map.clear();

		if (stl_map.empty() != ft_map.empty())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Size " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		if (stl_map.size() != ft_map.size())
			throw ko;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (stl_map.size() != ft_map.size())
			throw ko;

		stl_map.erase(50);
		ft_map.erase(50);

		if (stl_map.size() != ft_map.size())
			throw ko;
		
		stl_map.erase(stl_map.find(44), stl_map.end());
		ft_map.erase(ft_map.find(44), ft_map.end());

		if (stl_map.size() != ft_map.size())
			throw ko;

		stl_map.clear();
		ft_map.clear();

		if (stl_map.size() != ft_map.size())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }


		
	std::cout << BLUE << "Max size " << NC;
	try {
		std::map<unsigned char, std::string> stl_map1;
		ft::map<unsigned char, std::string> ft_map1;

		if (stl_map1.max_size() != ft_map1.max_size())
			throw ko;

		std::map<std::string, std::string> stl_map2;
		ft::map<std::string, std::string> ft_map2;

		if (stl_map2.max_size() != ft_map2.max_size())
			throw ko;

		std::map<size_t, char> stl_map3;
		ft::map<size_t, char> ft_map3;

		if (stl_map3.max_size() != ft_map3.max_size())
			throw ko;

		std::map<ptrdiff_t, bool> stl_map4;
		ft::map<ptrdiff_t, bool> ft_map4;

		if (stl_map4.max_size() != ft_map4.max_size())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|     ELEMENT ACCESS    |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";


	
	std::cout << BLUE << "Operator [] " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (stl_map[44] != ft_map[44])
			throw ko;

		if (stl_map.size() != ft_map.size())
			throw ko;

		stl_map[5] = stl_map[17];
		ft_map[5] = ft_map[17];

		if (stl_map.size() != ft_map.size())
			throw ko;

		if (stl_map[5] != ft_map[5])
			throw ko;

		std::map<int, std::string>::iterator stl_it = stl_map.begin();
		ft::map<int, std::string>::iterator ft_it = ft_map.begin();

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       MODIFIERS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Insert - Single element " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		std::pair<std::map<int, std::string>::iterator, bool> stl_pr;
		ft::pair<ft::map<int, std::string>::iterator, bool> ft_pr;
		
		stl_pr = stl_map.insert(std::make_pair(44, "root"));
		ft_pr = ft_map.insert(ft::make_pair(44, "root"));

		if (stl_pr.second != ft_pr.second || ((*(stl_pr.first)).first != (*(ft_pr.first)).first)
			|| ((*(stl_pr.first)).second != (*(ft_pr.first)).second))
			throw ko;

		ft::map<int, std::string>::iterator ft_it = ft_pr.first;
		if (++ft_it != ft_map.end())
			throw ko;

		stl_pr = stl_map.insert(std::make_pair(44, "root_clone"));
		ft_pr = ft_map.insert(ft::make_pair(44, "root_clone"));

		if (stl_pr.second != ft_pr.second || ((*(stl_pr.first)).first != (*(ft_pr.first)).first)
			|| ((*(stl_pr.first)).second != (*(ft_pr.first)).second))
			throw ko;

		ft_it = ft_pr.first;
		if (++ft_it != ft_map.end())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Insert - Hint " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		stl_map.insert(stl_map.find(88), std::make_pair(19, "left"));
		ft_map.insert(ft_map.find(88), ft::make_pair(19, "left"));

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		std::map<int, std::string>::iterator stl_it;
		ft::map<int, std::string>::iterator ft_it;

		stl_it = stl_map.insert(stl_map.find(88), std::make_pair(19, "left_clone"));
		ft_it = ft_map.insert(ft_map.find(88), ft::make_pair(19, "left_clone"));

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Insert - Range " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		std::map<int, std::string> stl_map_insert;
		ft::map<int, std::string> ft_map_insert;

		stl_map_insert.insert(stl_map.begin(), stl_map.end());
		ft_map_insert.insert(ft_map.begin(), ft_map.end());

		if (!compare_maps(stl_map_insert, ft_map_insert) || !iterate_maps(stl_map_insert, ft_map_insert))
			throw ko;

		stl_map_insert.clear();
		ft_map_insert.clear();

		stl_map_insert.insert(stl_map.find(44), stl_map.end());
		ft_map_insert.insert(ft_map.find(44), ft_map.end());

		if (!compare_maps(stl_map_insert, ft_map_insert) || !iterate_maps(stl_map_insert, ft_map_insert))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Erase - Position " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		stl_map.erase(stl_map.begin());
		ft_map.erase(ft_map.begin());

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		stl_map.erase(--(stl_map.end()));
		ft_map.erase(--(ft_map.end()));

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		stl_map.erase(stl_map.find(44));
		ft_map.erase(ft_map.find(44));

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Erase - Key " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		std::map<int, std::string>::size_type stl_st;
		ft::map<int, std::string>::size_type ft_st;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		stl_st = stl_map.erase(17);
		ft_st = ft_map.erase(17);

		if (stl_st != ft_st || !compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		stl_st = stl_map.erase(97);
		ft_map.erase(97);

		if (stl_st != ft_st || !compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		stl_st = stl_map.erase(44);
		ft_st = ft_map.erase(44);

		if (stl_st != ft_st || !compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		stl_st = stl_map.erase(50);
		ft_st = ft_map.erase(50);

		if (stl_st != ft_st || !compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Erase - Range " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		stl_map.erase(stl_map.begin(), stl_map.begin());
		ft_map.erase(ft_map.begin(), ft_map.begin());

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		stl_map.erase(stl_map.find(44), stl_map.find(80));
		ft_map.erase(ft_map.find(44), ft_map.find(80));

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		stl_map.erase(stl_map.begin(), stl_map.end());
		ft_map.erase(ft_map.begin(), ft_map.end());

		if (!compare_maps(stl_map, ft_map) || !test_empty_map_iterators(ft_map))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Swap " << NC;
	try {
		std::map<int, std::string> stl_map1;
		std::map<int, std::string> stl_map2;
		ft::map<int, std::string> ft_map1;
		ft::map<int, std::string> ft_map2;

		fill_std_map(stl_map1);
		fill_ft_map(ft_map1);

		stl_map1.swap(stl_map2);
		ft_map1.swap(ft_map2);

		if (!compare_maps(stl_map1, ft_map1) || !test_empty_map_iterators(ft_map1))
			throw ko;

		if (!compare_maps(stl_map2, ft_map2) || !iterate_maps(stl_map2, ft_map2))
			throw ko;

		fill_std_map(stl_map1);
		fill_ft_map(ft_map1);

		stl_map2.erase(stl_map2.find(29), stl_map2.find(82));
		ft_map2.erase(ft_map2.find(29), ft_map2.find(82));
		
		stl_map1.swap(stl_map2);
		ft_map1.swap(ft_map2);

		if (!compare_maps(stl_map1, ft_map1) || !iterate_maps(stl_map1, ft_map1))
			throw ko;

		if (!compare_maps(stl_map2, ft_map2) || !iterate_maps(stl_map2, ft_map2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }


	
	std::cout << BLUE << "Clear " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		stl_map.clear();
		ft_map.clear();

		if (!compare_maps(stl_map, ft_map) || !test_empty_map_iterators(ft_map))
			throw ko;

		stl_map.insert(std::make_pair<int, std::string>(50, "root"));
		ft_map.insert(ft::make_pair<int, std::string>(50, "root"));

		stl_map.clear();
		ft_map.clear();

		if (!compare_maps(stl_map, ft_map) || !test_empty_map_iterators(ft_map))
			throw ko;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		stl_map.clear();
		ft_map.clear();

		if (!compare_maps(stl_map, ft_map) || !test_empty_map_iterators(ft_map))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       OBSERVERS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Key_comp " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;
		
		size_t stl_count = 0;
		size_t ft_count = 0;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		std::map<int, std::string>::key_compare stl_comp = stl_map.key_comp();
		ft::map<int, std::string>::key_compare ft_comp = ft_map.key_comp();

		std::map<int, std::string>::iterator stl_it = stl_map.begin();
		ft::map<int, std::string>::iterator ft_it = ft_map.begin();

		while (stl_it != stl_map.end())
			if (stl_comp((*stl_it++).first, 80))
				stl_count++;

		while (ft_it != ft_map.end())
			if (ft_comp((*ft_it++).first, 80))
				ft_count++;

		if (stl_count != ft_count)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

		

	std::cout << BLUE << "Value_comp " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;
		
		size_t stl_count = 0;
		size_t ft_count = 0;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		std::pair<int, std::string> stl_pair = std::make_pair<int, std::string>(80, "root");
		ft::pair<int, std::string> ft_pair = ft::make_pair<int, std::string>(80, "root");

		std::map<int, std::string>::iterator stl_it = stl_map.begin();
		ft::map<int, std::string>::iterator ft_it = ft_map.begin();

		while (stl_it != stl_map.end())
			if (stl_map.value_comp()(*stl_it++, stl_pair))
				stl_count++;

		while (ft_it != ft_map.end())
			if (ft_map.value_comp()(*ft_it++, ft_pair))
				ft_count++;

		if (stl_count != ft_count)
			throw ko;
		
		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

		

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       OPERATIONS      |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Find " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		ft::map<int, std::string>::iterator it = ft_map.find(80);
		if (&(*it) != &(*ft_map.begin()) || &(*it) != &(*ft_map.end()))
			throw ko;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		it = (ft_map.insert(ft::make_pair(55, "right"))).first;
		stl_map.insert(std::make_pair(55, "right"));

		std::map<int, std::string>::iterator stl_it = stl_map.find(55);
		ft::map<int, std::string>::iterator ft_it = ft_map.find(55);

		if (&(*it) != &(*ft_it))
			throw ko;

		stl_it++;
		ft_it++;

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;
		
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Find - Const " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		const ft::map<int, std::string> ft_map_begin1(ft_map);

		ft::map<int, std::string>::const_iterator it = ft_map_begin1.find(80);
		if (&(*it) != &(*ft_map_begin1.begin()) || &(*it) != &(*ft_map_begin1.end()))
			throw ko;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		const std::map<int, std::string> stl_map_begin(stl_map);
		const ft::map<int, std::string> ft_map_begin2(ft_map);

		std::map<int, std::string>::const_iterator stl_it = stl_map_begin.find(54);
		ft::map<int, std::string>::const_iterator ft_it = ft_map_begin2.find(54);

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		stl_it++;
		ft_it++;

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	

	std::cout << BLUE << "Count " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		for (int i = 0; i < 100; i++)
			if (stl_map.count(i) != ft_map.count(i))
				throw ko;

		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Lower_bound " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		std::map<int, std::string>::iterator stl_it = stl_map.lower_bound(-5);
		ft::map<int, std::string>::iterator ft_it = ft_map.lower_bound(-5);

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		stl_it = stl_map.lower_bound(54);
		ft_it = ft_map.lower_bound(54);

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		ft_it = ft_map.lower_bound(100);

		if (ft_it != ft_map.end())
			throw ko;
		
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Lower_bound - Const " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		const std::map<int, std::string> stl_map_bound(stl_map);
		const ft::map<int, std::string> ft_map_bound(ft_map);

		std::map<int, std::string>::const_iterator stl_it = stl_map_bound.lower_bound(-5);
		ft::map<int, std::string>::const_iterator ft_it = ft_map_bound.lower_bound(-5);

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		stl_it = stl_map_bound.lower_bound(54);
		ft_it = ft_map_bound.lower_bound(54);

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		ft_it = ft_map_bound.lower_bound(100);

		if (ft_it != ft_map_bound.end())
			throw ko;

		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Upper_bound " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		std::map<int, std::string>::iterator stl_it = stl_map.upper_bound(-5);
		ft::map<int, std::string>::iterator ft_it = ft_map.upper_bound(-5);

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		stl_it = stl_map.upper_bound(54);
		ft_it = ft_map.upper_bound(54);

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		ft_it = ft_map.upper_bound(100);

		if (ft_it != ft_map.end())
			throw ko;
		
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Upper_bound - Const " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		const std::map<int, std::string> stl_map_bound(stl_map);
		const ft::map<int, std::string> ft_map_bound(ft_map);

		std::map<int, std::string>::const_iterator stl_it = stl_map_bound.upper_bound(-5);
		ft::map<int, std::string>::const_iterator ft_it = ft_map_bound.upper_bound(-5);

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		stl_it = stl_map_bound.upper_bound(54);
		ft_it = ft_map_bound.upper_bound(54);

		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			throw ko;

		ft_it = ft_map_bound.upper_bound(100);

		if (ft_it != ft_map_bound.end())
			throw ko;

		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Equal_range " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		std::pair<std::map<int, std::string>::iterator, std::map<int, std::string>::iterator> stl_pr;
		ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> ft_pr;

		stl_pr = stl_map.equal_range(5);
		ft_pr = ft_map.equal_range(5);

		if ((*(stl_pr.first)).first != (*(ft_pr.first)).first
			|| (*(stl_pr.first)).second != (*(ft_pr.first)).second
			|| (*(stl_pr.second)).first != (*(ft_pr.second)).first
			|| (*(stl_pr.second)).second != (*(ft_pr.second)).second)
			throw ko;

		stl_pr = stl_map.equal_range(50);
		ft_pr = ft_map.equal_range(50);

		if ((*(stl_pr.first)).first != (*(ft_pr.first)).first
			|| (*(stl_pr.first)).second != (*(ft_pr.first)).second
			|| (*(stl_pr.second)).first != (*(ft_pr.second)).first
			|| (*(stl_pr.second)).second != (*(ft_pr.second)).second)
			throw ko;

		ft_pr = ft_map.equal_range(100);

		if (ft_pr.first != ft_map.end() || ft_pr.second != ft_map.end())
			throw ko;
		
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Equal_range - Const " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		const std::map<int, std::string> stl_map_bound(stl_map);
		const ft::map<int, std::string> ft_map_bound(ft_map);

		std::pair<std::map<int, std::string>::const_iterator, std::map<int, std::string>::const_iterator> stl_pr;
		ft::pair<ft::map<int, std::string>::const_iterator, ft::map<int, std::string>::const_iterator> ft_pr;

		stl_pr = stl_map_bound.equal_range(5);
		ft_pr = ft_map_bound.equal_range(5);

		if ((*(stl_pr.first)).first != (*(ft_pr.first)).first
			|| (*(stl_pr.first)).second != (*(ft_pr.first)).second
			|| (*(stl_pr.second)).first != (*(ft_pr.second)).first
			|| (*(stl_pr.second)).second != (*(ft_pr.second)).second)
			throw ko;

		stl_pr = stl_map_bound.equal_range(50);
		ft_pr = ft_map_bound.equal_range(50);

		if ((*(stl_pr.first)).first != (*(ft_pr.first)).first
			|| (*(stl_pr.first)).second != (*(ft_pr.first)).second
			|| (*(stl_pr.second)).first != (*(ft_pr.second)).first
			|| (*(stl_pr.second)).second != (*(ft_pr.second)).second)
			throw ko;

		ft_pr = ft_map_bound.equal_range(100);

		if (ft_pr.first != ft_map_bound.end() || ft_pr.second != ft_map_bound.end())
			throw ko;

		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       ALLOCATOR       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Get_allocator " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		std::map<int, std::string> stl_map_alloc(stl_map.key_comp(), stl_map.get_allocator());
		ft::map<int, std::string> ft_map_alloc(ft_map.key_comp(), ft_map.get_allocator());

		if (!compare_maps(stl_map, ft_map) || !test_empty_map_iterators(ft_map))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|  NON-MEMBER FUNCTIONS |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Operator == " << NC;
	try {
		std::map<int, std::string> stl_map1;
		std::map<int, std::string> stl_map2;
		ft::map<int, std::string> ft_map1;
		ft::map<int, std::string> ft_map2;

		fill_std_map(stl_map1);
		fill_ft_map(ft_map1);

		fill_std_map(stl_map2);
		fill_ft_map(ft_map2);

		if ((stl_map1 == stl_map2) != (ft_map1 == ft_map2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator != " << NC;
	try {
		std::map<int, std::string> stl_map1;
		std::map<int, std::string> stl_map2;
		ft::map<int, std::string> ft_map1;
		ft::map<int, std::string> ft_map2;

		fill_std_map(stl_map1);
		fill_ft_map(ft_map1);

		fill_std_map(stl_map2);
		fill_ft_map(ft_map2);

		stl_map2.erase(stl_map2.find(44), stl_map2.find(82));
		ft_map2.erase(ft_map2.find(44), ft_map2.find(82));

		if ((stl_map1 != stl_map2) != (ft_map1 != ft_map2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator < " << NC;
	try {
		std::map<int, std::string> stl_map1;
		std::map<int, std::string> stl_map2;
		ft::map<int, std::string> ft_map1;
		ft::map<int, std::string> ft_map2;

		fill_std_map(stl_map1);
		fill_ft_map(ft_map1);

		fill_std_map(stl_map2);
		fill_ft_map(ft_map2);

		stl_map2.erase(stl_map2.find(44), stl_map2.find(82));
		ft_map2.erase(ft_map2.find(44), ft_map2.find(82));

		if ((stl_map1 < stl_map2) != (ft_map1 < ft_map2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator <= " << NC;
	try {
		std::map<int, std::string> stl_map1;
		std::map<int, std::string> stl_map2;
		ft::map<int, std::string> ft_map1;
		ft::map<int, std::string> ft_map2;

		fill_std_map(stl_map1);
		fill_ft_map(ft_map1);

		fill_std_map(stl_map2);
		fill_ft_map(ft_map2);

		stl_map2.erase(stl_map2.find(44), stl_map2.find(82));
		ft_map2.erase(ft_map2.find(44), ft_map2.find(82));

		if ((stl_map1 <= stl_map2) != (ft_map1 <= ft_map2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }




	std::cout << BLUE << "Operator > " << NC;
	try {
		std::map<int, std::string> stl_map1;
		std::map<int, std::string> stl_map2;
		ft::map<int, std::string> ft_map1;
		ft::map<int, std::string> ft_map2;

		fill_std_map(stl_map1);
		fill_ft_map(ft_map1);

		fill_std_map(stl_map2);
		fill_ft_map(ft_map2);

		stl_map2.erase(stl_map2.find(44), stl_map2.find(82));
		ft_map2.erase(ft_map2.find(44), ft_map2.find(82));

		if ((stl_map1 > stl_map2) != (ft_map1 > ft_map2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }




	std::cout << BLUE << "Operator >= " << NC;
	try {
		std::map<int, std::string> stl_map1;
		std::map<int, std::string> stl_map2;
		ft::map<int, std::string> ft_map1;
		ft::map<int, std::string> ft_map2;

		fill_std_map(stl_map1);
		fill_ft_map(ft_map1);

		fill_std_map(stl_map2);
		fill_ft_map(ft_map2);

		stl_map2.erase(stl_map2.find(44), stl_map2.find(82));
		ft_map2.erase(ft_map2.find(44), ft_map2.find(82));

		if ((stl_map1 >= stl_map2) != (ft_map1 >= ft_map2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Swap " << NC;
	try {
		std::map<int, std::string> stl_map1;
		std::map<int, std::string> stl_map2;
		ft::map<int, std::string> ft_map1;
		ft::map<int, std::string> ft_map2;

		fill_std_map(stl_map1);
		fill_ft_map(ft_map1);

		swap(stl_map1, stl_map2);
		swap(ft_map1, ft_map2);

		if (!compare_maps(stl_map1, ft_map1) || !test_empty_map_iterators(ft_map1))
			throw ko;

		if (!compare_maps(stl_map2, ft_map2) || !iterate_maps(stl_map2, ft_map2))
			throw ko;

		fill_std_map(stl_map1);
		fill_ft_map(ft_map1);

		stl_map2.erase(stl_map2.find(29), stl_map2.find(82));
		ft_map2.erase(ft_map2.find(29), ft_map2.find(82));
		
		swap(stl_map1, stl_map2);
		swap(ft_map1, ft_map2);

		if (!compare_maps(stl_map1, ft_map1) || !iterate_maps(stl_map1, ft_map1))
			throw ko;

		if (!compare_maps(stl_map2, ft_map2) || !iterate_maps(stl_map2, ft_map2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

}
