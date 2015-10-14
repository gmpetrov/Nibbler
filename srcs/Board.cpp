/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/10 12:45:21 by gpetrov           #+#    #+#             */
/*   Updated: 2015/10/10 13:09:01 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Board.hpp>

Board::Board(void){}

Board::Board(int width, int height) : isAlive(true), _width(width), _height(height){

	// Init the map
	std::vector<std::vector<eBlock>> init(NUM_BLOCKS_Y, std::vector<eBlock>(100));
	_map = init;

	_map[(NUM_BLOCKS_Y / 2)][(NUM_BLOCKS_X / 2)] = eBlock::SNAKE;
	_map[(NUM_BLOCKS_Y / 2)][(NUM_BLOCKS_X / 2) + 1] = eBlock::SNAKE;
	_map[(NUM_BLOCKS_Y / 2)][(NUM_BLOCKS_X / 2) + 2] = eBlock::SNAKE;
	_map[(NUM_BLOCKS_Y / 2)][(NUM_BLOCKS_X / 2) + 3] = eBlock::SNAKE;
}

Board::~Board(void){

}

Board::Board(const Board & src){
	*this = src;
}

Board &	Board::operator=(Board const & rhs){
	this->_width = rhs._width;
	this->_height = rhs._height;
	return *this;
}

void	Board::quit(void){
	std::cout << "You quit the game" << std::endl;
	exit(0);
}

std::vector<std::vector<eBlock>> Board::getMap(void){
	return _map;
}

// Print Map method, for debugging purpose
void	Board::printMap(void){
	for (int y = 0 ; y < NUM_BLOCKS_Y; y++){
		for (int x = 0; x < NUM_BLOCKS_X; x++){
			std::cout << _map[y][x] ;
		}
		std::cout << std::endl;
	}
}

void 	Board::drawMap(IGraphicHandler *graph){
	for (int y = 0 ; y < NUM_BLOCKS_Y; y++){
		for (int x = 0; x < NUM_BLOCKS_X; x++){
			if (_map[y][x] == eBlock::EMPTY){
				graph->drawBlock(x, y, eColor::DARK_BLUE);
			}
			else if (_map[y][x] == eBlock::SNAKE){
				graph->drawBlock(x, y, eColor::GREEN);
			}
			else if (_map[y][x] == eBlock::ITEM){
				graph->drawBlock(x, y, eColor::RED);
			}
		}
	}
}