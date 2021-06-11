#include "elements.hpp"

// Reading Variables

int Variables::get_sb() const { return size_ball; }
Size Variables::get_sw() const { return size_window; }
int Variables::get_distancing() const { return distancing; }
float Variables::get_beta() const { return beta; }
float Variables::get_gamma() const { return gamma; }
int Variables::get_population() const { return population; }
int Variables::get_infected() const { return infected; }

// Setting Variables

void Variables::set_sb(int sb) {
  condition_SizeBall(sb);
  size_ball = sb;
}

void Variables::set_sw(Size s) {
  condition_SizeWindow(s.width, s.height);
  size_window = s;
}

void Variables::set_distancing(int d) {
  condition_distancing(d);
  distancing = d;
}

void Variables::set_beta(float b) {
  condition_beta(b);
  beta = b;
}

void Variables::set_gamma(float g) {
  condition_gamma(g);
  gamma = g;
}

void Variables::set_population(int p) {
  condition_population(p);
  population = p;
}

void Variables::set_infected(int i) {
  condition_infected(i);
  infected = i;
}

// Check condition for the proper funcionting of the simulation

void Variables::condition_SizeBall(int const sb) const {
  if (sb < 0) {
    throw std::range_error("The size of the person must be greater than 0");
  }

  double window_size_avarege = size_window.width * size_window.width +
                                    size_window.height * size_window.height;
  double max_dimension = window_size_avarege / 10000;
  int sb2 = sb*sb;
  if ( sb2 > (int)max_dimension) {
    throw std::range_error(
        "The size of the person is too big for the size of the window");
  }
}

void condition_SizeWindow(int const w, int const h) {
  Size sw;
  sw.width = w;
  sw.height = h;
  if (sw.width < 0 || sw.height < 0) {
    throw std::range_error("The sizes of the window must be greater than 0");
  }
}

void Variables::condition_distancing(int const d) const {
  if (d < 0) {
    throw std::range_error(
        "The distance necessary to infect must be at least "
        "the size of the person");
  }
  double max_dimension = ((size_window.width + size_window.height) / 2) *
                         ((size_window.width + size_window.height) / 2);
  if (d > (int)max_dimension) {
    throw std::range_error(
        "The infectivity radius of each entity cannot be"
        "bigger than the square mean of the dimensions of"
        "the window");
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

void Variables::condition_infected(int const i) const {
  if (i < 0 || i > population) {
    throw std::range_error(
        "The number of infected entities must be a positive integer and "
        "smaller than the total amount of entities");
  }
}

void Variables::condition_population(int const p) const {
  if (p < 0) {
    throw std::range_error("The number of people must be greater than 0");
  } else if (p > 2000) {
    std::cout << "-------------------------------------" << '\n';
    std::cout << "* ---- * ATTENTION * ---- *" << '\n';
    std::cout << "-------------------------------------" << '\n';
    std::cout
        << "An elevated amount of entities in the simulation may slow down "
           "the performance of the computer"
        << '\n'
        << "\nKeep going (y - yes, n - no): ";
    char answer = ' ';
    std::cin >> answer;
    if (answer == 'n') {
      exit(EXIT_FAILURE);
    } else if (answer == 'y') {
      int area = size_window.width * size_window.height;
      double partition = area / 100;
      if (p > (int)partition) {
        throw std::range_error(
            "There bust be at least 10 pixels available for each entity");
      }
    }
  }
}

void Variables::parse_variables(int argc, const char **argv) {
  bool show_help = false;
  int sb = 3;
  Size sw;
  int d = 50;
  float b = 0.;
  float g = 0.;
  int p = 0;
  int i = 1;
  auto cli =
      lyra::help(show_help) |
      lyra::opt(sb, "Size Ball")["-s"]["--sizeBall"]["--sb"](
          "The radius of a single ball in the simulation. It must be a positive "
          "integer;") |
      lyra::opt(sw.width, "Window's Width")["-x"]["--width"](
          "The width of the window in which the balls move during the simulation. "
          "It must be a positive integer;") |
      lyra::opt(sw.height, "Window's High")["-y"]["--hieght"](
          "The height of the window in which the balls move during the simulation. "
          "It must be a positive integer;") |
      lyra::opt(d, "Distancing")["-d"]["--distance"](
          "The distance necessary to infect other entities. It must be a positive "
          "integer;") |
      lyra::opt(b, "Beta")["-b"]["--beta"](
          "The beta factor - the infectivity factor. "
          "It must be a value between 0 and 1;")
          .required() |
      lyra::opt(g, "Gamma")["-g"]["--gamma"](
          "the gamma factor - the recovery factor, usually it is the inverse of the "
          "time (in days) necessary to recover. It must be a value between 0 "
          "an 1;")
          .required() |
      lyra::opt(p, "Population")["-p"]["--population"](
          "The number of entities in the simulation. It must be a positive "
          "integer.")
          .required() |
      lyra::opt(i, "Infected")["-i"]["--infected"](
          "The number of sick entities that can spread out the disease at day 0. "
          "It must be greater than 0 but smaller than the total number of "
          "entities.");
  auto result = cli.parse({argc, argv});
  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage()
              << std::endl;
    std::cerr << cli << "\n";
    exit(EXIT_FAILURE);
  }
  if (show_help) {
    std::cout << cli << "\n";
    exit(EXIT_SUCCESS);
  }
  set_sb(sb);
  set_sw(sw);
  set_distancing(d);
  set_beta(b);
  set_gamma(g);
  set_population(p);
  set_infected(i);
}
