/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:35:42 by qtay              #+#    #+#             */
/*   Updated: 2025/02/06 16:20:45 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
using std::cout;
using std::endl;
using std::cerr;

RPN::RPN(void) {}

RPN::RPN(const RPN &other) :_storage(other._storage) {}

RPN	&RPN::operator=(const RPN &other)
{
	if (this != &other)
		this->_storage = other._storage;
	return (*this);
}

RPN::~RPN(void) {}

static bool	validChars(const std::string& args, exprToken token)
{
	if (token == OPERAND)
	{
		if (args.find_first_not_of("0123456789") == std::string::npos)
	    	return (true);		
	}
	else if (token == OPERATOR)
	{
		if (args.find_first_not_of("+-*/") == std::string::npos)
	    	return (true);		
	}
	return (false);
}

static int ft_stoi(const std::string& str)
{
	long	result = 0;
	int		sign = 1;
	size_t	i = 0;
	errno = 0;

	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}

	while (str[i] >= '0' && str[i] <= '9')
	{
		int	digit = str[i] - '0';
		if (sign == 1 && (result > (INT_MAX - digit) / 10))
		{
			errno = ERANGE;
			return (INT_MAX);
		}
		if (sign == -1 && (-result < (INT_MIN + digit) / 10))
		{
			errno = ERANGE;
			return (INT_MIN);
		}
		result = result * 10 + digit;
		i++;
	}
	return (static_cast<int>(result * sign));
}

/**
 * Take digits from 0-9
 */
int	RPN::evalExpression(const std::string &args)
{
	std::string	token;
	std::istringstream	ss(args);
	int	num;

	while (std::getline(ss, token, ' '))
	{
		if (validChars(token, OPERAND))
		{
			num = ft_stoi(token);
			if (errno == ERANGE || num < 0 || num > 9)
			{
				cerr << "Error: Number must be between 0 and 9\n";
				exit(1);
			}
			this->_storage.push(num);
		}

		else if (validChars(token, OPERATOR) && this->_storage.size() >= 2)
		{
			int	num1 = this->_storage.top();
			this->_storage.pop();
			int	num2 = this->_storage.top();
			this->_storage.pop();

			int	result;
			switch (token.at(0))
			{
			case ('+'): result = num2 + num1; break;
			
			case ('-'): result = num2 - num1; break;
			
			case ('*'): result = num2 * num1; break;

			case ('/'):
				if (num1 != 0)
					result = num2 / num1;
				else
				{
					cerr << "Error: Division by zero\n";
					exit(1);
				}
				break;

			default:
				break;
			}
			this->_storage.push(result);
		}
		else
		{
			cerr << "Error\n";
			exit(1);
		}
	}
	if (this->_storage.size() == 1)
		return (this->_storage.top());
	cerr << "Error\n";
	exit(1);
}
