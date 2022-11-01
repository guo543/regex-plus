#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <memory>

#include "src/parser/st-nodes.h"

namespace regex_plus {
namespace parser {

class Parser {
 public:
  explicit Parser(const char* source, std::ostream* st_stream);
  ~Parser();

  std::shared_ptr<STExpr> Parse();

 private:
  char Next();
  char Peek();

  bool PeekIs(char c);
  bool PeekIsNot(char c);
  bool PeekIsSymbol();

  std::shared_ptr<STExpr> ParseUnion();
  std::shared_ptr<STExpr> ParseConcat();
  std::shared_ptr<STExpr> ParseKleeneStar();

  void PrintSyntaxTree();

  const char* source_;
  const char* cursor_;

  char curr_char_;

  std::shared_ptr<STExpr> root_;

  std::ostream* st_stream_;

  bool parsed_;
};

} // namespace parser
} // namespace regex_plus

#endif