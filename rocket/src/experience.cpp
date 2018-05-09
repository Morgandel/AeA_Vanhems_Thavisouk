/* Copyright 2018 <Florian Vanhems & Axel Thavisouk> */

#include "experience.hpp"

#include <random>

Experience::Experience(unsigned int profit, unsigned int weight) {
  this->profit = profit;
  this->weight = weight;
}

Experience::Experience(unsigned int bound) {
  std::mt19937_64 rng;
  std::random_device rd;
  rng.seed(rd());

  std::uniform_int_distribution<unsigned int> gen_weight(1, bound);
  std::uniform_int_distribution<unsigned int> gen_profit(1, bound);

  this->profit = gen_weight(rng);
  this->weight = gen_profit(rng);
}

unsigned int Experience::getProfit() {
  return this->profit;
}

unsigned int Experience::getWeight() {
  return this->weight;
}

bool Experience::operator< (Experience &other) {
  return (this->profit <= other.getProfit() && this->weight >  other.getWeight())
      || (this->profit <  other.getProfit() && this->weight >= other.getWeight());
}

bool Experience::operator> (Experience &other) {
  return (this->profit >= other.getProfit() && this->weight <  other.getWeight())
      || (this->profit >  other.getProfit() && this->weight <= other.getWeight());
}
