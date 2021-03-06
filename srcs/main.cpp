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
#include <curses.h>
#include <Board.hpp>
#include <map>
#include <unistd.h>
#include <GraphSwitch.hpp>

void	usage(void);
bool	isStringDigit(std::string s);
void 	checkArgs(std::string s1, std::string s2);

int		main(int ac, char **av)
{
	if (ac != 3){
		usage();
	}
	checkArgs(std::string(av[1]), std::string(av[2]));

	srand (time(NULL));

	Board board(std::atoi(av[1]), std::atoi(av[2]));

	GraphSwitch graphic(std::atoi(av[1]), std::atoi(av[2]));

	graphic.setGraphic("sfml");

	while (board.isAlive){
		eKeys key = graphic.graph->getKeyPressed();
		try{
			if (key == eKeys::ONE)
				graphic.setGraphic("sfml");
			else if (key == eKeys::TWO)
				graphic.setGraphic("ncurses");
			else if (key == eKeys::THREE)
				graphic.setGraphic("sdl");
			else
				board.handleKey(key);
		}
		catch(std::string const & e){
			std::cout << e << std::endl;
			graphic.graph->close();
			exit(EXIT_SUCCESS);
		}

		graphic.graph->clearWindow();
		board.drawMap(graphic.graph);
		graphic.graph->show();
	}
	std::cout << "You are dead !" << std::endl << "Score : " << board.getScore() << std::endl;
	graphic.graph->close();
	return (0);
}

void	usage(void)
{
	std::cout << "[Usage] : ./nibbler [ 10 <= WIDTH <= 300] [10 <= HEIGHT <= 300]" << std::endl;
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
	else if (std::atoi(s1.c_str()) < 10 || std::atoi(s1.c_str()) > 300 || std::atoi(s2.c_str()) < 10 || std::atoi(s2.c_str()) > 300){
		usage();
	}
}
