/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:12:33 by gasselin          #+#    #+#             */
/*   Updated: 2022/06/16 13:44:23 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../set.hpp"

#include <set>
#include <utility>
#include <iostream>
#include <exception>

#define T1 std::string

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

template <class Key>
void fill_set(NAMESPACE::set<Key>& s)
{
	for (int i = 0; i < 100; i++)
		s.insert(s_string[i]);
}

template <class Key>
void iterate_sets(NAMESPACE::set<Key>& s)
{
	typename NAMESPACE::set<Key>::iterator it;

	it = s.begin();

	if (it != s.end())
	{
		std::cout << "Iteration : ";
		for (; it != s.end(); it++)
			std::cout << "[" << *it << "]; ";
	}
	else
		std::cout << "Empty set";
	std::cout << "\n";
}

template <class Key>
void iterate_sets(const NAMESPACE::set<Key>& s)
{
	typename NAMESPACE::set<Key>::const_iterator it;

	it = s.begin();

	if (it != s.end())
	{
		std::cout << "Iteration : ";
		for (; it != s.end(); it++)
			std::cout << "[" << *it << "]; ";
	}
	else
		std::cout << "Empty set";
	std::cout << "\n";
}

template <class Key>
void reverse_iterate_sets(NAMESPACE::set<Key>& s)
{
	typename NAMESPACE::set<Key>::reverse_iterator it;

	it = s.rbegin();

	if (it != s.rend())
	{
		std::cout << "Iteration : ";
		for (; it != s.rend(); it++)
			std::cout << "[" << *it << "]; ";
	}
	else
		std::cout << "Empty set";
	std::cout << "\n";
}

template <class Key>
void reverse_iterate_sets(const NAMESPACE::set<Key>& s)
{
	typename NAMESPACE::set<Key>::const_reverse_iterator it;

	it = s.rbegin();

	if (it != s.rend())
	{
		std::cout << "Iteration : ";
		for (; it != s.rend(); it++)
			std::cout << "[" << *it << "]; ";
	}
	else
		std::cout << "Empty set";
	std::cout << "\n";
}

template <class Key>
void compare_sets(NAMESPACE::set<Key>& s)
{
	std::cout << "Size : " << s.size() << " ";
	std::cout << "Max size : " << s.max_size() << "\n";
}

template <class Key>
void compare_sets(const NAMESPACE::set<Key>& s)
{
	std::cout << "Size : " << s.size() << " ";
	std::cout << "Max size : " << s.max_size() << "\n";
}

int main(void)
{
	std::cout << "-------------------------" << "\n";
	std::cout << "|      CONSTRUCTORS     |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Constructor - Default \n";
	{
		NAMESPACE::set<T1> m;
		compare_sets(m);
		iterate_sets(m);
	}

	std::cout << "\n";

	std::cout << "Constructor - Compare \n";
	{
		NAMESPACE::set<T1> m;

		compare_sets(m);
		iterate_sets(m);

		NAMESPACE::set<T1> m2(m.key_comp());

		compare_sets(m2);
		iterate_sets(m2);
	}

	std::cout << "\n";

	std::cout << "Constructor - Range \n";
	{
		NAMESPACE::set<T1> m;

		fill_set(m);

		compare_sets(m);
		iterate_sets(m);

		NAMESPACE::set<T1> m_range(m.begin(), m.end());

		compare_sets(m_range);
		iterate_sets(m_range);
	}

	std::cout << "\n";

	std::cout << "Constructor - Copy \n";
	{
		NAMESPACE::set<T1> m;

		fill_set(m);

		NAMESPACE::set<T1> m_cpy(m);

		compare_sets(m_cpy);
		iterate_sets(m_cpy);
	}

	std::cout << "\n";

	std::cout << "Operator = \n";
	{
		NAMESPACE::set<T1> m;

		fill_set(m);
		
		NAMESPACE::set<T1> m_op = m;

		compare_sets(m_op);
		iterate_sets(m_op);
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       ITERATORS       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Begin \n";
	{
		NAMESPACE::set<T1> s;

		if (s.begin() != s.end())
			std::cout << "KO\n";

		fill_set(s);

		NAMESPACE::set<T1>::iterator it = s.begin();

		std::cout << "Begin = [" << *it << "]\n";

		iterate_sets(s);
	}

	std::cout << "\n";

	std::cout << "Begin - Const \n";
	{
		const NAMESPACE::set<T1> s_empty;
		
		if (s_empty.begin() != s_empty.end())
			std::cout << "KO\n";
			
		NAMESPACE::set<T1> s;

		fill_set(s);

		const NAMESPACE::set<T1> s_begin(s);

		NAMESPACE::set<T1>::const_iterator it = s_begin.begin();

		std::cout << "Begin = [" << *it << "]\n";

		iterate_sets(s_begin);
	}

	std::cout << "\n";

	std::cout << "End \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		NAMESPACE::set<T1>::iterator it = s.end();

		--it;
		for (; it != s.begin(); it--)
			std::cout << "[" << *it << "]; ";
		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "End - Const \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		const NAMESPACE::set<T1> s_end(s);

		NAMESPACE::set<T1>::const_iterator it = s_end.end();

		--it;
		for (; it != s_end.begin(); it--)
			std::cout << "[" << *it << "]; ";
		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Rbegin \n";
	{
		NAMESPACE::set<T1> s;

		if (s.rbegin() != s.rend())
			std::cout << "KO\n";

		fill_set(s);

		NAMESPACE::set<T1>::reverse_iterator it = s.rbegin();

		std::cout << "Rbegin = [" << *it << "]\n";

		reverse_iterate_sets(s);
	}

	std::cout << "\n";
		
	std::cout << "Rbegin - Const \n";
	{
		const NAMESPACE::set<T1> s_empty;
		
		if (s_empty.rbegin() != s_empty.rend())
			std::cout << "KO\n";
			
		NAMESPACE::set<T1> s;

		fill_set(s);

		const NAMESPACE::set<T1> s_rbegin(s);

		NAMESPACE::set<T1>::const_reverse_iterator it = s_rbegin.rbegin();

		std::cout << "Rbegin = [" << *it << "]\n";

		reverse_iterate_sets(s_rbegin);
	}

	std::cout << "\n";

	std::cout << "Rend \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		NAMESPACE::set<T1>::reverse_iterator it = s.rend();

		it--;
		for (; it != s.rbegin(); it--)
			std::cout << "[" << *it << "]; ";
		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Rend - Const \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		const NAMESPACE::set<T1> s_rend(s);

		NAMESPACE::set<T1>::const_reverse_iterator it = s_rend.rend();

		it--;
		for (; it != s_rend.rbegin(); it--)
			std::cout << "[" << *it << "]; ";
		std::cout << "\n";
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|        CAPACITY       |" << "\n";
	std::cout << "-------------------------" << "\n\n";


	
	std::cout << "Empty \n";
	{
		NAMESPACE::set<T1> s;

		std::cout << (s.empty() ? "True" : "False") << "\n";

		s.insert(s_string[50]);

		std::cout << (s.empty() ? "True" : "False") << "\n";

		s.erase(s_string[50]);

		std::cout << (s.empty() ? "True" : "False") << "\n";
		
		s.insert(s_string[50]);

		std::cout << (s.empty() ? "True" : "False") << "\n";

		s.clear();

		std::cout << (s.empty() ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Size \n";
	{
		NAMESPACE::set<T1> s;

		std::cout << "Size : " << s.size() << "\n";

		fill_set(s);

		std::cout << "Size : " << s.size() << "\n";

		s.erase(s_string[50]);

		std::cout << "Size : " << s.size() << "\n";
		
		s.erase(s.find(s_string[42]), s.end());

		std::cout << "Size : " << s.size() << "\n";

		s.clear();

		std::cout << "Size : " << s.size() << "\n";
	}

	std::cout << "\n";
		
	std::cout << "Max size \n";
	{
		NAMESPACE::set<unsigned char> s1;

		std::cout << "Max size <unsigned char> : " << s1.max_size() << "\n";

		NAMESPACE::set<signed char> s2;

		std::cout << "Max size <signed char> : " << s2.max_size() << "\n";

		NAMESPACE::set<size_t> s3;

		std::cout << "Max size <size_t> : " << s3.max_size() << "\n";

		NAMESPACE::set<ptrdiff_t> s4;

		std::cout << "Max size <ptrdiff_t> : " << s4.max_size() << "\n";
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       MODIFIERS       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Insert - Single element \n";
	{
		NAMESPACE::set<T1> s;

		NAMESPACE::pair<NAMESPACE::set<T1>::iterator, bool> pr;
		
		pr = s.insert(s_string[42]);

		std::cout << "[" << *pr.first << "] ";
		std::cout << (pr.second ? "True" : "False") << "\n";

		NAMESPACE::set<T1>::iterator it = pr.first;
		if (++it != s.end())
			std::cout << "KO\n";

		pr = s.insert(s_string[50]);

		std::cout << "[" << *pr.first << "] ";
		std::cout << (pr.second ? "True" : "False") << "\n";

		it = pr.first;
		if (++it != s.end())
			std::cout << "KO\n";
	}

	std::cout << "\n";

	std::cout << "Insert - Hint \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		s.insert(s.begin(), "end");

		compare_sets(s);
		iterate_sets(s);

		NAMESPACE::set<T1>::iterator it;

		it = s.insert(s.find(s_string[50]), "end_clone");

		std::cout << "[" << *it << "]\n";
	}

	std::cout << "\n";

	std::cout << "Insert - Range \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		NAMESPACE::set<T1> s_insert;

		s_insert.insert(s.begin(), s.end());

		compare_sets(s);
		iterate_sets(s);

		s_insert.clear();

		s_insert.insert(s.find(s_string[25]), s.end());

		compare_sets(s);
		iterate_sets(s);
	}

	std::cout << "\n";

	std::cout << "Erase - Position \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		s.erase(s.begin());

		compare_sets(s);
		iterate_sets(s);

		s.erase(--(s.end()));

		compare_sets(s);
		iterate_sets(s);

		s.erase(s.find(s_string[42]));

		compare_sets(s);
		iterate_sets(s);
	}

	std::cout << "\n";

	std::cout << "Erase - Key \n";
	{
		NAMESPACE::set<T1> s;

		NAMESPACE::set<T1>::size_type st;

		fill_set(s);

		st = s.erase(s_string[42]);

		std::cout << st << "\n";
		compare_sets(s);
		iterate_sets(s);

		st = s.erase("100");

		std::cout << st << "\n";
		compare_sets(s);
		iterate_sets(s);

		st = s.erase(s_string[99]);

		std::cout << st << "\n";
		compare_sets(s);
		iterate_sets(s);

		st = s.erase(s_string[42]);

		std::cout << st << "\n";
		compare_sets(s);
		iterate_sets(s);
	}

	std::cout << "\n";

	std::cout << "Erase - Range \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		s.erase(s.begin(), s.begin());

		compare_sets(s);
		iterate_sets(s);

		s.erase(s.find(s_string[42]), s.find(s_string[84]));

		compare_sets(s);
		iterate_sets(s);

		s.erase(s.begin(), s.end());

		compare_sets(s);
		iterate_sets(s);
	}

	std::cout << "\n";

	std::cout << "Swap \n";
	{
		NAMESPACE::set<T1> s1;
		NAMESPACE::set<T1> s2;

		fill_set(s1);

		s1.swap(s2);

		compare_sets(s1);
		iterate_sets(s1);

		compare_sets(s2);
		iterate_sets(s2);

		fill_set(s1);

		s2.erase(s2.find(s_string[42]), s2.find(s_string[84]));
		
		s1.swap(s2);

		compare_sets(s1);
		iterate_sets(s1);

		compare_sets(s2);
		iterate_sets(s2);
	}

	std::cout << "\n";
	
	std::cout << "Clear \n";
	{
		NAMESPACE::set<T1> s;

		s.clear();

		compare_sets(s);
		iterate_sets(s);

		s.insert("root");

		s.clear();

		compare_sets(s);
		iterate_sets(s);

		fill_set(s);

		s.clear();

		compare_sets(s);
		iterate_sets(s);
	}

	

	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       OBSERVERS       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Key_comp \n";
	{
		NAMESPACE::set<T1> s;
		
		size_t count = 0;

		fill_set(s);

		NAMESPACE::set<T1>::key_compare _comp = s.key_comp();

		NAMESPACE::set<T1>::iterator it = s.begin();

		while (it != s.end())
			if (_comp(*it++, "Hello"))
				count++;

		std::cout << count << "\n";
	}

	std::cout << "\n";

	std::cout << "Value_comp \n";
	{
		NAMESPACE::set<T1> s;
		
		size_t count = 0;

		fill_set(s);

		NAMESPACE::set<T1>::iterator it = s.begin();

		while (it != s.end())
			if (s.value_comp()(*it++, "Hello"))
				count++;

		std::cout << count << "\n";
	}

		

	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       OPERATIONS      |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Find \n";
	{
		NAMESPACE::set<T1> s;

		NAMESPACE::set<T1>::iterator it = s.find(s_string[42]);
		if (&(*it) != &(*s.begin()) || &(*it) != &(*s.end()))
			std::cout << "KO\n";

		fill_set(s);

		s.erase(s_string[42]);

		it = (s.insert(s_string[42])).first;

		NAMESPACE::set<T1>::iterator it2 = s.find(s_string[42]);

		std::cout << "&(*it) == &(*it2) : " << ((&(*it) == &(*it2)) ? "True" : "False") << "\n";

		it++;

		std::cout << "[" << *it << "]\n";
	}

	std::cout << "\n";

	std::cout << "Find - Const \n";
	{
		NAMESPACE::set<T1> s;

		const NAMESPACE::set<T1> s_begin1(s);

		NAMESPACE::set<T1>::const_iterator it = s_begin1.find(s_string[42]);
		if (&(*it) != &(*s_begin1.begin()) || &(*it) != &(*s_begin1.end()))
			std::cout << "KO\n";

		fill_set(s);

		const NAMESPACE::set<T1> s_begin2(s);

		it = s_begin2.find(s_string[54]);

		std::cout << "[" << *it << "]\n";

		it++;

		std::cout << "[" << *it << "]\n";
	}

	std::cout << "\n";

	std::cout << "Count \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		for (int i = 0; i < 100; i++)
			std::cout << s.count(s_string[i]) << " ";
	}

	std::cout << "\n";

	std::cout << "Lower_bound \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		NAMESPACE::set<T1>::iterator it = s.lower_bound(*s.begin());

		std::cout << "[" << *it << "]\n";

		it = s.lower_bound(s_string[42]);

		std::cout << "[" << *it << "]\n";

		it = s.lower_bound(s_string[99]);

		std::cout << "[" << *it << "]\n";
	}

	std::cout << "\n";

	std::cout << "Lower_bound - Const \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		const NAMESPACE::set<T1> s_bound(s);

		NAMESPACE::set<T1>::const_iterator it = s_bound.lower_bound(*s_bound.begin());

		std::cout << "[" << *it << "]\n";

		it = s_bound.lower_bound(s_string[42]);

		std::cout << "[" << *it << "]\n";

		it = s_bound.lower_bound(*(--s_bound.end()));

		std::cout << "[" << *it << "]\n";
	}

	std::cout << "\n";

	std::cout << "Upper_bound \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		NAMESPACE::set<T1>::iterator it = s.upper_bound(*s.begin());

		std::cout << "[" << *it << "]\n";

		it = s.upper_bound(s_string[42]);

		std::cout << "[" << *it << "]\n";

		it = s.upper_bound(*(--s.end()));

		if (it != s.end())
			std::cout << "KO\n";
	}

	std::cout << "\n";

	std::cout << "Upper_bound - Const \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		const NAMESPACE::set<T1> s_bound(s);

		NAMESPACE::set<T1>::const_iterator it = s_bound.upper_bound(*s_bound.begin());

		std::cout << "[" << *it << "]\n";

		it = s_bound.upper_bound(s_string[42]);

		std::cout << "[" << *it << "]\n";

		it = s_bound.upper_bound(*(--s_bound.end()));

		if (it != s_bound.end())
			std::cout << "KO\n";
	}

	std::cout << "\n";

	std::cout << "Equal_range \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		NAMESPACE::pair<NAMESPACE::set<T1>::iterator, NAMESPACE::set<T1>::iterator> pr;

		pr = s.equal_range(*s.begin());

		std::cout << "[" << *pr.first << "]\n";
		std::cout << "[" << *pr.second << "]\n";

		pr = s.equal_range(s_string[42]);

		std::cout << "[" << *pr.first << "]\n";
		std::cout << "[" << *pr.second << "]\n";

		pr = s.equal_range(*(--s.end()));

		std::cout << "[" << *pr.first << "]\n";
		if (pr.second != s.end())
			std::cout << "KO\n";
	}

	std::cout << "\n";

	std::cout << "Equal_range - Const \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		const NAMESPACE::set<T1> s_bound(s);

		NAMESPACE::pair<NAMESPACE::set<T1>::const_iterator, NAMESPACE::set<T1>::const_iterator> pr;

		pr = s_bound.equal_range(*s_bound.begin());

		std::cout << "[" << *pr.first << "]\n";
		std::cout << "[" << *pr.second << "]\n";

		pr = s_bound.equal_range(s_string[42]);

		std::cout << "[" << *pr.first << "]\n";
		std::cout << "[" << *pr.second << "]\n";

		pr = s_bound.equal_range(*(--s_bound.end()));

		std::cout << "[" << *pr.first << "]\n";
		if (pr.second != s_bound.end())
			std::cout << "KO\n";
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       ALLOCATOR       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Get_allocator \n";
	{
		NAMESPACE::set<T1> s;

		NAMESPACE::set<T1> s_alloc(s.key_comp(), s.get_allocator());

		compare_sets(s_alloc);
		iterate_sets(s_alloc);
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|  NON-MEMBER FUNCTIONS |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Operator == \n";
	{
		NAMESPACE::set<T1> s1;
		NAMESPACE::set<T1> s2;

		fill_set(s1);
		fill_set(s2);

		std::cout << "s1 == s2 " << ((s1 == s2) ? "True" : "False") << "\n";

		s2.erase(s2.find(s_string[42]), s2.find(s_string[84]));
		
		std::cout << "s1 == s2 " << ((s1 == s2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator != \n";
	{
		NAMESPACE::set<T1> s1;
		NAMESPACE::set<T1> s2;

		fill_set(s1);
		fill_set(s2);

		std::cout << "s1 != s2 " << ((s1 != s2) ? "True" : "False") << "\n";

		s2.erase(s2.find(s_string[42]), s2.find(s_string[84]));
		
		std::cout << "s1 != s2 " << ((s1 != s2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator < \n";
	{
		NAMESPACE::set<T1> s1;
		NAMESPACE::set<T1> s2;

		fill_set(s1);
		fill_set(s2);

		std::cout << "s1 < s2 " << ((s1 < s2) ? "True" : "False") << "\n";

		s2.erase(s2.find(s_string[42]), s2.find(s_string[84]));
		
		std::cout << "s1 < s2 " << ((s1 < s2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator <= \n";
	{
		NAMESPACE::set<T1> s1;
		NAMESPACE::set<T1> s2;

		fill_set(s1);
		fill_set(s2);

		std::cout << "s1 <= s2 " << ((s1 <= s2) ? "True" : "False") << "\n";

		s2.erase(s2.find(s_string[42]), s2.find(s_string[84]));
		
		std::cout << "s1 <= s2 " << ((s1 <= s2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator > \n";
	{
		NAMESPACE::set<T1> s1;
		NAMESPACE::set<T1> s2;

		fill_set(s1);
		fill_set(s2);

		std::cout << "s1 > s2 " << ((s1 > s2) ? "True" : "False") << "\n";

		s2.erase(s2.find(s_string[42]), s2.find(s_string[84]));
		
		std::cout << "s1 > s2 " << ((s1 > s2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator >= \n";
	{
		NAMESPACE::set<T1> s1;
		NAMESPACE::set<T1> s2;

		fill_set(s1);
		fill_set(s2);

		std::cout << "s1 >= s2 " << ((s1 >= s2) ? "True" : "False") << "\n";

		s2.erase(s2.find(s_string[42]), s2.find(s_string[84]));
		
		std::cout << "s1 >= s2 " << ((s1 >= s2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Swap \n";
	{
		NAMESPACE::set<T1> s1;
		NAMESPACE::set<T1> s2;

		fill_set(s1);

		swap(s1, s2);

		compare_sets(s1);
		iterate_sets(s1);

		compare_sets(s2);
		iterate_sets(s2);

		fill_set(s1);

		s2.erase(s2.find(s_string[42]), s2.find(s_string[82]));
		
		swap(s1, s2);

		compare_sets(s1);
		iterate_sets(s1);

		compare_sets(s2);
		iterate_sets(s2);
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|  ITERATOR OPERATIONS  |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Iterator - Operator == \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		NAMESPACE::set<T1>::iterator it = s.begin();
		NAMESPACE::set<T1>::iterator it2 = s.end()--;

		for (; it != s.end(); it++, it2--)
			std::cout << ((it == it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Const Iterator - Operator == \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		const NAMESPACE::set<T1> s_op(s);

		NAMESPACE::set<T1>::const_iterator it = s_op.begin();
		NAMESPACE::set<T1>::const_iterator it2 = s_op.end()--;

		for (; it != s_op.end(); it++, it2--)
			std::cout << ((it == it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Reverse Iterator - Operator == \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		NAMESPACE::set<T1>::reverse_iterator it = s.rbegin()++;
		NAMESPACE::set<T1>::reverse_iterator it2 = s.rend();

		for (; it != s.rend(); it++, it2--)
			std::cout << ((it == it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator == \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		const NAMESPACE::set<T1> s_op(s);

		NAMESPACE::set<T1>::const_reverse_iterator it = s_op.rbegin()++;
		NAMESPACE::set<T1>::const_reverse_iterator it2 = s_op.rend();

		for (int i = 0; it != s_op.rend(); it++, it2--, i++)
			std::cout << ((it == it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator != \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		NAMESPACE::set<T1>::iterator it = s.begin();
		NAMESPACE::set<T1>::iterator it2 = s.end()--;

		for (; it != s.end(); it++, it2--)
			std::cout << ((it != it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Const Iterator - Operator != \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		const NAMESPACE::set<T1> s_op(s);

		NAMESPACE::set<T1>::const_iterator it = s_op.begin();
		NAMESPACE::set<T1>::const_iterator it2 = s_op.end()--;

		for (; it != s_op.end(); it++, it2--)
			std::cout << ((it != it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Reverse Iterator - Operator != \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		NAMESPACE::set<T1>::reverse_iterator it = s.rbegin()++;
		NAMESPACE::set<T1>::reverse_iterator it2 = s.rend();

		for (; it != s.rend(); it++, it2--)
			std::cout << ((it != it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator != \n";
	{
		NAMESPACE::set<T1> s;

		fill_set(s);

		const NAMESPACE::set<T1> s_op(s);

		NAMESPACE::set<T1>::const_reverse_iterator it = s_op.rbegin()++;
		NAMESPACE::set<T1>::const_reverse_iterator it2 = s_op.rend();

		for (; it != s_op.rend(); it++, it2--)
			std::cout << ((it != it2) ? "True" : "False") << " ";
		std::cout << "\n";
	}
}
