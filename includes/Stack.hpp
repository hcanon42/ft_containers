// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   megaphone.cpp                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hcanon <hcanon@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/10/14 16:00:46 by hcanon            #+#    #+#             */
// /*   Updated: 2020/09/04 14:58:29 by user42           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef STACK_HPP
// # define STACK_HPP

// # include "List.hpp"

// namespace ft
// {
// 	template<typename type, typename container = ft::List<type> >
// 	class Stack
// 	{
// 		protected:

// 			container		_container;

// 		public:

// 			Stack(container const &cont = container()) : _container(cont) {}
// 			Stack(Stack<type, container> const &ref) : _container(ref._container) {}
// 			virtual ~Stack() {}

// 			Stack	&operator=(Stack const &rhs)
// 			{
// 				this->_container = rhs._container;
// 				return (*this);
// 			}

// 			type				&top(void)
// 			{
// 				return (this->_container.back());
// 			}

// 			type const			&top(void) const
// 			{
// 				return (this->_container.back());
// 			}

// 			unsigned int		size(void) const
// 			{
// 				return (this->_container.size());
// 			}

// 			bool				empty(void) const
// 			{
// 				return (this->_container.empty());
// 			}

// 			void				push(type const &value)
// 			{
// 				return (this->_container.push_back(value));
// 			}

// 			void				pop(void)
// 			{
// 				return (this->_container.pop_back());
// 			}

// 			template<typename stack_type, typename container_type>
// 			friend bool operator==(Stack<stack_type, container_type> const &lhs, Stack<stack_type, container_type> const &rhs)
// 			{
// 				return (lhs._container == rhs._container);
// 			}

// 			template<typename stack_type, typename container_type>
// 			friend bool operator!=(Stack<stack_type, container_type> const &lhs, Stack<stack_type, container_type> const &rhs)
// 			{
// 				return (lhs._container != rhs._container);
// 			}

// 			template<typename stack_type, typename container_type>
// 			friend bool operator<(Stack<stack_type, container_type> const &lhs, Stack<stack_type, container_type> const &rhs)
// 			{
// 				return (lhs._container < rhs._container);
// 			}

// 			template<typename stack_type, typename container_type>
// 			friend bool operator<=(Stack<stack_type, container_type> const &lhs, Stack<stack_type, container_type> const &rhs)
// 			{
// 				return (lhs._container <= rhs._container);
// 			}

// 			template<typename stack_type, typename container_type>
// 			friend bool operator>(Stack<stack_type, container_type> const &lhs, Stack<stack_type, container_type> const &rhs)
// 			{
// 				return (lhs._container > rhs._container);
// 			}

// 			template<typename stack_type, typename container_type>
// 			friend bool operator>=(Stack<stack_type, container_type> const &lhs, Stack<type, container_type> const &rhs)
// 			{
// 				return (lhs._container >= rhs._container);
// 			}
// 	};
// }

// #endif
