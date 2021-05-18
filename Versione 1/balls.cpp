#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "balls.hpp"
#include "elements.hpp"

sf::Vector2f rescale(sf::Vector2u const &vector) {
  float xi = 200;
  float yi = 200;
  sf::Vector2f u;
  if (xi != vector.x || yi != vector.y) {
    u.x = xi / vector.x;
    u.y = yi / vector.y;
  }
  xi = vector.x;
  yi = vector.y;
  return u;
}

std::vector<sf::Vector2f>
Balls::bounce_off_the_wall(std::vector<sf::Vector2f> &vec_1,
                           sf::RenderWindow const &w2) {
  int N = ball.size();
  std::vector<sf::Vector2f> vec_2;

  for (int i = 0; i < N; ++i) {
    sf::Vector2f &v(vec_1[i]);
    if (ball[i].b.getPosition().x > w2.getSize().x) {
      v.x = -v.x;
    } else if (ball[i].b.getPosition().x < 0) {
      v.x = -v.x;
    }

    if (ball[i].b.getPosition().y > w2.getSize().y) {
      v.y = -v.y;
    } else if (ball[i].b.getPosition().y < 0) {
      v.y = -v.y;
    }
    vec_2.push_back(v);
  }
  return vec_2;
}

std::vector<sf::Vector2f> Balls::randomSpeed() {
  time_t timer;
  std::default_random_engine mt(time(&timer));
  int N = ball.size();
  std::vector<sf::Vector2f> v{};

  std::uniform_real_distribution<float> vx(-1, 1);
  std::uniform_real_distribution<float> vy(-1, 1);
  sf::Vector2f vec;
  for (int i = 0; i < N; ++i) {
    do {
      vec.x = vx(mt);
      vec.y = vy(mt);
    } while ((vec.x * vec.x) + (vec.y * vec.y) < 1);
    v.push_back(vec);
  }
  return v;
}

void Balls::moveBalls(std::vector<sf::Vector2f> v) {
  int N = ball.size();
  for (int i = 0; i < N; ++i) {
    ball[i].b.move(v[i]);
  }
}

void Balls::drawBalls(sf::RenderWindow &wind) {
  int N = ball.size();
  for (int i = 0; i < N; ++i) {
    ball[i].b.setScale(rescale(wind.getSize()));
    wind.draw(ball[i].b);
  }
}

int Balls::probability_of_infection() {
  time_t timer;
  std::mt19937 mt(time(&timer));
  std::uniform_real_distribution<float> pb(0, 1);

  return (pb(mt) < beta);
}

void Balls::check_Collision(int const g, Variables v) {

  int N = ball.size();
  int d = v.getDistancing();

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      float x_ = (ball[i].b.getPosition().x - ball[j].b.getPosition().x);
      float y_ = (ball[i].b.getPosition().y - ball[j].b.getPosition().y);
      if ((x_ * x_ + y_ * y_) < d && probability_of_infection() == true) {
        if (ball[i].b.getFillColor() ==
                sf::Color::Red || // modificare con enumclass !!
            ball[j].b.getFillColor() == sf::Color::Red) {
          ball[i].b.setFillColor(sf::Color::Red);
          ball[j].b.setFillColor(sf::Color::Red);
          if (day_counter(ball[i].t, ball[j].t) == 1) {
            ball[i].t = g;
          } else if (day_counter(ball[i].t, ball[j].t) == 1) {
            ball[j].t = g;
          }
        }
      }
    }
  }
}

void Balls::count_balls(sf::Clock &c, int &g, std::ofstream &w) {
  int N = ball.size();
  int infetti = 0;
  int sani = 0;
  int rimossi = 0;
  if (c.getElapsedTime() > sf::seconds(1)) {
    for (int i = 0; i < N; ++i) {
      if (ball[i].b.getFillColor() == sf::Color::Red) {
        ++infetti;
      } else if (ball[i].b.getFillColor() ==
                 sf::Color::Cyan) { // modificare con enumclass
        ++sani;
      } else if (ball[i].b.getFillColor() == sf::Color::Yellow) {
        ++rimossi;
      }
    }
    w << g << ' ' << sani << ' ' << infetti << ' ' << rimossi << '\n';
    std::cout << "   " << g + 1 << "       ";
    std::cout << sani << "         ";
    std::cout << infetti << "         ";
    std::cout << rimossi << '\n';
    c.restart();
    ++g;
  }
}

void Balls::addBalls(int const N, sf::RenderWindow const &window, Variables v) {
  time_t timer;
  std::default_random_engine mt(time(&timer));
  sf::Vector2f size(window.getSize());
  std::uniform_int_distribution<int> px(0, size.x);
  std::uniform_int_distribution<int> py(0, size.y);
  for (int i = 0; i < N; ++i) {
    sf::CircleShape c(v.getSb());
    c.setScale(1, 1);
    c.setFillColor(sf::Color::Cyan);
    c.setOrigin(12.5, 12.5);
    ball.push_back({c, 0});
  }
  ball[0].b.setFillColor(sf::Color::Red);
  for (int i = 0; i < N; ++i) {
    int x = px(mt);
    int y = py(mt);
    ball[i].b.setPosition(x, y);
  }
}

void Balls::removed(int const g) {
  int N = ball.size();
  for (int i = 0; i < N; ++i) {
    if (g - (ball[i].t) > (1 / gamma) &&
        ball[i].b.getFillColor() == sf::Color::Red) {
      ball[i].b.setFillColor(sf::Color::Yellow);
    }
  }
}
