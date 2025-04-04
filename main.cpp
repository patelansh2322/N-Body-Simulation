// Copyright [2025] Ansh Patel

#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Universe.hpp"

int main(int argc, char* argv[]) {
    // Return exit if number of arguments not found
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    // Taking Time and delta time from command line
    double T = std::stod(argv[1]);
    double dt = std::stod(argv[2]);

    // Create universe instance
    NB::Universe universe;
    // Read input file into the universe
    std::cin >> universe;

    // Create a audio instance
    sf::Music audio;
    if (!audio.openFromFile("universe_sound.wav"))
        return EXIT_FAILURE;
    audio.play();
    audio.setLoop(true);

    // Create a background image
    sf::Image image;
    if (!image.loadFromFile("background.png")) {
        return EXIT_FAILURE;
    }
    // Create a texture of the loaded image
    sf::Texture texture;
    texture.loadFromImage(image);
    // Create a sprite of the loaded image
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Create font instance
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }

    // Create text instance using font
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color:: White);
    text.setPosition(10, 10);

    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 500), "NBody Simulation");

    double timeElapsed = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Call step as long as dt<T
        if (timeElapsed < T) {
            double stepSize = std::min(dt, T-timeElapsed);
            universe.step(stepSize);
            timeElapsed += stepSize;
        } else {
            // Stop audio once animation is over
            audio.stop();
        }

        // Calculate time elapsed in days
        double time = timeElapsed/(24*3600);
        // Only display 2 decimal places
        std::stringstream str;
        str.precision(2);
        str << std::fixed <<time;
        text.setString(str.str() + " days");

        window.clear();
        // Draw the sprite before the universe
        window.draw(sprite);
        // Draw the universe
        window.draw(universe);
        // Draw the text
        window.draw(text);
        window.display();

        // Add a delay to display animation
        sf::sleep(sf::milliseconds(10));
    }
    // Print out the positon, velocity, mass and planet name
    std::cout << universe;
    return 0;
}
