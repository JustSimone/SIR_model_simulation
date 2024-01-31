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
  sf::Vector2f random_speed();
  void bounce_off_the_wall(sf::RenderWindow const &w1, int const i);
  void move_balls(sf::RenderWindow &window);
  void draw_balls(sf::RenderWindow &window) const;
  int probability_of_infection();
  void check_collision(int const day, Variables v);
  bool count_balls(sf::Clock &c, int &d, std::ofstream &write) const;
  void check_status(Variables const &v);
  sf::Vector2u random_position(Variables const &v);
  void add_balls(Variables const &v);
  void removed(int const day);
};
int day_counter(int t1, int t2);

#endif
