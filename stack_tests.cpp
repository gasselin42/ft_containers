/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:38:27 by gasselin          #+#    #+#             */
/*   Updated: 2022/05/17 11:25:51 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include "vector.hpp"

#include <stack>
#include <vector>
#include <utility>
#include <iostream>
#include <exception>

#define BRED	"\033[1;31m"
#define BGRN	"\033[1;32m"
#define BLUE	"\033[1;34m"
#define NC		"\033[0m"

#define KO		"\033[1;31mKO\033[0m"
#define PASSED	"\033[1;32mPASSED!\033[0m"

static class myexception: public std::exception
{
  virtual const char* what() const throw()
  {
    return "\033[1;31mKO\033[0m";
  }
} ko;

void fill_ft_stack(ft::stack<int>& stk)
{
	for (int i = 0; i < 25; i++)
		stk.push(i + 1);
}

void fill_stl_stack(std::stack<int>& stk)
{
	for (int i = 0; i < 25; i++)
		stk.push(i + 1);
}

void fill_ft_stack_vec(ft::stack<int, ft::vector<int> >& stk)
{
	for (int i = 0; i < 25; i++)
		stk.push(i + 1);
}

void fill_stl_stack_vec(std::stack<int, ft::vector<int> >& stk)
{
	for (int i = 0; i < 25; i++)
		stk.push(i + 1);
}

template <class T>
bool compare_stacks(std::stack<T>& stl_stack, ft::stack<T>& ft_stack)
{
	if ((stl_stack.empty() != ft_stack.empty()) ||
		(stl_stack.size() != ft_stack.size()) ||
		(stl_stack.top() != ft_stack.top()))
		return (false);

	return (true);
}

template <class T>
bool compare_stacks_vec(std::stack<T, ft::vector<T> >& stl_stack, ft::stack<T, ft::vector<T> >& ft_stack)
{
	if ((stl_stack.empty() != ft_stack.empty()) ||
		(stl_stack.size() != ft_stack.size()) ||
		(stl_stack.top() != ft_stack.top()))
		return (false);

	return (true);
}

void stack_tests(void)
{
	std::cout << BLUE << "-------------------------" << NC << "\n";
	std::cout << BLUE << "|   STACK / STD::DEQUE  |" << NC << "\n";
	std::cout << BLUE << "-------------------------" << NC << "\n\n";

	

	std::cout << BLUE << "Constructor - Default " << NC;
	try {
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		if ((stl_stack.empty() != ft_stack.empty()) || (stl_stack.size() != ft_stack.size()))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

		

	std::cout << BLUE << "Constructor - Copy " << NC;
	try {
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		std::stack<int> stl_stack_cpy(stl_stack);
		ft::stack<int> ft_stack_cpy(ft_stack);

		if ((stl_stack.empty() != ft_stack.empty()) || (stl_stack.size() != ft_stack.size()))
			throw ko;

		stl_stack.push(10);
		stl_stack.push(20);
		stl_stack.push(30);

		ft_stack.push(10);
		ft_stack.push(20);
		ft_stack.push(30);

		if (!compare_stacks(stl_stack, ft_stack))
			throw ko;

		std::stack<int> stl_stack_cpy2(stl_stack);
		ft::stack<int> ft_stack_cpy2(ft_stack);

		if (!compare_stacks(stl_stack_cpy2, ft_stack_cpy2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator = " << NC;
	try {
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		std::stack<int> stl_stack_op = stl_stack;
		ft::stack<int> ft_stack_op = ft_stack;

		if ((stl_stack_op.empty() != ft_stack_op.empty()) || (stl_stack_op.size() != ft_stack_op.size()))
			throw ko;

		stl_stack.push(10);
		stl_stack.push(20);
		stl_stack.push(30);

		ft_stack.push(10);
		ft_stack.push(20);
		ft_stack.push(30);

		if (!compare_stacks(stl_stack, ft_stack))
			throw ko;

		std::stack<int> stl_stack_op2 = stl_stack;
		ft::stack<int> ft_stack_op2 = ft_stack;

		if (!compare_stacks(stl_stack_op2, ft_stack_op2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Top " << NC;
	try {
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		for (int i = 1; i <= 50; i++)
		{
			stl_stack.push(i);
			ft_stack.push(i);

			if (stl_stack.top() != ft_stack.top())
				throw ko;
		}

		for (int i = 1; i < 50; i++)
		{
			stl_stack.pop();
			ft_stack.pop();

			if (stl_stack.top() != ft_stack.top())
				throw ko;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Top - Const " << NC;
	try {
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		for (int i = 1; i <= 50; i++)
		{
			stl_stack.push(i);
			ft_stack.push(i);

			const std::stack<int> stl_stack_push(stl_stack);
			const ft::stack<int> ft_stack_push(ft_stack);

			if (stl_stack_push.top() != ft_stack_push.top())
				throw ko;
		}

		for (int i = 1; i < 50; i++)
		{
			stl_stack.pop();
			ft_stack.pop();

			const std::stack<int> stl_stack_pop(stl_stack);
			const ft::stack<int> ft_stack_pop(ft_stack);

			if (stl_stack_pop.top() != ft_stack_pop.top())
				throw ko;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Empty " << NC;
	try {
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		if (stl_stack.empty() != ft_stack.empty())
			throw ko;

		stl_stack.push(42);
		ft_stack.push(42);

		if (stl_stack.empty() != ft_stack.empty())
			throw ko;

		stl_stack.push(77);
		ft_stack.push(77);

		if (stl_stack.empty() != ft_stack.empty())
			throw ko;

		stl_stack.pop();
		ft_stack.pop();

		if (stl_stack.empty() != ft_stack.empty())
			throw ko;

		stl_stack.pop();
		ft_stack.pop();

		if (stl_stack.empty() != ft_stack.empty())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Size " << NC;
	try {
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		if (stl_stack.size() != ft_stack.size())
			throw ko;

		for (int i = 1; i <= 50; i++)
		{
			stl_stack.push(i);
			ft_stack.push(i);

			if (stl_stack.size() != ft_stack.size())
				throw ko;
		}

		for (int i = 1; i <= 50; i++)
		{
			stl_stack.pop();
			ft_stack.pop();

			if (stl_stack.size() != ft_stack.size())
				throw ko;
		}

		if (stl_stack.size() != ft_stack.size())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Push & Pop " << NC;
	try {
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		for (int i = 1; i <= 50; i++)
		{
			stl_stack.push(i);
			ft_stack.push(i);

			if (!compare_stacks(stl_stack, ft_stack))
				throw ko;
		}

		std::stack<int> stl_stack_cpy(stl_stack);
		ft::stack<int> ft_stack_cpy(ft_stack);

		for (int i = 1; i < 50; i++)
		{
			stl_stack.pop();
			ft_stack.pop();

			if (!compare_stacks(stl_stack, ft_stack))
				throw ko;
		}

		for (int i = 51; i <= 100; i++)
		{
			stl_stack_cpy.push(i);
			ft_stack_cpy.push(i);

			if (!compare_stacks(stl_stack_cpy, ft_stack_cpy))
				throw ko;
		}

		for (int i = 1; i < 100; i++)
		{
			stl_stack_cpy.pop();
			ft_stack_cpy.pop();

			if (!compare_stacks(stl_stack_cpy, ft_stack_cpy))
				throw ko;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator == " << NC;
	try {
		std::stack<int> stl_stack1;
		std::stack<int> stl_stack2;
		ft::stack<int> ft_stack1;
		ft::stack<int> ft_stack2;

		fill_stl_stack(stl_stack1);
		fill_stl_stack(stl_stack2);

		fill_ft_stack(ft_stack1);
		fill_ft_stack(ft_stack2);

		if ((stl_stack1 == stl_stack2) != (ft_stack1 == ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 == stl_stack2) != (ft_stack1 == ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator != " << NC;
	try {
		std::stack<int> stl_stack1;
		std::stack<int> stl_stack2;
		ft::stack<int> ft_stack1;
		ft::stack<int> ft_stack2;

		fill_stl_stack(stl_stack1);
		fill_stl_stack(stl_stack2);

		fill_ft_stack(ft_stack1);
		fill_ft_stack(ft_stack2);

		if ((stl_stack1 != stl_stack2) != (ft_stack1 != ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 != stl_stack2) != (ft_stack1 != ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator < " << NC;
	try {
		std::stack<int> stl_stack1;
		std::stack<int> stl_stack2;
		ft::stack<int> ft_stack1;
		ft::stack<int> ft_stack2;

		fill_stl_stack(stl_stack1);
		fill_stl_stack(stl_stack2);

		fill_ft_stack(ft_stack1);
		fill_ft_stack(ft_stack2);

		if ((stl_stack1 < stl_stack2) != (ft_stack1 < ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 < stl_stack2) != (ft_stack1 < ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator > " << NC;
	try {
		std::stack<int> stl_stack1;
		std::stack<int> stl_stack2;
		ft::stack<int> ft_stack1;
		ft::stack<int> ft_stack2;

		fill_stl_stack(stl_stack1);
		fill_stl_stack(stl_stack2);

		fill_ft_stack(ft_stack1);
		fill_ft_stack(ft_stack2);

		if ((stl_stack1 > stl_stack2) != (ft_stack1 > ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 > stl_stack2) != (ft_stack1 > ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator <= " << NC;
	try {
		std::stack<int> stl_stack1;
		std::stack<int> stl_stack2;
		ft::stack<int> ft_stack1;
		ft::stack<int> ft_stack2;

		fill_stl_stack(stl_stack1);
		fill_stl_stack(stl_stack2);

		fill_ft_stack(ft_stack1);
		fill_ft_stack(ft_stack2);

		if ((stl_stack1 <= stl_stack2) != (ft_stack1 <= ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 <= stl_stack2) != (ft_stack1 <= ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator >= " << NC;
	try {
		std::stack<int> stl_stack1;
		std::stack<int> stl_stack2;
		ft::stack<int> ft_stack1;
		ft::stack<int> ft_stack2;

		fill_stl_stack(stl_stack1);
		fill_stl_stack(stl_stack2);

		fill_ft_stack(ft_stack1);
		fill_ft_stack(ft_stack2);

		if ((stl_stack1 >= stl_stack2) != (ft_stack1 >= ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 >= stl_stack2) != (ft_stack1 >= ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }


		
	std::cout << "\n";
	std::cout << BLUE << "-------------------------" << NC << "\n";
	std::cout << BLUE << "|   STACK / FT::VECTOR  |" << NC << "\n";
	std::cout << BLUE << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Constructor - Default " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack;
		ft::stack<int, ft::vector<int> > ft_stack;

		if ((stl_stack.empty() != ft_stack.empty()) || (stl_stack.size() != ft_stack.size()))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

		

	std::cout << BLUE << "Constructor - Copy " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack;
		ft::stack<int, ft::vector<int> > ft_stack;

		std::stack<int, ft::vector<int> > stl_stack_cpy(stl_stack);
		ft::stack<int, ft::vector<int> > ft_stack_cpy(ft_stack);

		if ((stl_stack.empty() != ft_stack.empty()) || (stl_stack.size() != ft_stack.size()))
			throw ko;

		stl_stack.push(10);
		stl_stack.push(20);
		stl_stack.push(30);

		ft_stack.push(10);
		ft_stack.push(20);
		ft_stack.push(30);

		if (!compare_stacks_vec(stl_stack, ft_stack))
			throw ko;

		std::stack<int, ft::vector<int> > stl_stack_cpy2(stl_stack);
		ft::stack<int, ft::vector<int> > ft_stack_cpy2(ft_stack);

		if (!compare_stacks_vec(stl_stack_cpy2, ft_stack_cpy2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator = " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack;
		ft::stack<int, ft::vector<int> > ft_stack;

		std::stack<int, ft::vector<int> > stl_stack_op = stl_stack;
		ft::stack<int, ft::vector<int> > ft_stack_op = ft_stack;

		if ((stl_stack_op.empty() != ft_stack_op.empty()) || (stl_stack_op.size() != ft_stack_op.size()))
			throw ko;

		stl_stack.push(10);
		stl_stack.push(20);
		stl_stack.push(30);

		ft_stack.push(10);
		ft_stack.push(20);
		ft_stack.push(30);

		if (!compare_stacks_vec(stl_stack, ft_stack))
			throw ko;

		std::stack<int, ft::vector<int> > stl_stack_op2 = stl_stack;
		ft::stack<int, ft::vector<int> > ft_stack_op2 = ft_stack;

		if (!compare_stacks_vec(stl_stack_op2, ft_stack_op2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Top " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack;
		ft::stack<int, ft::vector<int> > ft_stack;

		for (int i = 1; i <= 50; i++)
		{
			stl_stack.push(i);
			ft_stack.push(i);

			if (stl_stack.top() != ft_stack.top())
				throw ko;
		}

		for (int i = 1; i < 50; i++)
		{
			stl_stack.pop();
			ft_stack.pop();

			if (stl_stack.top() != ft_stack.top())
				throw ko;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Top - Const " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack;
		ft::stack<int, ft::vector<int> > ft_stack;

		for (int i = 1; i <= 50; i++)
		{
			stl_stack.push(i);
			ft_stack.push(i);

			const std::stack<int, ft::vector<int> > stl_stack_push(stl_stack);
			const ft::stack<int, ft::vector<int> > ft_stack_push(ft_stack);

			if (stl_stack_push.top() != ft_stack_push.top())
				throw ko;
		}

		for (int i = 1; i < 50; i++)
		{
			stl_stack.pop();
			ft_stack.pop();

			const std::stack<int, ft::vector<int> > stl_stack_pop(stl_stack);
			const ft::stack<int, ft::vector<int> > ft_stack_pop(ft_stack);

			if (stl_stack_pop.top() != ft_stack_pop.top())
				throw ko;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Empty " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack;
		ft::stack<int, ft::vector<int> > ft_stack;

		if (stl_stack.empty() != ft_stack.empty())
			throw ko;

		stl_stack.push(42);
		ft_stack.push(42);

		if (stl_stack.empty() != ft_stack.empty())
			throw ko;

		stl_stack.push(77);
		ft_stack.push(77);

		if (stl_stack.empty() != ft_stack.empty())
			throw ko;

		stl_stack.pop();
		ft_stack.pop();

		if (stl_stack.empty() != ft_stack.empty())
			throw ko;

		stl_stack.pop();
		ft_stack.pop();

		if (stl_stack.empty() != ft_stack.empty())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Size " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack;
		ft::stack<int, ft::vector<int> > ft_stack;

		if (stl_stack.size() != ft_stack.size())
			throw ko;

		for (int i = 1; i <= 50; i++)
		{
			stl_stack.push(i);
			ft_stack.push(i);

			if (stl_stack.size() != ft_stack.size())
				throw ko;
		}

		for (int i = 1; i <= 50; i++)
		{
			stl_stack.pop();
			ft_stack.pop();

			if (stl_stack.size() != ft_stack.size())
				throw ko;
		}

		if (stl_stack.size() != ft_stack.size())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Push & Pop " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack;
		ft::stack<int, ft::vector<int> > ft_stack;

		for (int i = 1; i <= 50; i++)
		{
			stl_stack.push(i);
			ft_stack.push(i);

			if (!compare_stacks_vec(stl_stack, ft_stack))
				throw ko;
		}

		std::stack<int, ft::vector<int> > stl_stack_cpy(stl_stack);
		ft::stack<int, ft::vector<int> > ft_stack_cpy(ft_stack);

		for (int i = 1; i < 50; i++)
		{
			stl_stack.pop();
			ft_stack.pop();

			if (!compare_stacks_vec(stl_stack, ft_stack))
				throw ko;
		}

		for (int i = 51; i <= 100; i++)
		{
			stl_stack_cpy.push(i);
			ft_stack_cpy.push(i);

			if (!compare_stacks_vec(stl_stack_cpy, ft_stack_cpy))
				throw ko;
		}

		for (int i = 1; i < 100; i++)
		{
			stl_stack_cpy.pop();
			ft_stack_cpy.pop();

			if (!compare_stacks_vec(stl_stack_cpy, ft_stack_cpy))
				throw ko;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }


	std::cout << BLUE << "Operator == " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack1;
		std::stack<int, ft::vector<int> > stl_stack2;
		ft::stack<int, ft::vector<int> > ft_stack1;
		ft::stack<int, ft::vector<int> > ft_stack2;

		fill_stl_stack_vec(stl_stack1);
		fill_stl_stack_vec(stl_stack2);

		fill_ft_stack_vec(ft_stack1);
		fill_ft_stack_vec(ft_stack2);

		if ((stl_stack1 == stl_stack2) != (ft_stack1 == ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 == stl_stack2) != (ft_stack1 == ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator != " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack1;
		std::stack<int, ft::vector<int> > stl_stack2;
		ft::stack<int, ft::vector<int> > ft_stack1;
		ft::stack<int, ft::vector<int> > ft_stack2;

		fill_stl_stack_vec(stl_stack1);
		fill_stl_stack_vec(stl_stack2);

		fill_ft_stack_vec(ft_stack1);
		fill_ft_stack_vec(ft_stack2);

		if ((stl_stack1 != stl_stack2) != (ft_stack1 != ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 != stl_stack2) != (ft_stack1 != ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator < " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack1;
		std::stack<int, ft::vector<int> > stl_stack2;
		ft::stack<int, ft::vector<int> > ft_stack1;
		ft::stack<int, ft::vector<int> > ft_stack2;

		fill_stl_stack_vec(stl_stack1);
		fill_stl_stack_vec(stl_stack2);

		fill_ft_stack_vec(ft_stack1);
		fill_ft_stack_vec(ft_stack2);

		if ((stl_stack1 < stl_stack2) != (ft_stack1 < ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 < stl_stack2) != (ft_stack1 < ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator > " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack1;
		std::stack<int, ft::vector<int> > stl_stack2;
		ft::stack<int, ft::vector<int> > ft_stack1;
		ft::stack<int, ft::vector<int> > ft_stack2;

		fill_stl_stack_vec(stl_stack1);
		fill_stl_stack_vec(stl_stack2);

		fill_ft_stack_vec(ft_stack1);
		fill_ft_stack_vec(ft_stack2);

		if ((stl_stack1 > stl_stack2) != (ft_stack1 > ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 > stl_stack2) != (ft_stack1 > ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator <= " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack1;
		std::stack<int, ft::vector<int> > stl_stack2;
		ft::stack<int, ft::vector<int> > ft_stack1;
		ft::stack<int, ft::vector<int> > ft_stack2;

		fill_stl_stack_vec(stl_stack1);
		fill_stl_stack_vec(stl_stack2);

		fill_ft_stack_vec(ft_stack1);
		fill_ft_stack_vec(ft_stack2);

		if ((stl_stack1 <= stl_stack2) != (ft_stack1 <= ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 <= stl_stack2) != (ft_stack1 <= ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator >= " << NC;
	try {
		std::stack<int, ft::vector<int> > stl_stack1;
		std::stack<int, ft::vector<int> > stl_stack2;
		ft::stack<int, ft::vector<int> > ft_stack1;
		ft::stack<int, ft::vector<int> > ft_stack2;

		fill_stl_stack_vec(stl_stack1);
		fill_stl_stack_vec(stl_stack2);

		fill_ft_stack_vec(ft_stack1);
		fill_ft_stack_vec(ft_stack2);

		if ((stl_stack1 >= stl_stack2) != (ft_stack1 >= ft_stack2))
			throw ko;

		stl_stack2.pop();
		ft_stack2.pop();

		if ((stl_stack1 >= stl_stack2) != (ft_stack1 >= ft_stack2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }
}