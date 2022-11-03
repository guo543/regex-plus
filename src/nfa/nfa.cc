#include "src/nfa/nfa.h"

#include <iostream>
#include <queue>

namespace regex_plus {
namespace nfa {

NFA::NFA(std::shared_ptr<NFAState> entry,
         std::shared_ptr<NFAState> accept,
         std::ostream* nfa_stream)
    : entry_(entry), accept_(accept), nfa_stream_(nfa_stream) {}

NFA::~NFA() {
  entry_->Clear();

  entry_.reset();
  accept_.reset();
}

NFA* NFA::FromSyntaxTree(std::shared_ptr<parser::STExpr> root,
                         std::ostream* nfa_stream) {
  printf("Generating NFA ...\n");
  
  // test comparator
  /*
  NFATransition transA = NFATransition::CreateSymbol('a');
  NFATransition transB = NFATransition::CreateSymbol('a');

  std::cout << (transA == transB ? "true\n" : "false\n");
  */
  
  auto pair = root->GenerateNFA();

  NFA* instance = new NFA(pair.first, pair.second, nfa_stream);

  instance->Finalize();
  instance->PrintNFA();

  return instance;
}

void NFA::AssignID() {
  std::queue<std::shared_ptr<NFAState>> q;

  int id = 0;

  q.push(entry_);

  while (!q.empty()) {
    std::shared_ptr<NFAState> curr = q.front();
    q.pop();

    // printf("%d\n", id);

    if (curr->id_ != -1 || curr == accept_) {
      continue;
    }

    curr->id_ = id++;

    for (auto iter = curr->transition_.begin();
         iter != curr->transition_.end();
         iter++) {
      auto set = iter->second;

      for (auto setIter = set->begin();
         setIter != set->end();
         setIter++) {
        q.push(*setIter);
      }
    }
  }

  accept_->id_ = id++;

  size_ = id;
}

void NFA::Finalize() {
  AssignID();

  entry_->SetType(StateType::kEntry);
  accept_->SetType(StateType::kAccept);
}

void NFA::PrintNFA() {
  *nfa_stream_ << "\nNFA:\n";
  *nfa_stream_ << "{\n";

  *nfa_stream_ << "size = " << size_ << "\n\n";

  int visited[size_] = { 0 };
  visited[size_ - 1] = 1;
  std::queue<std::shared_ptr<NFAState>> q;

  q.push(entry_);

  while (!q.empty()) {
    std::shared_ptr<NFAState> curr = q.front();
    q.pop();

    if (visited[curr->id_] == 1) {
      continue;
    } else {
      visited[curr->id_] = 1;
    }

    curr->Print(nfa_stream_);

    for (auto iter = curr->transition_.begin();
         iter != curr->transition_.end();
         iter++) {
      auto set = iter->second;

      for (auto setIter = set->begin();
         setIter != set->end();
         setIter++) {
        q.push(*setIter);
      }
    }
  }

  accept_->Print(nfa_stream_);

  *nfa_stream_ << "}\n";
}

} // namespace nfa
} // namespace regex_plus