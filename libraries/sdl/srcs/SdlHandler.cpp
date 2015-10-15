#include "SdlHandler.hpp"

SdlHandler::SdlHandler(int width, int height) : _w(width), _h(height){
	if (!(_window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w, _h, SDL_WINDOW_SHOWN))){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
}

SdlHandler::~SdlHandler(void){}

SdlHandler::SdlHandler(const SdlHandler & src)
{
	*this = src;
}

SdlHandler & SdlHandler::operator=(const SdlHandler & rhs)
{
	_w = rhs.getWidth();
	_h = rhs.getHeight();
	return *this;
}

int		SdlHandler::getWidth(void) const{
	return _w;
}

int 	SdlHandler::getHeight(void) const{
	return _h;
}

std::map<int, eKeys>	SdlHandler::getKeyMap(void){
	return this->_keyMap;
}

void SdlHandler::createWindow(void)
{

}

eKeys SdlHandler::getKeyPressed(void)
{

	return eKeys::UNKNOWN;
}


void SdlHandler::show(){

}

void SdlHandler::clearWindow(void){

}

void SdlHandler::drawBlock(int x, int y, eColor color){
	(void)x;
	(void)y;
	(void)color;
}

void SdlHandler::close(void){

}

extern "C" IGraphicHandler *create(int w, int h)
{
	return new SdlHandler(w, h);
}

extern "C" void destroy(IGraphicHandler *handler)
{
	delete handler;
}