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
	void movePlane();
	void processMousePress(sf::Event t_event);
	void processMouseRelease(sf::Event t_event);

	void setupPlaneSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Texture m_planeText; // plane texture
	sf::Sprite m_smallPlaneSprite; // small plane sprite
	sf::Sprite m_bigPlaneSprite; // big plane sprite

	sf::Vector2f m_firstClick{ 0.0f, 0.0f }; // First mouse click
	sf::Vector2f m_secondClick{ 0.0f, 0.0f }; // second mouse click
	sf::Vector2f m_smallPlaneLocation; // tracks location of small plane
	sf::Vector2f m_smallPlaneVelocity{ -2.0f,2.0f }; // velocity of small plane
	float m_smallPlaneFacing = 225.0f; // where the plane is facing

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

