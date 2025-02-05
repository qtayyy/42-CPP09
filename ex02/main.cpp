/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:34:33 by qtay              #+#    #+#             */
/*   Updated: 2024/11/25 14:36:09 by qtay             ###   ########.fr       */
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

	clock_t		dequeStartTime = clock();
	pmerge.fillDeque(fullSequence);
	cout << "[ DEQUE CONTAINER ]\n";
	cout << "Before: ";
	pmerge.printDeque();
	pmerge.fordJohnsonSortDeque(1);
	clock_t		dequeEndTime = clock();
	cout << "After: ";
	pmerge.printDeque();
	double dequeTimeElapsed = static_cast<double>(dequeEndTime - dequeStartTime) / CLOCKS_PER_SEC * 1000000;
    cout << "Time to process a range of " << pmerge.getDequeSize()
              << " elements with std::deque: "
              << dequeTimeElapsed << " us\n";
	cout << endl;

	clock_t		vecStartTime = clock();
	pmerge.fillVector(fullSequence);
	cout << "[ VECTOR CONTAINER ]\n";
	cout << "Before: ";
	pmerge.printVector();
	pmerge.fordJohnsonSortVector(1);
	clock_t		vecEndTime = clock();
	cout << "After: ";
	pmerge.printVector();
	double vecTimeElapsed = static_cast<double>(vecEndTime - vecStartTime) / CLOCKS_PER_SEC * 1000000;
    cout << "Time to process a range of " << pmerge.getVectorSize()
              << " elements with std::vector: "
              << vecTimeElapsed << " us\n";
	return (0);
}
