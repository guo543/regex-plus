#include "src/nfa/nfa-states.h"

#include <iostream>
#include <vector>

namespace regex_plus {
namespace nfa {

NFATransition::NFATransition(Type type, char symbol)
    : type_(type), symbol_(symbol) {}

NFATransition NFATransition::CreateWildcard() {
  return NFATransition(Type::kWildCard, '\0');
}

NFATransition NFATransition::CreateEpsilon() {
  return NFATransition(Type::kEpsilon, '\0');
}

NFATransition NFATransition::CreateSymbol(char symbol) {
  return NFATransition(Type::kSymbol, symbol);
}

NFAState::NFAState()
    : type_(StateType::kOther) {}

NFAState::NFAState(Type type)
    : type_(type) {}

NFAState::~NFAState() {
  printf("destroyed\n");
}

void NFAState::Clear() {
  for (auto it = transition_.begin(); it != transition_.end(); it++) {
    StateSet* set = it->second;
    std::vector<std::shared_ptr<NFAState>> tmp;
    for (auto iter = set->begin(); iter != set->end(); iter++) {
      tmp.push_back(*iter);
    }
    set->clear();
    for (auto neighbor : tmp) {
      neighbor->Clear();
    }
    delete it->second;
    it->second = nullptr;
  }
}

void NFAState::AddTransition(NFATransition trans, std::shared_ptr<NFAState> state) {
  auto it = transition_.find(trans);
  if (it == transition_.end()) {
    StateSet* set = new StateSet();
    set->insert(state);
    transition_.insert({trans, set});
  } else {
    it->second->insert(state);
  }
}

void NFAState::SetType(Type type) {
  type_ = type;
}

} // namespace nfa
} // namespace regex_plus