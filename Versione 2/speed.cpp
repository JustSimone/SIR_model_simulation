#include "speed.hpp"
#include "PerlinNoise.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#define PI 3.14159265

sf::Vector2f vectorConverter(double cellValue) {
  double angle = 2 * PI * cellValue;
  float sinV = sin(angle);
  float cosV = cos(angle);
  sf::Vector2f coordinates{sinV, cosV};
  return (coordinates);
}

void PerlinDistribution::Fill(sf::Vector2u const &windowSize) {
  unsigned int seed = 2021;
  PerlinNoise pn(seed);
  for (int i = 0; i < windowSize.y; ++i) {
    std::vector<Cell> cellLine{};
    for (int j = 0; j < windowSize.x; ++j) {
      double xValue = (double)j / ((double)windowSize.x);
      double yValue = (double)i / ((double)windowSize.y);
      double cellValue = pn.noise(10 * xValue, 10 * yValue, 0.8);
      unsigned int xPosition = (unsigned int)xValue * 100;
      unsigned int yPosition = (unsigned int)yValue * 100;
      sf::Vector2u interval{xPosition, yPosition};
      Cell singleCell{vectorConverter(cellValue), interval};
      cellLine.push_back(singleCell);
    }
    cellVector.push_back(cellLine);
  }
}

sf::Vector2f assingSpeed(sf::Vector2u const& currentPosition) {

}
