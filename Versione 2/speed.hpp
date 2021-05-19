#include "PerlinNoise.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef SPEED_HPP
#define SPEED_HPP

struct Cell {
  sf::Vector2f direction;
  sf::Vector2u position;
};

class PerlinDistribution {
private:
  using Row = std::vector<Cell>;
  using Cells = std::vector<Row>;
  Cells cellVector;

public:
  void Fill(sf::Vector2u const &windowSize);
};

#endif
