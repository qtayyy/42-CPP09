/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:48:47 by qtay              #+#    #+#             */
/*   Updated: 2024/11/25 14:09:20 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>

typedef std::vector<int>	vector_t;
typedef std::vector< std::vector<int>::iterator>	iter_vector;
typedef std::deque<int>	deque_t;
typedef std::deque<std::deque<int>::iterator>	iter_deque;

class PmergeMe
{
	private:
		vector_t	_vec;
		deque_t		_deque;

	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe &other);
		PmergeMe	&operator=(const PmergeMe &other);
		~PmergeMe(void);

		void	fillVector(std::string &numSequence);
		void	fillDeque(std::string &numSequence);

		size_t	getVectorSize(void);
		size_t	getDequeSize(void);

		void	printVector(void);
		void	printDeque(void);


		void	fordJohnsonSortVector(int UnitSize);
		void	fordJohnsonSortDeque(int unitSize);
};

template <typename T>
T advanceIter(T it, int steps)
{
	std::advance(it, steps);
	return (it);
}

template <typename T>
bool	compare(T left, T right)
{
	return (*left < *right);
}

template <typename T>
void	swapUnits(T firstUnit, int unitSize)
{
	T	start = advanceIter(firstUnit, -unitSize + 1);
	T	end = advanceIter(start, unitSize);
	while (start != end)
	{
		std::iter_swap(start, advanceIter(start, unitSize));
		start++;
	}
}

long	jacobsthalGenerator(long n);

#endif
