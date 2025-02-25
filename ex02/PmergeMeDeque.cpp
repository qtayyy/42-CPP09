/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeDeque.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:54:34 by qtay              #+#    #+#             */
/*   Updated: 2025/02/25 10:56:57 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cassert>
	
void	PmergeMe::fillDeque(std::string &numSequence)
{
	std::istringstream	stream(numSequence);
	std::string			numStr;
	while (std::getline(stream, numStr, ' '))
	{
		int	num = strtol(numStr.c_str(), NULL, 10);
		this->_deque.push_back(num);
	}
}

size_t	PmergeMe::getDequeSize(void)
{
	return (this->_deque.size());
}

void	PmergeMe::printDeque(void)
{
	for (size_t i = 0; i < getDequeSize(); i++)
	{
		std::cout << this->_deque[i] << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::fordJohnsonSortDeque(int unitSize)
{
	int			numOfUnits = _deque.size() / unitSize;
	if (numOfUnits < 2)
		return ;
	
	bool	hasStraggler = numOfUnits % 2 == 1;

	deque_t::iterator	start = _deque.begin();
	deque_t::iterator	end = advanceIter(_deque.begin(), numOfUnits * unitSize - (hasStraggler * unitSize));

	for (deque_t::iterator it = start; it != end; std::advance(it, 2 * unitSize))
	{
		deque_t::iterator	firstUnit = advanceIter(it, unitSize - 1);
		deque_t::iterator	secondUnit = advanceIter(it, unitSize * 2 - 1);
		numOfComparisons++;
		if (*firstUnit > *secondUnit)
			swapUnits(firstUnit, unitSize);
	}
	fordJohnsonSortDeque(unitSize * 2);

	iter_deque	main;
	iter_deque	pend;
	main.insert(main.end(), advanceIter(_deque.begin(), unitSize - 1));
	main.insert(main.end(), advanceIter(_deque.begin(), (unitSize * 2) - 1));
	for (int i = 4; i <= numOfUnits; i += 2)
	{
		pend.insert(pend.end(), advanceIter(_deque.begin(), unitSize * (i - 1) - 1));
		main.insert(main.end(), advanceIter(_deque.begin(), unitSize * i - 1));
	}

	if (hasStraggler)
	{
		pend.insert(pend.end(), advanceIter(_deque.begin(), unitSize * numOfUnits - 1));
	}

	long	prevJacobsthal = jacobsthalGenerator(2);
	int		insertedNums = 0;
	for (int k = 3;; k++)
	{
		long	currJacobsthal = jacobsthalGenerator(k);
		long	jacobsthalDiff = currJacobsthal - prevJacobsthal;
		int		offset = 0;
		if (jacobsthalDiff > static_cast<long>(pend.size()))
			break ;
		long	numOfUnitInsertions = jacobsthalDiff;

		iter_deque::iterator	pendIt = pend.begin() + jacobsthalDiff - 1;
		long int	boundIndex = currJacobsthal + insertedNums;
		while (numOfUnitInsertions--)
		{
			iter_deque::iterator boundIt = main.begin() + boundIndex - offset;
			iter_deque::iterator idx = std::upper_bound(main.begin(), boundIt, *pendIt, compare<deque_t::iterator>);
			iter_deque::iterator inserted = main.insert(idx, *pendIt);
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
		iter_deque::iterator	currPend = pend.begin() + i;
		iter_deque::iterator	currBound = advanceIter(main.begin(), main.size() - pend.size() + i + hasStraggler);
		iter_deque::iterator	idx = std::upper_bound(main.begin(), currBound, *currPend, compare<deque_t::iterator>);
		main.insert(idx, *currPend);
	}

	deque_t	copy;
	for (iter_deque::iterator it = main.begin(); it != main.end(); it++)
	{
		for (int i = 0; i < unitSize; i++)
		{
			deque_t::iterator	unitStart = *it;
			std::advance(unitStart, -unitSize + i + 1);
			copy.insert(copy.end(), *unitStart);
		}
	}

	deque_t::iterator containerIt = _deque.begin();
	deque_t::iterator copyIt = copy.begin();
	while (copyIt != copy.end())
	{
		*containerIt = *copyIt;
		containerIt++;
		copyIt++;
	}
}
