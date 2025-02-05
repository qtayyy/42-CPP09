/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:31:53 by qtay              #+#    #+#             */
/*   Updated: 2024/11/18 15:10:56 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <iostream>
#include <sstream>
#include <cctype>
#include <climits>
#include <stdlib.h>

enum exprToken
{
	OPERAND,
	OPERATOR
};

class RPN
{
	private:
		std::stack<int>	_storage;

	public:
		RPN(void);
		RPN(const RPN &other);
		RPN	&operator=(const RPN &other);
		~RPN(void);

		int	evalExpression(const std::string &args);
};

#endif
