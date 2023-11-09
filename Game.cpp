#include "Game.h"

Game::Game(const unsigned int& screen_size)
{
    screenSize = sf::Vector2f((float)screen_size, (float)screen_size);
    viewSize = { VIEW_SIZE, VIEW_SIZE };

	window = new sf::RenderWindow(sf::VideoMode(screen_size, screen_size), "SuikaGame", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(75);
    
    backgroundColor = sf::Color(18, 33, 43);

	view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(viewSize.x, viewSize.y));
	window->setView(view);

    if (!font.loadFromFile("res/notalot35.ttf"))
    {
        std::cerr << "Cannot load: " << "res/notalot35.ttf" << std::endl;
        exit(EXIT_FAILURE);
    }

    endShape.setSize(sf::Vector2f(X_BOUNDRY * 2.f, X_BOUNDRY * 2.f));
    endShape.setOrigin(X_BOUNDRY, X_BOUNDRY);
    endShape.setPosition(0.f, 0.f);
    endShape.setFillColor(sf::Color(18, 33, 43, 100));

    endText.setFont(font);
    endText.setPosition(-48.f, -24.f);
    endText.setCharacterSize(22);

    pointText.setFont(font);
    pointText.setString("Points:");
    pointText.setPosition(-(VIEW_SIZE / 2.f) + 12, -(VIEW_SIZE / 2.f));
    pointText.setCharacterSize(22);

    noPointsText.setFont(font);
    noPointsText.setString("0");
    noPointsText.setPosition(-(VIEW_SIZE / 2.f) + 12, -(VIEW_SIZE / 2.f) + 12);
    noPointsText.setCharacterSize(22);

    nextText.setFont(font);
    nextText.setString("Next:");
    nextText.setPosition((VIEW_SIZE / 2.f) - 64, -(VIEW_SIZE / 2.f));
    nextText.setCharacterSize(22);

    sf::Texture glassTexture;
    if (!glassTexture.loadFromFile("res/Glass.png"))
    {
        std::cerr << "Cannot load: " << "res/Glass.png" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->glass.setTexture(glassTexture);

    this->glass.setPosition(-X_BOUNDRY, -Y_BOUNDRY);

    this->topLine[0] = sf::Vertex(sf::Vector2f(- X_BOUNDRY, TOP_BOUNDRY));
    this->topLine[1] = sf::Vertex(sf::Vector2f(X_BOUNDRY, TOP_BOUNDRY));

    this->highScore = this->getHighScore();

	this->game();
}

Game::~Game()
{
    this->clearEntities();
	delete window;
}

void Game::game()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distEntity(0, 1000);

    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
    sf::Vector2f wordPos = window->mapPixelToCoords(pixelPos);

    this->initActualAndNext();

    sf::Thread th(&Game::renderTh, this);
    renderThread = true;
    window->setActive(false);
    th.launch();

    while (window->isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    this->window->close();
                    break;
                case sf::Keyboard::Enter:
                    if (gameOver)
                        restartGame();
                    break;
                case sf::Keyboard::Space:
                    if (gameOver)
                        break;
                    if (canClick)
                    {
                        this->pushToGame(mt, distEntity);
                        canClick = false;
                    }
                    break;
                default:
                    break;
                }
                break;

            case sf::Event::MouseMoved:
                pixelPos = sf::Mouse::getPosition(*window);
                wordPos = window->mapPixelToCoords(pixelPos);
                this->updateActualPosition(wordPos);
                break;

            case sf::Event::MouseButtonPressed:
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                    if (gameOver)
                        break;
                    if (canClick)
                    {
                        this->pushToGame(mt, distEntity);
                        canClick = false;
                    }
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }

        if (!gameOver)
        {
            this->keyboardMoving();

            this->updateClickDelay();
            this->updateText();

            this->updatingEntities();
            this->updatingEndGame();
            this->collisions();
            this->physics();
        }
        else
        {
            updateEndText();
        }
    }

    renderThread = false;
    th.wait();
}

