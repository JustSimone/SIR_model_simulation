#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <vector>

#include "PerlinNoise.hpp"
#ifndef SPEED_HPP
#define SPEED_HPP

#define PI 3.14159265

sf::Vector2f vector_converter(double cell_value) {
  double angle = 2 * PI * cell_value;
  float sinV = sin(angle);
  float cosV = cos(angle);
  sf::Vector2f coordinates{sinV, cosV};
  return (coordinates);
}

double gaussian_distribution(double const cell_value) {
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(cell_value, 0.1);
  double gaussian_cell_value = distribution(generator);
  return gaussian_cell_value;
}
sf::Vector2f perlin_speed(sf::Vector2u const &window_size,
                          sf::Vector2u const &ball_position, int const seed) {
  PerlinNoise pn(seed);
  double x_value = (double)ball_position.x / (((double)window_size.x) / 10);
  double y_value = (double)ball_position.y / (((double)window_size.y) / 10);
  double cell_value = pn.noise(10 * x_value, 10 * y_value, 0.2);
  return vector_converter(gaussian_distribution(cell_value));
}

#endif
