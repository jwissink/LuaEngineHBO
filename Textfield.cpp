#include "stdafx.h"
#include "Textfield.hpp"


Textfield::Textfield(std::string aName, std::string fontName, const sf::Vector2f size)
	: m_overActive(true)
	, m_buttonPressed(false)
	, name(aName) {
	setSize(size);
	
	if (!font.loadFromFile(fontName)) {
		std::cout << fontName << " not found, falling back to default" << std::endl;
		font.loadFromFile("minster.ttf");
	}

	setFont(font);
}


Textfield::~Textfield() {
}
void Textfield::handler(sf::RenderWindow &window) {
	
}
void Textfield::update() {
	if (m_size.x > 0 && m_size.y > 0 && m_text.getString() != "") {
		if (m_text.getGlobalBounds().width < m_size.x / 4 * 3 && m_text.getGlobalBounds().height < m_size.y - 10.f) {
			while (m_text.getGlobalBounds().width < m_size.x / 4 * 3 && m_text.getGlobalBounds().height < m_size.y - 10.f) {
				m_text.setCharacterSize(m_text.getCharacterSize() + 1);
			}
			if (m_text.getGlobalBounds().width < m_size.x / 4 * 3 || m_text.getGlobalBounds().height < m_size.y - 10.f) {
				m_text.setCharacterSize(m_text.getCharacterSize() - 1);
			}
		} else {
			while (m_text.getGlobalBounds().width > m_size.x / 4 * 3 && m_text.getGlobalBounds().height > m_size.y - 10.f) {
				m_text.setCharacterSize(m_text.getCharacterSize() - 1);
			}
			if (m_text.getGlobalBounds().width > m_size.x / 4 * 3 || m_text.getGlobalBounds().height > m_size.y - 10.f) {
				m_text.setCharacterSize(m_text.getCharacterSize() + 1);
			}
		}

		m_text.setOrigin(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2);
		m_text.setPosition(m_size.x / 2, m_size.y / 2);
	}
}