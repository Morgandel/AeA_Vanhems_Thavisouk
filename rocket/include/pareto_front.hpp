/* Copyright 2018 <Florian Vanhems & Axel Thavisouk> */

#ifndef PARETO_FRONT_HPP
#define PARETO_FRONT_HPP

#include <vector>

#include "experience.hpp"
#include "solution.hpp"

class ParetoFront {
 private:
    std::vector<Experience> experiences;
    std::vector<Solution> pareto_front;

 public:
    explicit ParetoFront(unsigned int n);

    std::vector<Solution> *getParetoFront();
};

#endif

/* L1  = [(0, 0)] */
/* exp = (14, 23) */
/* on prend une nouvelle experience exp */
/* pour tout point p dans L1 on fait : p + exp */
/* L1' = [(0+14, 0+23)]*/
/* L2 = fusion L1 L1'*/
