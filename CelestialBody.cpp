// Copyright [2025] Ansh Patel

#include <iomanip>
#include "CelestialBody.hpp"

// // Constants to scale the universe
static float universeRadius;
static float screenSizeX;
static float scaleFactorX;
static float screenSizeY;
static float scaleFactorY;

// Function to set universe radius dynamically
void NB::CelestialBody::setUniverseRadius(float radius) {
    universeRadius = radius;
}

namespace NB {
// Overload the extraction operator to read the CelestialBody
std::istream& operator>>(std::istream& is, NB::CelestialBody& body) {
    // Read the position, velocity, mass and file name
    is >> body.position_.x >> body.position_.y
    >> body.velocity_.x >> body.velocity_.y
    >> body.mass_ >> body.imageFile_;

    if (!body.texture->loadFromFile(body.imageFile_)) {
        // Print error if unable to load file
        std::cerr << "Error loading texture: " << body.imageFile_ << std::endl;
        return is;
    } else {
        // Set the texture for the body
        body.sprite_.setTexture(*body.texture);
    }
    return is;
}

// Overload the insertion operator
std::ostream& operator<<(std::ostream& os, const NB::CelestialBody& body) {
    // Print
    os << std::scientific << std::setprecision(4)
    << body.position_.x << " " << body.position_.y << " "
    << body.velocity_.x << " " << body.velocity_.y << " "
    << body.mass_ << " "
    << body.imageFile_;
    return os;
}
}  // namespace NB

// Default constructor
NB::CelestialBody::CelestialBody()
    : position_(0.f, 0.f), velocity_(0.f, 0.f), mass_(0.f),
    texture(std::make_shared<sf::Texture>()) {}

// Return the position of the body
sf::Vector2f NB::CelestialBody::position() const {
    return position_;
}

// Return the velocity of the body
sf::Vector2f NB::CelestialBody::velocity() const {
    return velocity_;
}

// Return the mass of the body
float NB::CelestialBody::mass() const {
    return mass_;
}

// Draw the body onto the window
void NB::CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    sf::Sprite sprite(sprite_);
    screenSizeX = 800.0f;
    scaleFactorX = (screenSizeX / 2) / universeRadius;
    screenSizeY = 500.0f;
    scaleFactorY = (screenSizeY / 2) / universeRadius;
    float screenX = position_.x * scaleFactorX + screenSizeX / 2;
    float screenY = -position_.y * scaleFactorY + screenSizeY / 2;

    sprite.setPosition(screenX, screenY);
    window.draw(sprite, states);
}

// Updating the velocity during the simulation
void NB::CelestialBody::updateVelocity(const sf::Vector2f acceleration, double dt) {
    velocity_.x += acceleration.x * dt;
    velocity_.y += acceleration.y * dt;
}

// Updating the position during the simulation
void NB::CelestialBody::updatePosition(double dt) {
    position_.x += velocity_.x * dt;
    position_.y += velocity_.y * dt;
}
