// This program had been created by Simone Coli, along with the help of
// Giuseppe Sguera and Matteo Bonaccini.
// This code is the main document that allows to show a simulation of a
// pandemy, approximating people with small circles.
//
// Copyright, Bologna 2021 ©
//
//

#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "balls.hpp"
#include "elements.hpp"
#include "argument.hpp"

int main(int argc, const char **argv) {

  //float beta = std::stof(argv[1]);
  //float gamma = std::stof(argv[2]);
  //int population = std::stoi(argv[3]);

  //Variables v{beta, gamma, population};
  Variables v{0.1, 0.1, 1000};
  Balls b(v.getBeta(), v.getGamma());

  v.setSw(add_sizeWindow(argc, argv));
  v.setSb(add_sizeBall(argc, argv));
  v.setDistancing(add_distance(argc, argv));
  
  std::ofstream write;
  write.open("ball_pandemy.dat");

  sf::Clock clock;
  int giorno = 0;
  std::cout << "Giorno - n° Sani - n° Infetti - n° Rimossi" << '\n';

  sf::RenderWindow w(sf::VideoMode(v.getSw().width, v.getSw().high),
                     "Movimento random");
  w.setFramerateLimit(120);

  b.addBalls(v.getPopulation(), w, v);
  std::vector<sf::Vector2f> vec = b.randomSpeed();

  while (w.isOpen()) {
    sf::Event e;
    while (w.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        w.close();
      }
    }
    w.clear();
    b.check_Collision(giorno, v);
    b.count_balls(clock, giorno, write);
    b.removed(giorno);
    b.moveBalls(b.bounce_off_the_wall(vec, w));
    b.drawBalls(w);
    w.display();
  }
  write.close();
  return 0;
}
