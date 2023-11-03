#include "DisplayManager.h"
#include "LogManager.h"
#include "WorldManager.h"

float charHeight() {
	return (float)DM.getVerticalPixels() / (float)DM.getVertical();
}
float charWidth() {
	return (float)DM.getHorizontalPixels() / (float)DM.getHorizontal();
}
df::Vector spacesToPixels(const df::Vector spaces)
{
	return df::Vector(spaces.getX() * charWidth(), spaces.getY() * charHeight());
}
df::Vector pixelsToSpaces(const df::Vector pixels)
{
	return df::Vector(pixels.getX() / charWidth(), pixels.getY() / charHeight());
}
df::Vector worldToView(df::Vector world_pos) {
	df::Vector view_origin = WM.getView().getCorner();
	int view_x = view_origin.getX();
	int view_y = view_origin.getY();
	df::Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
	return view_pos;
}

namespace df {

	DisplayManager::DisplayManager() {
		m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
		m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
		m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
		m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
		//p_window = //new sf::RenderWindow(sf::VideoMode(m_window_horizontal_pixels, m_window_vertical_pixels), "Dragonfly1");
	}
	void DisplayManager::operator=(DisplayManager const&){

	}

	DisplayManager& DisplayManager::getInstance()
	{
		static DisplayManager single;
		return single;
	}

	int DisplayManager::startUp(){

		if (p_window != NULL) {
			return 0;
		}
		p_window = new sf::RenderWindow(sf::VideoMode(m_window_horizontal_pixels, m_window_vertical_pixels), WINDOW_TITLE_DEFAULT.c_str());
		p_window->setMouseCursorVisible(false);
		p_window->setVerticalSyncEnabled(true);

		if (m_font.loadFromFile(FONT_FILE_DEFAULT.c_str()) == false) {
			std::cout << "Failed to load font" << FONT_FILE_DEFAULT << std::endl;
			LM.writeLog("Failed to load font: %s", FONT_FILE_DEFAULT.c_str());
			return -1;
		}
		if (p_window != NULL) {
			return Manager::startUp();
		}
		return -1;
	}

	void DisplayManager::shutDown(){
		p_window = NULL;
		Manager::shutDown();
	}

	int DisplayManager::drawCh(Vector world_pos, char ch, Color color) const{
		if (ch == ' ') {
			return 0;
		}
		if (p_window == NULL) {
			return -1;
		}
		Vector view_pos = worldToView(world_pos);
		Vector pixel_pos = spacesToPixels(view_pos);

		static sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(charWidth(), charHeight() - 1));
		rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
		rectangle.setSize(sf::Vector2f(charWidth(), charHeight() - 1));
		//rectangle.setFillColor(sf::Color::Blue);
		rectangle.setPosition(pixel_pos.getX() + charWidth() / 10, pixel_pos.getY() + charHeight() / 5);
		//rectangle.setPosition(pixel_pos.getX(), pixel_pos.getY());
		//p_window->draw(rectangle);
		std::string c = std::string(1, ch);
		sf::Text text(c.c_str(), m_font);
		if (charWidth() < charHeight()) {
			text.setCharacterSize(charWidth() * 2);
		}
		else {
			text.setCharacterSize(charHeight() * 2);
		}
		switch (color)
		{
		case BLACK:
			text.setFillColor(sf::Color::Black);
			break;
		case RED:
			text.setFillColor(sf::Color::Red);
			break;
		case GREEN:
			text.setFillColor(sf::Color::Green);
			break;
		case YELLOW:
			text.setFillColor(sf::Color::Yellow);
			break;
		case BLUE:
			text.setFillColor(sf::Color::Blue);
			break;
		case MAGENTA:
			text.setFillColor(sf::Color::Magenta);
			break;
		case CYAN:
			text.setFillColor(sf::Color::Cyan);
			break;
		case WHITE:
			text.setFillColor(sf::Color::White);
			break;
		default:
			break;
		}
		text.setPosition(pixel_pos.getX(), pixel_pos.getY());
		p_window->draw(text);
		return 0;
	}

	int DisplayManager::getHorizontal() const{
		return m_window_horizontal_chars;
	}

	int DisplayManager::getVertical() const{
		return m_window_vertical_chars;
	}

	int DisplayManager::getHorizontalPixels() const{
		return m_window_horizontal_pixels;
	}

	int DisplayManager::getVerticalPixels() const{
		return m_window_vertical_pixels;
	}

	int DisplayManager::swapBuffers(){

		if (p_window == NULL) {
			return -1;
		}
		p_window->display();
		p_window->clear();
		return 0;
	}
	sf::RenderWindow* DisplayManager::getWindow()
	{
		return p_window;
	}

	int DisplayManager::drawString(Vector world_pos, std::string s, Color color) const {
		for (int i = 0; i < s.size(); i++) {
			Vector nVector = Vector(world_pos.getX() + i - s.length()/2, world_pos.getY());
			if (drawCh(nVector, s[i], color) != 0) {
				return -1;
			}
		}
		return 0;
	}

}

