// Copyright [2025] Ansh Patel

#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody: public sf::Drawable {
 public:
    explicit CelestialBody();

    void updateScreenPosition();

    static void setUniverseRadius(float radius);

    sf::Vector2f position() const;
    sf::Vector2f velocity() const;
    float mass() const;

    void updateVelocity(const sf::Vector2f acceleration, double dt);
    void updatePosition(double dt);

    friend std::istream& operator>>(std::istream& is, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& os, const CelestialBody& body);

 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    float mass_;
    std::string imageFile_;
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite_;
};

}  // namespace NB
