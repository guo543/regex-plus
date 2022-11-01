#ifndef NFA_H_
#define NFA_H_

#include <memory>

#include "src/parser/st-nodes.h"
#include "src/nfa/nfa-states.h"

namespace regex_plus {
namespace nfa {

class NFA {
 public:
  static NFA* FromSyntaxTree(std::shared_ptr<parser::STExpr> root);
  ~NFA();

 private:
  explicit NFA(std::shared_ptr<NFAState> entry, std::shared_ptr<NFAState> accept);

  void PrintNFA();

  std::shared_ptr<NFAState> entry_;
  std::shared_ptr<NFAState> accept_;
};

} // namespace nfa
} // namespace regex_plus

#endif