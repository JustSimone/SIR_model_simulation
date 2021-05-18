#ifndef BALLS_HPP
#define BALLS_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>

#include "elements.hpp"

enum class State { Sus, Inf, Rec };

struct Ball {
  sf::CircleShape b;
  int t;
  sf::Vector2f speed;
  State state;
};

class Balls {
private:
  std::vector<Ball> ball{};
  float beta;
  float gamma;

public:
  Balls(float b, float g) : beta{b}, gamma{g} {}

  void drawBalls(sf::RenderWindow &wind);
  void addBalls(Balls b, int const N, sf::RenderWindow const &window, Variables v);
  void moveBalls(Balls b, sf::RenderWindow &w);
  void check_Collision(int const g, Variables v);
  void removed(int const g);
  void count_balls(sf::Clock &c, int &g, std::ofstream &w);

  int probability_of_infection();
  std::vector<sf::Vector2f> bounce_off_the_wall(sf::RenderWindow const &w1);
  std::vector<sf::Vector2f> BallsPosition();
  std::vector<sf::Vector2f> randomSpeed();
};

#endif
