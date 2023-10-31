#include "Game.h"

Game::Game()
{
    screenSize = sf::Vector2f(SCREEN_SIZE, SCREEN_SIZE);
    viewSize = { VIEW_SIZE, VIEW_SIZE };

	window = new sf::RenderWindow(sf::VideoMode(screenSize.x, screenSize.y), "SuikaGame", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(244);
    
    backgroundColor = sf::Color(18, 33, 43);

	view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(viewSize.x, viewSize.y));
	window->setView(view);

    sf::Texture glassTexture;
    if (!glassTexture.loadFromFile("res/Glass.png"))
    {
        std::cerr << "Cannot load: " << "res/Glass.png" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->glass.setTexture(glassTexture);

    this->glass.setPosition(-X_BOUNDRY, -Y_BOUNDRY);

	this->game();
}

Game::~Game()
{
    this->clearEntities();
    this->window->close();
	delete window;
}

void Game::game()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distPos(-40, 40);
    std::uniform_int_distribution<int> distEntity(0, 5);

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

            case sf::Event::MouseButtonPressed:
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
                    sf::Vector2f wordPos = window->mapPixelToCoords(pixelPos);
                    entities.push_back(new Strawberry({ wordPos.x, wordPos.y }));
                    break;
                }
                case sf::Mouse::Right:
                {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
                    sf::Vector2f wordPos = window->mapPixelToCoords(pixelPos);
                    entities.push_back(new Apple({ wordPos.x, wordPos.y }));
                    break;
                }
                case sf::Mouse::Middle:
                {
                    for (int i = 0; i < 2; i++)
                    {
                        switch (distEntity(mt))
                        {
                        case 0:
                            entities.push_back(new Strawberry({ static_cast<float>(distPos(mt)), static_cast<float>(distPos(mt)) }));
                            break;
                        case 1:
                            entities.push_back(new Apple({ static_cast<float>(distPos(mt)), static_cast<float>(distPos(mt)) }));
                            break;
                        case 2:
                            entities.push_back(new Orange({ static_cast<float>(distPos(mt)), static_cast<float>(distPos(mt)) }));
                            break;
                        case 3:
                            entities.push_back(new Melon({ static_cast<float>(distPos(mt)), static_cast<float>(distPos(mt)) }));
                            break;
                        case 4:
                            entities.push_back(new Watermelon({ static_cast<float>(distPos(mt)), static_cast<float>(distPos(mt)) }));
                            break;
                        case 5:
                            entities.push_back(new Final({ static_cast<float>(distPos(mt)), static_cast<float>(distPos(mt)) }));
                            break;
                        default:
                            break;
                        }
                        
                    }
                }
                default:
                    break;
                }

            default:
                break;
            }
        }
        

        this->updatingEntities();
        this->collisions();
        this->physics();
        this->render();
    }
}

void Game::updatingEntities()
{
    for (auto i = entities.begin(); i != entities.end();)
    {
        Entity* e = *i;
        e->update(deltaTime);

        if (!e->life)
        {
            i = entities.erase(i);
            delete e;
        }
        else
            ++i;
    }
}

void Game::collisions()
{
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
                if (typeid(*entities[i]) == typeid(*entities[j]) && !dynamic_cast<Final*>(entities[i]))
                {
                    createNext(entities[i], entities[j]);
                    ++i;
                    continue;
                }
                vecCollidingPairs.push_back({
                    entities[i],
                    entities[j]
                    });

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
}

void Game::physics()
{
    for (auto c : vecCollidingPairs)
    {
        Entity* b1 = c.first;
        Entity* b2 = c.second;

        // Distance between balls
        float fDistance = sqrtf((b1->position.x - b2->position.x) * (b1->position.x - b2->position.x) + (b1->position.y - b2->position.y) * (b1->position.y - b2->position.y));

        // Normal
        float nx = (b2->position.x - b1->position.x) / fDistance;
        float ny = (b2->position.y - b1->position.y) / fDistance;

        // Tangent
        float tx = -ny;
        float ty = nx;

        // Dot Product Tangent
        float dpTan1 = b1->velocity.x * tx + b1->velocity.y * ty;
        float dpTan2 = b2->velocity.x * tx + b2->velocity.y * ty;

        // Dot Product Normal
        float dpNorm1 = b1->velocity.x * nx + b1->velocity.y * ny;
        float dpNorm2 = b2->velocity.x * nx + b2->velocity.y * ny;

        // Conservation of momentum in 1D
        float m1 = (dpNorm1 * (b1->mass - b2->mass) + 2.0f * b2->mass * dpNorm2) / (b1->mass + b2->mass);
        float m2 = (dpNorm2 * (b2->mass - b1->mass) + 2.0f * b1->mass * dpNorm1) / (b1->mass + b2->mass);

        // Update ball velocities
        b1->velocity.x = (tx * dpTan1 + nx * m1);
        b1->velocity.y = (ty * dpTan1 + ny * m1);
        b2->velocity.x = (tx * dpTan2 + nx * m2);
        b2->velocity.y = (ty * dpTan2 + ny * m2);

    }
    vecCollidingPairs.clear();
}

void Game::render()
{
    sf::Vertex bottomLine[] =
    {
        sf::Vertex({ -X_BOUNDRY, Y_BOUNDRY}),
        sf::Vertex({ X_BOUNDRY, Y_BOUNDRY})
    };

    sf::Vertex leftLine[] =
    {
        sf::Vertex({ -X_BOUNDRY, -Y_BOUNDRY}),
        sf::Vertex({ -X_BOUNDRY, Y_BOUNDRY})
    };

    sf::Vertex rightLine[] =
    {
        sf::Vertex({ X_BOUNDRY, -Y_BOUNDRY}),
        sf::Vertex({ X_BOUNDRY, Y_BOUNDRY})
    };


    window->clear(sf::Color(18, 33, 43)); // Color background
    for (auto x : entities)
        x->draw(*window);
    /*window->draw(bottomLine, 2, sf::Lines);
    window->draw(rightLine, 2, sf::Lines);
    window->draw(leftLine, 2, sf::Lines);*/
    window->draw(this->glass);
    window->display();
}

void Game::createNext(Entity*& first, Entity*& second)
{
    Entity* ptr = nullptr;
    first->life = false;
    second->life = false;
    sf::Vector2f position = 
    {
        (first->position.x + second->position.x) / 2,
        (first->position.y + second->position.y) / 2
    };

    if (dynamic_cast<Strawberry*>(first))
        ptr = new Apple(position);
    else if (dynamic_cast<Apple*>(first))
        ptr = new Orange(position);
    else if (dynamic_cast<Orange*>(first))
        ptr = new Melon(position);
    else if (dynamic_cast<Melon*>(first))
        ptr = new Watermelon(position);
    else if (dynamic_cast<Watermelon*>(first))
        ptr = new Final(position);

    if (ptr != nullptr)
        entities.push_back(ptr);
}

void Game::clearEntities()
{
    for (auto x : entities)
        delete x;
    entities.erase(entities.begin(), entities.end());
}
