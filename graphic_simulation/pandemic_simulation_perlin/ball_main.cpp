// This program had been created by Simone Coli, along with the help of
// Giuseppe Sguera and Matteo Bonacini.
// This code is the main document that allows to show a simulation of a
// pandemy, approximating people with small circles.
//
// Copyright, Bologna 2021 ©
//
//

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "library.hpp"

int main(int argc, const char **argv) {
  Variables v;
  try {
    v.parse_variables(argc, argv);
  } catch (std::exception& e) {
    std::cout << e.what();
    exit(EXIT_FAILURE);
  }

  int seed = 2021;
  bool stop = false;

  Balls b(v.get_beta(), v.get_gamma());

  std::ofstream write;
  write.open("ball_pandemy.dat");

  sf::Clock clock;
  sf::Clock check;

  int giorno = 0;
  std::cout << " ------ PERLIN PANDEMIC SIMULATION ------" << '\n';
  std::cout << "\nGiorno - n° Sani - n° Infetti - n° Rimossi" << '\n';

  sf::RenderWindow w(sf::VideoMode(v.get_sw().width, v.get_sw().height),
                     "Movimento random", sf::Style::Close);
  w.setFramerateLimit(60);
  b.add_balls(v);

  while (w.isOpen()) {
    sf::Event e;
    while (w.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        w.close();
      }
    }
    w.clear();
    if (check.getElapsedTime() > sf::seconds(0.17)) {
      b.check_collision(giorno, v);
      b.change_speed(w, seed);
      check.restart();
    }
    stop = b.count_balls(clock, giorno, write);
    b.check_status(v);
    b.removed(giorno);
    b.move_balls(w);
    b.draw_balls(w);
    w.display();
    if (stop) {
      w.close();
    }
  }
  write.close();
  std::cout << " --------- THE SIMULATION ENDED ---------" << '\n';
  return 0;
}
