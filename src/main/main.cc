#include <cstring>
#include <iostream>
#include <fstream>

#include "src/parser/parser.h"
#include "src/parser/st-nodes.h"
#include "src/nfa/nfa.h"

using namespace regex_plus;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Please specify an input string.\n");
    printf("Usage: regexp [regex]\n");
    return 1;
  }

  // std::ofstream out("./out");
  char* buffer = new char[strlen(argv[1]) + 1];
  buffer[strlen(argv[1])] = '\0';
  strncpy(buffer, argv[1], strlen(argv[1]));
  
  parser::Parser parser(buffer, &std::cout);
  std::shared_ptr<parser::STExpr> syntax_tree = parser.Parse();

  nfa::NFA* nfa = nfa::NFA::FromSyntaxTree(syntax_tree);

  delete[] buffer;

  return 0;
}
