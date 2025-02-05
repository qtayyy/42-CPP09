/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:41:13 by qtay              #+#    #+#             */
/*   Updated: 2024/11/18 15:09:59 by qtay             ###   ########.fr       */
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
		cerr << "Invalid number of arguments: usage: ./RPN <n1> <n2> + <n3> - ...";
		return (1);
	}
	RPN	rpn;

	cout << rpn.evalExpression(argv[1]) << endl;
}
