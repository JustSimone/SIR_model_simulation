# Basic simulation of a Pandemic
Within this project we implement a program that uses the SIR model to simulate the outbreak of a pandemic. The external libraries needed to properly run the program (some of them must be installed onto the user’s computer):
- Lyra;
- SFML;
- Doctest;
- CMake (optional);

Given the information about the features of a population and the characteristics of the disease, it is possible to recreate a simulation of a pandemic in a space where the entities are allowed to move with a random speed and random directions.
The original idea that we had in mind was to create a space in which the entities would not move around at a constant random velocity but according to a vector field that would have been generated through a Perlin noise generator. Unfortunately, the implementation of the Perlin generator turned out to be more challenging than we thought, and the improvements we made were not as good as we hoped. We included both scripts in the directory: the one without the Perlin noise generator in the pandemic_simulation_no_perlin folder and the one that has it in pandemic_simulation_perlin.

## Running the program

Both of these programs can be complied with simultaneously using the CMakelists.txt file. To optimize the execution and the compilation of the code it is recommended to use the command:

' $ cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build '

The two executables that come out are one named simulation and the
other perlin_simulation both of which accept the same input:

- The beta factor: it represents the probability that a sick entity would
infect a susceptible when they are at a certain distance;
- The gamma factor: it represents the inverse of the recovery time (a gamma factor of 0.1 tells us that an infected entity would take 1/0.1 = 10 days to recover);
11
- The number of entities;
- The dimensions of the window;
- The distance needed to infect;
- The size of the entities in the simulation; – The amount of entities infected at day 0;

In the simulation, the beta factor, the gamma factor, and the number of entities are the essentials inputs that must be provided to the program to run correctly, while the last four variables are already preset but still changeable from the user. In particular, the window’s dimensions are initialized to a 1500 by 1500 pixels square, the distance needed for an entity to infect another is 7 pixels, the number of infected entities is set at 1, and the size of their radius is 3 pixels. The user must give these variables at runtime. To make the input clearer, we used the Lyra library. To every one of the parameters is assigned a command that must be followed from the input value.