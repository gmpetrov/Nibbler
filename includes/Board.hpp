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

# define BLOCK_SIZE 20
# define NUM_BLOCKS_X 100
# define NUM_BLOCKS_Y 100

class Board{
	public:
		Board(int width, int height);
		~Board(void);
		Board(const Board & src);
		Board &	operator=(Board const & rhs);

		void quit();
		std::vector<std::vector<eBlock>> getMap(void);
		void initMap(void);
		void printMap(void);
		void drawMap(IGraphicHandler *graph);

		bool isAlive;
	private:
		Board(void);
		int	_width;
		int _height;
		std::vector<std::vector<eBlock>> _map;
		// std::vector<std::vector<int>> _m(NUM_BLOCKS_Y, std::vector<int>(NUM_BLOCKS_X));
};

#endif