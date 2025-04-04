// Copyright [2025] Ansh Patel

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {
class Universe: public sf::Drawable {
 public:
    Universe();
    explicit Universe(const std::string& filename);

    size_t size() const;
    double radius() const;
    std::vector<std::unique_ptr<CelestialBody>>& planets() { return numPlanets_; }


    const CelestialBody& operator[](size_t i) const;

    void step(double dt);

    friend std::istream& operator>>(std::istream& is, Universe& uni);
    friend std::ostream& operator<<(std::ostream& os, const Universe& uni);

 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
    double radius_;
    std::vector<std::unique_ptr<CelestialBody>> numPlanets_;
};

}  // namespace NB
