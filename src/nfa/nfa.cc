#include "src/nfa/nfa.h"

#include <iostream>

namespace regex_plus {
namespace nfa {

NFA::NFA(std::shared_ptr<NFAState> entry, std::shared_ptr<NFAState> accept)
    : entry_(entry), accept_(accept) {}

NFA* NFA::FromSyntaxTree(std::shared_ptr<parser::STExpr> root) {
  printf("Generating NFA ...\n");
  
  // test comparator
  
  NFATransition transA = NFATransition::CreateSymbol('a');
  NFATransition transB = NFATransition::CreateSymbol('a');

  std::cout << (transA == transB ? "true\n" : "false\n");
  

  return new NFA(nullptr, nullptr);
}

} // namespace nfa
} // namespace regex_plus