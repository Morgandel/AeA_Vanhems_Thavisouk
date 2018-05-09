/* Copyright 2018 <Florian Vanhems & Axel Thavisouk> */

#ifndef EXPERIENCE_HPP
#define EXPERIENCE_HPP

class Experience {
 private:
    unsigned int profit;
    unsigned int weight;

 public:
    Experience(unsigned int profit, unsigned int weight);
    explicit Experience(unsigned int bound);
    /* Default constructor */
    Experience() : Experience(100) {}

    /* Getters */
    unsigned int getProfit();
    unsigned int getWeight();

    /* Operators */
    bool operator< (Experience &other);
    bool operator> (Experience &other);
};

#endif
