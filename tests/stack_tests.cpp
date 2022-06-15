/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:38:27 by gasselin          #+#    #+#             */
/*   Updated: 2022/06/15 10:11:45 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../stack.hpp"
#include "../vector.hpp"

#include <stack>
#include <vector>
#include <utility>
#include <iostream>
#include <exception>

#define T1 int

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

template <class T>
void fill_stack(NAMESPACE::stack<T>& stk)
{
	for (int i = 0; i < 25; i++)
		stk.push(i + 1);
}

template <class T>
void fill_stack_vec(NAMESPACE::stack<T, NAMESPACE::vector<T> >& stk)
{
	for (int i = 0; i < 25; i++)
		stk.push(i + 1);
}

template <class T>
void compare_stacks(NAMESPACE::stack<T>& stk)
{
	std::cout << "Size : " << stk.size() << " ";
	if (!stk.empty())
		std::cout << "Top : " << stk.top();
	std::cout << "\n";
}

template <class T>
void compare_stacks_vec(NAMESPACE::stack<T, NAMESPACE::vector<T> >& stk)
{
	std::cout << "Size : " << stk.size() << " ";
	if (!stk.empty())
		std::cout << "Top : " << stk.top();
	std::cout << "\n";
}

int main(void)
{
	std::cout << "-------------------------" << "\n";
	std::cout << "|   STACK / STD::DEQUE  |" << "\n";
	std::cout << "-------------------------" << "\n\n";

	

	std::cout << "Constructor - Default \n";
	{
		NAMESPACE::stack<T1> stk;
		compare_stacks(stk);
	}

	std::cout << "\n";

	std::cout << "Constructor - Copy \n";
	{
		NAMESPACE::stack<T1> stk;

		NAMESPACE::stack<T1> stk_cpy(stk);

		compare_stacks(stk);

		stk_cpy.push(10);
		stk_cpy.push(20);
		stk_cpy.push(30);

		compare_stacks(stk_cpy);
		
		NAMESPACE::stack<T1> stk_cpy2(stk_cpy);

		compare_stacks(stk_cpy2);
	}

	std::cout << "\n";

	std::cout << "Operator = \n";
	{
		NAMESPACE::stack<T1> stk;

		NAMESPACE::stack<T1> stk_op = stk;

		compare_stacks(stk_op);

		stk_op.push(10);
		stk_op.push(20);
		stk_op.push(30);

		compare_stacks(stk_op);

		NAMESPACE::stack<T1> stk_op2 = stk_op;

		compare_stacks(stk_op2);
	}

	std::cout << "\n";

	std::cout << "Top \n";
	{
		NAMESPACE::stack<T1> stk;

		std::cout << "Push : ";
		for (int i = 1; i <= 50; i++)
		{
			stk.push(i);
			std::cout << stk.top() << " ";
		}

		std::cout << "\n";
		
		std::cout << "Pop : ";
		for (int i = 1; i < 50; i++)
		{
			stk.pop();
			std::cout << stk.top() << " ";
		}

		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Top - Const \n";
	{
		NAMESPACE::stack<T1> stk;

		std::cout << "Push : ";
		for (int i = 1; i <= 50; i++)
		{
			stk.push(i);

			const NAMESPACE::stack<T1> stk_push(stk);
			std::cout << stk_push.top() << " ";
		}

		std::cout << "\n";

		std::cout << "Pop : ";
		for (int i = 1; i < 50; i++)
		{
			stk.pop();

			const NAMESPACE::stack<T1> stk_pop(stk);
			std::cout << stk_pop.top() << " ";
		}

		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Empty \n";
	{
		NAMESPACE::stack<T1> stk;

		std::cout << (stk.empty() ? "True" : "False") << "\n";

		stk.push(42);

		std::cout << (stk.empty() ? "True" : "False") << "\n";

		stk.push(77);

		std::cout << (stk.empty() ? "True" : "False") << "\n";

		stk.pop();

		std::cout << (stk.empty() ? "True" : "False") << "\n";

		stk.pop();

		std::cout << (stk.empty() ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Size \n";
	{
		NAMESPACE::stack<T1> stk;

		std::cout << stk.size() << "\n";

		std::cout << "Push : ";
		for (int i = 1; i <= 50; i++)
		{
			stk.push(i);
			std::cout << stk.size() << " ";
		}

		std::cout << "\n";

		std::cout << "Pop : ";
		for (int i = 1; i <= 50; i++)
		{
			stk.pop();
			std::cout << stk.size() << " ";
		}
	}

	std::cout << "\n";

	std::cout << "Push & Pop \n";
	{
		NAMESPACE::stack<T1> stk;

		for (int i = 1; i <= 50; i++)
		{
			stk.push(i);
			compare_stacks(stk);
		}

		std::cout << "\n";

		NAMESPACE::stack<T1> stk_cpy(stk);

		for (int i = 1; i < 50; i++)
		{
			stk.pop();
			compare_stacks(stk);
		}

		std::cout << "\n";

		for (int i = 51; i <= 100; i++)
		{
			stk_cpy.push(i);
			compare_stacks(stk_cpy);
		}

		std::cout << "\n";

		for (int i = 1; i < 100; i++)
		{
			stk_cpy.pop();
			compare_stacks(stk_cpy);
		}
	}

	std::cout << "\n";

	std::cout << "Operator == \n";
	{
		NAMESPACE::stack<T1> stk1;
		NAMESPACE::stack<T1> stk2;

		fill_stack(stk1);
		fill_stack(stk2);

		std::cout << "stk1 == stk2 ? " << ((stk1 == stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 == stk2 ? " << ((stk1 == stk2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator != \n";
	{
		NAMESPACE::stack<T1> stk1;
		NAMESPACE::stack<T1> stk2;

		fill_stack(stk1);
		fill_stack(stk2);
		
		std::cout << "stk1 != stk2 ? " << ((stk1 != stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 != stk2 ? " << ((stk1 != stk2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator < \n";
	{
		NAMESPACE::stack<T1> stk1;
		NAMESPACE::stack<T1> stk2;

		fill_stack(stk1);
		fill_stack(stk2);
		
		std::cout << "stk1 < stk2 ? " << ((stk1 < stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 < stk2 ? " << ((stk1 < stk2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator > \n";
	{
		NAMESPACE::stack<T1> stk1;
		NAMESPACE::stack<T1> stk2;

		fill_stack(stk1);
		fill_stack(stk2);
		
		std::cout << "stk1 > stk2 ? " << ((stk1 > stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 > stk2 ? " << ((stk1 > stk2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator <= \n";
	{
		NAMESPACE::stack<T1> stk1;
		NAMESPACE::stack<T1> stk2;

		fill_stack(stk1);
		fill_stack(stk2);
		
		std::cout << "stk1 <= stk2 ? " << ((stk1 <= stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 <= stk2 ? " << ((stk1 <= stk2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator >= \n";
	{
		NAMESPACE::stack<T1> stk1;
		NAMESPACE::stack<T1> stk2;

		fill_stack(stk1);
		fill_stack(stk2);
		
		std::cout << "stk1 >= stk2 ? " << ((stk1 >= stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 >= stk2 ? " << ((stk1 >= stk2) ? "True" : "False") << "\n";
	}


		
	std::cout << "\n";
	std::cout << "-------------------------" << "\n";
	std::cout << "|     STACK / VECTOR    |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Constructor - Default \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk;
		compare_stacks_vec(stk);
	}

	std::cout << "\n";

	std::cout << "Constructor - Copy \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk;

		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk_cpy(stk);

		compare_stacks_vec(stk);

		stk_cpy.push(10);
		stk_cpy.push(20);
		stk_cpy.push(30);

		compare_stacks_vec(stk_cpy);
		
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk_cpy2(stk_cpy);

		compare_stacks_vec(stk_cpy2);
	}

	std::cout << "\n";

	std::cout << "Operator = \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk;

		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk_op = stk;

		compare_stacks_vec(stk_op);

		stk_op.push(10);
		stk_op.push(20);
		stk_op.push(30);

		compare_stacks_vec(stk_op);

		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk_op2 = stk_op;

		compare_stacks_vec(stk_op2);
	}

	std::cout << "\n";

	std::cout << "Top \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk;

		std::cout << "Push : ";
		for (int i = 1; i <= 50; i++)
		{
			stk.push(i);
			std::cout << stk.top() << " ";
		}

		std::cout << "\n";
		
		std::cout << "Pop : ";
		for (int i = 1; i < 50; i++)
		{
			stk.pop();
			std::cout << stk.top() << " ";
		}

		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Top - Const \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk;

		std::cout << "Push : ";
		for (int i = 1; i <= 50; i++)
		{
			stk.push(i);

			const NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk_push(stk);
			std::cout << stk_push.top() << " ";
		}

		std::cout << "\n";

		std::cout << "Pop : ";
		for (int i = 1; i < 50; i++)
		{
			stk.pop();

			const NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk_pop(stk);
			std::cout << stk_pop.top() << " ";
		}

		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Empty \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk;

		std::cout << (stk.empty() ? "True" : "False") << "\n";

		stk.push(42);

		std::cout << (stk.empty() ? "True" : "False") << "\n";

		stk.push(77);

		std::cout << (stk.empty() ? "True" : "False") << "\n";

		stk.pop();

		std::cout << (stk.empty() ? "True" : "False") << "\n";

		stk.pop();

		std::cout << (stk.empty() ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Size \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk;

		std::cout << stk.size() << "\n";

		std::cout << "Push : ";
		for (int i = 1; i <= 50; i++)
		{
			stk.push(i);
			std::cout << stk.size() << " ";
		}

		std::cout << "\n";

		std::cout << "Pop : ";
		for (int i = 1; i <= 50; i++)
		{
			stk.pop();
			std::cout << stk.size() << " ";
		}
	}

	std::cout << "\n";

	std::cout << "Push & Pop \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk;

		for (int i = 1; i <= 50; i++)
		{
			stk.push(i);
			compare_stacks_vec(stk);
		}

		std::cout << "\n";

		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk_cpy(stk);

		for (int i = 1; i < 50; i++)
		{
			stk.pop();
			compare_stacks_vec(stk);
		}

		std::cout << "\n";

		for (int i = 51; i <= 100; i++)
		{
			stk_cpy.push(i);
			compare_stacks_vec(stk_cpy);
		}

		std::cout << "\n";

		for (int i = 1; i < 100; i++)
		{
			stk_cpy.pop();
			compare_stacks_vec(stk_cpy);
		}
	}

	std::cout << "\n";

	std::cout << "Operator == \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk1;
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk2;

		fill_stack_vec(stk1);
		fill_stack_vec(stk2);

		std::cout << "stk1 == stk2 ? " << ((stk1 == stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 == stk2 ? " << ((stk1 == stk2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator != \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk1;
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk2;

		fill_stack_vec(stk1);
		fill_stack_vec(stk2);
		
		std::cout << "stk1 != stk2 ? " << ((stk1 != stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 != stk2 ? " << ((stk1 != stk2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator < \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk1;
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk2;

		fill_stack_vec(stk1);
		fill_stack_vec(stk2);
		
		std::cout << "stk1 < stk2 ? " << ((stk1 < stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 < stk2 ? " << ((stk1 < stk2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator > \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk1;
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk2;

		fill_stack_vec(stk1);
		fill_stack_vec(stk2);
		
		std::cout << "stk1 > stk2 ? " << ((stk1 > stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 > stk2 ? " << ((stk1 > stk2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator <= \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk1;
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk2;

		fill_stack_vec(stk1);
		fill_stack_vec(stk2);
		
		std::cout << "stk1 <= stk2 ? " << ((stk1 <= stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 <= stk2 ? " << ((stk1 <= stk2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator >= \n";
	{
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk1;
		NAMESPACE::stack<T1, NAMESPACE::vector<T1> > stk2;

		fill_stack_vec(stk1);
		fill_stack_vec(stk2);
		
		std::cout << "stk1 >= stk2 ? " << ((stk1 >= stk2) ? "True" : "False") << "\n";

		stk2.pop();

		std::cout << "stk1 >= stk2 ? " << ((stk1 >= stk2) ? "True" : "False") << "\n";
	}

}