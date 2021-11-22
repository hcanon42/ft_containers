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

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "List.hpp"

namespace ft
{
	template<typename type>
	class Itvector
	{
		public:

			typedef type value_type;

		protected:

			type		*_pointer;

		public:
	
			Itvector() : _pointer(NULL) {}
			Itvector(type *ptr) : _pointer(ptr) {}
			Itvector(Itvector const &ref) : _pointer(ref._pointer) {}
			virtual ~Itvector() {}

			type			&operator*() 
			{
				return (*this->_pointer);
			}

			const type		&operator*() const
			{
				return (*this->_pointer);
			}

			type			*operator->()
			{
				return (this->_pointer);
			}

			const type		*operator->() const
			{
				return (this->_pointer);
			}

			Itvector			&operator=(Itvector const &rhs)
			{
				this->_pointer = rhs._pointer;
				return (*this);
			}

			type				*operator[](int value)
			{
				return (*(this->_pointer + value));
			}

			const type			*operator[](int value) const
			{
				return (*(this->_pointer + value));
			}

			Itvector			&operator+=(int value)
			{
				this->_pointer += value;
				return (*this);
			}

			Itvector			&operator-=(int value)
			{
				this->_pointer -= value;
				return (*this);
			}

			Itvector			operator+(int value) const
			{
				Itvector		tmp(*this);

				return (tmp += value);
			}

			Itvector			operator-(int value) const
			{
				return (this->operator+(-value));
			}

			std::ptrdiff_t		operator-(Itvector const &ref) const
			{
				return (this->_pointer - ref._pointer);
			}

			Itvector			&operator++(void)
			{
				++this->_pointer;
				return (*this);
			}

			Itvector			operator++(int)
			{
				Itvector	tmp(this->_pointer);

				++this->_pointer;
				return (tmp);
			}

			Itvector			&operator--(void)
			{
				--this->_pointer;
				return (*this);
			}

			Itvector			operator--(int)
			{
				Itvector	tmp(this->_pointer);

				--this->_pointer;
				return (tmp);
			}

			bool			operator==(Itvector const &rhs) const
			{
				return (this->_pointer == rhs._pointer);
			}
			bool			operator>=(Itvector const &rhs) const
			{
				return (this->_pointer >= rhs._pointer);
			}
			bool			operator<=(Itvector const &rhs) const
			{
				return (this->_pointer <= rhs._pointer);
			}
			bool			operator!=(Itvector const &rhs) const
			{
				return (this->_pointer != rhs._pointer);
			}
			bool			operator>(Itvector const &rhs) const
			{
				return (this->_pointer > rhs._pointer);
			}
			bool			operator<(Itvector const &rhs) const
			{
				return (this->_pointer < rhs._pointer);
			}
	};

	template<typename type>
	class Vector
	{
		public:

			typedef ft::Itvector<type> Itvector;
			typedef ft::Itvector<type const> Itvector_const;

		private:

			type					*_container;
			unsigned int			_capacity;
			unsigned int			_size;

		public:

			Vector() : _container(NULL), _capacity(0), _size(0)
			{
			}

			Vector(Itvector first, Itvector last) : _container(NULL), _capacity(0), _size(0)
			{
				this->assign(first, last);
			}

			Vector(unsigned int nb, type value = type()) :  _container(NULL), _capacity(0), _size(0)
			{
				this->assign(nb, value);
			}

			Vector(Vector const &ref) : _container(NULL), _capacity(0), _size(ref._size)
			{
				this->reserve(ref._capacity);
				this->assign(ref.begin(), ref.end());
			}

			virtual ~Vector()
			{
				this->clear();
				if (this->_container)
					::operator delete(this->_container);
			}

			Vector								&operator=(Vector const &rhs)
			{
				this->clear();
				this->assign(rhs.begin(), rhs.end());
				return (*this);
			}

			Itvector							begin(void)
			{
				return (Itvector(this->_container));
			}

