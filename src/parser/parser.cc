#include "src/parser/parser.h"

#include <cwctype>

namespace regex_plus {
namespace parser {

Parser::Parser(const char* source, std::ostream* st_stream)
    : source_(source),
      st_stream_(st_stream),
      root_(nullptr),
      parsed_(false) {
  printf("Parser: { source = %s }\n", source);
  cursor_ = source;
  curr_char_ = *cursor_;
}

Parser::~Parser() {
  delete[] source_;
}

char Parser::Next() {
  char tmp = curr_char_;
  cursor_++;
  curr_char_ = *cursor_;

  return tmp;
}

char Parser::Peek() {
  return curr_char_;
}

bool Parser::PeekIs(char c) {
  return c == curr_char_;
}

bool Parser::PeekIsNot(char c) {
  return c != curr_char_;
}

bool Parser::PeekIsSymbol() {
  return iswalnum(Peek()) || PeekIs('.');
}

std::shared_ptr<STExpr> Parser::Parse() {
  root_ = ParseUnion();

  parsed_ = true;

  if (st_stream_ && root_) {
    PrintSyntaxTree();
  }

  return root_;
}

std::shared_ptr<STExpr> Parser::ParseUnion() {
  std::shared_ptr<STExpr> ret = nullptr;
  
  ret = ParseConcat();

  if (PeekIs('|')) {
    std::shared_ptr<STUnion> st_union = std::make_shared<STUnion>();
    st_union->AddOperand(ret);

    while (PeekIs('|')) {
      Next();
      std::shared_ptr<STExpr> operand = ParseConcat();
      st_union->AddOperand(operand);
    }

    ret = st_union;
  }

  return ret;
}

std::shared_ptr<STExpr> Parser::ParseConcat() {
  std::shared_ptr<STExpr> ret = nullptr;

  ret = ParseKleeneStar();

  if (PeekIsSymbol() || PeekIs('(')) {
    std::shared_ptr<STConcat> st_concat = std::make_shared<STConcat>();
    st_concat->AddOperand(ret);

    while (PeekIsSymbol() || PeekIs('(')) {
      std::shared_ptr<STExpr> operand = ParseKleeneStar();
      st_concat->AddOperand(operand);
    }

    ret = st_concat;
  }

  return ret;
}

std::shared_ptr<STExpr> Parser::ParseKleeneStar() {

  std::shared_ptr<STExpr> ret = nullptr;

  if (PeekIsSymbol()) {
    ret = std::make_shared<STSymbol>(Next());
  } else if (PeekIs('(')) {
    Next();
    ret = ParseUnion();
    Next();
  }

  if (PeekIs('*')) {
    ret = std::make_shared<STKleeneStar>(ret);
    Next();
  }
  
  return ret;
}

void Parser::PrintSyntaxTree() {
  if (parsed_) {
    *st_stream_ << "\nSyntax Tree:\n";
    *st_stream_ << "{\n";

    root_->Print(st_stream_, 0);

    *st_stream_ << "}\n\n";
  } else {
    *st_stream_ << "Syntax Tree has not been created\n";
  }
}

} // namespace parser
} // namespace regex_plus