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

#ifndef LIST_HPP
# define LIST_HPP

# include <stdlib.h>
# include <unistd.h>
# include "node.hpp"
# include "Iterator.hpp"
# include <limits>
# include <iostream>
# include <utility>
# include <cstring>

namespace ft
{
	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template<typename T>
	struct less: public std::binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return (x < y);
		}
	};

	template<class value_type>
	value_type const &min(value_type const &a, value_type const &b)
	{
		return (a < b ? a : b);
	}

	template<class value_type>
	value_type const &max(value_type const &a, value_type const &b)
	{
		return (a < b ? b : a);
	}

	template<class value_type>
	bool equal(value_type const &a, value_type const &b)
	{
		return (a == b);
	}

	template<class value_type>
	bool less_than(value_type const &a, value_type const &b)
	{
		return (a < b);
	}

	template<class value_type>
	bool more_than(value_type const &a, value_type const &b)
	{
		return (a > b);
	}

	template<class value_type>
	void swap(value_type &a, value_type &b)
	{
		value_type tmp(a);
		a = b;
		b = tmp;
	}

	template<typename type, typename node_type>
	class Itlist : public IteratorTrait
	{
		public:

			typedef type value_type;

		protected:
	
			node_type		*_pointer;
	
		public:
	
			Itlist() : _pointer(NULL) {}
			Itlist(node_type *ptr) : _pointer(ptr) {}
			Itlist(Itlist const &ref) : _pointer(ref._pointer) {}
			virtual ~Itlist() {}

			node_type		*&getRefNode(void) const
			{
				return (this->_pointer);
			}
			node_type		*getNode(void) const
			{
				return (this->_pointer);
			}

			type			&operator*() const
			{
				return (this->_pointer->getData());
			}
			type			*operator->() const
			{
				return (&this->_pointer->getData());
			}

			Itlist			&operator=(Itlist const &rhs)
			{
				this->_pointer = rhs._pointer;
				return (*this);
			}

			Itlist			&operator+=(int value)
			{
				if (value > 0)
				{
					for (int i = 0; i == value; i++)
					{
						if (this->_pointer == NULL)
							return (*this);
						this->_pointer = this->_pointer->getNext();
					}
				}
				else
				{
					for (int i = 0; i == value; i--)
					{
						if (this->_pointer == NULL)
							return (*this);
						this->_pointer = this->_pointer->getPrevious();
					}
				}
				return (*this);
			}
			Itlist			&operator-=(int value)
			{
				return (this->operator+=(-value));
			}
			Itlist			operator+(int value) const
			{
				Itlist		tmp(*this);

				return (tmp += value);
			}
			Itlist			operator-(int value) const
			{
				return (this->operator+(-value));
			}

			Itlist			&operator++(void)
			{
				this->_pointer = this->_pointer->getNext();
				return (*this);
			}
			Itlist			operator++(int)
			{
				Itlist	tmp(this->_pointer);

				this->_pointer = this->_pointer->getNext();
				return (tmp);
			}
			Itlist			&operator--(void)
			{
				this->_pointer = this->_pointer->getPrevious();
				return (*this);
			}
			Itlist			operator--(int)
			{
				Itlist	tmp(this->_pointer);

				this->_pointer = this->_pointer->getPrevious();
				return (tmp);
			}

			bool			operator==(Itlist const &rhs)
			{
				return (this->_pointer == rhs._pointer);
			}
			bool			operator>=(Itlist const &rhs)
			{
				return (this->_pointer >= rhs._pointer);
			}
			bool			operator<=(Itlist const &rhs)
			{
				return (this->_pointer <= rhs._pointer);
			}
			bool			operator!=(Itlist const &rhs)
			{
				return (this->_pointer != rhs._pointer);
			}
			bool			operator>(Itlist const &rhs)
			{
				return (this->_pointer > rhs._pointer);
			}
			bool			operator<(Itlist const &rhs)
			{
				return (this->_pointer < rhs._pointer);
			}
	};

	template<typename type>
	class List
	{
		public:

			typedef ft::Itlist<type, node<type> > 				Itlist;
			typedef ft::Itlist<const type, const node<type> >	Itlist_const;

		private:

			node<type>				*_nodeBegin;
			node<type>				*_nodeEnd;
			unsigned int			_size;

			void					starting(void)
			{
				this->_nodeEnd = new node<type>();
				this->_nodeBegin = this->_nodeEnd;
				this->_nodeEnd->getNext() = NULL;
				this->_nodeEnd->getPrevious() = NULL;
			}

		public:

			List() : _nodeBegin(NULL), _nodeEnd(NULL), _size(0)
			{
				this->starting();
			}

			List(Itlist first, Itlist last) : _nodeBegin(NULL), _nodeEnd(NULL), _size(0)
			{
				this->starting();
				this->assign(first, last);
			}

			List(unsigned int nb, type value) :  _nodeBegin(NULL), _nodeEnd(NULL), _size(0)
			{
				this->starting();
				this->assign(nb, value);
			}

			List(List const &ref) : _nodeBegin(NULL), _nodeEnd(NULL), _size(0)
			{
				this->starting();
				this->assign(ref._nodeBegin, ref._nodeEnd);
			}

			virtual ~List()
			{
				this->clear();
				delete this->_nodeEnd;
			}

			List				&operator=(List const &rhs)
			{
				this->assign(rhs._nodeBegin, rhs._nodeEnd);
				return (*this);
			}

			Itlist				begin(void)
			{
				return (Itlist(this->_nodeBegin));
			}

			Itlist_const		begin(void) const
			{
				return (Itlist_const(this->_nodeBegin));
			}

			ft::ReverseIterator<Itlist>			rbegin(void)
			{
				return (ReverseIterator<Itlist>(this->end()));
			}

			ft::ReverseIterator<Itlist_const>	rbegin(void) const
			{
				return (ReverseIterator<Itlist_const>(this->end()));
			}

			Itlist				end(void)
			{
				return (Itlist(this->_nodeEnd));
			}

			Itlist_const		end(void) const
			{
				return (Itlist_const(this->_nodeEnd));
			}

			ft::ReverseIterator<Itlist>			rend(void)
			{
				return (ReverseIterator<Itlist>(this->begin()));
			}

			ft::ReverseIterator<Itlist_const>	rend(void) const
			{
				return (ReverseIterator<Itlist_const>(this->begin()));
			}

			type				&front(void)
			{
				return (this->_nodeBegin->getData());
			}

			type const			&front(void) const
			{
				return (this->_nodeBegin->getData());
			}

			type				&back(void)
			{
				return (this->_nodeEnd->getPrevious()->getData());
			}

			type const			&back(void) const
			{
				return (this->_nodeEnd->getPrevious()->getData());
			}

			unsigned int		size(void) const
			{
				return (this->_size);
			}

			unsigned int		max_size(void) const
			{
				return (ft::min((unsigned long) std::numeric_limits<std::ptrdiff_t>::max(), std::numeric_limits<unsigned int>::max() / (sizeof(node<type>) - sizeof(type*))));
			}

			bool				empty(void) const
			{
				if (this->_size == 0)
					return (true);
				return (false);
			}

			void				assign(int nb, type const &value)
			{
				this->clear();
				for (int i = 0; i < nb; i++)
					this->push_back(value);
			}

			void				assign(Itlist begin, Itlist end)
			{
				this->clear();
				while (begin != end)
					this->push_back(*begin++);
			}

			void				push_front(type const &value)
			{
				node<type>		*tmp = new node<type>(value);

				if (this->_size == 0)
					this->_nodeEnd->insert_front(tmp);
				else
					this->_nodeBegin->insert_front(tmp);
				this->_nodeBegin = tmp;
				++this->_size;
			}

			void				pop_front(void)
			{
				if (this->_size == 0)
					return ;
				else if (this->_size == 1)
				{
					delete this->_nodeBegin;
					this->_nodeBegin = this->_nodeEnd;
					this->_nodeEnd->getPrevious() = NULL;
				}
				else
				{
					node<type>		*tmp;

					tmp = this->_nodeBegin->getNext();
					this->_nodeBegin->disconnect();
					delete this->_nodeBegin;
					this->_nodeBegin = tmp;
				}
				--this->_size;
			}

			void				push_back(type const &value)
			{
				node<type>		*tmp = new node<type>(value);

				this->_nodeEnd->insert_front(tmp);
				if (this->_size == 0)
					this->_nodeBegin = tmp;
				++this->_size;
			}

			void				pop_back(void)
			{
				if (this->_size == 0)
					return ;
				else if (this->_size == 1)
				{
					delete this->_nodeEnd;
					this->_nodeEnd = this->_nodeBegin;
					this->_nodeBegin->getNext() = NULL;
				}
				else
				{
					node<type>		*tmp;

					tmp = this->_nodeEnd->getPrevious();
					this->_nodeEnd->disconnect();
					delete this->_nodeEnd;
					this->_nodeEnd = tmp;
				}
				--this->_size;
			}

			void				insert(Itlist it, unsigned int n, type const &value)
			{
				for (unsigned int i = 0; i < n; i++)
					this->insert(it, value);
			}

			void				insert(Itlist it, Itlist begin, Itlist end)
			{
				while (begin != end)
					this->insert(it, *begin++);
			}

			Itlist				insert(Itlist it, type const &value)
			{
				if (it == this->begin())
				{
					push_front(value);
					return (this->begin());
				}
				else if (it == this->end())
				{
					push_back(value);
					return (this->end());
				}
				node<type>	*newNode = new node<type>(value);
				it.getNode()->insert_front(newNode);
				++this->_size;
				return (Itlist(newNode));
			}

			Itlist				erase(Itlist it)
			{
				if (it == this->begin())
				{
					this->pop_front();
					return (this->begin());
				}
				if (it == this->end())
				{
					this->pop_back();
					return (this->end());
				}
				Itlist			itret(it.getNode()->getNext());
				it.getNode()->disconnect();
				delete it.getNode();
				--this->_size;
				return (itret);
			}

			Itlist				erase(Itlist begin, Itlist end)
			{
				while (begin != end)
					this->erase(begin++);
				return (begin);
			}

			void				swap(List &ref)
			{
				ft::swap(this->_nodeBegin, ref._nodeBegin);
				ft::swap(this->_nodeEnd, ref._nodeEnd);
				ft::swap(this->_size, ref._size);
			}

			void				resize(int n, type const &value = type())
			{
				Itlist		it;

				it = this->begin();
				if (n == 0)
					this->clear();
				else if (static_cast<unsigned int>(n) > this->size())
					while (this->size() < static_cast<unsigned int>(n))
						this->push_back(value);
				else
					for (unsigned int i = this->size() - n; i > 0; i--)
						this->pop_back();
			}

			void				clear(void)
			{
				this->erase(this->begin(), this->end());
				this->_nodeEnd->getPrevious() = NULL;
				this->_nodeEnd->getNext() = NULL;
				this->_nodeBegin = this->_nodeEnd;
			}

			void				splice(Itlist it, List &origin)
			{
				return (this->splice(it, origin, origin.begin(), origin.end()));
			}

			void				splice(Itlist it, List &origin, Itlist elem)
			{
				Itlist		tmp;
				
				tmp = elem;
				return (this->splice(it, origin, tmp, ++elem));
			}

			void				splice(Itlist it, List &origin, Itlist begin, Itlist end)
			{
				node<type>		*tmp;

				while (begin != end)
				{
					tmp = begin.getNode();
					++begin;
					if (tmp == origin._nodeBegin)
						origin._nodeBegin = tmp->getNext();
					tmp->disconnect();
					it.getNode()->insert_front(tmp);
					if (it == this->begin())
						this->_nodeBegin = tmp;
					++this->_size;
					--origin._size;
				}
				if (origin.empty() == true)
				{
					origin._nodeBegin = origin._nodeEnd;
					origin._nodeEnd->getNext() = NULL;
					origin._nodeEnd->getPrevious() = NULL;
				}
			}

			void				remove(type const &value)
			{
				Itlist		it;

				it = this->begin();
				while (it != this->end())
				{
					if (*it == value)
						it = this->erase(it);
					else
						++it;
				}
			}

			template<typename Predicate>
			void				remove_if(Predicate predicate)
			{
				Itlist		it;

				it = this->begin();
				while (it != this->end())
				{
					if ((*predicate)(*it))
						it = this->erase(it);
					else
						++it;
				}
			}

			void				unique(void)
			{
				this->unique(&equal<type>);
			}

			template<typename BinaryPredicate>
			void				unique(BinaryPredicate binary_pred)
			{
				Itlist			first_elem;
				Itlist			second_elem;

				first_elem = this->begin();
				second_elem = this->begin();
				while (second_elem != this->end())
				{
					++second_elem;
					if ((*binary_pred)(*first_elem, *second_elem))
					{
						this->erase(second_elem);
						second_elem = first_elem;
					}
					else
						++first_elem;
				}
			}

			void				merge(List &origin)
			{
				this->merge(origin, &less_than<type>);
			}

			template<typename Compare>
			void				merge(List &origin, Compare comp)
			{
				if (origin == *this)
					return ;
				if (this->size() == 0)
				{
					this->assign(origin.begin(), origin.end());
					origin.clear();
				}
				else
				{
					Itlist		elem_this;
					Itlist		elem_origin;

					elem_this = this->begin();
					elem_origin = origin.begin();
					while (elem_this != this->end() && elem_origin != origin.end())
					{
						if ((*comp)(*elem_origin, *elem_this))
						{
							// if (elem_origin == origin.begin())
								origin._nodeBegin = elem_origin.getNode()->getNext();
							--origin._size;
							elem_origin.getNode()->disconnect();
							elem_this.getNode()->insert_front(elem_origin.getNode());
							if (elem_this == this->begin())
								this->_nodeBegin = this->_nodeBegin->getPrevious();
							++this->_size;
							elem_origin = origin.begin();
						}
						else
						{
							++elem_this;
							// if (elem_this == this->end())
							// {
							// 	++elem_origin;
							// 	elem_this = this->begin();
							// }
						}
					}
					this->splice(this->end(), origin);
				}
			}

			void				sort(void)
			{
				this->sort(&less_than<type>);
			}

			template<typename Compare>
			void				sort(Compare comp)
			{
				Itlist			first_elem;
				Itlist			second_elem;

				first_elem = this->begin();
				second_elem = first_elem;
				while (++second_elem != this->end())
				{
					if ((*comp)(*second_elem, *first_elem))
					{
						second_elem.getNode()->swap(first_elem.getNode());
						while (first_elem.getNode()->getPrevious())
							--first_elem;
						second_elem = first_elem;
					}
					else
						++first_elem;
				}
				while (first_elem.getNode()->getPrevious())
					--first_elem;
				this->_nodeBegin = first_elem.getNode();
			}

			void				reverse(void)
			{
				Itlist			first_elem;
				Itlist			second_elem;

				if (this->empty())
					return ;
				first_elem = this->begin();
				second_elem = --this->end();
				for (unsigned int i = this->size() / 2; i > 0; i--)
					first_elem++.getNode()->swap(second_elem--.getNode());
				while (second_elem.getNode()->getPrevious())
					--second_elem;
				this->_nodeBegin = second_elem.getNode();
			}
	};

	template<typename type>
	bool operator==(List<type> const &lhs, List<type> const &rhs)
	{
		typename List<type>::Itlist_const first1 = lhs.begin();
		typename List<type>::Itlist_const first2 = rhs.begin();

		if (lhs.size() != rhs.size())
			return (false);
		while (first1 != lhs.end())
			if (*first1++ != *first2++)
				return (false);
		return (true);
	}

	template<typename type>
	bool operator!=(List<type> const &lhs, List<type> const &rhs)
	{
		return (!(lhs == rhs));
	}

	template<typename type>
	bool operator<(List<type> const &lhs, List<type> const &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<typename type>
	bool operator<=(List<type> const &lhs, List<type> const &rhs)
	{
		return (!(rhs < lhs));
	}

	template<typename type>
	bool operator>(List<type> const &lhs, List<type> const &rhs)
	{
		return (rhs < lhs);
	}

	template<typename type>
	bool operator>=(List<type> const &lhs, List<type> const &rhs)
	{
		return (!(lhs < rhs));
	}

	template<typename type>
	void swap(List<type> &x, List<type> &y)
	{
		x.swap(y);
	}
}

#endif
