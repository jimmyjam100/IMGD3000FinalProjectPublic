
#pragma once
#define NOMINMAX
#include <SFML/Graphics.hpp>
#include "Color.h"
#include "Manager.h"
#include "Vector.h"

const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1700;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 850;
const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 85;
const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
const std::string FONT_FILE_DEFAULT = "df-font.ttf";

#define DM df::DisplayManager::getInstance()
namespace df {

	class DisplayManager : public Manager {
	private:
		DisplayManager(); // dont allow cunstructor to be called
		DisplayManager(DisplayManager const&); // dont allow copys
		void operator=(DisplayManager const&); // dont allow copys
		sf::Font m_font; // font being rendered
		sf::RenderWindow* p_window; //window to render to
		int m_window_horizontal_pixels; //how many pixels horizontally in the window
		int m_window_vertical_pixels; // how many pixels vertically in the window
		int m_window_horizontal_chars; // how may pixels horixontally in a char
		int m_window_vertical_chars; // how many pixels vertically in a char
	public:
		static DisplayManager& getInstance(); //get the one and only instance of Display Manager
		int startUp(); //starts up display manager
		void shutDown(); //shuts down display manager
		int drawCh(Vector world_pos, char ch, Color color) const; //draw a char in the window
		int getHorizontal() const; // get horizontal chars
		int getVertical() const; // ger vertical chars
		int getHorizontalPixels() const; // get horizontal pixels
		int getVerticalPixels() const; // get vertical pixels
		int swapBuffers(); // swap the back buffer with the front one and clear new back buffer
		sf::RenderWindow* getWindow(); // get the window
		int drawString(Vector world_pos, std::string s, Color color) const; // draw a whole string
	};
}