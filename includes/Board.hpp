/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/10 12:44:42 by gpetrov           #+#    #+#             */
/*   Updated: 2015/10/10 13:09:45 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_HPP
# define BOARD_HPP

# include <iostream>
# include <string>
# include <Enums.hpp>
# include <vector>
# include <IGraphicHandler.hpp>
#include <stdlib.h>
#include <time.h>

class Board{
	public:
		Board(int width, int height);
		~Board(void);
		Board(const Board & src);
		Board &	operator=(Board const & rhs);

		void quit();
		std::vector<std::vector<eBlock>> getMap(void);
		void initMap(void);
		void drawMap(IGraphicHandler *graph);
		void updateMap(void);
		void move(void);
		void setDirection(eDirection);
		void handleKey(eKeys);
		void createBonus(void);
		void removeBonus(void);

		bool isAlive;
		int  getScore() const;
	private:
		Board(void);
		void _growUp(void);
		bool _hasEaten(int);

		std::pair<int, int> _getRandomEmptyLocation(void);
		int	_width;
		int _height;
		eDirection _direction;
		std::vector<std::vector<eBlock>> _map;
		std::vector<std::pair<int, int>> _snake;
		std::pair<int, int> _food;
		int _score;
		std::vector<std::pair<int, int>> _bonus;
		time_t _elapsedTime;
};

#endif