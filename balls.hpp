#ifndef BALLS_HPP
#define BALLS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

struct Ball {
  sf::CircleShape b;
  int t;
};

class Balls {
 private:
  std::vector<Ball> ball{};
  float beta;
  int urti=0;
  float gamma;
 public:
  Balls(float b, float g) : beta{b}, gamma{g} {}

  void drawBalls(sf::RenderWindow& wind);
  void addBalls(int const N, sf::RenderWindow const& window);
  void moveBalls(std::vector<sf::Vector2f>);
  void check_Collision(int const& g);
  void removed(int const g);
  void count_balls(sf::Clock& c, int& g, std::ofstream& w);
  int probability_of_infection();
  std::vector<sf::Vector2f> bounce_off_the_wall(
      std::vector<sf::Vector2f>& vec_1, sf::RenderWindow const& w1);
  std::vector<sf::Vector2f> BallsPosition();
  std::vector<sf::Vector2f> randomSpeed();
};

int day_counter(int t1, int t2);


#endif
