/* Copyright 2018 <Florian Vanhems & Axel Thavisouk> */

#include "pareto_front.hpp"

#include <vector>
#include <iostream>

ParetoFront::ParetoFront(unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        this->experiences.emplace_back();
    }
}

std::vector<Solution> *ParetoFront::getParetoFront() {
    this->pareto_front.emplace_back();

    /*
    std::cout << "initial pareto : ";
    for (Solution &solution : this->pareto_front) {
        std::cout << "(" << solution.getWeight() << ", " << solution.getProfit() << ")";
    }
    std::cout << "\n";
    */
    // maybe sort the experiences here
    for (Experience &experience : this->experiences) {
        // std::cout << "getting exp : (" << experience.getWeight() << ", " << experience.getProfit() << ")\n";
        std::vector<Solution> l1;
        std::vector<Solution> l2;
        for (Solution solution : this->pareto_front) {
            l1.push_back(solution);
            l2.emplace_back(solution, &experience);
        }
        /*
        std::cout << "l1 : ";
        for (Solution &solution : l1) {
            std::cout << "(" << solution.getWeight() << ", " << solution.getProfit() << "), ";
        }
        std::cout << "\n";
        std::cout << "l2 : ";
        for (Solution &solution : l2) {
            std::cout << "(" << solution.getWeight() << ", " << solution.getProfit() << "), ";
        }
        std::cout << "\n";
        */
        // merging l1 & l2
        this->pareto_front.erase(this->pareto_front.begin(),
                                 this->pareto_front.end());
        // std::cout << "erasure done" << "\n";
        auto l1_it = l1.begin();
        auto l2_it = l2.begin();
        while (l1_it != l1.end() && l2_it != l2.end()) {
            // if 1 is lighter than 2
            if (l1_it->getWeight() < l2_it->getWeight()) {
                // but not pareto dominating 2
                if (l1_it->getProfit() < l2_it->getProfit()) {
                    this->pareto_front.push_back(*l1_it);
                    l1_it++;
                // and pareto dominating 2
                } else {
                    l2_it++;
                }
            // if 2 is lighter than 1
            } else {
                // but not pareto dominating 1
                if (l2_it->getProfit() < l1_it->getProfit()) {
                    this->pareto_front.push_back(*l2_it);
                    l2_it++;
                // and pareto dominating 1
                } else {
                    l1_it++;
                }
            }
        }
        // std::cout << "got to the end of a list" << "\n";
        while (l1_it != l1.end()) {
            this->pareto_front.push_back(*l1_it);
            l1_it++;
        }
        while (l2_it != l2.end()) {
            this->pareto_front.push_back(*l2_it);
            l2_it++;
        }
        /*
        std::cout << "pareto front : ";
        for (Solution &solution : this->pareto_front) {
            std::cout << "(" << solution.getWeight() << "," << solution.getProfit() << "), ";
        }
        std::cout << "\n";
        */
    }
    std::cout << "pareto front : ";
    for (Solution &solution : this->pareto_front) {
        std::cout << "(" << solution.getWeight() << "," << solution.getProfit() << "), ";
    }
    std::cout << "\n";
    std::cout << this->pareto_front.size() << "\n";
    return &this->pareto_front;
}
