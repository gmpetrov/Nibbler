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
		{ eColor::DARK_BLUE, { 51, 110, 123 } },
		{ eColor::BLUE, { 134, 226, 213 } },
		{ eColor::RED, { 214, 69, 65 } },
		{ eColor::GREEN, { 104, 195, 163 } },
		{ eColor::VIOLET, { 224, 130, 131 } },
		{ eColor::ORANGE, { 242, 121, 53 } }

	};

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE) ;
	}

	if (!(_window = SDL_CreateWindow("SDL - Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w * BLOCK_SIZE, _h * BLOCK_SIZE, SDL_WINDOW_SHOWN))){
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

	if (TTF_Init() == -1) {
		std::cout << "TTF_init error" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!(_font = TTF_OpenFont("./fonts/PoiretOne-Regular.ttf", 24))){
		std::cerr << "TTF_OpenFont failed" << std::endl;
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
    SDL_Rect rect = { x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE , BLOCK_SIZE };
    SDL_SetRenderDrawColor(_renderer, _colorMap[color][0], _colorMap[color][1], _colorMap[color][2], 255);
    SDL_RenderFillRect(_renderer, &rect);
}

void SdlHandler::close(void){
    SDL_DestroyWindow(_window);
    SDL_Quit();
    TTF_CloseFont(_font);
    TTF_Quit();
}

void SdlHandler::drawBonus(int score){

	std::string msg = "Score : " + std::to_string(score);

	SDL_Color color = {255, 255, 255, 255};

	SDL_Surface *surface = TTF_RenderText_Blended(_font, msg.c_str(), color);

	SDL_Texture *text = SDL_CreateTextureFromSurface(_renderer, surface);


	SDL_Rect textRect;
    textRect.x = 5;
    textRect.y = 5;
    textRect.w = surface->clip_rect.w;
    textRect.h = surface->clip_rect.h;

	SDL_RenderCopy(_renderer, text, NULL, &textRect);

}

extern "C" IGraphicHandler *create(int w, int h)
{
	return new SdlHandler(w, h);
}

extern "C" void destroy(IGraphicHandler *handler)
{
	delete handler;
}