/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Number.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hcanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 15:14:55 by hcanon            #+#    #+#             */
/*   Updated: 2020/03/04 20:02:17 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMBER_HPP
# define NUMBER_HPP

# include <iostream>

class Number
{
private:
	static int created;
	static int destructed;
	int n;
public:
	Number();
	Number(int const &a);
	Number(Number const &other);
	virtual ~Number();


	Number &operator=(Number const &other);
	Number &operator=(int value);

	Number &operator+=(Number const &other);
	Number operator+(Number const &other);
	Number &operator-=(Number const &other);
	Number operator-(Number const &other);

	Number &operator+=(int a);
	Number operator+(int a);
	Number &operator-=(int a);
	Number operator-(int a);

	bool operator==(Number const &b) const;
	bool operator!=(Number const &b) const;
	bool operator<(Number const &b) const;
	bool operator<=(Number const &b) const;
	bool operator>(Number const &b) const;
	bool operator>=(Number const &b) const;

	bool operator==(int const &b) const;
	bool operator!=(int const &b) const;
	bool operator<(int const &b) const;
	bool operator<=(int const &b) const;
	bool operator>(int const &b) const;
	bool operator>=(int const &b) const;

	int getValue(void) const;
	static int getCreated(void);
	static int getDestructed(void);
};

bool operator==(Number const &lhs, Number const &rhs);
bool operator!=(Number const &lhs, Number const &rhs);
bool operator<(Number const &lhs, Number const &rhs);
bool operator<=(Number const &lhs, Number const &rhs);
bool operator>(Number const &lhs, Number const &rhs);
bool operator>=(Number const &lhs, Number const &rhs);

std::ostream &operator<<(std::ostream &out, Number const &n);

#endif
