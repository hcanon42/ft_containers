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

#ifndef NODEMAP_HPP
# define NODEMAP_HPP

# include "Iterator.hpp"
# include <utility>

namespace ft
{
	template<typename type, typename node_type>
	class Itnodemap : public IteratorTrait
	{
		public:

			typedef type value_type;

		protected:

			node_type		*_pointer;

			void previous()
			{
				if (this->_pointer->_left)
				{
					this->_pointer = this->_pointer->_left;
					while (this->_pointer->_right)
						this->_pointer = this->_pointer->_right;
				}
				else
					this->_pointer = this->_pointer->_parent;
			}

			void next()
			{
				if (this->_pointer->_right)
				{
					this->_pointer = this->_pointer->_right;
					while (this->_pointer->_left)
						this->_pointer = this->_pointer->_left;
				}
				else
				{
					node_type	*tmp;
					
					tmp = this->_pointer;
					this->_pointer = this->_pointer->_parent;
					while (this->_pointer->_left != tmp)
					{
						tmp = this->_pointer;
						this->_pointer = this->_pointer->_parent;
					}
				}
			}

		public:

			Itnodemap(): _pointer(NULL) {}
			Itnodemap(node_type *pointer): _pointer(pointer) {}
			Itnodemap(Itnodemap const &ref): _pointer(ref._pointer) {}
			virtual ~Itnodemap() {}

			node_type			*getNode(void) const
			{
				return (this->_pointer);
			}

			Itnodemap			&operator=(Itnodemap const &rhs)
			{
				this->_pointer = rhs._pointer;
				return (*this);
			}

			type				&operator*()
			{
				return (this->_pointer->_data);
			}

			type const			&operator*() const
			{
				return (this->_pointer->_data);
			}

			type				*operator->()
			{
				return (&this->_pointer->_data);
			}

			type const			*operator->() const
			{
				return (&this->_pointer->_data);
			}

			Itnodemap			operator++(int)
			{
				Itnodemap	tmp(*this);

				this->next();
				return (tmp);
			}

			Itnodemap			&operator++()
			{
				this->next();
				return (*this);
			}

			Itnodemap			operator--(int)
			{
				Itnodemap tmp(*this);
				this->previous();
				return (tmp);
			}

			Itnodemap			&operator--()
			{
				this->previous();
				return (*this);
			}

			Itnodemap			&operator+=(int value)
			{
				if (value > 0)
				{
					for (int i = 0; i < value; i++)
						this->next();
				}
				else
				{
					for (int i = value; i > 0; i--)
						this->previous();
				}
				return (*this);
			}

			Itnodemap			operator+(int value) const
			{
				Itnodemap	tmp(*this);

				return (tmp += value);
			}

			Itnodemap			&operator-=(int value)
			{
				operator+=(-value);
				return (*this);
			}

			Itnodemap			operator-(int value) const
			{
				Itnodemap	tmp(*this);

				return (tmp -= value);
			}

			bool				operator==(Itnodemap const &rhs) const
			{
				return (this->_pointer == rhs._pointer);
			}

			bool				operator!=(Itnodemap const &rhs) const
			{
				return (this->_pointer != rhs._pointer);
			}

			bool				operator<(Itnodemap const &rhs) const
			{
				return (this->_pointer < rhs._pointer);
			}

			bool				operator<=(Itnodemap const &rhs) const
			{
				return (this->_pointer <= rhs._pointer);
			}

			bool				operator>(Itnodemap const &rhs) const
			{
				return (this->_pointer > rhs._pointer);
			}

			bool				operator>=(Itnodemap const &rhs) const
			{
				return (this->_pointer >= rhs._pointer);
			}
	};

	template<typename type, typename Compare>
	class nodemap
	{
		public:

			struct node
			{
				node		*_left;
				node		*_right;
				node		*_parent;
				type		_data;

				node(type const &value=type()) : _left(NULL), _right(NULL), _parent(NULL), _data(value) {}
				node(node const &ref) : _left(NULL), _right(NULL), _parent(NULL), _data(ref._data) {}
			};

