#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>

#include "balls.hpp"

int main(int argc, char *argv[]) {
  Balls b(0.5, 0.0333);
  std::ofstream write;
  write.open("ball_pandemy.dat");
  sf::Clock clock;
  int giorno = 0;
  std::cout << "Giorno - n° Sani - n° Infetti - n° Rimossi" << '\n';
  sf::RenderWindow w(sf::VideoMode(argv[1], argv[1]), "Movimento random");
  w.setFramerateLimit(120);

  b.addBalls(argv[0], w);
  std::vector<sf::Vector2f> v = b.randomSpeed();

  while (w.isOpen()) {
    sf::Event e;
    while (w.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        w.close();
      }
    }
    w.clear();
    b.check_Collision(giorno);
    b.count_balls(clock, giorno, write);
    b.removed(giorno);
    b.moveBalls(b.bounce_off_the_wall(v, w));
    b.drawBalls(w);
    w.display();
  }
  write.close();
  return 0;
}
