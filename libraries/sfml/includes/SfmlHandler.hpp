#ifndef SFML_HANDLER_HPP
# define SFML_HANDLER_HPP

# include <IGraphicHandler.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>

class SfmlHandler : public IGraphicHandler{
public:
	SfmlHandler(void);
	SfmlHandler(const SfmlHandler & src);
	SfmlHandler &	operator=(SfmlHandler const & rhs);
	~SfmlHandler(void);
	void announce(void);
	void createWindow(int, int);
};

#endif //SFML_HANDLER_HPP