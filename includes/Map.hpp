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

#ifndef MAP_HPP
# define MAP_HPP

# include "List.hpp"
# include "nodemap.hpp"

namespace ft
{
	template<typename Key, typename Value, typename Compare = ft::less<Key> >
	class MapKeyCompare : std::binary_function<std::pair<Key, Value>, std::pair<Key, Value>, bool>
	{
		public:

			typedef typename std::pair<Key, Value> value_type;

		private:

			Compare	comp;

		public:

			MapKeyCompare(Compare const &comp=Compare()): comp(comp) {}
			virtual ~MapKeyCompare() {}

			bool operator()(const value_type& a, const value_type& b) const
			{
				return (comp(a.first, b.first));
			}

			bool operator()(const value_type& a, const Key& b) const
			{
				return (comp(a.first, b));
			}

			bool operator()(const Key& a, const value_type& b) const
			{
				return (comp(a, b.first));
			}
	};

	template<typename Key, typename Value, typename Compare = ft::MapKeyCompare<Key, Value> >
	class Map
	{
		public:

			typedef ft::Itnodemap<std::pair<Key, Value>, typename nodemap<std::pair<Key, Value>, Compare>::node> 				Itnodemap;
			typedef ft::Itnodemap<std::pair<Key, Value> const, typename nodemap<std::pair<Key, Value>, Compare>::node const>	Itnodemap_const;

		protected:
	
			nodemap<std::pair<Key, Value>, Compare>	_nodemap;
			unsigned int							_size;
	
		public:
	
			Map() : _nodemap(), _size(0) {}
			Map(Itnodemap begin, Itnodemap end) : _nodemap(), _size(0)
			{
				this->insert(begin, end);
			}
			Map(Map const &ref) : _nodemap(nodemap<std::pair<Key, Value>, Compare>(ref._nodemap)), _size(ref._size) {}
			virtual ~Map() {}

			Map														&operator=(Map const &rhs)
			{
				this->clear();
				this->_nodemap = nodemap<std::pair<Key, Value>, Compare>(rhs._nodemap);
				this->_size = rhs._size;
				return (*this);
			}

			Itnodemap												begin(void)
			{
				return (Itnodemap(this->_nodemap.begin()));
			}

			Itnodemap_const											begin(void) const
			{
				return (Itnodemap_const(this->_nodemap.begin()));
			}

			Itnodemap												end(void)
			{
				return (Itnodemap(this->_nodemap.end()));
			}

			Itnodemap_const											end(void) const
			{
				return (Itnodemap_const(this->_nodemap.end()));
			}

			ft::ReverseIterator<Itnodemap>							rbegin(void)
			{
				return (ft::ReverseIterator<Itnodemap>(this->end()));
			}

			ft::ReverseIterator<Itnodemap_const>					rbegin(void) const
			{
				return (ft::ReverseIterator<Itnodemap_const>(this->end()));
			}

			ft::ReverseIterator<Itnodemap>							rend(void)
			{
				return (ft::ReverseIterator<Itnodemap>(this->begin()));
			}

			ft::ReverseIterator<Itnodemap_const>					rend(void) const
			{
				return (ft::ReverseIterator<Itnodemap_const>(this->begin()));
			}

			bool													empty(void) const
			{
				return (this->_size == 0);
			}

			unsigned int											size(void) const
			{
				return (this->_size);
			}

			unsigned int											max_size(void) const
			{
				return (ft::min((unsigned long)std::numeric_limits<std::ptrdiff_t>::max(), std::numeric_limits<unsigned int>::max() / sizeof(typename nodemap<std::pair<Key, Value>, Compare>::node) + sizeof(std::pair<Key, Value>*)));
			}

			Value													&operator[](Key const &key)
			{
				typename nodemap<std::pair<Key, Value>, Compare>::node	*nod;

				nod = this->_nodemap.find(key);
				if (nod)
					return (nod->_data.second);
				++this->_size;
				return (this->_nodemap.insert(std::make_pair(key, Value()))->_data.second);
			}

			typename std::pair<Itnodemap, bool>						insert(std::pair<Key, Value> const &value)
			{
				typename nodemap<std::pair<Key, Value>, Compare>::node	*nod;
				typename nodemap<std::pair<Key, Value>, Compare>::node	*insert;

				nod = this->_nodemap.find(value);
				if (nod)
					return (std::make_pair(Itnodemap(nod), false));
				insert = this->_nodemap.insert(value);
				++this->_size;
				return (std::make_pair(Itnodemap(insert), true));
			}