			Itvector_const						begin(void) const
			{
				return (Itvector_const(this->_container));
			}

			ft::ReverseIterator<Itvector>		rbegin(void)
			{
				return (ReverseIterator<Itvector>(this->end()));
			}

			ft::ReverseIterator<Itvector_const>	rbegin(void) const
			{
				return (ReverseIterator<Itvector_const>(this->end()));
			}

			Itvector							end(void)
			{
				return (Itvector(this->_container + this->size()));
			}

			Itvector_const						end(void) const
			{
				return (Itvector_const(this->_container + this->size()));
			}

			ft::ReverseIterator<Itvector>		rend(void)
			{
				return (ReverseIterator<Itvector>(this->begin()));
			}

			ft::ReverseIterator<Itvector_const>	rend(void) const
			{
				return (ReverseIterator<Itvector_const>(this->begin()));
			}

			unsigned int						size(void) const
			{
				return (this->_size);
			}

			unsigned int						max_size(void) const
			{
				return (ft::min((unsigned long) std::numeric_limits<std::ptrdiff_t>::max(), std::numeric_limits<unsigned int>::max() / (sizeof(type))));
			}

			bool								empty(void) const
			{
				if (this->_size == 0)
					return (true);
				return (false);
			}

			unsigned int						capacity(void)
			{
				return (this->_capacity);
			}

			void								resize(unsigned int n, type value = type())
			{
				unsigned int		i;

				if (n < this->size())
				{
					i = n;
					while (++n < this->size())
						this->_container[n].type::~type();
					this->_size = i;
					return ;
				}
				if (n > this->capacity())
					this->reserve(n);
				if (n > this->size())
				{
					i = this->size() - 1;
					while (++i < n)
						new(&this->_container[i]) type(value);
					this->_size = n;
				}
			}

			void								reserve(unsigned int n)
			{
				if (this->capacity() == 0)
				{
					if (n < 128)
						n = 128;
					this->_container = static_cast<type*>(::operator new(sizeof(type) * n));
					this->_capacity = n;
				}
				else if (n > this->capacity())
				{
					if (n < this->capacity() * 2)
						n = this->capacity() * 2;
					type		*tmp = static_cast<type*>(::operator new(sizeof(type) * n));
					if (this->_container)
					{
						for (unsigned int i = 0; i < this->size(); ++i)
							tmp[i] = type(this->_container[i]);
						delete [] this->_container;
					}
					this->_container = tmp;
					this->_capacity = n;
				}
			}

			type								&operator[](unsigned int i)
			{
				return (this->_container[i]);
			}

			const type							&operator[](unsigned int i) const
			{
				return (this->_container[i]);
			}

			type								at(unsigned int i)
			{
				if (i >= this->size())
					throw std::out_of_range("Vector index out of range");
				return (this->_container[i]);
			}

			type								&front(void)
			{
				return (this->_container[0]);
			}

			const type							&front(void) const
			{
				return (this->_container[0]);
			}

			type								&back(void)
			{
				return (this->_container[this->size() - 1]);
			}

			const type							&back(void) const
			{
				return (this->_container[this->size() - 1]);
			}

			void								assign(int nb, type const &value)
			{
				unsigned int		i;

				i = 0;
				if (this->_capacity < static_cast<unsigned int>(nb))
					this->reserve(nb);
				while (static_cast<int>(i) < nb)
				{
					if (i >= this->size())
						new(&this->_container[i]) type(value);
					else
						this->_container[i] = value;
					++i;
				}
				while (i < this->size())
					this->_container[i++].type::~type();
				this->_size = nb;
			}

			void								assign(Itvector begin, Itvector end)
			{
				size_t				length;
				unsigned int		i;

				length = end - begin;
				i = 0;
				if (this->_capacity < length)
					this->reserve(length);
				while (begin != end)
				{
					if (i >= this->size())
						new(&this->_container[i]) type(*begin);
					else
						this->_container[i] = *begin;
					++begin;
					++i;
				}
				while (i < this->_size)
					this->_container[i++].type::~type();
				this->_size = length;
			}