		protected:

			node			*_end;
			node			*_begin;
			node			*_root;
			Compare			ft_compare;

			void				unbound_node(node *nod)
			{
				if (nod)
				{
					nod->_parent = NULL;
					nod->_left = NULL;
					nod->_right = NULL;
				}
			}

			void				starter(void)
			{
				this->_begin = new node();
				this->_end = this->_begin;
				this->_root = this->_end;
			}

			void				repair_bounds(void)
			{
				node	*tmp(this->_root);

				while (tmp->_left)
					tmp = tmp->_left;
				this->_begin = tmp;
				tmp = this->_root;
				while (tmp->_right)
					tmp = tmp->_right;
				tmp->_right = this->_end;
				this->_end->_parent = tmp;
			}

			template<typename Type>
			node				*find_node(Type const &value, node *nod)
			{
				bool	comp;

				if (nod == this->_end || !nod)
					return (NULL);				
				comp = this->ft_compare(value, nod->_data);
				if (!comp && !this->ft_compare(nod->_data, value))
					return (nod);
				if (comp)
					return (this->find_node(value, nod->_left));
				return (this->find_node(value, nod->_right));
			}

			void				insert_node_at(node *nod, node *new_nod)
			{
				if (this->ft_compare(new_nod->_data, nod->_data))
				{
					if (nod->_left)
					{
						this->insert_node_at(nod->_left, new_nod);
						return ;
					}
					else
						nod->_left = new_nod;
				}
				else
				{
					if (nod->_right)
					{
						this->insert_node_at(nod->_right, new_nod);
						return ;
					}
					else
						nod->_right = new_nod;
				}
				new_nod->_parent = nod;
			}

			void				copy_node(node **destination, node *source, node *end)
			{
				if (!source)
					return ;
				*destination = new node(*source);
				if (source->_left)
				{
					copy_node(&(*destination)->_left, source->_left, end);
					(*destination)->_left->_parent = *destination;
				}
				if (source->_right && source->_right != end)
				{
					copy_node(&(*destination)->_right, source->_right, end);
					(*destination)->_right->_parent = *destination;
				}
			}

			node				*erase_node(node *nod)
			{
				node	*ret(nod);

				if (!nod)
					return (nod);
				if (!nod->_left && !nod->_right)
				{
					if (nod == this->_root)
					{
						this->_begin = this->_end;
						this->_root = this->_end;
						this->unbound_node(this->_end);
					}
					if (nod->_parent)
					{
						if (nod->_parent->_left == nod)
							nod->_parent->_left = NULL;
						else
							nod->_parent->_right = NULL;
					}
					ret = nod->_parent;
					delete nod;
				}
				else if (!nod->_left)
				{
					if (nod->_parent)
					{
						if (nod->_parent->_left == nod)
							nod->_parent->_left = nod->_right;
						else
							nod->_parent->_right = nod->_right;
					}
					nod->_right->_parent = nod->_parent;
					if (nod == this->_root)
						this->_root = nod->_right;
					ret = nod->_right;
					delete nod;
				}
				else if (!nod->_right)
				{
					if (nod->_parent)
					{
						if (nod->_parent->_left == nod)
							nod->_parent->_left = nod->_left;
						else
							nod->_parent->_right = nod->_left;
					}
					nod->_left->_parent = nod->_parent;
					if (nod == this->_root)
						this->_root = nod->_left;
					ret = nod->_parent;
					delete nod;
				}
				else
				{
					node	*tmp(nod->_right);

					while (tmp && tmp->_left != NULL)
						tmp = tmp->_left;
					if (nod->_parent)
					{
						if (nod->_parent->_left == nod)
							nod->_parent->_left = tmp;
						else
							nod->_parent->_right = tmp;
					}
					tmp->_parent = nod->_parent;
					nod->_data.type::~type();
					new(&nod->_data) type(tmp->_data);
					if (nod == this->_root)
						this->_root = nod;
					nod->_right = erase_node(nod->_right);
					ret = nod;
				}
				return (ret);
			}

