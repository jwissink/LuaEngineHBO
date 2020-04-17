#pragma once
#include "Button.hpp"
class Textfield :	public Button
{
public:
	Textfield(std::string aName, std::string fontName, const sf::Vector2f size);
	virtual ~Textfield();
	void handler(sf::RenderWindow &window);
private:
	sf::Vector2f m_size;
	sf::RectangleShape m_body;

	sf::Font* m_font;
	sf::Text m_text;

	sf::Color m_backgroundColor;
	sf::Color m_textColor;
	sf::Color m_outlineColor;

	sf::Color m_overBackgroundColor;
	sf::Color m_overTextColor;
	sf::Color m_overOutlineColor;

	bool m_overActive;

	bool m_mouseCursorOver;
	bool m_buttonPressed;
	function m_triggerFunction;
	std::string name;
	void update();
	sf::Font font;
};

