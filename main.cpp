/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hcanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 15:57:31 by hcanon            #+#    #+#             */
/*   Updated: 2020/03/11 15:21:35 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test/test.hpp"
#include <fstream>

/**
 * * ft tests
 **/
void start_all_ft_tests(void)
{
	test("Vector");
	test_Vector<ft::Vector<int> >();
	end_test("Vector");

	test("List");
	test_List<ft::List<int>, int>();
	end_test("List");

	// test("Stack");
	// test_Stack<ft::Stack<int>, ft::List<int> >();
	// test_Stack<ft::Stack<int, ft::Vector<int> >, ft::Vector<int> >();
	// end_test("Stack");

	test("Queue");
	test_Queue<ft::Queue<int>, ft::List<int> >();
	end_test("Queue");

	test("Map");
	test_Map<ft::Map<int, int> >();
	test_Map<ft::Map<char, int> >(48);
	end_test("Map");
}

int main(void)
{
	start_all_ft_tests();
	return (0);
}
