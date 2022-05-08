//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : 
// Description    : 
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#include "Mover.h"
#include "SFML/Graphics.hpp"

Mover::Mover(float xpos, float ypos, float mass)
{
	velocity = new sf::Vector2f(0.0f, 0.0f);
	acceleration = new sf::Vector2f(0.0f, 0.0f);
	kg = mass;

	shape = new sf::CircleShape(sqrt(mass) * 10.0f);
	shape->setFillColor(sf::Color(255, 225, 255, 225));
	shape->setOutlineColor(sf::Color(200, 225, 200, 225));
	shape->setOutlineThickness(5.0f);

	sf::Vector2f pos = sf::Vector2f(xpos, ypos);

	shape->setPosition(pos);

}

void Mover::ApplyForce(sf::Vector2f force)
{
	*acceleration += force / kg;
}

void Mover::Update(sf::RenderWindow& renderWindow)
{
	//sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(renderWindow).x, sf::Mouse::getPosition(renderWindow).y);
	//*acceleration = (mousePos - shape->getPosition());
	//*acceleration = Normalize(*acceleration) * 0.1f;

	//velocity += acceleration
	//position += velocity
	*velocity = (*velocity + *acceleration);
	shape->setPosition(shape->getPosition() + *velocity);

	*acceleration = sf::Vector2f(0.0f, 0.0f);
}

void Mover::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(*shape);
}

void Mover::Friction(sf::RenderWindow& renderWindow)
{
	if (renderWindow.getSize().y - (shape->getPosition().y + shape->getRadius()) < 1.0f)
	{
		sf::Vector2f friction = *velocity;
		friction = Normalize(friction);
		friction *= -1.0f;

		float mu = 0.1f;
		float normal = kg;
		friction *= (mu * normal);

		ApplyForce(friction);
	}
}

void Mover::Collision(sf::RenderWindow& renderWindow)
{
	if (shape->getPosition().y >= renderWindow.getSize().y - shape->getRadius())
	{
		shape->setPosition(shape->getPosition().x, renderWindow.getSize().y - shape->getRadius());
		*velocity = sf::Vector2f(velocity->x, -velocity->y);
	}
	if (shape->getPosition().x >= renderWindow.getSize().x - shape->getRadius())
	{
		shape->setPosition(renderWindow.getSize().x - shape->getRadius(), shape->getPosition().y);
		*velocity = sf::Vector2f(-velocity->x, velocity->y);
	}
	else if (shape->getPosition().x <= shape->getRadius())
	{
		shape->setPosition(shape->getRadius(), shape->getPosition().y);
		*velocity = sf::Vector2f(-velocity->x, velocity->y);
	}
}

sf::Vector2f Mover::Normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}
