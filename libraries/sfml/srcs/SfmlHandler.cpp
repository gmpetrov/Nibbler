#include "SfmlHandler.hpp"

SfmlHandler::SfmlHandler(void){}

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

void SfmlHandler::announce(void)
{
	std::cout << "I'am the sfml shared library" << std::endl;
}

void SfmlHandler::createWindow(int width, int height)
{
    sf::Window window(sf::VideoMode(width, height), "Nibbler");

    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

}

extern "C" IGraphicHandler *create(void)
{
	return new SfmlHandler();
}

extern "C" void destroy(IGraphicHandler *handler)
{
	delete handler;
}