void Game::updatingEntities()
{
    entityOverEndBound = false;
    mutex.lock();
    for (auto i = entities.begin(); i != entities.end();)
    {
        Entity* e = *i;
        e->update(deltaTime);

        if (isEntityOverEndBound(e))
            entityOverEndBound = true;

        if (!e->life)
        {
            i = entities.erase(i);
            delete e;
        }
        else
            ++i;
    }
    mutex.unlock();
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
                if (typeid(*entities[i]) == typeid(*entities[j]) && !dynamic_cast<Ball_XII*>(entities[i]))
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
    window->clear(sf::Color(18, 33, 43)); // Color background

    // ENTITIES
    actual->draw(*window);
    next->draw(*window);
    for (auto x : entities)
        x->draw(*window);

    // TOP LINE
    window->draw(topLine, 2, sf::Lines);

    // GLASS
    window->draw(this->glass);

    // TEXT
    window->draw(pointText);
    window->draw(nextText);
    window->draw(noPointsText);

    if (gameOver)
    {
        window->draw(endShape);
        window->draw(endText);
    }

    window->display();
}

void Game::renderTh()
{
    window->setActive(true);
    while (renderThread)
    {
        window->clear(sf::Color(18, 33, 43)); // Color background

        // ENTITIES
        actual->draw(*window);
        next->draw(*window);

        mutex.lock();
        for (auto x : entities)
            if (x != nullptr)
                x->draw(*window);
        mutex.unlock();

        // TOP LINE
        window->draw(topLine, 2, sf::Lines);

        // GLASS
        window->draw(this->glass);

        // TEXT
        window->draw(pointText);
        window->draw(nextText);
        window->draw(noPointsText);

        if (gameOver)
        {
            window->draw(endShape);
            window->draw(endText);
        }

        window->display();
    }
    window->setActive(false);
}

void Game::createNext(Entity*& first, Entity*& second)
{
    if (!first->life || !second->life)
        return;
    Entity* ptr = nullptr;
    first->life = false;
    second->life = false;
    sf::Vector2f position = 
    {
        (first->position.x + second->position.x) / 2,
        (first->position.y + second->position.y) / 2
    };

    ptr = first->createNext(position);
    if (dynamic_cast<Ball_XII*>(ptr))
        this->blackHole();
    
    mutex.lock();
    if (ptr != nullptr)
    {
        noPoints += static_cast<int>(ptr->radius);
        entities.push_back(ptr);
    }
    mutex.unlock();
        
}

void Game::initActualAndNext()
{
    actual = new Ball_I({ 0,NEXT_POSITION_Y });
    next = new Ball_I({ NEXT_POSITION_X,NEXT_POSITION_Y });
}

void Game::blackHole()
{
    mutex.lock();
    for (auto x : entities)
    {
        noPoints += (int)x->radius;
        x->life = false;
    }
    mutex.unlock();
}

void Game::updateActualPosition(const sf::Vector2f& position)
{
    if (position.x >= X_BOUNDRY - actual->radius)
        actual->position.x = X_BOUNDRY - actual->radius;
    else if (position.x <= -X_BOUNDRY + actual->radius)
        actual->position.x = -X_BOUNDRY + actual->radius;
    else
        actual->position.x = position.x;
    actual->position.y = TOP_BOUNDRY - FINAL_SIZE;
}

