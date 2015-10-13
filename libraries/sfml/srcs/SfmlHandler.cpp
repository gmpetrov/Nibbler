#include "SfmlHandler.hpp"

SfmlHandler::SfmlHandler(int width, int height) : _w(width), _h(height){
	(void)_w;
	(void)_h;
	this->_keyMap = {
		{ sf::Keyboard::Escape, eKeys::ESC },
		{ sf::Keyboard::Up, eKeys::UP },
		{ sf::Keyboard::Down, eKeys::DOWN },
		{ sf::Keyboard::Left, eKeys::LEFT },
		{ sf::Keyboard::Right, eKeys::RIGHT },
		{ sf::Keyboard::Num1, eKeys::ONE },
		{ sf::Keyboard::Num2, eKeys::TWO },
		{ sf::Keyboard::Num3, eKeys::THREE }
	};

	// _colorMap = {
	// 	{ eColor::BLACK, sf::Color(0, 0, 0) },
	// 	{ eColor::DARK_BLUE, sf::Color(52, 73, 94) },
	// 	{ eColor::BLUE, sf::Color(22, 160, 133) },
	// 	{ eColor::RED, sf::Color(231, 76, 60) },
	// 	{ eColor::GREEN, sf::Color(46, 204, 113) }
	// };
}

SfmlHandler::~SfmlHandler(void){}

SfmlHandler::SfmlHandler(const SfmlHandler & src)
{
	*this = src;
}

SfmlHandler & SfmlHandler::operator=(const SfmlHandler & rhs)
{
	(void)rhs;
	return *this;
}

std::map<int, eKeys>	SfmlHandler::getKeyMap(void){
	return this->_keyMap;
}

void SfmlHandler::announce(void)
{
	std::cout << "I'am the sfml shared library" << std::endl;
}

void SfmlHandler::createWindow(void)
{
    _window = new sf::RenderWindow(sf::VideoMode(_w, _h), "Nibbler");
}

eKeys SfmlHandler::getKeyPressed(void)
{
	sf::Event event;

	// While there is events to handle
	while (_window->pollEvent(event))
	{
	    // Check the type of event
	    if (event.type == sf::Event::Closed){
	    	// Window Closed Event
	    	return eKeys::ESC;

	    }
	    else if (event.type == sf::Event::KeyPressed){
	    	// Key Pressed
	    	if (_keyMap.find(event.key.code) != _keyMap.end()){
	    		return _keyMap[event.key.code];
	    	}
	    	return eKeys::UNKNOWN;
	    }
	}
	return eKeys::UNKNOWN;
}

// sf::Color SfmlHandler::_getColor(eColor color){
// 	if (_colorMap.find(color) != _colorMap.end()){
// 		return (_colorMap[color]);
// 	}
// 	return sf::Color(55, 55, 55);
// }

void SfmlHandler::draw(void){
	// définit un rectangle de 120x50
	sf::RectangleShape rectangle(sf::Vector2f(120, 50));

	// change sa taille en 100x100
	rectangle.setSize(sf::Vector2f(100, 100));
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color::Green);

	_window->draw(rectangle);
	_window->display();
}

void SfmlHandler::clearWindow(void){
	_window->clear(sf::Color::Black);
}

extern "C" IGraphicHandler *create(int w, int h)
{
	return new SfmlHandler(w, h);
}

extern "C" void destroy(IGraphicHandler *handler)
{
	delete handler;
}