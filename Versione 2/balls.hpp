#include <SFML/Graphics.hpp>
#include <fstream>
#include <random>
#include <vector>

#include "elements.hpp"

#ifndef BALLS_HPP
#define BALLS_HPP

enum class State { Sus, Inf, Rec };

struct Ball {
  sf::CircleShape b;
  int t;
  sf::Vector2f speed;
  State state;
};

class Balls {
private:
  std::random_device rd{};
  std::default_random_engine rnd{rd()};
  std::vector<Ball> ball{};
  float beta;
  float gamma;

public:
  Balls(float b, float g) : beta{b}, gamma{g} {}
  sf::Vector2f randomSpeed();
  void bounce_off_the_wall(sf::RenderWindow const &w1, int const i);
  void changeSpeed();
  void moveBalls(sf::RenderWindow &window);
  void drawBalls(sf::RenderWindow &window);
  int probability_of_infection();
  void check_Collision(int const g, Variables v);
  void count_balls(sf::Clock &c, int &g, std::ofstream &write);
  void checkStatus(int const i);
  sf::Vector2u randomPosition(sf::RenderWindow const &window);
  void addBalls(sf::RenderWindow const &window, Variables v);
  void removed(int const g);
};

#endif
