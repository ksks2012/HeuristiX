# Problem

## Combinatorial optimization problem

## Continuous optimization problem

## Multi-objective optimization problem

## Constrained optimization problem

## NP-hard problem

# Algorithm

## Stages

- Initialization
- Iteration
    - Generation
    - Evaluation
    - Update
- Result

### Flow of Result

- Table of Latex
- Figure by gnuplot

## Genetic Algorithm (GA)

## Particle Swarm Optimization (PSO)

## Ant Colony Optimization (ACO)

## Simulated Annealing (SA)

## Differential Evolution (DE)

## Tabu Search

## Artificial Bee Colony (ABC)

### Standard ABC Update Formula

- For Employed and Onlooker Bees
$$
v_{ij} = x_{ij} + \phi_{ij} \times (x_{ij} - x_{kj})
$$

- For Scout Bees
$$
x_{ij} = x_{j}^{\text{min}} + \text{rand}(0, 1) \times (x_{j}^{\text{max}} - x_{j}^{\text{min}})
$$

### Adaptive ABC Update Formula

$$
v_{ij} = x_{ij} + (2 \times \text{rand}(0, 1) - 1) \times (x_{ij} - x_{kj}) \times \alpha
$$

### ABC with Differential Mutation

$$
v_{ij} = x_{ij} + F \times (x_{r1j} - x_{r2j}) + \phi_{ij} \times (x_{ij} - x_{kj})
$$

### Hybrid ABC Update Formula

$$
v_{ij} = x_{ij} + \beta \times (g_{j} - x_{ij}) + \phi_{ij} \times (x_{ij} - x_{kj})
$$

# Common Config

- iteration (evaluation)
- run time

# File Config

- example in **/etc/config.yml
- using yaml-cpp for parser

# TODO List

- Different evaluate function for every problem
- Config
    - common config
        - input
        - iteration
    - config that only for the algorithm

# Ref

https://github.com/jbeder/yaml-cpp