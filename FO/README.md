# Function Optimization

# Command

## Flags

- algo
    - PSO
    - GA
- func
    - 1~n
- dim: dimentions of function
    - 2
    - 10
    - 20
    - 30
    - 50
    - 100
    - NOTE: hf01,hf02,hf03,hf04,hf05,hf06,cf07&cf08 are NOT defined for D=2

## Example

```
./fo_solver --help
```

```
./fo_solver --algo=<algorithm> --func=<function number> --dim=<dimentions>
```

### PSO

```
./fo_solver -algo PSO -func 1 -dim 2
```

# Ref

https://www.ntu.edu.sg/index/EPNSugan
https://github.com/tsingke/CEC-Benchmark-Functions/tree/master
https://github.com/P-N-Suganthan
