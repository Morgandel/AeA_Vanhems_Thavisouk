/* Copyright 2018 <Florian Vanhems & Axel Thavisouk> */

#include "pareto_front.hpp"

#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

ParetoFront::ParetoFront(unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        this->experiences.emplace_back();
    }
}

std::vector<Solution> *ParetoFront::getParetoFront(bool sort) {
    auto start = std::chrono::steady_clock::now();
    this->pareto_front.emplace_back();

    /*
    std::cout << "initial pareto : ";
    for (Solution &solution : this->pareto_front) {
        std::cout << "(" << solution.getWeight() << ", " << solution.getProfit() << ")";
    }
    std::cout << "\n";
    */
    if (sort) {
        std::sort(this->experiences.begin(), this->experiences.end(),
                  [](Experience &a, Experience &b) {
                      return ((double) a.getProfit() / a.getWeight()) < ((double) b.getProfit() / b.getWeight());
                  });
    }
    // NOTE : when the algorithm adds an experience to the computation (each iteration) :
    //          _ there is at least 1 more optimal point than the
    //            last iteration (the one with each experience)
    //          _ at most k more optimal points than the last
    //            iteration (k being the number of experiments
    //            in the last iteration so far)
    //            (best ratio profit/price so far)
    //          _ we can suppose that the second best is going to grow add k-1
    //            points, the third k-2, etc...
    for (Experience &experience : this->experiences) {  // NOTE : n times
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
        this->pareto_front.erase(this->pareto_front.begin(),  // NOTE : O(k)
                                 this->pareto_front.end());
        // std::cout << "erasure done" << "\n";
        auto l1_it = l1.begin();
        auto l2_it = l2.begin();

        while (l1_it != l1.end() && l2_it != l2.end()) {  // NOTE : O(4k)
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
            } else if (l2_it->getWeight() < l1_it->getWeight()) {
                // but not pareto dominating 1
                if (l2_it->getProfit() < l1_it->getProfit()) {
                    this->pareto_front.push_back(*l2_it);
                    l2_it++;
                // and pareto dominating 1
                } else {
                    l1_it++;
                }
            // if they have the same weight
            } else {
                // and l1 is dominated by l2
                if (l1_it->getProfit() < l2_it->getProfit()) {
                    l1_it++;
                // and l1 dominates l2
                } else {
                    l2_it++;
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
    // std::cout << "experiences : " << "\n";
    // for (Experience &experience : this->experiences) {
    //     std::cout << "(" << experience.getWeight() << "," << experience.getProfit() << "), ";
    // }
    // std::cout << "\n" << "----------------- pareto front -------------------------" << "\n";
    // for (Solution &solution : this->pareto_front) {
    //     std::cout << "(" << solution.getWeight() << "," << solution.getProfit() << "), ";
    // }
    // std::cout << "\n";
    // std::cout << this->pareto_front.size() << "\n";
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << this->experiences.size() << " " << diff.count() << std::endl;
    return &this->pareto_front;
}
