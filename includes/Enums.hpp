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

enum eBlock {
	EMPTY = 0,
	SNAKE,
	SNAKE_HEAD,
	ITEM
};

enum eColor {
	BLACK = 0,
	RED,
	GREEN,
	BLUE,
	DARK_BLUE,
	VIOLET
};

enum eDirection{
	TOP = 0,
	TRIBORD,
	BABORD,
	BOTTOM
};

#endif // ENUMS_HPP