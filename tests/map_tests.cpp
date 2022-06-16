/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:39:43 by gasselin          #+#    #+#             */
/*   Updated: 2022/06/16 13:01:52 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.hpp"

#include <map>
#include <utility>
#include <iostream>
#include <exception>

#define T1 int
#define T2 std::string

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

std::string s_string[100] = {                                                                   \
        "QExoqp0nICr0sXsHqty2", "naax9QcpJhvaL7DezsNQ", "25ZTtB6wbptfbxM8AvHB",                    \
        "tShYNtc0MkdjqLrOatgz", "7Z3kf1Qec0NnsLSEpbOt", "WhkSNrKJC966fvjZ2Or1",                    \
        "8vlxlFRRgW7yYj4GO7dt", "5sq1aoT8zP0HaHj3nFOK", "61Dv31GYZhkgjKCErpng",                    \
        "l0IIcWWHhOcPzoxEamQM", "bE1RYclskwXlhCm46YFs", "kXeoi5qz94JYPqSDTs79",                    \
        "TFsQP1dz8VVos9KzUpY0", "b3wYQR7An193gjgYuRj3", "xSmyNsnSJ47jLqrvbpyr",                    \
        "guAIP2Wq43Gf8VhHsyu5", "yT6c2loPebHovnq9BQog", "3qvU1xcVm2g1DKFDlqh4",                    \
        "L0q8RR9P41VD4sVjdnWl", "YdjESsIZM4b1oGQPjpBe", "l1ZVQbWKw7brHUSimJgq",                    \
        "xdn0cf4vqRzpfXWtl10G", "lYnZvpqaV0s8DowMZwzV", "8P1cyKrwJNLoJyvLjYqO",                    \
        "4MhOXNbAX23CEijO5cRT", "tHe3miAwCOVQbuoLaEP2", "l6uNLsc8fiLl3eWoG6j6",                    \
        "477xt6l0lph9ALQdr4HX", "D9UJNe4s8YF02LhrwOdl", "dLCisBNOdE8yugntu6cj",                    \
        "uvg6KqtcgduR31n3ajsv", "wbiAcjgojb9JOagZwyMn", "ATZKCzaPOqgkhPjwuGlf",                    \
        "MOhaJs56yjOw8f6nLPRA", "0gyB2Tr42v6awMw2nK7J", "e6GsiLFUuoDpVFEhJKZ1",                    \
        "z0jXAhiV9keBsaLOY0Xf", "P68p2ZAosHJdmoZh1C7N", "Pu3EuZVeY0TCO3ojdK0t",                    \
        "z7jCHMooHCS73M8GygKB", "uT4KoK83JrZxZjkul7ty", "g8gfrZoY5XwfzRusvHvv",                    \
        "7PGmkM0OSRnYREt9mFIP", "q1od7mBIpPEsCtpF9kdw", "XQo0LWId5TdZnLnpUNOb",                    \
        "U0m1R0kFFhAFyS6hmHHw", "K0lPKfxJxIOnE8QB90xn", "cZ5xyQifMJhrKxqBK9A7",                    \
        "cFBiwjfYw7Js6qEGy5Kt", "1tW0KWfXxeFO69tByqcE", "3Fvq9NxBrhPXHe0IlIVx",                    \
        "MSRDjdFRvHAhFGhiMtDe", "zGm2joMh71jQkYzg5L4V", "Mq4RRaeLvSAO0z2ibp8Q",                    \
        "WnLFYnQKP8TNJkqVVbUg", "E98UphbbVSzrW5Mzurmg", "F8HRxeEcaTZDkFPkioij",                    \
        "jmUVl4Q8X5BwVNzXN219", "n7Xp4w4FwzGKit7AI4SO", "4MxXYr6rKOcXLt9UkVd2",                    \
        "4RVTDsADtRyboaai9d29", "XaSqsrrtdhAfFoJIc5KK", "9Z9jdVCrTT09bg348ceb",                    \
        "I6uqLG9dO5mfNdSMwOYm", "UwMTzJPlbnhgwbHpDi6w", "DebjMP9afncYE6GhhO00",                    \
        "YGPuscYDiGfAjY1UWST0", "K6gbvgGjVZgEFUDlkdSk", "8xCBPI0w6TpC0RA62c2W",                    \
        "fYMxkNwmKg3moP8KvD9v", "QpPdhwhEYjIugg3OPcPH", "qQBXjSn43I3EMP54SyxZ",                    \
        "7qvdKwoW1CQEZTWPvuSC", "rCT212rdYO0zTGHXesKg", "dBHvlHsBwcR9MkkenYYG",                    \
        "NQiSlergqR8fVbOeivLj", "xYVqsV147UIe7jVBVwXo", "tcxayO4DdEJ885TbqUMy",                    \
        "9TGSMTD8U8ksRpHqq0cL", "TIJ16jCv9BSUiWvhbF9T", "BM9GL2ig1hePkA6lM6Ck",                    \
        "TfJTYB9JQMU6CGcYg20Q", "Fg6e5YT2FQbpTZNTDqdo", "LI5q6ml40MeE9H1dPb93",                    \
        "OaxJUSm3nYN9Y8Ela7sS", "BgBeODAwXz7xJo50Rwqd", "xdkgKj1dEoJ6zuVhkvvo",                    \
        "olIewtUEvXJgs1lB9bCn", "dTsPDS0x2uXtcgOIJHb8", "DYvJ2phLppGNZKboTBrd",                    \
        "DjNFMtt9PxkzqvWBHI6j", "1Z3YkeTFlPniKnzFhzgu", "76XqQg6hqMf5IXxKPOEs",                    \
        "gzaapTWW7i9EZjjzLeK6", "YvY4aQFHgAuagn4dFLO1", "eGR6Dtv7LW75qlV5Fkik",                    \
        "oiahfuhiowIEQTHGUIOO", "oOIFoinfniAIOhhinIo9", "038egfjnfpIOPejh9o0n",                    \
        "uoh89fUBkOfoiabjk22l"                                                                     \
    };

template < class Key, class T >
void fill_map(NAMESPACE::map<Key, T>& m)
{
	for (int i = 0; i < 100; i++)
		m.insert(NAMESPACE::make_pair<Key, T>(i, s_string[i]));
}

template < class Key, class T >
void test_deep_copy(NAMESPACE::map<Key, T>& m)
{
	(*(m.find(29))).second = "BST";
	(*(m.find(44))).second = "BST";
	(*(m.find(54))).second = "BST";
	(*(m.find(65))).second = "BST";
	(*(m.find(97))).second = "BST";
}

template <class Key, class T>
void iterate_maps(NAMESPACE::map<Key, T>& m)
{
	typename NAMESPACE::map<Key, T>::iterator it;

	it = m.begin();

	if (it != m.end())
	{
		std::cout << "Iteration : ";
		for (; it != m.end(); it++)
			std::cout << "[" << (*it).first << "," << (*it).second << "]; ";
	}
	else
		std::cout << "Empty map";
	std::cout << "\n";
}

template <class Key, class T>
void iterate_maps(const NAMESPACE::map<Key, T>& m)
{
	typename NAMESPACE::map<Key, T>::const_iterator it;

	it = m.begin();

	if (it != m.end())
	{
		std::cout << "Iteration : ";
		for (; it != m.end(); it++)
			std::cout << "[" << (*it).first << "," << (*it).second << "]; ";
	}
	else
		std::cout << "Empty map";
	std::cout << "\n";
}

template <class Key, class T>
void reverse_iterate_maps(NAMESPACE::map<Key, T>& m)
{
	typename NAMESPACE::map<Key, T>::reverse_iterator it;

	it = m.rbegin();

	if (it != m.rend())
	{
		std::cout << "Iteration : ";
		for (; it != m.rend(); it++)
			std::cout << "[" << (*it).first << "," << (*it).second << "]; ";
	}
	else
		std::cout << "Empty map";
	std::cout << "\n";
}

template <class Key, class T>
void reverse_iterate_maps(const NAMESPACE::map<Key, T>& m)
{
	typename NAMESPACE::map<Key, T>::const_reverse_iterator it;

	it = m.rbegin();

	if (it != m.rend())
	{
		std::cout << "Iteration : ";
		for (; it != m.rend(); it++)
			std::cout << "[" << (*it).first << "," << (*it).second << "]; ";
	}
	else
		std::cout << "Empty map";
	std::cout << "\n";
}

template <class Key, class T>
void compare_maps(NAMESPACE::map<Key, T>& m)
{
	std::cout << "Size : " << m.size() << " ";
	std::cout << "Max size : " << m.max_size() << "\n";
}

template <class Key, class T>
void compare_maps(const NAMESPACE::map<Key, T>& m)
{
	std::cout << "Size : " << m.size() << " ";
	std::cout << "Max size : " << m.max_size() << "\n";
}

int main(void)
{
	std::cout << "-------------------------" << "\n";
	std::cout << "|      CONSTRUCTORS     |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Constructor - Default \n";
	{
		NAMESPACE::map<T1, T2> m;
		compare_maps(m);
		iterate_maps(m);
	}

	std::cout << "\n";

	std::cout << "Constructor - Compare \n";
	{
		NAMESPACE::map<T1, T2> m;

		compare_maps(m);
		iterate_maps(m);

		NAMESPACE::map<T1, T2> m2(m.key_comp());

		compare_maps(m2);
		iterate_maps(m2);
	}

	std::cout << "\n";

	std::cout << "Constructor - Range \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		compare_maps(m);
		iterate_maps(m);

		NAMESPACE::map<T1, T2> m_range(m.begin(), m.end());

		compare_maps(m_range);
		iterate_maps(m_range);
	}

	std::cout << "\n";

	std::cout << "Constructor - Copy \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		NAMESPACE::map<T1, T2> m_cpy(m);

		compare_maps(m_cpy);
		iterate_maps(m_cpy);

		test_deep_copy(m);

		compare_maps(m);
		iterate_maps(m);

		compare_maps(m_cpy);
		iterate_maps(m_cpy);
	}

	std::cout << "\n";

	std::cout << "Operator = \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);
		
		NAMESPACE::map<T1, T2> m_op = m;

		compare_maps(m_op);
		iterate_maps(m_op);

		test_deep_copy(m);
		
		compare_maps(m);
		iterate_maps(m);

		compare_maps(m_op);
		iterate_maps(m_op);
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       ITERATORS       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Begin \n";
	{
		NAMESPACE::map<T1, T2> m;

		if (m.begin() != m.end())
			std::cout << "KO\n";

		fill_map(m);

		NAMESPACE::map<T1, T2>::iterator it = m.begin();

		std::cout << "Begin = [" << (*it).first << "," << (*it).second << "]\n";

		iterate_maps(m);
	}

	std::cout << "\n";

	std::cout << "Begin - Const \n";
	{
		const NAMESPACE::map<T1, T2> m_empty;
		
		if (m_empty.begin() != m_empty.end())
			std::cout << "KO\n";
			
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_begin(m);

		NAMESPACE::map<T1, T2>::const_iterator it = m_begin.begin();

		std::cout << "Begin = [" << (*it).first << "," << (*it).second << "]\n";

		iterate_maps(m_begin);
	}

	std::cout << "\n";

	std::cout << "End \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		NAMESPACE::map<T1, T2>::iterator it = m.end();

		--it;
		for (; it != m.begin(); it--)
			std::cout << "[" << (*it).first << "," << (*it).second << "]; ";
		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "End - Const \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_end(m);

		NAMESPACE::map<T1, T2>::const_iterator it = m_end.end();

		--it;
		for (; it != m_end.begin(); it--)
			std::cout << "[" << (*it).first << "," << (*it).second << "]; ";
		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Rbegin \n";
	{
		NAMESPACE::map<T1, T2> m;

		if (m.rbegin() != m.rend())
			std::cout << "KO\n";

		fill_map(m);

		NAMESPACE::map<T1, T2>::reverse_iterator it = m.rbegin();

		std::cout << "Rbegin = [" << (*it).first << "," << (*it).second << "]\n";

		reverse_iterate_maps(m);
	}

	std::cout << "\n";
		
	std::cout << "Rbegin - Const \n";
	{
		const NAMESPACE::map<T1, T2> m_empty;
		
		if (m_empty.rbegin() != m_empty.rend())
			std::cout << "KO\n";
			
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_rbegin(m);

		NAMESPACE::map<T1, T2>::const_reverse_iterator it = m_rbegin.rbegin();

		std::cout << "Rbegin = [" << (*it).first << "," << (*it).second << "]\n";

		reverse_iterate_maps(m_rbegin);
	}

	std::cout << "\n";

	std::cout << "Rend \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		NAMESPACE::map<T1, T2>::reverse_iterator it = m.rend();

		it--;
		for (; it != m.rbegin(); it--)
			std::cout << "[" << (*it).first << "," << (*it).second << "]; ";
		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Rend - Const \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_rend(m);

		NAMESPACE::map<T1, T2>::const_reverse_iterator it = m_rend.rend();

		it--;
		for (; it != m_rend.rbegin(); it--)
			std::cout << "[" << (*it).first << "," << (*it).second << "]; ";
		std::cout << "\n";
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|        CAPACITY       |" << "\n";
	std::cout << "-------------------------" << "\n\n";


	
	std::cout << "Empty \n";
	{
		NAMESPACE::map<T1, T2> m;

		std::cout << (m.empty() ? "True" : "False") << "\n";

		m.insert(NAMESPACE::make_pair(50, "root"));

		std::cout << (m.empty() ? "True" : "False") << "\n";

		m.erase(50);

		std::cout << (m.empty() ? "True" : "False") << "\n";
		
		m.insert(NAMESPACE::make_pair(50, "root"));

		std::cout << (m.empty() ? "True" : "False") << "\n";

		m.clear();

		std::cout << (m.empty() ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Size \n";
	{
		NAMESPACE::map<T1, T2> m;

		std::cout << "Size : " << m.size() << "\n";

		fill_map(m);

		std::cout << "Size : " << m.size() << "\n";

		m.erase(50);

		std::cout << "Size : " << m.size() << "\n";
		
		m.erase(m.find(44), m.end());

		std::cout << "Size : " << m.size() << "\n";

		m.clear();

		std::cout << "Size : " << m.size() << "\n";
	}

	std::cout << "\n";
		
	std::cout << "Max size \n";
	{
		NAMESPACE::map<unsigned char, std::string> m1;

		std::cout << "Max size <unsigned char, std::string> : " << m1.max_size() << "\n";

		NAMESPACE::map<std::string, std::string> m2;

		std::cout << "Max size <std::string, std::string> : " << m2.max_size() << "\n";

		NAMESPACE::map<size_t, char> m3;

		std::cout << "Max size <size_t, char> : " << m3.max_size() << "\n";

		NAMESPACE::map<ptrdiff_t, bool> m4;

		std::cout << "Max size <ptrdiff_t, bool> : " << m4.max_size() << "\n";
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|     ELEMENT ACCESS    |" << "\n";
	std::cout << "-------------------------" << "\n\n";


	
	std::cout << "Operator [] \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		std::cout << "Iteration : ";
		for (int i = 0; i < 100; i++)
			std::cout << "[" << i << "] = " << m[i] << "; ";
		std::cout << "\n";

		m[5] = m[17];
		
		std::cout << "[5] = " << m[5] << "\n";

		m[101] = m[50];

		compare_maps(m);
		iterate_maps(m);
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       MODIFIERS       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Insert - Single element \n";
	{
		NAMESPACE::map<T1, T2> m;

		NAMESPACE::pair<NAMESPACE::map<T1, T2>::iterator, bool> pr;
		
		pr = m.insert(NAMESPACE::make_pair(44, s_string[44]));

		std::cout << "[" << (*(pr.first)).first << "," << (*(pr.first)).second << "] ";
		std::cout << (pr.second ? "True" : "False") << "\n";

		NAMESPACE::map<T1, T2>::iterator it = pr.first;
		if (++it != m.end())
			std::cout << "KO\n";

		pr = m.insert(NAMESPACE::make_pair(44, s_string[50]));

		std::cout << "[" << (*(pr.first)).first << "," << (*(pr.first)).second << "] ";
		std::cout << (pr.second ? "True" : "False") << "\n";

		it = pr.first;
		if (++it != m.end())
			std::cout << "KO\n";
	}

	std::cout << "\n";

	std::cout << "Insert - Hint \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		m.insert(m.find(1), NAMESPACE::make_pair(150, "end"));

		compare_maps(m);
		iterate_maps(m);

		NAMESPACE::map<T1, T2>::iterator it;

		it = m.insert(m.find(50), NAMESPACE::make_pair(150, "end_clone"));

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";
	}

	std::cout << "\n";

	std::cout << "Insert - Range \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		NAMESPACE::map<T1, T2> m_insert;

		m_insert.insert(m.begin(), m.end());

		compare_maps(m);
		iterate_maps(m);

		m_insert.clear();

		m_insert.insert(m.find(25), m.end());

		compare_maps(m);
		iterate_maps(m);
	}

	std::cout << "\n";

	std::cout << "Erase - Position \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		m.erase(m.begin());

		compare_maps(m);
		iterate_maps(m);

		m.erase(--(m.end()));

		compare_maps(m);
		iterate_maps(m);

		m.erase(m.find(44));

		compare_maps(m);
		iterate_maps(m);
	}

	std::cout << "\n";

	std::cout << "Erase - Key \n";
	{
		NAMESPACE::map<T1, T2> m;

		NAMESPACE::map<T1, T2>::size_type st;

		fill_map(m);

		st = m.erase(17);

		std::cout << st << "\n";
		compare_maps(m);
		iterate_maps(m);

		st = m.erase(100);

		std::cout << st << "\n";
		compare_maps(m);
		iterate_maps(m);

		st = m.erase(99);

		std::cout << st << "\n";
		compare_maps(m);
		iterate_maps(m);

		st = m.erase(17);

		std::cout << st << "\n";
		compare_maps(m);
		iterate_maps(m);
	}

	std::cout << "\n";

	std::cout << "Erase - Range \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		m.erase(m.begin(), m.begin());

		compare_maps(m);
		iterate_maps(m);

		m.erase(m.find(44), m.find(80));

		compare_maps(m);
		iterate_maps(m);

		m.erase(m.begin(), m.end());

		compare_maps(m);
		iterate_maps(m);
	}

	std::cout << "\n";

	std::cout << "Swap \n";
	{
		NAMESPACE::map<T1, T2> m1;
		NAMESPACE::map<T1, T2> m2;

		fill_map(m1);

		m1.swap(m2);

		compare_maps(m1);
		iterate_maps(m1);

		compare_maps(m2);
		iterate_maps(m2);

		fill_map(m1);

		m2.erase(m2.find(29), m2.find(82));
		
		m1.swap(m2);

		compare_maps(m1);
		iterate_maps(m1);

		compare_maps(m2);
		iterate_maps(m2);
	}

	std::cout << "\n";
	
	std::cout << "Clear \n";
	{
		NAMESPACE::map<T1, T2> m;

		m.clear();

		compare_maps(m);
		iterate_maps(m);

		m.insert(NAMESPACE::make_pair<T1, T2>(50, "root"));

		m.clear();

		compare_maps(m);
		iterate_maps(m);

		fill_map(m);

		m.clear();

		compare_maps(m);
		iterate_maps(m);
	}

	

	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       OBSERVERS       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Key_comp \n";
	{
		NAMESPACE::map<T1, T2> m;
		
		size_t count = 0;

		fill_map(m);

		NAMESPACE::map<T1, T2>::key_compare _comp = m.key_comp();

		NAMESPACE::map<T1, T2>::iterator it = m.begin();

		while (it != m.end())
			if (_comp((*it++).first, 42))
				count++;

		std::cout << count << "\n";
	}

	std::cout << "\n";

	std::cout << "Value_comp \n";
	{
		NAMESPACE::map<T1, T2> m;
		
		size_t count = 0;

		fill_map(m);

		NAMESPACE::pair<T1, T2> pr = NAMESPACE::make_pair<T1, T2>(42, s_string[42]);

		NAMESPACE::map<T1, T2>::iterator it = m.begin();

		while (it != m.end())
			if (m.value_comp()(*it++, pr))
				count++;

		std::cout << count << "\n";
	}

		

	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       OPERATIONS      |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Find \n";
	{
		NAMESPACE::map<T1, T2> m;

		NAMESPACE::map<T1, T2>::iterator it = m.find(42);
		if (&(*it) != &(*m.begin()) || &(*it) != &(*m.end()))
			std::cout << "KO\n";

		fill_map(m);
		m.erase(42);

		it = (m.insert(NAMESPACE::make_pair(42, s_string[42]))).first;

		NAMESPACE::map<T1, T2>::iterator it2 = m.find(42);

		std::cout << "&(*it) == &(*it2) : " << ((&(*it) == &(*it2)) ? "True" : "False") << "\n";

		it++;

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";
	}

	std::cout << "\n";

	std::cout << "Find - Const \n";
	{
		NAMESPACE::map<T1, T2> m;

		const NAMESPACE::map<T1, T2> m_begin1(m);

		NAMESPACE::map<T1, T2>::const_iterator it = m_begin1.find(42);
		if (&(*it) != &(*m_begin1.begin()) || &(*it) != &(*m_begin1.end()))
			std::cout << "KO\n";

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_begin2(m);

		it = m_begin2.find(54);

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";

		it++;

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";
	}

	std::cout << "\n";

	std::cout << "Count \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		for (int i = 0; i < 150; i++)
			std::cout << m.count(i) << " ";
	}

	std::cout << "\n";

	std::cout << "Lower_bound \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		NAMESPACE::map<T1, T2>::iterator it = m.lower_bound(-5);

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";

		it = m.lower_bound(42);

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";

		it = m.lower_bound(111);

		if (it != m.end())
			std::cout << "KO\n";
	}

	std::cout << "\n";

	std::cout << "Lower_bound - Const \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_bound(m);

		NAMESPACE::map<T1, T2>::const_iterator it = m_bound.lower_bound(-5);

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";

		it = m_bound.lower_bound(42);

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";

		it = m_bound.lower_bound(111);

		if (it != m_bound.end())
			std::cout << "KO\n";
	}

	std::cout << "\n";

	std::cout << "Upper_bound \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		NAMESPACE::map<T1, T2>::iterator it = m.upper_bound(-5);

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";

		it = m.upper_bound(42);

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";

		it = m.upper_bound(111);

		if (it != m.end())
			std::cout << "KO\n";
	}

	std::cout << "\n";

	std::cout << "Upper_bound - Const \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_bound(m);

		NAMESPACE::map<T1, T2>::const_iterator it = m_bound.upper_bound(-5);

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";

		it = m_bound.upper_bound(42);

		std::cout << "[" << (*it).first << "," << (*it).second << "]\n";

		it = m_bound.upper_bound(111);

		if (it != m_bound.end())
			std::cout << "KO\n";
	}

	std::cout << "\n";

	std::cout << "Equal_range \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		NAMESPACE::pair<NAMESPACE::map<T1, T2>::iterator, NAMESPACE::map<T1, T2>::iterator> pr;

		pr = m.equal_range(5);

		std::cout << "[" << (*(pr.first)).first << "," << (*(pr.first)).second << "]\n";
		std::cout << "[" << (*(pr.second)).first << "," << (*(pr.second)).second << "]\n";

		pr = m.equal_range(42);

		std::cout << "[" << (*(pr.first)).first << "," << (*(pr.first)).second << "]\n";
		std::cout << "[" << (*(pr.second)).first << "," << (*(pr.second)).second << "]\n";

		pr = m.equal_range(111);

		if (pr.first != m.end() || pr.second != m.end())
			std::cout << "KO\n";
	}

	std::cout << "\n";

	std::cout << "Equal_range - Const \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_bound(m);

		NAMESPACE::pair<NAMESPACE::map<T1, T2>::const_iterator, NAMESPACE::map<T1, T2>::const_iterator> pr;

		pr = m_bound.equal_range(5);

		std::cout << "[" << (*(pr.first)).first << "," << (*(pr.first)).second << "]\n";
		std::cout << "[" << (*(pr.second)).first << "," << (*(pr.second)).second << "]\n";

		pr = m_bound.equal_range(42);

		std::cout << "[" << (*(pr.first)).first << "," << (*(pr.first)).second << "]\n";
		std::cout << "[" << (*(pr.second)).first << "," << (*(pr.second)).second << "]\n";

		pr = m_bound.equal_range(111);

		if (pr.first != m_bound.end() || pr.second != m_bound.end())
			std::cout << "KO\n";
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       ALLOCATOR       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Get_allocator \n";
	{
		NAMESPACE::map<T1, T2> m;

		NAMESPACE::map<T1, T2> m_alloc(m.key_comp(), m.get_allocator());

		compare_maps(m_alloc);
		iterate_maps(m_alloc);
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|  NON-MEMBER FUNCTIONS |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Operator == \n";
	{
		NAMESPACE::map<T1, T2> m1;
		NAMESPACE::map<T1, T2> m2;

		fill_map(m1);
		fill_map(m2);

		std::cout << "m1 == m2 " << ((m1 == m2) ? "True" : "False") << "\n";

		m2.erase(m2.find(44), m2.find(82));
		
		std::cout << "m1 == m2 " << ((m1 == m2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator != \n";
	{
		NAMESPACE::map<T1, T2> m1;
		NAMESPACE::map<T1, T2> m2;

		fill_map(m1);
		fill_map(m2);

		std::cout << "m1 != m2 " << ((m1 != m2) ? "True" : "False") << "\n";

		m2.erase(m2.find(44), m2.find(82));

		std::cout << "m1 != m2 " << ((m1 != m2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator < \n";
	{
		NAMESPACE::map<T1, T2> m1;
		NAMESPACE::map<T1, T2> m2;

		fill_map(m1);
		fill_map(m2);

		std::cout << "m1 < m2 " << ((m1 < m2) ? "True" : "False") << "\n";

		m2.erase(m2.find(44), m2.find(82));

		std::cout << "m1 < m2 " << ((m1 < m2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator <= \n";
	{
		NAMESPACE::map<T1, T2> m1;
		NAMESPACE::map<T1, T2> m2;

		fill_map(m1);
		fill_map(m2);

		std::cout << "m1 <= m2 " << ((m1 <= m2) ? "True" : "False") << "\n";

		m2.erase(m2.find(44), m2.find(82));

		std::cout << "m1 <= m2 " << ((m1 <= m2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator > \n";
	{
		NAMESPACE::map<T1, T2> m1;
		NAMESPACE::map<T1, T2> m2;

		fill_map(m1);
		fill_map(m2);

		std::cout << "m1 > m2 " << ((m1 > m2) ? "True" : "False") << "\n";

		m2.erase(m2.find(44), m2.find(82));

		std::cout << "m1 > m2 " << ((m1 > m2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator >= \n";
	{
		NAMESPACE::map<T1, T2> m1;
		NAMESPACE::map<T1, T2> m2;

		fill_map(m1);
		fill_map(m2);

		std::cout << "m1 >= m2 " << ((m1 >= m2) ? "True" : "False") << "\n";

		m2.erase(m2.find(44), m2.find(82));

		std::cout << "m1 >= m2 " << ((m1 >= m2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Swap \n";
	{
		NAMESPACE::map<T1, T2> m1;
		NAMESPACE::map<T1, T2> m2;

		fill_map(m1);

		swap(m1, m2);

		compare_maps(m1);
		iterate_maps(m1);

		compare_maps(m2);
		iterate_maps(m2);

		fill_map(m1);

		m2.erase(m2.find(29), m2.find(82));
		
		swap(m1, m2);

		compare_maps(m1);
		iterate_maps(m1);

		compare_maps(m2);
		iterate_maps(m2);
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|  ITERATOR OPERATIONS  |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Iterator - Operator == \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		NAMESPACE::map<T1, T2>::iterator it = m.begin();
		NAMESPACE::map<T1, T2>::iterator it2 = m.end()--;

		for (; it != m.end(); it++, it2--)
			std::cout << ((it == it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Const Iterator - Operator == \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_op(m);

		NAMESPACE::map<T1, T2>::const_iterator it = m_op.begin();
		NAMESPACE::map<T1, T2>::const_iterator it2 = m_op.end()--;

		for (; it != m_op.end(); it++, it2--)
			std::cout << ((it == it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Reverse Iterator - Operator == \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		NAMESPACE::map<T1, T2>::reverse_iterator it = m.rbegin()++;
		NAMESPACE::map<T1, T2>::reverse_iterator it2 = m.rend();

		for (; it != m.rend(); it++, it2--)
			std::cout << ((it == it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator == \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_op(m);

		NAMESPACE::map<T1, T2>::const_reverse_iterator it = m_op.rbegin()++;
		NAMESPACE::map<T1, T2>::const_reverse_iterator it2 = m_op.rend();

		for (int i = 0; it != m_op.rend(); it++, it2--, i++)
			std::cout << ((it == it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator != \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		NAMESPACE::map<T1, T2>::iterator it = m.begin();
		NAMESPACE::map<T1, T2>::iterator it2 = m.end()--;

		for (; it != m.end(); it++, it2--)
			std::cout << ((it != it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Const Iterator - Operator != \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_op(m);

		NAMESPACE::map<T1, T2>::const_iterator it = m_op.begin();
		NAMESPACE::map<T1, T2>::const_iterator it2 = m_op.end()--;

		for (; it != m_op.end(); it++, it2--)
			std::cout << ((it != it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Reverse Iterator - Operator != \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		NAMESPACE::map<T1, T2>::reverse_iterator it = m.rbegin()++;
		NAMESPACE::map<T1, T2>::reverse_iterator it2 = m.rend();

		for (; it != m.rend(); it++, it2--)
			std::cout << ((it != it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator != \n";
	{
		NAMESPACE::map<T1, T2> m;

		fill_map(m);

		const NAMESPACE::map<T1, T2> m_op(m);

		NAMESPACE::map<T1, T2>::const_reverse_iterator it = m_op.rbegin()++;
		NAMESPACE::map<T1, T2>::const_reverse_iterator it2 = m_op.rend();

		for (; it != m_op.rend(); it++, it2--)
			std::cout << ((it != it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}
}
