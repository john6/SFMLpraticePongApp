#include "Button.h"


Button::Button(std::string string, sf::RectangleShape positionAndSize) {
	SetPositionAndSize(positionAndSize);
	SetText(string);
	m_state = UP;
	SetColorsFromState();
}

Button::~Button() {
}

sf::RectangleShape Button::GetRect() { return m_positionAndSize; }

sf::Text Button::GetText() { return m_text; }

Button::BUTTON_STATE Button::GetState() {
	return m_state;
}

void Button::SetText(std::string s) {
	m_text.setString(s);
	m_text.setCharacterSize(m_positionAndSize.getSize().x / 10.0f);
	m_text.setPosition(sf::Vector2f(m_positionAndSize.getPosition().x + (m_positionAndSize.getSize().x / 3.0f),
		m_positionAndSize.getPosition().y + (m_positionAndSize.getSize().y / 3.0f)));
}

void Button::SetColorsFromState() {
	switch (m_state) {
	case Button::UP: {
		m_positionAndSize.setFillColor(m_colorUp);
		m_positionAndSize.setOutlineColor(m_colorDown);
		m_text.setFillColor(m_colorDown);
		break;
	}
	case Button::HOVER: {
		m_positionAndSize.setFillColor(m_colorHover);
		m_positionAndSize.setOutlineColor(m_colorDown);
		m_text.setFillColor(m_colorDown);
		break;
	}
	case Button::DOWN: {
		m_positionAndSize.setFillColor(m_colorDown);
		m_positionAndSize.setOutlineColor(m_colorUp);
		m_text.setFillColor(m_colorUp);
		break;
	}
	default: {
		m_positionAndSize.setFillColor(m_colorUp);
		m_positionAndSize.setOutlineColor(m_colorDown);
		m_text.setFillColor(m_colorDown);
		break;
	}
	}
}

void Button::SetPositionAndSize(sf::RectangleShape rect) {
	m_positionAndSize = rect;
	m_positionAndSize.setOutlineThickness(rect.getSize().x / 30);
}

void Button::SetSize(sf::Vector2f size) { m_positionAndSize.setSize(size); }

void Button::SetPosition(sf::Vector2f position) { m_positionAndSize.setPosition(position); }

void Button::SetColors(sf::Color colorUp, sf::Color colorDown, sf::Color colorHover) {
	m_colorUp = colorUp;
	m_colorDown = colorDown;
	m_colorHover = colorHover;
	SetColorsFromState();
}

void Button::SetState(BUTTON_STATE state) {
	m_state = state;
	SetColorsFromState();
}

bool Button::HandleInput(sf::Vector2f mousePosition, bool mouseState) {
	if (true) {
		return true;
	}
	return false;
}
