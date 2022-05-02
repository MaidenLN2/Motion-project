#pragma once

// to avoid circular includes
namespace sf
{
	class CircleShape;
	class RenderWindow;
	template <typename> class Vector2;
	typedef Vector2<float> Vector2f;
}
class Mover
{
public:
	Mover(float xpos, float ypos, float mass);
	void Update(sf::RenderWindow& renderWindow);
	void Render(sf::RenderWindow& renderWindow);
	void Friction(sf::RenderWindow& renderWindow);
	void Collision(sf::RenderWindow& renderWindow);
	void ApplyForce(sf::Vector2f force);
	float kg;
private:
	sf::CircleShape* shape;
	sf::Vector2f* acceleration;
	sf::Vector2f* velocity;
	sf::Vector2f Normalize(const sf::Vector2f& source);

};

