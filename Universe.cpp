// Copyright [2025] Ansh Patel

#include <fstream>
#include <memory>
#include <iomanip>
#include <cmath>
#include "Universe.hpp"
#include "CelestialBody.hpp"

namespace NB {
// Overload the extraction operator to read file
std::istream& operator>>(std::istream& is, NB::Universe& uni) {
    size_t planets;
    double radius;
    // Read the first two lines, number of planets and radius
    is >> planets >> radius;

    // Set universeRadius to scale the planets
    NB::CelestialBody::setUniverseRadius(radius);

    uni.radius_ = radius;
    // Clear any existing planets
    uni.numPlanets_.clear();

    for (size_t i = 0; i < planets; ++i) {
        // Create a unique pointer for each planet
        auto planet = std::make_unique<CelestialBody>();
        // Read the planets
        is >> *planet;
        // Store them in the universe
        uni.numPlanets_.push_back(std::move(planet));
    }

    return is;
}

// Overload the insertion operator to print the contents
std::ostream& operator<<(std::ostream& os, const NB::Universe& uni) {
    // Print the universe radius and number of planets with accuracy
    os << uni.numPlanets_.size() << "\n"
    << std::scientific << std::setprecision(2) << uni.radius_ << "\n";
    for (const auto& planets : uni.numPlanets_) {
        // Print each planet data
        os << *planets << "\n";
    }

    return os;
}
}  // namespace NB

// Creates a universe with radius 0
NB::Universe::Universe() : radius_(0) {}

void NB::Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    for (const auto& planets : numPlanets_) {
        // Loop to draw all the planets into the window
        window.draw(*planets, states);
    }
}

// Return the number of planets in the universe
size_t NB::Universe::size() const { return numPlanets_.size(); }

// Return the radius of the universe
double NB::Universe::radius() const { return radius_; }

const NB::CelestialBody& NB::Universe::operator[](size_t i) const {
    return *numPlanets_.at(i);
}

constexpr double G = 6.67e-11;

void NB::Universe::step(double dt) {
    std::vector<sf::Vector2f> forces(numPlanets_.size(), sf::Vector2f(0, 0));

    // Compute gravitational forces
    for (size_t i = 0; i < numPlanets_.size(); ++i) {
        for (size_t j = 0; j < numPlanets_.size(); ++j) {
            if (i == j) continue;

            sf::Vector2f diff = numPlanets_[j]->position() - numPlanets_[i]->position();
            double dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

            if (dist > 0) {
                // Newtons law of gravitation
                double force = (G * numPlanets_[i]->mass() * numPlanets_[j]->mass()) /
                (dist * dist);
                sf::Vector2f unitVector(diff.x / dist, diff.y / dist);
                sf::Vector2f forceVec(unitVector.x * force, unitVector.y * force);
                forces[i] += forceVec;
            }
        }
    }

    // Apply forces and update velocity/position
    for (size_t i = 0; i < numPlanets_.size(); ++i) {
        sf::Vector2f acceleration(forces[i].x /  numPlanets_[i]->mass(),
        forces[i].y / numPlanets_[i]->mass());
        // Update the velocity and position
        numPlanets_[i]->updateVelocity(acceleration, dt);
        numPlanets_[i]->updatePosition(dt);
    }
}
