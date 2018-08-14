# Simulation of Human Operator Workload
This program is a discrete event simulation to model the workload of train operators. You can specify the number of human operators and optional automated assistants as well as the tasks to be completed, each with specified interarrival and service time distributions.

## Compilation 
The simulation is compiled via:
```
g++ -std=c++11 -o SHOW runSim.cpp
```

## Deployment
The program is deployed online [here](http://apps.hal.pratt.duke.edu/show) and the front-end source code is available [here](https://github.com/branchvincent/show-web).
