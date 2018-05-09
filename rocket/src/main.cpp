#include <string>
#include <iostream>
using std::stoi;
using std::stod;

#include "options_parser.hpp"
#include "pareto_front.hpp"

unsigned int parse_unsigned_int(InputParser const &input, std::string const &option);

int main(int argc, char **argv) {
  InputParser input(argc, argv);

  unsigned int n = parse_unsigned_int(input, "-n");

  ParetoFront(n).getParetoFront();

  return 0;
}


unsigned int parse_unsigned_int(InputParser const &input, std::string const &option) {
  if (input.cmdOptionExists({option})) {
    const string &string_n = input.getCmdOption({option});
    if (string_n.empty()) {
      std::cout << "Error : you specified the " << option << " option but did not input a number" << std::endl;
      exit(EXIT_FAILURE);
    }
    int signed_n;
    try {
      signed_n = stoi(string_n);
    } catch (std::invalid_argument& e) {
        std::cerr << "You passed " << string_n << " to the option " << option << "which could not be converted to an int." << std::endl;
        exit(EXIT_FAILURE);
    } catch (std::out_of_range& e) {
        std::cerr << "Error : " << string_n << "is too big to be converted to an int !" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (signed_n <= 0) {
      std::cerr << "Error : " << option << " expects a positive integer !" << std::endl;
      exit(EXIT_FAILURE);
    } else {
      return signed_n;
    }
  } else {
    std::cout << "Error : you must use the `-n <amount>` option to define how many nodes you wish to have in your graph" << std::endl;
    exit(1);
  }
}
