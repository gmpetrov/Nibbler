#ifndef NCURSES_HANDLER_HPP
# define NCURSES_HANDLER_HPP

# include <map>
# include <IGraphicHandler.hpp>
# include <curses.h>

class NcursesHandler : public IGraphicHandler{
public:
	NcursesHandler(int w, int h);
	NcursesHandler(const NcursesHandler & src);
	NcursesHandler &	operator=(NcursesHandler const & rhs);
	~NcursesHandler(void);
	int getWidth() const;
	int getHeight() const;

	void createWindow(void);
	eKeys getKeyPressed(void);
	void clearWindow(void);
	void drawBlock(int x, int y, eColor color);
	void show(void);
	void close(void);

	std::map<int, eKeys> getKeyMap();

private:
	int _getColor(eColor);

	std::map<int, eKeys> _keyMap;
	std::map<eColor, int> _colorMap;

	WINDOW *_window;

	int	_w;
	int _h;
};

#endif // NCURSES_HANDLER_HPP