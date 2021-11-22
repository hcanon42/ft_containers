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

#ifndef NODE_HPP
# define NODE_HPP

namespace ft
{
	template<typename type>
	class node
	{

		protected:

			node<type>		*_previous;
			type			_data;
			node<type>		*_next;

		public:

			node() : _previous(NULL), _data(), _next(NULL) {}
			node(type const &value) : _previous(NULL), _data(value), _next(NULL) {}
			node(node *prev, type const &value, node *next = NULL) : _previous(prev), _data(value), _next(next) {}
			node(node const &ref) : _previous(ref->_previous), _data(ref->_data), _next(ref->_next) {}
			
			virtual ~node() {}

			node			&operator=(node const &rhs)
			{
				this->_previous = rhs->_previous;
				this->_data = rhs->_data;
				this->_next = rhs->_next;
			}

			void			insert_back(node *node)
			{
				if (this->_next)
				{
					node->_next = this->_next;
					this->_next->_previous = node;
				}
				node->_previous = this;
				this->_next = node;
			}

			void			insert_front(node *node)
			{
				if (this->_previous)
				{
					node->_previous = this->_previous;
					this->_previous->_next = node;
				}
				node->_next = this;
				this->_previous = node;
			}

			void			disconnect(void)
			{
				if (this->_next)
					this->_next->_previous = this->_previous;
				if (this->_previous)
					this->_previous->_next = this->_next;
			}

			void			swap(node<type> *other)
			{
				if (this->_next == other)
				{
					if (this->_previous)
						this->_previous->_next = other;
					if (other->_next)
						other->_next->_previous = this;
					other->_previous = this->_previous;
					this->_previous = other;
					this->_next = other->_next;
					other->_next = this;
				}
				else if (this->_previous == other)
				{
					if (other->_previous)
						other->_previous->_next = this;
					if (this->_next)
						this->_next->_previous = other;
					this->_previous = other->_previous;
					other->_previous = this;
					other->_next = this->_next;
					this->_next = other;
				}
				else
				{
					node<type> *previous = this->_previous;
					node<type> *next = this->_next;

					if (this->_previous)
						this->_previous->_next = other;
					if (this->_next)
						this->_next->_previous = other;
					this->_previous = other->_previous;
					this->_next = other->_next;
					if (other->_previous)
						other->_previous->_next = this;
					if (other->_next)
						other->_next->_previous = this;
					other->_previous = previous;
					other->_next = next;
				}
			}

			type			&getData(void)
			{
				return (this->_data);
			}

			type const		&getData(void) const
			{
				return (this->_data);
			}

			node			*&getNext(void)
			{
				return (this->_next);
			}
			node			*&getPrevious(void)
			{
				return (this->_previous);
			}

			node const		*getNext(void) const
			{
				return (this->_next);
			}
			node const		*getPrevious(void) const
			{
				return (this->_previous);
			}
	};
}

#endif