			Itnodemap												insert(Itnodemap it, std::pair<Key, Value> const &value)
			{
				typename nodemap<std::pair<Key, Value>, Compare>::node	*nod;

				nod = this->_nodemap.find(it.getNode(), value);
				if (nod)
					return (Itnodemap(nod));
				++this->_size;
				return (Itnodemap(this->_nodemap.insert(it.getNode(), value)));
			}

			template<class inputiterator>
			void													insert(inputiterator start, inputiterator end)
			{
				while (start != end)
					this->insert(*start++);
			}

			void													erase(Itnodemap it)
			{
				this->_nodemap.erase(it.getNode());
				--this->_size;
			}

			unsigned int											erase(Key const &key)
			{
				unsigned int	count;

				count = this->_nodemap.erase(key);
				this->_size -= count;
				return (count);
			}

			void													erase(Itnodemap first, Itnodemap last)
			{
				if (first == this->_nodemap.begin() && last == this->_nodemap.end())
					this->clear();
				else
					while (first != last)
					{
						first = this->_nodemap.erase(first.getNode());
						--this->_size;
					}
			}

			void													swap(Map &ref)
			{
				this->_nodemap.swap(ref._nodemap);
				ft::swap(this->_size, ref._size);
			}

			void													clear(void)
			{
				if (this->_size > 0)
					this->_nodemap.make_empty();
				this->_size = 0;
			}

			Itnodemap												find(Key const &key)
			{
				typename nodemap<std::pair<Key, Value>, Compare>::node	*nod;

				nod = this->_nodemap.find(key);
				if (nod)
					return (Itnodemap(nod));
				return (this->end());
			}

			Itnodemap_const											find(Key const &key) const
			{
				typename nodemap<std::pair<Key, Value>, Compare>::node	*nod;

				nod = this->_nodemap.find(key);
				if (nod)
					return (Itnodemap_const(nod));
				return (this->end());
			}

			Compare													key_comp(void) const
			{
				return (this->_nodemap.key_compare());
			}

			Compare													value_comp(void) const
			{
				return (Compare());
			}

			unsigned int											count(Key const &key) const
			{
				Itnodemap_const		it(this->begin());
				Itnodemap_const		ite(this->end());
				unsigned int		count;

				count = 0;
				while (it != ite)
				{
					if (!this->key_comp()(*it, key) && !this->key_comp()(key, *it))
						++count;
					++it;
				}
				return (count);
			}

			Itnodemap												lower_bound(Key const &key)
			{
				Itnodemap			it(this->begin());
				Itnodemap			ite(this->end());

				while (it != ite)
				{
					if (!this->key_comp()(*it, key))
						return (Itnodemap(it));
					++it;
				}
				return (this->end());
			}

			Itnodemap_const											lower_bound(Key const &key) const
			{
				Itnodemap_const		it(this->begin());
				Itnodemap_const		ite(this->end());

				while (it != ite)
				{
					if (!this->key_comp()(*it, key))
						return (Itnodemap_const(it));
					++it;
				}
				return (this->end());
			}

			Itnodemap												upper_bound(Key const &key)
			{
				Itnodemap			it(this->begin());
				Itnodemap			ite(this->end());

				while (it != ite)
				{
					if (this->key_comp()(key, *it))
						return (Itnodemap(it));
					++it;
				}
				return (this->end());
			}

			Itnodemap_const											upper_bound(Key const &key) const
			{
				Itnodemap_const		it(this->begin());
				Itnodemap_const		ite(this->end());

				while (it != ite)
				{
					if (this->key_comp()(key, *it))
						return (Itnodemap_const(it));
					++it;
				}
				return (this->end());
			}

			typename std::pair<Itnodemap, Itnodemap>				equal_range(Key const &key)
			{
				return (std::pair<Itnodemap, Itnodemap>(this->lower_bound(key), this->upper_bound(key)));
			}

			typename std::pair<Itnodemap_const, Itnodemap_const>	equal_range(Key const &key) const
			{
				return (std::pair<Itnodemap_const, Itnodemap_const>(this->lower_bound(key), this->upper_bound(key)));
			}
	};
}

#endif
