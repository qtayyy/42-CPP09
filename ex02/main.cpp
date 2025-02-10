/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:34:33 by qtay              #+#    #+#             */
/*   Updated: 2025/02/10 15:14:44 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <climits>
#include <cerrno>
#include "PmergeMe.hpp"

using std::cout;
using std::endl;

int numOfComparisons = 0;

static bool	containsOnly(const std::string &word, const std::string &allowedChars)
{
	for (std::string::size_type i = 0; i < word.length(); ++i)
	{
		if (allowedChars.find(word[i]) == std::string::npos)
			return (false);
	}
	return (true);
}

static bool	validInput(std::string &fullSequence)
{
	std::istringstream	stream(fullSequence);
	std::string			numStr;
	while (std::getline(stream, numStr, ' '))
	{
		if (!containsOnly(numStr, "0123456789"))
			return (false);
		long	num = strtol(numStr.c_str(), NULL, 10);
		if (num > INT_MAX || num <= 0 || errno == ERANGE)
			return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		cout << "Error: no arguments provided!\n";
		return (1);
	}
	std::string	fullSequence;
	for (int i = 1; i < argc; i++)
	{
		fullSequence += argv[i];
		if (i < argc - 1)
			fullSequence += " ";
	}
	if (!validInput(fullSequence))
	{
		cout << "Error: invalid input!\n";
		return (1);
	}
	PmergeMe	pmerge;

	#ifdef BENCHMARK
		pmerge.fillDeque(fullSequence);
		pmerge.fordJohnsonSortDeque(1);
		if (!isSorted(pmerge.getDeque()))
		{
			cout << RED "Fatal: sequence not sorted!" RESET << endl;
			pmerge.printDeque();
			exit(123);
		}
		cout << numOfComparisons << endl;
	#else
		clock_t		dequeStartTime = clock(); // number of CPU clock ticks elapsed
		pmerge.fillDeque(fullSequence);
		cout << CYAN "[ DEQUE CONTAINER ]\n" RESET;
		cout << RED "Before: ";
		pmerge.printDeque();
		pmerge.fordJohnsonSortDeque(1);
		clock_t		dequeEndTime = clock();
		if (!isSorted(pmerge.getDeque()))
		{
			cout << RED "Fatal: sequence not sorted: " ;
			pmerge.printDeque();
			exit(123);
		}
		cout << GREEN "After: ";
		pmerge.printDeque();
		cout << MAGENTA "Sorted successfully!" RESET << endl;
		double dequeTimeElapsed = static_cast<double>(dequeEndTime - dequeStartTime) / CLOCKS_PER_SEC * 1000000;
		cout << YELLOW "Time to process a range of " << pmerge.getDequeSize()
				<< " elements with std::deque: "
				<< dequeTimeElapsed << " us\n" RESET;
		std::cout << "Num of comparisons: " << numOfComparisons << std::endl;
		cout << endl;
	#endif

	#ifdef BENCHMARK
		numOfComparisons = 0;
		pmerge.fillVector(fullSequence);
		pmerge.fordJohnsonSortVector(1);
		if (!isSorted(pmerge.getVector()))
		{
			cout << MAGENTA "Fatal: sequence not sorted!" RESET << endl;
			pmerge.printVector();
			exit(123);
		}
		cout << numOfComparisons << endl;
	#else
		numOfComparisons = 0;
		clock_t		vecStartTime = clock();
		pmerge.fillVector(fullSequence);
		cout << CYAN "[ VECTOR CONTAINER ]\n" RESET;
		cout << RED "Before: ";
		pmerge.printVector();
		pmerge.fordJohnsonSortVector(1);
		clock_t		vecEndTime = clock();
		if (!isSorted(pmerge.getVector()))
		{
			cout << MAGENTA "Fatal: sequence not sorted!" RESET << endl;
			pmerge.printVector();
			exit(123);
		}
		cout << GREEN"After: ";
		pmerge.printVector();
		cout << MAGENTA "Sorted successfully!" RESET << endl;
		double vecTimeElapsed = static_cast<double>(vecEndTime - vecStartTime) / CLOCKS_PER_SEC * 1000000;
		cout << YELLOW "Time to process a range of " << pmerge.getVectorSize()
				<< " elements with std::vector: "
				<< vecTimeElapsed << " us\n" RESET;
		std::cout << "Num of comparisons: " << numOfComparisons << std::endl;
		cout << "------------------------------------------------------------------------------------------" << endl;
	#endif

	return (0);
}
