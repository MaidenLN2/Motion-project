#include "SFML/Graphics.hpp"
#include "Mover.h"
#include <iostream>

int main()
{

    //window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Test");
    window.setFramerateLimit(60);

    std::vector<Mover> movers;

    movers.push_back(Mover(300.0f, 300.0f, 1.0f));
    movers.push_back(Mover(500.0f, 300.0f, 7.0f));
    movers.push_back(Mover(700.0f, 300.0f, 5.0f));


    while (window.isOpen())
    {

        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
            {

                break;
            }
            case sf::Event::MouseMoved:
            {

                break;
            }
            case sf::Event::MouseButtonReleased:
            {

                break;
            }
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        for (int i = 0; i < movers.size(); ++i)
        {
            sf::Vector2f gravity = sf::Vector2f(0, 0.1f);
            sf::Vector2f kg = gravity * movers[i].kg;

            movers[i].ApplyForce(kg);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2f wind = sf::Vector2f(0.5f, 0.0f);


                movers[i].ApplyForce(wind);
            }

            movers[i].Friction(window);
            movers[i].Update(window);
            movers[i].Render(window);
            movers[i].Collision(window);
            // uncomment to have a stroke
            //window.display();

        }
        

        window.display();
    }

        return 0;
    }
