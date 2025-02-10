/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:49:17 by qtay              #+#    #+#             */
/*   Updated: 2025/02/07 13:13:06 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(const PmergeMe &other)
	: _vec(other._vec), _deque(other._deque) {}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vec = other._vec;
		this->_deque = other._deque;
	}
	return (*this);
}

PmergeMe::~PmergeMe(void) {}

long	jacobsthalGenerator(long n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	long	prev = 0, curr = 1;
	for (long i = 2; i <= n; i++)
	{
		long	next = curr + 2 * prev;
		prev = curr;
		curr = next;
	}
	return (curr);
}
