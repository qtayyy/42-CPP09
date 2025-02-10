/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:48:47 by qtay              #+#    #+#             */
/*   Updated: 2025/02/10 12:02:48 by qtay             ###   ########.fr       */
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

extern int numOfComparisons;
typedef std::vector<int>	vector_t;
typedef std::vector< std::vector<int>::iterator>	iter_vector;
typedef std::deque<int>	deque_t;
typedef std::deque<std::deque<int>::iterator>	iter_deque;

#define RED "\001\033[31m\002"
#define GREEN "\001\033[32m\002"
#define YELLOW "\001\033[33m\002"
#define MAGENTA "\001\033[35m\002"
#define CYAN "\001\033[36m\002"
#define GRAY "\001\033[90m\002"
#define RESET "\001\033[0m\002"

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

		vector_t	&getVector(void) { return (_vec); };
		deque_t		&getDeque(void) { return (_deque); };

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
	numOfComparisons++;
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

template <typename T>
bool	isSorted(T &container)
{
	if (container.empty())
	{
		std::cerr << RED "empty container\n" RESET;
		return (true);
	}

	typename T::iterator it = container.begin();
	typename T::iterator next = it;
	++next;
	for (; next != container.end(); ++it, ++next)
	{
		if (*it > *next)
			return (false);
	}
	return (true);
}
		
long	jacobsthalGenerator(long n);

#endif
