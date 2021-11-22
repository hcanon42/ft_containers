/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hcanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:27:56 by hcanon            #+#    #+#             */
/*   Updated: 2020/03/11 14:06:10 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

# ifdef def_test_full
#  define FULL
# endif

# include <iostream>
# include "Number.hpp"
# include "../includes/Vector.hpp"
# include "../includes/List.hpp"
# include "../includes/Stack.hpp"
# include "../includes/Queue.hpp"
# include "../includes/Map.hpp"

# include <vector>
# include <list>
# include <stack>
# include <queue>
# include <map>
# include <cassert>

void test(std::string const &what) {
	std::cout << "######################################## START TEST " << what << std::endl;
}

void end_test(std::string const &what) {
	std::cout << "######################################## END TEST " << what << '\n' << std::endl;
}

template<typename Container>
void display_container(std::string const &header, Container const &ctn)
{
	typename Container::const_iterator it = ctn.begin();
	typename Container::const_iterator ite = ctn.end();
	std::cout << header;
	if (it == ite)
		std::cout << " empty !";
	std::cout << '\n';
	while (it != ite)
	{
		std::cout << *it;
		if (++it == ite)
			std::cout << '\n';
		else
			std::cout <<  ", ";
	}
}

template<typename type>
void display_container(std::string const &header, ft::List<type> const &ctn)
{
	typename ft::List<type>::Itlist_const it = ctn.begin();
	typename ft::List<type>::Itlist_const ite = ctn.end();
	std::cout << header;
	if (it == ite)
		std::cout << " empty !";
	std::cout << '\n';
	while (it != ite)
	{
		std::cout << *it;
		if (++it == ite)
			std::cout << '\n';
		else
			std::cout <<  ", ";
	}
}

template<typename type>
void display_container(std::string const &header, ft::Vector<type> const &ctn)
{
	typename ft::Vector<type>::Itvector_const it = ctn.begin();
	typename ft::Vector<type>::Itvector_const ite = ctn.end();
	std::cout << header;
	if (it == ite)
		std::cout << " empty !";
	std::cout << '\n';
	while (it != ite)
	{
		std::cout << *it;
		if (++it == ite)
			std::cout << '\n';
		else
			std::cout <<  ", ";
	}
}

template<typename key_type, typename value_type>
void display_container(std::string const &header, std::map<key_type, value_type> const &ctn)
{
	typename std::map<key_type, value_type>::const_iterator it = ctn.begin();
	typename std::map<key_type, value_type>::const_iterator ite = ctn.end();
	std::cout << header;
	if (it == ite)
		std::cout << " empty !";
	std::cout << '\n';
	while (it != ite)
	{
		std::cout << (*it).first << " => " << (*it).second;
		if (++it == ite)
			std::cout << '\n';
		else
			std::cout <<  ", ";
	}
}


template<typename key_type, typename value_type>
void display_container(std::string const &header, ft::Map<key_type, value_type> const &ctn)
{
	typename ft::Map<key_type, value_type>::Itnodemap_const it = ctn.begin();
	typename ft::Map<key_type, value_type>::Itnodemap_const ite = ctn.end();
	std::cout << header;
	if (it == ite)
		std::cout << " empty !";
	std::cout << '\n';
	while (it != ite)
	{
		std::cout << (*it).first << " => " << (*it).second;
		if (++it == ite)
			std::cout << '\n';
		else
			std::cout <<  ", ";
	}
}

# include "vector_test.hpp"
# include "list_test.hpp"
# include "stack_test.hpp"
# include "queue_test.hpp"
# include "map_test.hpp"

#endif