			void				delete_from(node *nod)
			{
				if (!nod || nod == this->_end)
					return ;
				delete_from(nod->_left);
				delete_from(nod->_right);
				delete nod;
			}

		public:

			nodemap() : _root(NULL), ft_compare()
			{
				this->starter();
			}

			nodemap(Compare const &comp) : _root(NULL), ft_compare(comp)
			{
				this->starter();
			}

			nodemap(nodemap const &ref) : _root(ref._root), ft_compare(ref.ft_compare)
			{
				this->starter();
				this->copy(ref);
			}

			virtual ~nodemap()
			{
				this->make_empty();
				delete this->_end;
			}

			nodemap			&operator=(nodemap const &ref)
			{
				if (this->_root != this->_end)
					this->make_empty();
				this->ft_compare = ref.ft_compare;
				this->copy(ref);
				return (*this);
			}

			void			copy(nodemap const &ref)
			{
				if (ref._root == ref._end)
					return ;
				this->_root = new node(*ref._root);
				if (ref._root->_left)
				{
					this->copy_node(&this->_root->_left, ref._root->_left, ref._end);
					this->_root->_left->_parent = this->_root;
				}
				if (ref._root->_right)
				{
					this->copy_node(&this->_root->_right, ref._root->_right, ref._end);
					this->_root->_right->_parent = this->_root;
				}
				this->repair_bounds();
			}

			node			*insert(type const &value)
			{
				node	*new_node = new node(value);

				if (this->_root == this->_end)
					this->_root = new_node;
				else
				{
					if (this->_end->_parent)
						this->_end->_parent->_right = NULL;
					this->insert_node_at(this->_root, new_node);
				}
				this->repair_bounds();
				return (new_node);
			}

			node			*insert(node *hint, type const &value)
			{
				if (!hint || this->_root == this->_end || (hint->_parent && (ft_compare(value, hint->_parent->_data) || ft_compare(hint->_parent->_data, value))))
					return (this->insert(value));
				node		*new_node = new node(value);
				if (this->_end->_parent)
					this->_end->_parent->_right = NULL;
				this->insert_node_at(hint, new_node);
				this->repair_bounds();
				return (new_node);
			}

			template<typename Type>
			node			*find(Type const &value)
			{
				return (this->find_node(value, this->_root));
			}

			template<typename Type>
			node			*find(node *hint, Type const &value)
			{
				if (!hint)
					return (this->find_node(value, this->_root));
				if (!ft_compare(hint->_data, value) && !ft_compare(value, hint->_data))
					return (hint);
				return (this->find_node(value, hint));
			}

			node			*erase(node *nod)
			{
				node	*next = this->erase_node(nod);

				if (this->_end->_parent)
					this->_end->_parent->_right = NULL;
				this->repair_bounds();
				return (next);
			}

			template<typename Type>
			unsigned int	erase(Type const &key)
			{
				node			*nod;
				unsigned int	total;

				nod = NULL;
				total = 0;
				if (this->_end->_parent)
					this->_end->_parent->_right = NULL;
				while ((nod = this->find(key)))
				{
					this->erase_node(nod);
					++total;
				}
				this->repair_bounds();
				return (total);
			}

			Compare			key_compare(void) const
			{
				return (this->ft_compare);
			}

			node			*begin(void) const
			{
				return (this->_begin);
			}

			node			*end(void) const
			{
				return (this->_end);
			}

			void make_empty(void)
			{
				this->delete_from(this->_root);
				this->_end->_parent = NULL;
				this->_end->_left = NULL;
				this->_end->_right = NULL;
				this->_root = this->_end;
				this->_begin = this->_end;
			}

			void swap(nodemap &ref)
			{
				ft::swap(this->_root, ref._root);
				ft::swap(this->_begin, ref._begin);
				ft::swap(this->_end, ref._end);
				ft::swap(this->ft_compare, ref.ft_compare);
			}
	};
}

#endif
