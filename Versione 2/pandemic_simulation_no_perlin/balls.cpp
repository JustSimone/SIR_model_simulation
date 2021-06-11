#include "balls.hpp"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "elements.hpp"

sf::Vector2f Balls::random_speed() {
  sf::Vector2f random_speed{};
  std::uniform_real_distribution<float> vx(-1, 1);
  std::uniform_real_distribution<float> vy(-1, 1);
  do {
    random_speed.x = vx(rnd);
    random_speed.y = vy(rnd);
  } while (
      (random_speed.x * random_speed.x) + (random_speed.y * random_speed.y) <
          1 &&
      (random_speed.x * random_speed.x) + (random_speed.y * random_speed.y) >
          0.8);
  return random_speed;
}

void Balls::bounce_off_the_wall(sf::RenderWindow const &window, int const i) {
  sf::Vector2f &current_speed{ball[i].speed};
  sf::Vector2u const current_position{ball[i].b.getPosition()};
  sf::Vector2u window_size{window.getSize()};
  if (current_position.x < 0) {
    current_speed.x = -current_speed.x;
  } else if (current_position.x > window_size.x) {
    current_speed.x = -current_speed.x;
  }
  if (current_position.y < 0) {
    current_speed.y = -current_speed.y;
  } else if (current_position.y > window_size.y) {
    current_speed.y = -current_speed.y;
  }
}

void Balls::move_balls(sf::RenderWindow &window) {
  int N = ball.size();
  for (int i = 0; i < N; ++i) {
    sf::Vector2u currentPosition{ball[i].b.getPosition()};
    bounce_off_the_wall(window, i);
    float x_velocity = ball[i].speed.x;
    float y_velocity = ball[i].speed.y;
    ball[i].b.move(x_velocity, y_velocity);
  }
}

void Balls::draw_balls(sf::RenderWindow &window) const {
  int N = ball.size();
  for (int i = 0; i < N; ++i) {
    window.draw(ball[i].b);
  }
}

int Balls::probability_of_infection() {
  std::uniform_real_distribution<float> pb(0, 1);
  return (pb(rnd) < beta);
}

int day_counter(int t1, int t2) {
  if (t1 == 0) {
    return 1;
  } else if (t2 == 0) {
    return 2;
  } else
    return 0;
}

void Balls::check_collision(int const day, Variables v) {
  int N = v.get_population();
  int d = v.get_distancing();
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      float x_ = (ball[i].b.getPosition().x - ball[j].b.getPosition().x);
      float y_ = (ball[i].b.getPosition().y - ball[j].b.getPosition().y);
      if (ball[i].state != State::Rec || ball[j].state != State::Rec) {
        if ((x_ * x_ + y_ * y_) < d && probability_of_infection() == true) {
          if (ball[i].state == State::Inf || ball[j].state == State::Inf) {
            ball[i].state = State::Inf;
            ball[j].state = State::Inf;
            if (day_counter(ball[i].t, ball[j].t) == 1) {
              ball[i].t = day;
            } else if (day_counter(ball[i].t, ball[j].t) == 1) {
              ball[j].t = day;
            }
          }
        }
      }
    }
  }
}

bool Balls::count_balls(sf::Clock &c, int &day, std::ofstream &write) const {
  int N = ball.size();
  int infected = 0;
  int susceptible = 0;
  int recovered = 0;
  if (c.getElapsedTime() > sf::seconds(1)) {
    for (int i = 0; i < N; ++i) {
      if (ball[i].state == State::Inf) {
        ++infected;
      } else if (ball[i].state == State::Sus) {
        ++susceptible;
      } else if (ball[i].state == State::Rec) {
        ++recovered;
      }
    }
    write << day << ' ' << susceptible << ' ' << infected << ' ' << recovered
          << '\n';
    std::cout << "   " << day + 1 << "       ";
    std::cout << susceptible << "         ";
    std::cout << infected << "         ";
    std::cout << recovered << '\n';
    if (infected == 0 && day != 0) {
      return true;
    }
    c.restart();
    ++day;
  }
  return false;
}

void Balls::check_status(Variables const &v) {
  int N = v.get_population();
  int const aurea = sqrt(v.get_distancing());
  for (int i = 0; i < N; ++i) {
    State condition = ball[i].state;
    switch (condition) {
      case (State::Rec):
        ball[i].b.setFillColor(sf::Color(255, 255, 0));
        ball[i].b.setOutlineThickness(0);
        break;
      case (State::Inf):
        ball[i].b.setFillColor(sf::Color(255, 0, 0));
        ball[i].b.setOutlineThickness(aurea);
        ball[i].b.setOutlineColor(sf::Color(255, 0, 0, 80));
        break;
      default:
        ball[i].b.setFillColor(sf::Color(130, 245, 255));
        ball[i].b.setOutlineThickness(0);
    }
  }
}

sf::Vector2u Balls::random_position(Variables const &v) {
  int window_height = v.get_sw().height;
  int window_width = v.get_sw().height;
  std::uniform_int_distribution<int> px(0, window_width);
  std::uniform_int_distribution<int> py(0, window_height);
  unsigned int x_position = (unsigned int)px(rnd);
  unsigned int y_position = (unsigned int)py(rnd);
  sf::Vector2u random_position{x_position, y_position};
  return random_position;
}

void Balls::add_balls(Variables const &v) {
  int const N = v.get_population();
  int const n = v.get_infected();
  int const radius = v.get_sb();
  int const age = 0;
  State condition = State::Sus;
  for (int i = 0; i < N; ++i) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    float x_velocity = random_speed().x;
    float y_velocity = random_speed().y;
    sf::Vector2f initial_speed{x_velocity, y_velocity};
    Ball single_ball{circle, age, initial_speed, condition};
    ball.push_back(single_ball);
  }
  for (int j = 0; j < n; ++j) {
    ball[j].state = State::Inf;
  }
  for (int i = 0; i < N; ++i) {
    sf::Vector2u inital_position{random_position(v)};
    int x_position = inital_position.x;
    int y_position = inital_position.y;
    ball[i].b.setPosition(x_position, y_position);
  }
}

void Balls::removed(int const day) {
  int N = ball.size();
  for (int i = 0; i < N; ++i) {
    if (day - (ball[i].t) > (1 / gamma) && ball[i].state == State::Inf) {
      ball[i].state = State::Rec;
    }
  }
}
