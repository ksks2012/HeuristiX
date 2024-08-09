# Travelling salesman problem (TSP)

# Command

## Flags

- algo
    - SA: sim
    - TABU: tabu search
- dataset: path of dataset

## Examples

```
./tsp_solver -algo <algorithm> -dataset <path_to_dataset>
```

### Simulated annealing (SA)

```
/tsp_solver  -algo SA -dataset ../dataset/pr76.tsp
```

```
/tsp_solver  -algo SA -dataset ../dataset/eil51.tsp
```

### TABU

```
/tsp_solver  -algo TABU -dataset ../dataset/pr76.tsp
```

# Solution

## Node

- index
- x
- y

## Simple

- index