#include "NcursesHandler.hpp"

NcursesHandler::NcursesHandler(int width, int height) : _w(width), _h(height){

	initscr();

	_window = newwin(_h, _w, 0, 0);
	// Enable colors
	start_color();

	// Enable use of keyboards
	keypad(stdscr,1);

	nodelay(stdscr, TRUE);

	// Key pressed not 'echoed'
	noecho();

	// Remove cursor
	curs_set(FALSE);

	this->_keyMap = {
		{ 27, eKeys::ESC },
		{ KEY_UP, eKeys::UP },
		{ KEY_DOWN, eKeys::DOWN },
		{ KEY_LEFT, eKeys::LEFT },
		{ KEY_RIGHT, eKeys::RIGHT },
		{ 49, eKeys::ONE },
		{ 50, eKeys::TWO },
		{ 51, eKeys::THREE }
	};

	init_color(COLOR_RED, 231, 76, 60); 	// 1
	init_color(COLOR_BLUE, 231, 76, 60); 	// 2
	init_color(COLOR_GREEN, 46, 204, 113); 	// 3
	init_color(COLOR_CYAN, 52, 73, 94); 	// 4
	init_color(COLOR_MAGENTA, 61, 35, 71); 	// 5

	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
	init_pair(4, COLOR_CYAN, COLOR_CYAN);
	init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);

	this->_colorMap = {
		{ eColor::BLACK, COLOR_BLACK },
		{ eColor::DARK_BLUE, COLOR_PAIR(4) },
		{ eColor::BLUE, COLOR_PAIR(2) },
		{ eColor::RED, COLOR_PAIR(1) },
		{ eColor::GREEN, COLOR_PAIR(3) },
		{ eColor::VIOLET, COLOR_PAIR(5) }
	};
}

NcursesHandler::~NcursesHandler(void){

}

NcursesHandler::NcursesHandler(const NcursesHandler & src)
{
	*this = src;
}

NcursesHandler & NcursesHandler::operator=(const NcursesHandler & rhs)
{
	_w = rhs.getWidth();
	_h = rhs.getHeight();
	return *this;
}

int		NcursesHandler::getWidth(void) const{
	return _w;
}

int 	NcursesHandler::getHeight(void) const{
	return _h;
}

std::map<int, eKeys>	NcursesHandler::getKeyMap(void){
	return this->_keyMap;
}

void NcursesHandler::createWindow(void)
{

}

eKeys NcursesHandler::getKeyPressed(void)
{
	int c;
	usleep(200000);
    if ((c = getch()) != ERR) {
        if (_keyMap.find(c) != _keyMap.end()) {
            return _keyMap[c];
        } else {
            return eKeys::UNKNOWN;
        }
    }
    return eKeys::UNKNOWN;
}

int NcursesHandler::_getColor(eColor color){
	if (_colorMap.find(color) != _colorMap.end()){
		return (_colorMap[color]);
	}
	return COLOR_CYAN;
}

void NcursesHandler::show(){
	wrefresh(_window);
}

void NcursesHandler::clearWindow(void){
	werase(_window);
}

void NcursesHandler::drawBlock(int x, int y, eColor color){
    wattrset(_window, _getColor(color));
    mvwaddch(_window, y, x, ' ');
    wattroff(_window, _getColor(color));
}

void NcursesHandler::close(void){
    delwin(_window);
    endwin();
}

extern "C" IGraphicHandler *create(int w, int h)
{
	return new NcursesHandler(w, h);
}

extern "C" void destroy(IGraphicHandler *handler)
{
	delete handler;
}