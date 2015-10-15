#include "SdlHandler.hpp"

SdlHandler::SdlHandler(int width, int height) : _w(width), _h(height){

	this->_keyMap = {
		{ SDLK_ESCAPE, eKeys::ESC },
		{ SDLK_UP, eKeys::UP },
		{ SDLK_DOWN, eKeys::DOWN },
		{ SDLK_LEFT, eKeys::LEFT },
		{ SDLK_RIGHT, eKeys::RIGHT },
		{ SDLK_1, eKeys::ONE },
		{ SDLK_2, eKeys::TWO },
		{ SDLK_3, eKeys::THREE }
	};

	this->_colorMap = {
		{ eColor::BLACK, { 0, 0, 0 } },
		{ eColor::DARK_BLUE, { 52, 73, 94 } },
		{ eColor::BLUE, { 22, 160, 133 } },
		{ eColor::RED, { 231, 76, 60 } },
		{ eColor::GREEN, { 46, 204, 113 } },
		{ eColor::VIOLET, { 61, 35, 71 } }

	};

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE) ;
	}

	if (!(_window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w, _h, SDL_WINDOW_SHOWN))){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	if (!(_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))){
		SDL_DestroyWindow(_window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	clearWindow();
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
	SDL_Event event;

	while (SDL_PollEvent(&event)){
	    // Check the type of event
	    if (event.type == SDL_QUIT){
	    	// Window Closed Event
	    	return eKeys::ESC;
	    }
	    else if (event.type == SDL_KEYDOWN){
	    	// Key Pressed
	    	if (_keyMap.find(event.key.keysym.sym) != _keyMap.end()){
	    		return _keyMap[event.key.keysym.sym];
	    	}
	    	return eKeys::UNKNOWN;
	    }
	}
	return eKeys::UNKNOWN;
}


void SdlHandler::show(){
    SDL_RenderPresent(_renderer);
}

void SdlHandler::clearWindow(void){
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void SdlHandler::drawBlock(int x, int y, eColor color){
    SDL_Rect rect = { x * (_w / NUM_BLOCKS_X), y * (_h / NUM_BLOCKS_Y), _w / NUM_BLOCKS_X , _h / NUM_BLOCKS_Y };
    SDL_SetRenderDrawColor(_renderer, _colorMap[color][0], _colorMap[color][1], _colorMap[color][2], 255);
    SDL_RenderFillRect(_renderer, &rect);
}

void SdlHandler::close(void){
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

extern "C" IGraphicHandler *create(int w, int h)
{
	return new SdlHandler(w, h);
}

extern "C" void destroy(IGraphicHandler *handler)
{
	delete handler;
}