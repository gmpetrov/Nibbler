#ifndef IGRAPHIC_HANDLER_HPP
# define IGRAPHIC_HANDLER_HPP

# include <iostream>

class IGraphicHandler{

public:
	virtual ~IGraphicHandler(void) {};

	virtual void announce(void) = 0;
	virtual void createWindow(int, int) = 0;

};

#endif // IGRAPHIC_HANDLER_HPP