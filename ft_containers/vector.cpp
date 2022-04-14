/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:54:20 by seungyel          #+#    #+#             */
/*   Updated: 2022/04/14 18:08:09 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

size_type size() const { return (this->_end - this->_start); };

size_type capacity() const
{
	
}

void reserve (size_type n)


reference operator[] (size_type n);
const_reference operator[] (size_type n) const;

reference at (size_type n);
const_reference at (size_type n) const;