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

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "node.hpp"

namespace ft
{
	struct IteratorTrait {};

	template<typename It>
	class ReverseIterator : public It
	{
		public:

			using typename It::value_type;

			ReverseIterator(): It() {}
			ReverseIterator(It const &it): It(it) {}
			ReverseIterator(ReverseIterator<It> const &ref): It(ref._pointer) {}
			ReverseIterator<It>			&operator=(ReverseIterator<It> const &rhs)
			{
				this->_pointer = rhs._pointer;
				return (*this);
			}

			value_type					&operator*(void)
			{
				It		tmp(*this);
				return (*--tmp);
			}

			value_type const				&operator*(void) const
			{
				It		tmp(*this);
				return (*--tmp);
			}

			value_type					*operator->(void)
			{
				It		tmp(*this);
				return (&*--tmp);
			}

			value_type const				*operator->(void) const
			{
				It		tmp(*this);
				return (&*--tmp);
			}

			ReverseIterator<It>			operator++(int)
			{
				ReverseIterator<It>	tmp(*this);

				operator++();
				return (tmp);
			}

			It							&operator++(void)
			{
				return (this->It::operator--());
			}

			ReverseIterator<It>			operator--(int)
			{
				ReverseIterator<It>	tmp(*this);

				operator--();
				return (tmp);
			}

			It							&operator--(void)
			{
				return (this->It::operator++());
			}
	};
}

#endif
