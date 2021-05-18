
#include "elements.hpp"
#include <iostream>

Variables::Variables(float b, float g, int p)
    : beta{b}, gamma{g}, population{p} {
  condition_beta(b);
  condition_gamma(g);
  condition_pupulation(p);
}

// Reading Variables

int Variables::getSb() { return size_ball; }

Size Variables::getSw() { return size_window; }

int Variables::getDistancing() { return distancing; }

float Variables::getBeta() { return beta; }

float Variables::getGamma() { return gamma; }

int Variables::getPopulation() { return population; }

// Setting Variables

void Variables::setSb(int sb) {
  condition_SizeBall(sb);
  size_ball = sb;
}

void Variables::setSw(Size s) {
  condition_SizeWindow(s.width, s.high);
  size_window = s;
}

void Variables::setDistancing(int d) {
  condition_distancing(d);
  distancing = d;
}

void Variables::setBeta(float b) {
  condition_beta(b);
  beta = b;
}

void Variables::setGamma(float g) {
  condition_gamma(g);
  gamma = g;
}

void Variables::setPopulation(int p) {
  condition_pupulation(p);
  population = p;
}

// Check condition for the proper funcionting of the simulation

void condition_SizeBall(int const sb) {
  if (sb < 0) {
    throw std::range_error("The size of the person must be greater than 0");
  }
}

void condition_SizeWindow(int const w, int const h) {
  Size sw;
  sw.width = w;
  sw.high = h;
  if (sw.width < 0 || sw.high < 0) {
    throw std::range_error("The sizes of the window must be greater than 0");
  }
}

void condition_distancing(int const d) {
  if (d < 0) {
    throw std::range_error("The distance necessary to infect must be at least "
                           "the size of the person");
  }
}

void condition_beta(float const b) {
  if (b < 0 || b > 1) {
    throw std::range_error(
        "The Beta factor must be a value included between 0 and 1");
  }
}

void condition_gamma(float const g) {
  if (g < 0 || g > 1) {
    throw std::range_error(
        "The Gamma factor must be a value included between 0 and 1");
  }
}

void Variables::condition_pupulation(int const p) {
  if (p < 0) {
    throw std::range_error("The number of people must be greater than 0");
  } else if (p > 1500) {
    std::cout << "-------------------------------------" << '\n';
    std::cout << "* ---- * ATTENTION * ---- *" << '\n';
    std::cout << "-------------------------------------" << '\n';
    std::cout << "An elevated ammount of people in the simulation may slow dow "
                 "the performance of the computer"
              << '\n'
              << "\nKeep going (y - yes, n - no): ";
    char answer = ' ';
    std::cin >> answer;
    if (answer == 'n') {
      std::cout << "Pupulation: ";
      std::cin >> population;
    }
  }
}

int day_counter(int t1, int t2) {
  if (t1 == 0) {
    return 1;
  } else if (t2 == 0) {
    return 2;
  } else
    return 0;
}
