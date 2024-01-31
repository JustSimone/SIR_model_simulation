#include <SFML/Graphics.hpp>
#include <lyra/lyra.hpp>

#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

struct Size {
  int width = 1500;
  int height = 1500;
};

class Variables {
 private:
  int size_ball;
  Size size_window;
  int distancing;
  float beta;
  float gamma;
  int population;
  int infected;

 public:
  // Get Variables
  int get_sb() const;
  Size get_sw() const;
  int get_distancing() const;
  float get_beta() const;
  float get_gamma() const;
  int get_population() const;
  int get_infected() const;

  // Set Variables

  void set_sb(int sb);
  void set_sw(Size s);
  void set_distancing(int d);
  void set_beta(float b);
  void set_gamma(float g);
  void set_population(int p);
  void set_infected(int i);

  // Check of the number of people to aboid the slowing down of the simulation

  void condition_population(int const p) const;
  void condition_SizeBall(int const sb) const;
  void condition_distancing(int const d) const;
  void condition_infected(int const i) const;

  // Give the value of each element from parse

  void parse_variables(int argc, const char **argv);
};

// COndition for the proprer functioning of the simulation

void condition_SizeWindow(int const w, int const h);
void condition_beta(float const b);
void condition_gamma(float const g);

#endif
