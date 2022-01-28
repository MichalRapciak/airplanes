/// <summary>
/// Michael Rapciak
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void movement();
	void processMousePress(sf::Event t_event);
	void processMouseRelease(sf::Event t_event);

	void setupPlaneSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Texture m_planeText; // plane texture
	sf::Texture m_biggerPlaneText; // big plane texture
	sf::Sprite m_smallPlaneSprite; // small plane sprite
	sf::Sprite m_biggerPlaneSprite; // big plane sprite

	sf::Vector2f m_clickDown{ 0.0f, 0.0f }; // mouse click down
	sf::Vector2f m_clickUp{ 0.0f, 0.0f }; // mouse click up
	sf::Vector2f m_smallPlaneLocation{ 300.0f, 200.0f }; // tracks location of small plane
	sf::Vector2f m_smallPlaneVelocity{ 1.0f, 1.0f }; // velocity of small plane
	sf::Vector2f m_biggerPlaneLocation{ 500.0f, 400.0f }; // location of big plane
	sf::Vector2f m_biggerPlaneVelocity{ -1.0f, -1.0f }; // velocity of big plane
	float m_smallPlaneFacing = 135.0f; // where the small plane is facing
	float m_biggerPlaneFacing = 315.0f; // where the bigger plane is facing

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

