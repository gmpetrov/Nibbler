#ifndef SFML_HANDLER_HPP
# define SFML_HANDLER_HPP

# include <map>
# include <IGraphicHandler.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>

# define SQUARE_SIZE 20

class SfmlHandler : public IGraphicHandler{
public:
	SfmlHandler(int w, int h);
	SfmlHandler(const SfmlHandler & src);
	SfmlHandler &	operator=(SfmlHandler const & rhs);
	~SfmlHandler(void);

	void announce(void);
	void createWindow(void);
	eKeys getKeyPressed(void);
	void clearWindow(void);
	void draw(void);
	void drawBlock(int x, int y, eColor color);

	std::map<int, eKeys> getKeyMap();

private:
	sf::Color _getColor(eColor);

	std::map<int, eKeys> _keyMap;
	std::map<eKeys, sf::Color> _colorMap;
	sf::RenderWindow *_window;
	int	_w;
	int _h;
};

#endif //SFML_HANDLER_HPP