// Suggestions:
// Karissa do you want to organize the functions like this or match exactly to the instructions? I think this looks more sequential but lemme know what you think

#include "Engine.h"
#include <iostream> // added for cout 

// engine constructor
Engine::Engine() : m_Window(VideoMode(1920, 1080), "Particles!!", Style::Default)
{
    // added this in case font doesnt load for whatever reason
    Font font;
    if (!font.loadFromFile("font.ttf")) 
    {
        // Displays message to user if font doesn't load
        cout << "Error loading font!" << endl;
        // returns error and exits program
        return -1;
    }
}

// input function to handle user input
void Engine::input()
{

}

// update function to update game state
void Engine::update(float dtAsSeconds)
{
    // add code here


    // loops through particles to update them
    auto it = m_particles.begin();
    while (it != m_particles.end())
    {
        if (it->getTTL() > 0.0f)
        {
            it->update(dtAsSeconds);
            ++it;
        }
        else
        {
            it = m_particles.erase(it);
        }
    }
}

// draw function to draw out the program

void Engine::draw()
{
    m_Window.clear();

    // here add draw code for the engine

    // loops through particles and draws them out, i think we've already learned how to add range based for loops but let me know if you wanna do it another way
    for (const auto& particle : m_particles)
    {
        m_Window.draw(particle);
    }

    m_Window.display();

}

// run function to run program loop
void Engine::run()
{
    // creating text objects here 
    Text text;

    text.setFont(font);
    text.setCharacterSize(60); //Sets text size
    text.setFillColor(Color::White); //Sets text color
    text.setPosition(10, 10); //Positions text

    Text titleText;
    
    titleText.setFont(font);
    titleText.setCharacterSize(250);
    titleText.setFillColor(Color(210, 43, 41));
    titleText.setOutlineColor(Color::White);
    titleText.setOutlineThickness(2);
    titleText.setPosition(150, 140);
    titleText.setString("Particles"); //Adds title screen

    // bool for titlescreen
    bool titleScreen = true;

    // constructs the clock object to track time per frame
    Clock clock;

    // constructs a local particle to be used for unit tests
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    // here's the game loop
    while (m_Window.isOpen())
    {
        // restarts the clock which returns the time elapsed since the last frame
        Time dt = clock.restart();

        // converts clock time into seconds
        float dtAsSeconds = dt.asSeconds();

        // calls input function
        input();

        // calls update function
        update(dtAsSeconds);

        // calls draw function
        draw();
    }
}

