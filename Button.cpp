#include "stdafx.h"
#include "Button.hpp"


Button::Button(std::string aName, std::string fontName, const sf::Vector2f size)
	: m_overActive(true)
	, m_buttonPressed(false)
	, name(aName){
	setSize(size);
	

	if (!font.loadFromFile(fontName)) {
		std::cout << fontName << " not found, falling back to default" << std::endl;
		font.loadFromFile("minster.ttf");
	}
	
	setFont(font);
}

void Button::setSize(const sf::Vector2f size) {
	m_size = size;
	m_body.setSize(m_size);
	update();
}

void Button::setFont(sf::Font &font) {
	m_font = &font;
	m_text.setFont(*m_font);
	update();
}

void Button::setString(const std::string string) {
	m_text.setString(string);
	update();
}

void Button::setBackgroundColor(const sf::Color &color) {
	m_backgroundColor = color;
	m_body.setFillColor(color);
}

void Button::setTextColor(const sf::Color &color) {
	m_textColor = color;
	m_text.setColor(color);
}

void Button::setOutlineThickness(float thickness) {
	m_body.setOutlineThickness(thickness);
}

void Button::setOutlineColor(const sf::Color &color) {
	m_outlineColor = color;
	m_body.setOutlineColor(color);
}

sf::Vector2f Button::getSize() {
	return m_size;
}

void Button::setOverAction(bool active) {
	m_overActive = active;
}

void Button::setOverBackgroundColor(const sf::Color &color) {
	m_overBackgroundColor = color;
}

void Button::setOverTextColor(const sf::Color &color) {
	m_overTextColor = color;
}

void Button::setOverOutlineColor(const sf::Color &color) {
	m_overOutlineColor = color;
}

void Button::handler(sf::RenderWindow &window) {
	m_mouseCursorOver = false;
	sf::FloatRect body(getPosition().x, getPosition().y, m_size.x, m_size.y);
	if (body.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
		m_mouseCursorOver = true;
		if (m_overActive) {
			m_text.setColor(m_overTextColor);
			m_body.setFillColor(m_overBackgroundColor);
			m_body.setOutlineColor(m_overOutlineColor);
		}
		//edit else if to else if (m_text.getColor() != m_textColor) 
	} else  {
		m_text.setColor(m_textColor);
		m_body.setFillColor(m_backgroundColor);
		m_body.setOutlineColor(m_outlineColor);
	} 
}

void Button::events(sf::Event &event) {
	if (event.type == sf::Event::MouseButtonPressed && m_mouseCursorOver) {
		m_buttonPressed = true;
	} else if (m_buttonPressed && event.type == sf::Event::MouseButtonReleased) {
		m_buttonPressed = false;
		if (m_mouseCursorOver && m_triggerFunction != nullptr) {
			m_triggerFunction(name);
		}
	}
}

void Button::setTriggerFunction(function triggerFunction) {
	m_triggerFunction = triggerFunction;
}

std::string Button::getName() {
	return name;
}


void Button::update() {
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

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(m_body, states);
	target.draw(m_text, states);
}