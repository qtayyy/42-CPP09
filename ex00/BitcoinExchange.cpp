/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:05:04 by qtay              #+#    #+#             */
/*   Updated: 2025/02/10 17:22:10 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

using std::cout;
using std::endl;

BitcoinExchange::BitcoinExchange(void)
{
	cout << "BitcoinExchange default constructor called\n";
}

/**
 * std::map's copy constructor and copy assignment operator automatically
 * perform deep copying of all key-value pairs
 */
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
	: _keyValPair(other._keyValPair)
{
	cout << "BitcoinExchange copy constructor called\n";
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->_keyValPair = other._keyValPair;
		cout << "BitcoinExchange copy assignment operator called\n";
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
	cout << "BitcoinExchange destructor called\n";
}

void	BitcoinExchange::readFile(std::ifstream &fileName)
{
	std::string	line;
	float		value;

	std::getline(fileName, line); // skip first line
	while (std::getline(fileName, line))
	{
		size_t pos = line.find(',');
		if (pos != std::string::npos)
		{
			value = strtof(line.substr(pos + 1).c_str(), NULL);
			this->_keyValPair.insert
				(std::make_pair(line.substr(0 ,pos), value));
		}
	}
}

/**
 * The count method() returns 1 if the key to be found is available
 * 
 * The lower_bound() method finds the first element in the map whose key
 * is either equal to or greater than the given key
 * 
 * ->second accesses the value (first accesses the key)
 */
float	BitcoinExchange::getRate(std::string &date)
{
	if (this->_keyValPair.count(date) > 0)
		return (this->_keyValPair.at(date));
	return ((--this->_keyValPair.lower_bound(date))->second);
}
