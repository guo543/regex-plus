#include <iostream>
#include <fstream>

#include "src/parser/parser.h"
#include "src/parser/st-nodes.h"

using namespace regex_plus;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Please specify an input string.\n");
    printf("Usage: regexp [regex]\n");
    return 1;
  }

  parser::Parser parser(argv[1], &std::cout);
  std::shared_ptr<parser::STExpr> syntax_tree = parser.Parse();

  return 0;
}