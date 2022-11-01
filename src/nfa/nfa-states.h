#ifndef NFA_STATES_H_
#define NFA_STATES_H_

#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace regex_plus {
namespace nfa {

class NFA;

enum class TransitionType {
  kEpsilon = 0,
  kWildCard = 1,
  kSymbol = 2
};

class NFATransition {
 public:
  using Type = TransitionType;

  static NFATransition CreateWildcard();
  static NFATransition CreateEpsilon();
  static NFATransition CreateSymbol(char symbol);

  class Hash {
   public:
    std::size_t operator()(const NFATransition& trans) const {
      return (std::size_t) trans.type_;
    }
  };

  bool operator==(const NFATransition& other) const {
    if (type_ == other.type_) {
      return type_ == Type::kSymbol ? symbol_ == other.symbol_ : true;
    } else {
      return false;
    }
  }

 private:
  NFATransition(Type type, char symbol);

  //std::unordered_set<char> accepted_set;
  Type type_;
  char symbol_;

  friend class NFAState;
};

enum class StateType {
  kEntry,
  kAccept,
  kOther
};

class NFAState {
 public:
  using Type = StateType;

  explicit NFAState(Type type);
  NFAState();

  ~NFAState();

  void AddTransition(NFATransition trans, std::shared_ptr<NFAState> state);
  void SetType(Type type);

  void Clear();

 private:
  using StateSet = std::unordered_set<std::shared_ptr<NFAState>>;
  std::unordered_map<NFATransition, StateSet*, NFATransition::Hash> transition_;

  Type type_;
};

} // namespace nfa
} // namespace regex_plus

#endif