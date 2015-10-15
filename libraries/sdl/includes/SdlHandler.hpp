#ifndef SDL_HANDLER_HPP
# define SDL_HANDLER_HPP

# include <map>
# include <IGraphicHandler.hpp>
# include <SDL2/SDL.h>

class SdlHandler : public IGraphicHandler{
public:
	SdlHandler(int w, int h);
	SdlHandler(const SdlHandler & src);
	SdlHandler &	operator=(SdlHandler const & rhs);
	~SdlHandler(void);
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
	std::map<int, eKeys> _keyMap;
	int	_w;
	int _h;
	SDL_Window *_window;
};

#endif //SFML_HANDLER_HPP