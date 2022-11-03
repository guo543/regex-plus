#include "src/nfa/nfa-states.h"

#include <iostream>
#include <vector>

namespace regex_plus {
namespace nfa {

NFATransition::NFATransition(Type type, char symbol)
    : type_(type), symbol_(symbol) {}

NFATransition NFATransition::CreateWildcard() {
  return NFATransition(Type::kWildcard, '\0');
}

NFATransition NFATransition::CreateEpsilon() {
  return NFATransition(Type::kEpsilon, '\0');
}

NFATransition NFATransition::CreateSymbol(char symbol) {
  return NFATransition(Type::kSymbol, symbol);
}

void NFATransition::Print(std::ostream* nfa_stream) const {
  *nfa_stream << "  ";
  switch (type_) {
    case Type::kEpsilon:
      *nfa_stream << "Epsilon:\n";
      break;

    case Type::kWildcard:
      *nfa_stream << "Wildcard:\n";
      break;

    case Type::kSymbol:
      *nfa_stream << "Symbol " << symbol_ << ":\n";
      break;

    default:
      break;
  }
}

NFAState::NFAState()
    : type_(StateType::kOther), id_(-1) {}

NFAState::NFAState(Type type)
    : type_(type), id_(-1) {}

NFAState::~NFAState() {
  //printf("destroyed\n");
}

void NFAState::Clear() {
  std::vector<std::shared_ptr<NFAState>> tmp;

  for (auto it = transition_.begin(); it != transition_.end(); it++) {
    StateSet* set = it->second;
    if (set) {
      for (auto iter = set->begin(); iter != set->end(); iter++) {
        tmp.push_back(*iter);
      }
      set->clear();
      delete set;
      it->second = nullptr;
    }
  }

  for (auto neighbor : tmp) {
    neighbor->Clear();
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

int NFAState::GetID() {
  return id_;
}

void NFAState::SetID(int id) {
  id_ = id;
}

void NFAState::Print(std::ostream* nfa_stream) {
  *nfa_stream << "q" << id_;

  if (type_ == Type::kEntry) {
    *nfa_stream << " (entry state):\n";
  } else if (type_ == Type::kAccept) {
    *nfa_stream << " (accept state):\n";
  } else {
    *nfa_stream << ":\n";
  }

  for (auto iter = transition_.begin(); iter != transition_.end(); iter++) {
    auto set = iter->second;
    iter->first.Print(nfa_stream);

    for (auto setIter = set->begin(); setIter != set->end(); setIter++) {
      *nfa_stream << "    q" << (*setIter)->id_ << "\n";
    }
  }

  *nfa_stream << "\n";
}

} // namespace nfa
} // namespace regex_plus