			void								assign(Itvector_const begin, Itvector_const end)
			{
				size_t				length;
				unsigned int		i;

				length = end - begin;
				i = 0;
				if (this->_capacity < length)
					this->reserve(length);
				while (begin != end)
				{
					if (i >= this->size())
						new(&this->_container[i]) type(*begin);
					else
						this->_container[i] = *begin;
					++begin;
					++i;
				}
				while (i < this->_size)
					this->_container[i++].type::~type();
				this->_size = length;
			}

			void								push_back(type const &value)
			{
				if (this->size() == this->capacity())
					this->reserve(this->capacity() * 2);
				new(&this->_container[this->size()]) type(value);
				++this->_size;
			}

			void								pop_back(void)
			{
				this->_container[--this->_size].type::~type();
			}

			Itvector							insert(Itvector it, type const &value)
			{
				this->insert(it, 1, value);
				return (++it);
			}

			void								insert(Itvector it, unsigned int n, type const &value)
			{
				Vector			tmp(it, this->end());
				Itvector		ite;

				this->_size -= this->end() - it;
				while (n)
				{
					this->push_back(value);
					--n;
				}
				ite = tmp.begin();
				while (ite != tmp.end())
					this->push_back(*ite++);
			}

			void								insert(Itvector it, Itvector begin, Itvector end)
			{
				Vector			tmp(it, this->end());
				Itvector		ite;

				this->_size -= this->end() - it;
				while (begin != end)
					this->push_back(*begin++);
				ite = tmp.begin();
				while (ite != tmp.end())
					this->push_back(*ite++);
			}

			Itvector							erase(Itvector it)
			{
				return (this->erase(it, it + 1));
			}

			Itvector							erase(Itvector begin, Itvector end)
			{
				Itvector			itret;
				unsigned int		i;
				unsigned int		deleted;

				deleted = 0;
				itret = this->begin() - 1;
				i = 0;
				while (++itret != begin)
					++i;
				while (begin != end)
				{
					(*begin++).type::~type();
					++deleted;
				}
				--end;
				while (++end != this->end())
					new(&this->_container[i++]) type(*end);
				this->_size -= deleted;
				return (itret);
			}

			void				swap(Vector &ref)
			{
				ft::swap(this->_container, ref._container);
				ft::swap(this->_size, ref._size);
				ft::swap(this->_capacity, ref._capacity);
			}

			void				clear(void)
			{
				for (unsigned int i = 0; i < this->size(); i++)
					this->pop_back();
				this->_size = 0;
			}
	};

	template<typename type>
	bool operator==(Vector<type> const &lhs, Vector<type> const &rhs)
	{
		typename Vector<type>::Itvector_const first1 = lhs.begin();
		typename Vector<type>::Itvector_const first2 = rhs.begin();

		if (lhs.size() != rhs.size())
			return (false);
		while (first1 != lhs.end())
			if (*first1++ != *first2++)
				return (false);
		return (true);
	}

	template<typename type>
	bool operator!=(Vector<type> const &lhs, Vector<type> const &rhs)
	{
		return (!(lhs == rhs));
	}

	template<typename type>
	bool operator<(Vector<type> const &lhs, Vector<type> const &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<typename type>
	bool operator<=(Vector<type> const &lhs, Vector<type> const &rhs)
	{
		return (!(rhs < lhs));
	}

	template<typename type>
	bool operator>(Vector<type> const &lhs, Vector<type> const &rhs)
	{
		return (rhs < lhs);
	}

	template<typename type>
	bool operator>=(Vector<type> const &lhs, Vector<type> const &rhs)
	{
		return (!(lhs < rhs));
	}

	template<typename type>
	void swap(Vector<type> &x, Vector<type> &y)
	{
		x.swap(y);
	}
}

#endif

