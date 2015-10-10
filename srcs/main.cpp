/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/10 12:35:50 by gpetrov           #+#    #+#             */
/*   Updated: 2015/10/10 13:11:58 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <Board.hpp>

void	usage(void)
{
	std::cout << "[Usage] : ./nibbler [WIDTH] [HEIGHT]" << std::endl;
	exit(EXIT_FAILURE);
}

bool	isStringDigit(std::string s){
	for (std::string::iterator it = s.begin(); it != s.end(); it++){
		if (!isdigit(*it)){
			return false;
		}
	}
	return true;
}

void 	checkArgs(std::string s1, std::string s2){
	if (!isStringDigit(s1) || !isStringDigit(s2)){
		usage();
	}
}

int		main(int ac, char **av)
{
	(void) av;
	if (ac != 3){
		usage();
	}
	checkArgs(std::string(av[1]), std::string(av[2]));
	Board board(std::atoi(av[1]), std::atoi(av[2]));
	return (0);
}
