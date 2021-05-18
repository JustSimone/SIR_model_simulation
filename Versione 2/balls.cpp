#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "balls.hpp"

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

sf::Vector2f Balls::randomSpeed() {
  sf::Vector2f randomSpeed{};
  std::uniform_real_distribution<float> vx(-1, 1); // modificare
  std::uniform_real_distribution<float> vy(-1, 1); // modificare
  do {
    randomSpeed.x = vx(rnd);
    randomSpeed.y = vy(rnd);
  } while ((randomSpeed.x * randomSpeed.x) + (randomSpeed.y * randomSpeed.y) <
           1);
  return randomSpeed;
}

void Balls::bounce_off_the_wall(sf::RenderWindow const &window, int const i) {
  sf::Vector2f &currentSpeed{ball[i].speed};
  sf::Vector2u const currentPosition{ball[i].b.getPosition()};
  sf::Vector2u windowSize{window.getSize()};
  if (currentPosition.x < 0) {
    currentSpeed.x = -currentSpeed.x;
  } else if (currentPosition.x > windowSize.x) {
    currentSpeed.x = -currentSpeed.x;
  }
  if (currentPosition.y < 0) {
    currentSpeed.y = -currentSpeed.y;
  } else if (currentPosition.y > windowSize.y) {
    currentSpeed.y = -currentSpeed.y;
  }
}


void Balls::changeSpeed() {
  int N = ball.size();
  for(int i=0; i<N; ++i){
    sf::Vector2f velocity{randomSpeed()};
    ball[i].speed = velocity;
  }
}


void Balls::moveBalls(sf::RenderWindow &window) {
  int N = ball.size();
  for (int i = 0; i < N; ++i) {
    sf::Vector2u currentPosition{ball[i].b.getPosition()};
    bounce_off_the_wall(window, i);
    float xVelocity = ball[i].speed.x;
    float yVelocity = ball[i].speed.y;
    ball[i].b.move(xVelocity, yVelocity);
  }
}

void Balls::drawBalls(sf::RenderWindow &window) {
  int N = ball.size();
  for (int i = 0; i < N; ++i) {
    ball[i].b.setScale(rescale(window.getSize()));
    window.draw(ball[i].b);
  }
}

int Balls::probability_of_infection() {
  std::mt19937 mt{rd()};
  std::uniform_real_distribution<float> pb(0, 1);
  return (pb(mt) < beta);
}

void Balls::check_Collision(int const g, Variables v) {
  int N = ball.size();
  int d = v.getDistancing();
  for (int i = 0; i < N; ++i) {
    checkStatus(i);
    for (int j = 0; j < N; ++j) {
      float x_ = (ball[i].b.getPosition().x - ball[j].b.getPosition().x);
      float y_ = (ball[i].b.getPosition().y - ball[j].b.getPosition().y);
      if ((x_ * x_ + y_ * y_) < d && probability_of_infection() == true) {
        if (ball[i].state == State::Inf || ball[j].state == State::Inf) {
          ball[i].state = State::Inf;
          ball[j].state = State::Inf;
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


void Balls::count_balls(sf::Clock &c, int &g, std::ofstream &write) {
  int N = ball.size();
  int infetti = 0;
  int sani = 0;
  int rimossi = 0;
  if (c.getElapsedTime() > sf::seconds(1)) {
    changeSpeed();
    for (int i = 0; i < N; ++i) {
      if (ball[i].state == State::Inf) {
        ++infetti;
      } else if (ball[i].state == State::Sus) {
        ++sani;
      } else if (ball[i].state == State::Rec) {
        ++rimossi;
      }
    }
    write << g << ' ' << sani << ' ' << infetti << ' ' << rimossi << '\n';
    std::cout << "   " << g + 1 << "       ";
    std::cout << sani << "         ";
    std::cout << infetti << "         ";
    std::cout << rimossi << '\n';
    c.restart();
    ++g;
  }
}

void Balls::checkStatus(int const i) {
  State condition = ball[i].state;
  switch (condition) {
  case (State::Rec):
    ball[i].b.setFillColor(sf::Color::Yellow);
    break;
  case (State::Inf):
    ball[i].b.setFillColor(sf::Color::Red);
    break;
  default:
    ball[i].b.setFillColor(sf::Color::Cyan);
  }
}

sf::Vector2u Balls::randomPosition(sf::RenderWindow const &window) {
  int windowHigh = window.getSize().y;
  int windowWidth = window.getSize().x;
  std::uniform_int_distribution<int> px(0, windowWidth);
  std::uniform_int_distribution<int> py(0, windowHigh);
  unsigned int xPosition = (unsigned int)px(rnd);
  unsigned int yPosition = (unsigned int)py(rnd);
  sf::Vector2u randomPosition{xPosition, yPosition};
  return randomPosition;
}

void Balls::addBalls(sf::RenderWindow const &window, Variables v) {
  int const N = v.getPopulation();
  int const radius = v.getSb();
  int const age = 0;
  State condition = State::Sus;
  for (int i = 0; i < N; ++i) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    float xVelocity = randomSpeed().x;
    float yVelocity = randomSpeed().y;
    sf::Vector2f initialSpeed{xVelocity, yVelocity};
    Ball singleBall{circle, age, initialSpeed, condition};
    ball.push_back(singleBall);
  }
  ball[0].state = State::Inf;
  for (int i=0; i<N; ++i) {
    sf::Vector2u initalPosition{randomPosition(window)};
    int xPosition = initalPosition.x;
    int yPosition = initalPosition.y;
    ball[i].b.setPosition(xPosition, yPosition);
  }
}

void Balls::removed(int const g) {
  int N = ball.size();
  for (int i = 0; i < N; ++i) {
    if (g - (ball[i].t) > (1 / gamma) &&
        ball[i].state == State::Inf) {
      ball[i].state = State::Rec;
    }
  }
}
