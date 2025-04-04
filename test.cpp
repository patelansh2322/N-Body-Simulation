// Copyright [2025] Ansh Patel

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "CelestialBody.hpp"
#include "Universe.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CelestialBodyTest
#include <boost/test/unit_test.hpp>

using NB::CelestialBody;

// Test to check formatting
BOOST_AUTO_TEST_CASE(testFormatting) {
    CelestialBody body;
    std::istringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    input >> body;

    std::ostringstream output;
    output << std::scientific << std::setprecision(4) << std::showpoint;
    output << body;

    std::ostringstream expected;
    expected << std::scientific << std::setprecision(4) << std::showpoint
             << "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif";

    BOOST_REQUIRE_EQUAL(output.str(), expected.str());
}

// Test to check format after flipping values
BOOST_AUTO_TEST_CASE(testFlipped) {
    CelestialBody body;
    std::istringstream input
    ("-1.4960e+11 -0.0000e+00 -0.0000e+00 -2.9800e+04 -5.9740e+24 mars.gif");
    input >> body;

    std::ostringstream output;
    output << std::scientific << std::setprecision(4) << std::showpoint;
    output << body;

    std::ostringstream expected;
    expected << std::scientific << std::setprecision(4) << std::showpoint
             << "-1.4960e+11 -0.0000e+00 -0.0000e+00 -2.9800e+04 -5.9740e+24 mars.gif";

    BOOST_REQUIRE_EQUAL(output.str(), expected.str());
}

// Test to verify format by manual coding
BOOST_AUTO_TEST_CASE(testHardcoded) {
    CelestialBody body;
    std::istringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    input >> body;

    std::ostringstream output;
    output << std::scientific << std::setprecision(4) << std::showpoint;
    output << body;

    BOOST_REQUIRE_EQUAL(output.str(),
    "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
}

// Test for step method
BOOST_AUTO_TEST_CASE(testStep) {
    std::ifstream input("planets.txt");
    NB::Universe uni;
    input >> uni;
    input.close();

    double dt = 0;
    while (dt <= 31557600) {
        uni.step(1000);
        dt+=1000;
    }

    const double tolerance = 0.01;

        double expected_positions[][2] = {
        {1.49582692e+11, -2.14338496e+09},
        {-2.21799760e+11, -4.77353001e+10},
        {3.56999496e+10, 4.56049091e+10},
        {5.97145250e+05, 6.22959800e+06},
        {-7.49330678e+10, -7.78241802e+10}
    };

    double expected_velocities[][2] = {
        {4.27029205e+02, 2.97974316e+04},
        {5.07995752e+03, -2.36690020e+04},
        {-3.76729375e+04, 2.95685293e+04},
        {-5.84228039e-02, 1.63713798e-01},
        {2.52281484e+04, -2.43338301e+04}
    };

    for (size_t i = 0; i < 5; ++i) {
        BOOST_CHECK_CLOSE(uni[i].position().x, expected_positions[i][0], tolerance);
        BOOST_CHECK_CLOSE(uni[i].position().y, expected_positions[i][1], tolerance);
        BOOST_CHECK_CLOSE(uni[i].velocity().x, expected_velocities[i][0], tolerance);
        BOOST_CHECK_CLOSE(uni[i].velocity().y, expected_velocities[i][1], tolerance);
    }
}