void Game::pushToGame(std::mt19937& mt, std::uniform_int_distribution<int>& distEntity)
{
    mutex.lock();
    entities.push_back(actual);
    noPoints += (int)actual->radius;
    next->position = actual->position;
    actual = next;
    updateActualPosition(actual->position);

    Entity* ptr = nullptr;

    int chance = distEntity(mt);

    if (chance <= 250)
        ptr = new Ball_I({ NEXT_POSITION_X, NEXT_POSITION_Y });
    else if (chance <= 500)
        ptr = new Ball_II({ NEXT_POSITION_X, NEXT_POSITION_Y });
    else if (chance <= 750)
        ptr = new Ball_III({ NEXT_POSITION_X, NEXT_POSITION_Y });
    else if (chance <= 900)
        ptr = new Ball_IV({ NEXT_POSITION_X, NEXT_POSITION_Y });
    else if (chance <= 975)
        ptr = new Ball_V({ NEXT_POSITION_X, NEXT_POSITION_Y });
    else if (chance <= 995)
        ptr = new Ball_VI({ NEXT_POSITION_X, NEXT_POSITION_Y });
    else if (chance <= 999)
        ptr = new Ball_VII({ NEXT_POSITION_X, NEXT_POSITION_Y });
    else
        ptr = new Ball_VIII({ NEXT_POSITION_X, NEXT_POSITION_Y });
    
    next = ptr;
    mutex.unlock();
}

bool Game::isEntityOverEndBound(Entity* entity)
{
    return entity->position.y - entity->radius < TOP_BOUNDRY;
}

void Game::updatingEndGame()
{
    if (entityOverEndBound)
    {
        endTime += deltaTime;
        if (endTime > 1.0f)
        {
            this->topLine[0].color = sf::Color::Red;
            this->topLine[1].color = sf::Color::Red;
        }
        if (endTime > TIME_TO_END)
            gameOver = true;
    }
    else
    {
        endTime = 0.f;
        this->topLine[0].color = sf::Color::White;
        this->topLine[1].color = sf::Color::White;
    }
}

void Game::updateClickDelay()
{
    if (!canClick)
    {
        clickDelayTime += deltaTime;
    }
    if (clickDelayTime > CLICK_DELAY_END)
    {
        canClick = true;
        clickDelayTime = 0.f;
    }
}

void Game::updateText()
{
    noPointsText.setString(std::to_string(noPoints));
}

void Game::updateEndText()
{
    if (highScore < noPoints)
    {
        highScore = noPoints;
        this->updateHighScore((int)highScore);
    }
        
    endText.setString("Points: " + std::to_string(noPoints)
                        + "\nHighscore: " + std::to_string(highScore)
                        + "\n\n     [ ENTER ]");
}

void Game::restartGame()
{
    this->clearEntities();
    this->initActualAndNext();

    gameOver = false;
    noPoints = 0;
}

void Game::keyboardMoving()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->updateActualPosition({ actual->position.x - (150.f * deltaTime), 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->updateActualPosition({ actual->position.x + (150.f * deltaTime), 0 });
}

void Game::updateHighScore(const int& highscore)
{
    std::string encryptedHighScore = encrypt(FIRST_EN + " " + std::to_string(highscore) + " " + SECOND_EN);

    std::ofstream file(HIGHSCORE_FILE, std::ios::out);
    file << encryptedHighScore;
    file.close();
}

int Game::getHighScore()
{
    std::ifstream readFile(HIGHSCORE_FILE, std::ios::in);
    std::string encryptedData;
    readFile >> encryptedData;
    readFile.close();

    std::string decryptedHighScore = this->decrypt(encryptedData);

    std::istringstream iss(decryptedHighScore);
    std::string word;
    std::vector<std::string> vec;
    while (iss >> word)
        vec.push_back(word);

    if (vec.size() < 3)
        return 0;

    if (vec[0] == FIRST_EN && vec[2] == SECOND_EN)
        return std::stoi(vec[1]);
    return 0;
}

std::string Game::encrypt(const std::string& data)
{
    std::string encryptedText = data;
    for (char& c : encryptedText) {
        c = c ^ XORKEY;
    }
    return encryptedText;
}

std::string Game::decrypt(const std::string& data)
{
    return encrypt(data);
}

void Game::clearEntities()
{
    mutex.lock();
    for (auto x : entities)
    {
        noPoints += (int)x->radius;
        delete x;
    }
        
    entities.erase(entities.begin(), entities.end());

    delete actual;
    delete next;
    mutex.unlock();
}