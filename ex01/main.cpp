/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:41:13 by qtay              #+#    #+#             */
/*   Updated: 2025/02/06 16:12:39 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		cerr << "Invalid number of arguments: usage: ./RPN \"<n1> <n2> + <n3> - ...\"\n";
		return (1);
	}
	RPN	rpn;

	cout << rpn.evalExpression(argv[1]) << endl;
}
