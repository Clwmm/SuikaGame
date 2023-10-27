#include "Game.h"

Game::Game()
{
    screenSize = sf::Vector2f(1000, 1000);
    viewSize = { screenSize.x * 4, screenSize.y * 4 };

	window = new sf::RenderWindow(sf::VideoMode(screenSize.x, screenSize.y), "SuikaGame", sf::Style::Titlebar | sf::Style::Close);
	backgroundColor = sf::Color(18, 33, 43);

	view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(viewSize.x, viewSize.y));
	window->setView(view);

	this->game();
}

Game::~Game()
{
    window->close();
	delete window;
}

void Game::game()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    Entity* e = nullptr;

    for (int i = 0; i < 1700; i++)
    {
        e = new Ball(15, { static_cast<float>(dist(mt)), static_cast<float>(dist(mt))});
        entities.push_back(e);
    }

    e = new Ball(75, { 2000, 2000 });
    entities.push_back(e);

    while (window->isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                return;

            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    return;

                default:
                    break;
                }

            default:
                break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
            sf::Vector2f wordPos = window->mapPixelToCoords(pixelPos);
            e->position = wordPos;
        }
        else
        {
            e->position = { -9000, -9000 };
        }
        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            e->position.y -= 100 * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            e->position.y += 100 * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            e->position.x -= 100 * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            e->position.x += 100 * deltaTime;


        auto DoCirclesOverlap = [](float x1, float y1, float r1, float x2, float y2, float r2)
            {
                return fabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
            };

        for (int i = 0; i < entities.size(); ++i)
        {
            for (int j = i + 1; j < entities.size(); ++j)
            {
                if (DoCirclesOverlap(entities[i]->position.x, entities[i]->position.y, entities[i]->radius, entities[j]->position.x, entities[j]->position.y, entities[j]->radius))
                {
                    // Distance between ball centers
                    float distance = sqrtf((entities[i]->position.x - entities[j]->position.x) * (entities[i]->position.x - entities[j]->position.x) + (entities[i]->position.y - entities[j]->position.y) * (entities[i]->position.y - entities[j]->position.y));

                    float overlap = 0.5f * (distance - entities[i]->radius - entities[j]->radius);

                    // Displace Current Ball
                    entities[i]->position.x -= overlap * (entities[i]->position.x - entities[j]->position.x) / distance;
                    entities[i]->position.y -= overlap * (entities[i]->position.y - entities[j]->position.y) / distance;

                    // Displace Target Ball
                    entities[j]->position.x += overlap * (entities[i]->position.x - entities[j]->position.x) / distance;
                    entities[j]->position.y += overlap * (entities[i]->position.y - entities[j]->position.y) / distance;
                }
            }
        }


        window->clear(sf::Color(18, 33, 43)); // Color background
        for (auto x : entities)
            x->draw(*window);
        window->display();
    }
}
