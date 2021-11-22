/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hcanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:00:46 by hcanon            #+#    #+#             */
/*   Updated: 2020/09/04 14:58:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "List.hpp"

namespace ft
{
	template<typename type, typename container = ft::List<type> >
	class Queue
	{
		private:

			container		_container;

		public:

			Queue(container const &cont=container()) : _container(cont) {}
			Queue(Queue<type, container> const &ref) : _container(ref.container()) {}
			virtual ~Queue() {}

			Queue	&operator=(Queue const &rhs)
			{
				this->_container = rhs._container;
				return (*this);
			}

			type				&front(void)
			{
				return (this->_container.front());
			}

			type const			&front(void) const
			{
				return (this->_container.front());
			}

			type				&back(void)
			{
				return (this->_container.back());
			}

			type const			&back(void) const
			{
				return (this->_container.back());
			}

			unsigned int		size(void) const
			{
				return (this->_container.size());
			}

			bool				empty(void) const
			{
				return (this->_container.empty());
			}

			void				push(type const &value)
			{
				return (this->_container.push_back(value));
			}

			void				pop(void)
			{
				return (this->_container.pop_front());
			}

			template<typename queue_type, typename container_type>
			friend bool operator==(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs)
			{
				return (lhs._container == rhs._container);
			}

			template<typename queue_type, typename container_type>
			friend bool operator!=(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs)
			{
				return (lhs._container != rhs._container);
			}

			template<typename queue_type, typename container_type>
			friend bool operator<(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs)
			{
				return (lhs._container < rhs._container);
			}

			template<typename queue_type, typename container_type>
			friend bool operator<=(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs)
			{
				return (lhs._container <= rhs._container);
			}

			template<typename queue_type, typename container_type>
			friend bool operator>(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs)
			{
				return (lhs._container > rhs._container);
			}

			template<typename queue_type, typename container_type>
			friend bool operator>=(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs)
			{
				return (lhs._container >= rhs._container);
			}
	};
}

#endif
