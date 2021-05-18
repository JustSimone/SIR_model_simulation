#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

struct Size {
  int width;
  int high;
};

class Variables {
private:
  int size_ball = 25;
  Size size_window;
  int distancing = 200;
  float beta;
  float gamma;
  int population;

public:
  Variables(float b = 0.2, float g = 0.1, int p = 1000);

  // Get Variables
  int getSb();
  Size getSw();
  int getDistancing();
  float getBeta();
  float getGamma();
  int getPopulation();

  // Set Variables

  void setSb(int sb);
  void setSw(Size s);
  void setDistancing(int d);
  void setBeta(float b);
  void setGamma(float g);
  void setPopulation(int p);

  void condition_pupulation(int const p);
};

// COndition for the proprer functioning of the simulation

void condition_SizeBall(int const sb);

void condition_SizeWindow(int const w, int const h);

void condition_distancing(int const d);

void condition_beta(float const b);

void condition_gamma(float const g);



int day_counter(int t1, int t2);

#endif
