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
#include <IGraphicHandler.hpp>
#include <dlfcn.h>
#include <map>

void 	dlerror_wrapper(void)
{
	std::cerr << "Error : " << dlerror() << std::endl;
	exit(EXIT_FAILURE);
}

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

	srand (time(NULL));

	Board board(std::atoi(av[1]), std::atoi(av[2]));

	void *dl_handler;
	IGraphicHandler *(*create)(int, int);

	dl_handler = dlopen("./libraries/sfml/libsfml.so", RTLD_LAZY | RTLD_LOCAL);
	create = (IGraphicHandler *(*)(int, int))dlsym(dl_handler, "create");
	if (!create)
		dlerror_wrapper();

	IGraphicHandler *graph = create(std::atoi(av[1]), std::atoi(av[2]));

	graph->createWindow();

	std::map<eKeys, std::string> map = {
		{ eKeys::ESC, "ESC" },
		{ eKeys::UP, "UP" },
		{ eKeys::DOWN, "DOWN" },
		{ eKeys::LEFT, "LEFT" },
		{ eKeys::RIGHT, "RIGHT" }
	};

	while (board.isAlive){
		eKeys key = graph->getKeyPressed();
		if (map.find(key) != map.end()){

			// Pressed Key is mapped
			board.handleKey(key);
		}
		else{

			// Unknown Key or no key pressed so default iteration
			board.move();
		}
		graph->clearWindow();
		board.drawMap(graph);
		graph->show();
	}
	dlclose(dl_handler);
	return (0);
}
