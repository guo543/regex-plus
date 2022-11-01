#include "src/nfa/nfa-states.h"

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

NFAState::NFAState(Type type)
    : type_(type) {}

void NFAState::AddTransition(NFATransition trans, std::shared_ptr<NFAState> state) {
  transition_[trans]->insert(state);
}

void NFAState::SetType(Type type) {
  type_ = type;
}

} // namespace nfa
} // namespace regex_plus