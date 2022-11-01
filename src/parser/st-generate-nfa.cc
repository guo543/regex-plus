#include "src/parser/st-nodes.h"

#include <utility>
#include <iostream>

namespace regex_plus {
namespace parser {

using namespace nfa;

StatePair STUnion::GenerateNFA() {
  return std::make_pair(nullptr, nullptr);
}

StatePair STConcat::GenerateNFA() {
  return std::make_pair(nullptr, nullptr);
}

StatePair STKleeneStar::GenerateNFA() {
  std::cout << "Generating KleeneStar\n";

  StatePair pair = expr_->GenerateNFA();

  std::shared_ptr<NFAState> start = std::make_shared<NFAState>(StateType::kOther);
  std::shared_ptr<NFAState> end = std::make_shared<NFAState>(StateType::kOther);

  NFATransition epsilon = NFATransition::CreateEpsilon();
  start->AddTransition(epsilon, pair.first);
  start->AddTransition(epsilon, end);
  pair.second->AddTransition(epsilon, end);
  pair.second->AddTransition(epsilon, pair.first);

  return std::make_pair(start, end);
}

StatePair STSymbol::GenerateNFA() {
  std::cout << "Generating Symbol\n";

  std::shared_ptr<NFAState> start = std::make_shared<NFAState>(StateType::kOther);
  std::shared_ptr<NFAState> end = std::make_shared<NFAState>(StateType::kOther);

  if (value_ == '.') {
    NFATransition trans = NFATransition::CreateWildcard();
    start->AddTransition(trans, end);
  } else {
    NFATransition trans = NFATransition::CreateSymbol(value_);
    start->AddTransition(trans, end);
  }

  return std::make_pair(start, end);
}

} // namespace parser
} // namespace regex_plus