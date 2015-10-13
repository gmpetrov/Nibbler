#ifndef ENUMS_HPP
# define ENUMS_HPP

enum eKeys {
	UNKNOWN = -1,
	ESC,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ONE,
	TWO,
	THREE
};

enum eTile {
	EMPTY = 0,
	SNAKE,
	ITEM
};

enum eColor {
	BLACK = 0,
	RED,
	GREEN,
	BLUE,
	DARK_BLUE
};

#endif // ENUMS_HPP