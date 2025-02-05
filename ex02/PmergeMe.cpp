/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:49:17 by qtay              #+#    #+#             */
/*   Updated: 2024/11/25 14:25:27 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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

void	PmergeMe::fillVector(std::string &numSequence)
{
	std::istringstream	stream(numSequence);
	std::string			numStr;
	while (std::getline(stream, numStr, ' '))
	{
		int	num = strtol(numStr.c_str(), NULL, 10);
		this->_vec.push_back(num);
	}
}
size_t	PmergeMe::getVectorSize(void)
{
	return (this->_vec.size());
}

void	PmergeMe::printVector(void)
{
	for (size_t i = 0; i < getVectorSize(); i++)
	{
		std::cout << this->_vec[i] << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::fordJohnsonSortVector(int unitSize)
{
	int			numOfUnits = _vec.size() / unitSize;
	if (numOfUnits < 2)
		return ;
	
	bool	hasStraggler = numOfUnits % 2 == 1;

	vector_t::iterator	start = _vec.begin();
	vector_t::iterator	end = advanceIter(_vec.begin(), numOfUnits * unitSize - (hasStraggler * unitSize)); //

	for (vector_t::iterator it = start; it != end; std::advance(it, 2 * unitSize))
	{
		vector_t::iterator	firstUnit = advanceIter(it, unitSize - 1);
		vector_t::iterator	secondUnit = advanceIter(it, unitSize * 2 - 1);
		if (*firstUnit > *secondUnit)
			swapUnits(firstUnit, unitSize);
	}
	fordJohnsonSortVector(unitSize * 2);

	iter_vector	main;
	iter_vector	pend;
	main.insert(main.end(), advanceIter(_vec.begin(), unitSize - 1)); // same as line 77 & 78; move b1 
	main.insert(main.end(), advanceIter(_vec.begin(), (unitSize * 2) - 1)); // move b2
	for (int i = 4; i <= numOfUnits; i += 2) // must at least have a2 and b2 for pend to exist that's why start from i = 4 (nicer to start from 4 so that numOfUnits has equal)
	{
		pend.insert(pend.end(), advanceIter(_vec.begin(), unitSize * (i - 1) - 1));
		main.insert(main.end(), advanceIter(_vec.begin(), unitSize * i - 1));
	}

	long	prevJacobsthal = jacobsthalGenerator(2);
	int		insertedNums = 0;
	for (int k = 3;; k++)
	{
		long	currJacobsthal = jacobsthalGenerator(k);
		long	jacobsthalDiff = currJacobsthal - prevJacobsthal; // this represents number of numbers to be inserted into main chain
		int		offset = 0;
		if (jacobsthalDiff > static_cast<long>(pend.size()))
			break ;
		long	numOfUnitInsertions = jacobsthalDiff;

		iter_vector::iterator	pendIt = pend.begin() + jacobsthalDiff - 1; // starting pend unit to start inserting into the main chain
		long int	boundIndex = currJacobsthal + insertedNums; // currJacobsthal gives the bound, e.g. if we insert b3 the bound is a3 which comes after {b1, a1, a2}
		while (numOfUnitInsertions--)
		{
			iter_vector::iterator boundIt = main.begin() + boundIndex - offset;
			iter_vector::iterator idx = std::upper_bound(main.begin(), boundIt, *pendIt, compare<vector_t::iterator>);
			iter_vector::iterator inserted = main.insert(idx, *pendIt);
			pendIt = pend.erase(pendIt);
			if (pendIt != pend.begin())
				pendIt--;
			offset += ((inserted - main.begin()) == boundIndex);
		}
		prevJacobsthal = currJacobsthal;
		insertedNums += jacobsthalDiff;
		offset = 0;
	}

	for (long unsigned int i = 0; i < pend.size(); i++)
	{
		iter_vector::iterator	currPend = pend.begin() + i;
		iter_vector::iterator	currBound = main.end() - pend.size() + i;
		iter_vector::iterator	idx = std::upper_bound(main.begin(), currBound, *currPend, compare<vector_t::iterator>);
		main.insert(idx, *currPend);
	}

	if (hasStraggler)
	{
		vector_t::iterator	straggler  = advanceIter(end, unitSize - 1);
		iter_vector::iterator	idx = std::upper_bound(main.begin(), main.end(), straggler, compare<vector_t::iterator>);
		main.insert(idx, straggler);
	}
	
	// The iterators in the iterator vector "main" point towards _vec.
	// So direct modification of _vec is not allowed.
	vector_t	copy;
	copy.reserve(_vec.size());
	for (iter_vector::iterator it = main.begin(); it != main.end(); it++)
	{
		for (int i = 0; i < unitSize; i++)
		{
			vector_t::iterator	unitStart = *it;
			std::advance(unitStart, -unitSize + i + 1);
			copy.insert(copy.end(), *unitStart);
		}
	}

	// recopy it to _vec
	vector_t::iterator containerIt = _vec.begin();
	vector_t::iterator copyIt = copy.begin();
	while (copyIt != copy.end())
	{
		*containerIt = *copyIt;
		containerIt++;
		copyIt++;
	}
}


// #include <iostream>
// #include <cstdlib> 
// int	main(int ac, char **av)
// {

// 	vector_t	myVec;
// 	for (int i = 1; i < ac; ++i)
// 	{
//         int num = std::atoi(av[i]);
//         myVec.push_back(num);
//     }
// 	for (int i = 0; i < myVec.size(); i++)
// 	{
// 		std::cout << myVec.at(i) << " ";
// 	}
// 	std::cout << std::endl;
// 	fordJohnsonSortVector(myVec, 1);
// 	for (int i = 0; i < myVec.size(); i++)
// 	{
// 		std::cout << myVec.at(i) << " ";
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }
