/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:05:00 by qtay              #+#    #+#             */
/*   Updated: 2024/11/18 01:30:12 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;

static std::string	strtrim(const std::string &str)
{
	size_t	start = 0;
	while (start < str.length() && std::isspace(str[start]))
		++start;
	size_t	end = str.length();
	while (end > start && std::isspace(str[end - 1]))
		--end;
	return (str.substr(start, end - start));
}

static bool	containsOnly(const std::string &input, const std::string &allowedChars)
{
	for (size_t i = 0; i < input.length(); ++i)
		if (allowedChars.find(input[i]) == std::string::npos)
			return (false);
	return (true);
}

int strToInt(const std::string& str)
{
    long	result = 0;
    int		sign = 1;
    size_t	i = 0;

	if (str.empty())
		return 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;

	for (; i < str.length(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		int	digit = str[i] - '0';
		result = result * 10 + digit;
	}
	result = result * sign;
	if (result > INT_MAX || result < INT_MIN)
		return (0);
	return (static_cast<int>(result));
}

static bool	isLeapYear(int year)
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}
/**
 * YYYY-MM-DD
 */
static bool	validDate(const std::string &date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	int	year = strToInt(date.substr(0, 4));
	int	month = strToInt(date.substr(5, 2));
	int	day = strToInt(date.substr(8, 2));
	if (year < 2009 || year > 2022 || month < 1 || month > 12 || day < 1)
		return (false);
	
	int	daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && isLeapYear(year))
		daysInMonth[1] = 29;

	if (day > daysInMonth[month - 1] || (year == 2009 && month == 1 && day < 2))
		return (false);

	return (true);
}

static bool	validValue(const std::string &value)
{	
	if (value.empty())
		return (false);
	float	floatValue = strtof(value.c_str(), NULL);
	if (floatValue < 0)
	{
		cerr <<  "Error: not a positive number" << endl;
		return (false);
	}
	if (floatValue > 1000)
	{
		cerr <<  "Error: too large a number" << endl;
		return (false);
	}
	return (true);
}

static void	analyzeInput(std::ifstream &inputFile, BitcoinExchange &btc)
{
	std::string	line;

	std::getline(inputFile, line);
	while (std::getline(inputFile, line))
	{
		size_t	pos = line.find('|');
		if (pos == std::string::npos)
		{
			cerr <<  "Error: bad input => " << line << endl;
			continue ;
		}

		std::string	date = strtrim(line.substr(0, pos));
		if (!containsOnly(line, "0123456789-|. ") || !validDate(date))
		{
			cerr <<  "Error: bad input => " << line << endl;
			continue ;
		}

		std::string	value = strtrim(line.substr(pos + 1));
		if (!validValue(value))
			continue ;
		cout << date << " => " << value << " = " << std::setprecision(2)
			<< strtof(value.c_str(), NULL) * btc.getRate(date) << endl;
	}
}

/**
 * Input file will have the format "date | value"
 * Valid date format: Year-Month-Day
 * Valid value is float/integer from 0-1000
 */
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		cerr << "Invalid number of arguments: usage: ./btc <filename.txt>\n";
		return (1);
	}
	std::ifstream database("data.csv");
	if (!database.is_open())
		cerr << "Error: Could not open data.csv\n";

	std::ifstream input(argv[1]);
	if (!input.is_open())
		cerr << "Error: Could not open " << argv[1] << endl;

	BitcoinExchange	btc;
	btc.readFile(database);

	analyzeInput(input, btc);
	
	database.close();
	input.close();
	return (0);
}
