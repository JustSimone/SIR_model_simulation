#include "argument.hpp"
#include "elements.hpp"

#include <lyra/lyra.hpp>

#include <lyra/lyra.hpp>
#include <iostream>
#include "elements.hpp"

Size add_sizeWindow(int argc, const char **argv) {

  int width = 0;
  int high = 0;

  auto cli = lyra::cli();
  cli.add_argument(lyra::opt(width, "width")
                       .name("-w")
                       .name("--width")
                       .help("How wide should it be?"));
  cli.add_argument(lyra::opt(high, "high")
                       .name("-h")
                       .name("--high")
                       .help("By what name should I be known"));

  auto result = cli.parse({ argc, argv });

  std::cout << "width: "<< width << '\n';
  std::cout << "high: "<< high << '\n';

  Size s{width, high};
  return s;
}

int add_distance(int argc, const char **argv) {
  int d;
  auto cli = lyra::cli();
  cli.add_argument(lyra::opt(d, "distancing")
                       .name("-d")
                       .name("--distancing")
                       .help("Set the distance neccesary to infect"));

  auto result = cli.parse({ argc, argv });

  return d;
}

int add_sizeBall(int argc, const char **argv) {
  int sb;
  auto cli = lyra::cli();
  cli.add_argument(lyra::opt(sb, "sizeBall")
                       .name("-sb")
                       .name("--sizeBall")
                       .help("Set the size of the balls in the simulation"));

  auto result = cli.parse({ argc, argv });

  return sb;
}
