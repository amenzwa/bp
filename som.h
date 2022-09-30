/* Author: Amen Zwa, Esq.
 * Copyright (c) 2022 sOnit, Inc. */

#ifndef NN_SOM_H
#define NN_SOM_H

#include <stdbool.h>
#include "vec.h"

#define ORDERING 1000 // number of cycles for early, ordering phase

typedef enum Arch {
  r4 = 4, // rectangular, 4 neighbors
  r8 = 8 // rectangular, 8 neighbors
} Arch;

typedef enum Dir {
  north,
  east,
  south,
  west,
  northeast,
  southeast,
  southwest,
  northwest
} Dir;

typedef struct Node {
  int x, y; // node location
} Node;

typedef double (* Dist)(const Vec* u, const Vec* v);

typedef struct Som {
  char* name; // network name
  double alpha; // starting learning rate
  double epsilon; // error criterion
  double e; // current cycle's error
  int C; // number of training cycles
  int P; // number of data patterns
  bool shuffle; // shuffle the input vectors
  int* ord; // input presentation order
  int I; // input vector length
  int H, W; // network dimensions
  Arch arch; // connection architecture
  Node hood[8]; // neighborhood around the winner
  Dist dist; // distance measure
  Vec* i; // temporary store for alpha * [x]
  Vec*** m; // grid of code vectors m[r][c] = w[i]
  int** hits; // hits per node
} Som;

extern Som* newSom(const char* name, double alpha, double epsilon, int C, int P, bool shuffle, int I, int H, int W, Arch arch, Dist dist);
extern void delSom(Som* som);
extern void learn(Vec** ii, Som* som);
extern void dump(Som* som);

#endif // NN_SOM_H
