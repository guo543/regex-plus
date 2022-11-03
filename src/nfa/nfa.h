#ifndef NFA_H_
#define NFA_H_

#include <memory>

#include "src/parser/st-nodes.h"
#include "src/nfa/nfa-states.h"

namespace regex_plus {
namespace nfa {

class NFA {
 public:
  static NFA* FromSyntaxTree(std::shared_ptr<parser::STExpr> root,
                             std::ostream* nfa_stream);
  ~NFA();

 private:
  explicit NFA(std::shared_ptr<NFAState> entry,
               std::shared_ptr<NFAState> accept,
               std::ostream* nfa_stream);

  void AssignID();

  void Finalize();
  void PrintNFA();

  size_t size_;

  std::shared_ptr<NFAState> entry_;
  std::shared_ptr<NFAState> accept_;

  std::ostream* nfa_stream_;
};

} // namespace nfa
} // namespace regex_plus

#endif