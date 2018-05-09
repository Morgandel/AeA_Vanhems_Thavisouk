/* Copyright 2018 <Florian Vanhems & Axel Thavisouk> */

#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

#include "experience.hpp"

class Solution {
 private:
    unsigned int profit;
    unsigned int weight;
    std::vector<Experience *> experiences;

 public:
    explicit Solution(std::vector<Experience *> &experiences);
    Solution();
    Solution(Solution &solution, Experience *experiences);

    unsigned int getWeight();
    unsigned int getProfit();
    std::vector<Experience *> *getExperiences();

    bool operator< (Solution &other);
    bool operator> (Solution &other);
};

#endif
