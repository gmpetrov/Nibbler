#ifndef IGRAPHIC_HANDLER_HPP
# define IGRAPHIC_HANDLER_HPP

# include <iostream>
# include <Enums.hpp>

class IGraphicHandler{

public:
	virtual ~IGraphicHandler(void) {};

	virtual void announce(void) = 0;
	virtual void createWindow(void) = 0;
	virtual eKeys getKeyPressed(void) = 0;
	virtual void clearWindow(void) = 0;
	virtual void draw(void) = 0;
	// virtual void drawBlock(int, int, int) = 0;
};

#endif // IGRAPHIC_HANDLER_HPP