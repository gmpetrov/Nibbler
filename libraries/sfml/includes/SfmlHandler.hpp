#ifndef SFML_HANDLER_HPP
# define SFML_HANDLER_HPP

# include <map>
# include <IGraphicHandler.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/Audio.hpp>

class SfmlHandler : public IGraphicHandler{
public:
	SfmlHandler(int w, int h);
	SfmlHandler(const SfmlHandler & src);
	SfmlHandler &	operator=(SfmlHandler const & rhs);
	~SfmlHandler(void);
	int getWidth() const;
	int getHeight() const;

	void createWindow(void);
	eKeys getKeyPressed(void);
	void clearWindow(void);
	void drawBlock(int x, int y, eColor color);
	void show(void);
	void close(void);
	void drawBonus(int);

	std::map<int, eKeys> getKeyMap();

private:
	sf::Color _getColor(eColor);

	std::map<int, eKeys> _keyMap;
	std::map<eColor, sf::Color> _colorMap;
	sf::RenderWindow *_window;
	int	_w;
	int _h;
	sf::Font _font;
};

#endif //SFML_HANDLER_HPP