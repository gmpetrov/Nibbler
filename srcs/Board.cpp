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

Board::Board(int width, int height) : isAlive(true), _width(width), _height(height), _score(0){

	// Init the map
	std::vector<std::vector<eBlock>> init(_height, std::vector<eBlock>(_width));
	_map = init;

	// Init Snake
	std::vector<std::pair<int, int>> initSnake(4, std::pair<int, int>());
	_snake = initSnake;

	_snake[0] = std::make_pair(_width / 2, _height / 2);
	_snake[1] = std::make_pair((_width / 2) + 1, _height / 2);
	_snake[2] = std::make_pair((_width / 2) + 2, _height / 2);
	_snake[3] = std::make_pair((_width / 2) + 3, _height / 2);

	_direction = eDirection::BABORD;

	_food = _getRandomEmptyLocation();

	updateMap();

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
	for (int y = 0 ; y < _height; y++){
		for (int x = 0; x < _width; x++){
			std::cout << _map[y][x] ;
		}
		std::cout << std::endl;
	}
}

void	Board::updateMap(void){
	if (!isAlive)
		return ;

	// Update snake position on the map
	for (size_t i = 0; i < _snake.size(); i++){
		int x = _snake[i].first;
		int y = _snake[i].second;

		if (i == 0){
			_map[y][x] = eBlock::SNAKE_HEAD;
		}
		else if (_map[y][x] == eBlock::EMPTY || _map[y][x] == eBlock::SNAKE_HEAD){
			_map[y][x] = eBlock::SNAKE;
		}

		if (x == _food.first && y == _food.second){
			// Snake ate food

			_map[y][x] = eBlock::SNAKE_HEAD;
			_growUp();
			_food = _getRandomEmptyLocation();
		}
	}

	//Update food position on the map
	int x = _food.first;
	int y = _food.second;
	_map[y][x] = eBlock::FOOD;
}

void 	Board::drawMap(IGraphicHandler *graph){
	for (int y = 0 ; y < _height; y++){
		for (int x = 0; x < _width; x++){
			if (_map[y][x] == eBlock::EMPTY){
				graph->drawBlock(x, y, eColor::DARK_BLUE);
			}
			else if (_map[y][x] == eBlock::SNAKE){
				graph->drawBlock(x, y, eColor::GREEN);
			}
			else if (_map[y][x] == eBlock::FOOD){
				graph->drawBlock(x, y, eColor::VIOLET);
			}
			else if (_map[y][x] == eBlock::SNAKE_HEAD){
				graph->drawBlock(x, y, eColor::RED);
			}
		}
	}

	graph->drawBonus(_score);
}

void	Board::move(void){

	// Get the coordinate of the last snake's block
	int x = _snake[_snake.size() - 1].first;
	int y = _snake[_snake.size() - 1].second;

	// Setting the block as empty
	_map[y][x] = eBlock::EMPTY;

	// Updating the position of snake's block
	for (size_t i = (_snake.size() - 1); i >= 1; i--){
		_snake[i] = _snake[i - 1];
	}

	// Updating the position of the head depending his direction
	if (_direction == eDirection::TOP){
		_snake[0].second -= 1;

		// Checking if snake is out of bounds
		if (_snake[0].second < 0 || (_map[_snake[0].second][_snake[0].first] == eBlock::SNAKE)){
			isAlive = false;
		}
	}
	else if (_direction == eDirection::BOTTOM){
		_snake[0].second += 1;
		if (_snake[0].second >= _height || (_map[_snake[0].second][_snake[0].first] == eBlock::SNAKE)){
			isAlive = false;
		}
	}
	else if (_direction == eDirection::TRIBORD){
		_snake[0].first += 1;
		if (_snake[0].first >= _width || (_map[_snake[0].second][_snake[0].first] == eBlock::SNAKE))
			isAlive = false;
	}
	else if (_direction == eDirection::BABORD || (_map[_snake[0].second][_snake[0].first] == eBlock::SNAKE)){
		_snake[0].first -= 1;
		if (_snake[0].first < 0)
			isAlive = false;
	}

	updateMap();
}

void	Board::setDirection(eDirection direction){
	_direction = direction;
}

void 	Board::handleKey(eKeys key){
	if (key == eKeys::ESC){
		throw std::string("You quit !");
	}
	else if (key == eKeys::UP && _direction != eDirection::BOTTOM){
		setDirection(eDirection::TOP);
	}
	else if (key == eKeys::DOWN && _direction != eDirection::TOP){
		setDirection(eDirection::BOTTOM);
	}
	else if (key == eKeys::LEFT && _direction != eDirection::TRIBORD){
		setDirection(eDirection::BABORD);
	}
	else if (key == eKeys::RIGHT && _direction != eDirection::BABORD){
		setDirection(eDirection::TRIBORD);
	}
	move();
}

void	Board::_growUp(void){
	std::pair<int, int> tmp = _snake[_snake.size() - 1];
	int x = tmp.first;
	int y = tmp.second;

	_snake.push_back(std::make_pair(x + 1, y));

	_score += 1;
}

std::pair<int, int>	Board::_getRandomEmptyLocation(void){
	std::vector<std::pair<int, int>> locations;

	for (int y = 0; y < _height; y++){
		for (int x = 0; x < _width; x++){
			if (_map[y][x] == eBlock::EMPTY){
				locations.push_back(std::make_pair(x, y));
			}
		}
	}

	int size = locations.size() - 1;
	int rnd = rand() % (size + 1);

	return locations[rnd];
}