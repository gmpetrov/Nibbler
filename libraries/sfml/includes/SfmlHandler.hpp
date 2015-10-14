#ifndef SFML_HANDLER_HPP
# define SFML_HANDLER_HPP

# include <map>
# include <IGraphicHandler.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>

# define BLOCK_SIZE 20
# define NUM_BLOCKS_X 100
# define NUM_BLOCKS_Y 100

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

	std::map<int, eKeys> getKeyMap();

private:
	sf::Color _getColor(eColor);

	std::map<int, eKeys> _keyMap;
	std::map<eColor, sf::Color> _colorMap;
	sf::RenderWindow *_window;
	int	_w;
	int _h;
};

#endif //SFML_HANDLER_HPP