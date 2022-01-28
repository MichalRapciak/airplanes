/// <summary>
/// Michael Rapciak
/// 24/01/2022
/// Estimated time - 12 Hours
/// Session 1 - 24/01/2022 - 2 Hours
/// Session 2 - 26/01/2022 - 1 Hour
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupPlaneSprite();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMousePress(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseRelease(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// deals with mouse keys pressed
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processMousePress(sf::Event t_event)
{
	m_clickDown.x = t_event.mouseButton.x; // when it is pressed down
	m_clickDown.y = t_event.mouseButton.y;
}

/// <summary>
/// Deals with mouse keys being released
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processMouseRelease(sf::Event t_event)
{
	m_clickUp.x = t_event.mouseButton.x; // when it is pressed up
	m_clickUp.y = t_event.mouseButton.y;
	sf::Vector2f velocity = m_clickUp - m_clickDown; // velocity vector used for the speed and direction of the airplane
	float facingRadians = std::atan2(velocity.y, velocity.x); // used to calculate the radians of the velocity
	float facingDegrees = 180.0f * facingRadians / static_cast<float>(M_PI); // used to switch the radians to degrees
	facingDegrees += 90.0f; // adds 90 degrees for it to move in the right direction and not 90 degrees off
	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		m_smallPlaneVelocity = velocity / 100.0f; // speed of the flight
		m_smallPlaneFacing = facingDegrees; // set facing degree using degrees
		m_smallPlaneSprite.setRotation(facingDegrees); // update airplane rotation
	}
	if (sf::Mouse::Right == t_event.mouseButton.button)
	{
		m_biggerPlaneVelocity = velocity / 200.0f;
		m_biggerPlaneFacing = facingDegrees;
		m_biggerPlaneSprite.setRotation(facingDegrees);
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	movement();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_smallPlaneSprite);
	m_window.draw(m_biggerPlaneSprite);
	m_window.display();
}

/// <summary>
/// Sets up the texture and sprite for the plane
/// </summary>
void Game::setupPlaneSprite()
{
	if (!m_planeText.loadFromFile("ASSETS\\IMAGES\\planes.png"))
	{
		std::cout << "Problem loading plane texture" << std::endl;
	}
	m_smallPlaneSprite.setTexture(m_planeText);
	m_smallPlaneSprite.setTextureRect(sf::IntRect{ 360, 200, 90, 90 });
	m_smallPlaneSprite.setOrigin(sf::Vector2f{ 45.0f,45.0f });
	m_smallPlaneSprite.setPosition(sf::Vector2f{ 300.0f, 200.0f });
	m_smallPlaneSprite.setRotation(m_smallPlaneFacing);
	m_biggerPlaneSprite.setTexture(m_planeText);
	m_biggerPlaneSprite.setTextureRect(sf::IntRect{ 0, 0, 110, 110 });
	m_biggerPlaneSprite.setOrigin(sf::Vector2f{ 55.0f, 55.0f });
	m_biggerPlaneSprite.setPosition(sf::Vector2f{ 500.0f, 400.0f });
	m_biggerPlaneSprite.setRotation(m_biggerPlaneFacing);
}

/// <summary>
/// Used to move plane
/// </summary>
void Game::movement()
{
	m_smallPlaneLocation += m_smallPlaneVelocity; // Adding velocity to the location
	m_smallPlaneSprite.setPosition(m_smallPlaneLocation); // updating location
	m_biggerPlaneLocation += m_biggerPlaneVelocity;
	m_biggerPlaneSprite.setPosition(m_biggerPlaneLocation);
}