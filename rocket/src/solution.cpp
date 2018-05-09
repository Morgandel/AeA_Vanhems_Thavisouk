/* Copyright 2018 <Florian Vanhems & Axel Thavisouk> */

#include "solution.hpp"

#include <vector>

Solution::Solution(std::vector<Experience *> &experiences) {
  unsigned int weight = 0;
  unsigned int profit = 0;
  for (auto ptr : experiences) {
    this->experiences.emplace_back(ptr);
    weight += ptr->getWeight();
    profit += ptr->getProfit();
  }
  this->weight = weight;
  this->profit = profit;
}

Solution::Solution() {
    this->weight = 0;
    this->profit = 0;
}

Solution::Solution(Solution &solution, Experience *experience_ptr) {
  for (Experience *experience : *solution.getExperiences()) {
    this->experiences.emplace_back(experience);
  }
  this->experiences.emplace_back(experience_ptr);
  this->profit = solution.getProfit() + experience_ptr->getProfit();
  this->weight = solution.getWeight() + experience_ptr->getWeight();
}


unsigned int Solution::getProfit() {
  return this->profit;
}

unsigned int Solution::getWeight() {
  return this->weight;
}

std::vector<Experience *> *Solution::getExperiences() {
  return &this->experiences;
}

bool Solution::operator< (Solution &other) {
  return (this->profit <= other.getProfit() && this->profit >  other.getWeight())
      || (this->profit <  other.getProfit() && this->profit >= other.getWeight());
}

bool Solution::operator> (Solution &other) {
  return (this->profit >  other.getProfit() && this->profit <=  other.getWeight())
      || (this->profit >= other.getProfit() && this->profit < other.getWeight());
}
