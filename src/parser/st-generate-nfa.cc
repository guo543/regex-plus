#include <iostream>
#include <utility>

#include "src/parser/st-nodes.h"

namespace regex_plus {
namespace parser {

using namespace nfa;

StatePair STUnion::GenerateNFA() {
  std::shared_ptr<NFAState> start = std::make_shared<NFAState>();
  std::shared_ptr<NFAState> end = std::make_shared<NFAState>();

  NFATransition epsilon = NFATransition::CreateEpsilon();

  for (std::shared_ptr<STExpr> operand : operands_) {
    StatePair pair = operand->GenerateNFA();

    start->AddTransition(epsilon, pair.first);
    pair.second->AddTransition(epsilon, end);
  }

  return std::make_pair(start, end);
}

StatePair STConcat::GenerateNFA() {
  std::shared_ptr<NFAState> start = nullptr;
  std::shared_ptr<NFAState> end = nullptr;

  NFATransition epsilon = NFATransition::CreateEpsilon();

  for (std::shared_ptr<STExpr> operand : operands_) {
    StatePair pair = operand->GenerateNFA();

    if (start) {
      end->AddTransition(epsilon, pair.first);
      end = pair.second;
    } else {
      start = pair.first;
      end = pair.second;
    }
  }

  return std::make_pair(start, end);
}

StatePair STKleeneStar::GenerateNFA() {
  // std::cout << "Generating KleeneStar\n";

  StatePair pair = expr_->GenerateNFA();

  std::shared_ptr<NFAState> start = std::make_shared<NFAState>();
  std::shared_ptr<NFAState> end = std::make_shared<NFAState>();

  NFATransition epsilon = NFATransition::CreateEpsilon();
  start->AddTransition(epsilon, pair.first);
  start->AddTransition(epsilon, end);
  pair.second->AddTransition(epsilon, end);
  pair.second->AddTransition(epsilon, pair.first);

  return std::make_pair(start, end);
}

StatePair STSymbol::GenerateNFA() {
  // std::cout << "Generating Symbol\n";

  std::shared_ptr<NFAState> start = std::make_shared<NFAState>();
  std::shared_ptr<NFAState> end = std::make_shared<NFAState>();

  if (value_ == '.') {
    NFATransition trans = NFATransition::CreateWildcard();
    start->AddTransition(trans, end);
  } else {
    NFATransition trans = NFATransition::CreateSymbol(value_);
    start->AddTransition(trans, end);
  }

  return std::make_pair(start, end);
}

}  // namespace parser
}  // namespace regex_plus