#include "balls.hpp"
#include "elements.hpp"

#include <iostream>
#include <lyra/lyra.hpp>

#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

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

  auto result = cli.parse({argc, argv});

  Size s;

  if (s.width != 0 && s.high != 0) {
    s.width = width;
    s.high = high;
  } else {
    s.width = 1500;
    s.high = 1500;
  }
  return s;
}

int add_distance(int argc, const char **argv) {
  int d = 0;
  auto cli = lyra::cli();
  cli.add_argument(lyra::opt(d, "distancing")
                       .name("-d")
                       .name("--distancing")
                       .help("Set the distance neccesary to infect"));

  auto result = cli.parse({argc, argv});

  return (d != 0 ? d : 200);
}

int add_sizeBall(int argc, const char **argv) {
  int sb = 0;
  auto cli = lyra::cli();
  cli.add_argument(lyra::opt(sb, "sizeBall")
                       .name("-sb")
                       .name("--sizeBall")
                       .help("Set the size of the balls in the simulation"));

  auto result = cli.parse({argc, argv});

  return (sb != 0 ? sb : 25);
}

#endif
