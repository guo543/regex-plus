#include "src/parser/st-nodes.h"

#include <iostream>

#define PRINT_DASHES(st_stream, depth)\
  for (int i = 0; i < depth; i++) {\
    *st_stream << "---";\
  }

namespace regex_plus {
namespace parser {

STUnion::STUnion() {}

void STUnion::Print(std::ostream* st_stream, int depth) {
  PRINT_DASHES(st_stream, depth);
  *st_stream << "Union:\n";
  for (std::shared_ptr<STExpr> operand : operands_) {
    operand->Print(st_stream, depth + 1);
  }
}

void STUnion::AddOperand(std::shared_ptr<STExpr> operand) {
  operands_.push_back(operand);
}

STConcat::STConcat() {}

void STConcat::Print(std::ostream* st_stream, int depth) {
  PRINT_DASHES(st_stream, depth);
  *st_stream << "Concat:\n";
  for (std::shared_ptr<STExpr> operand : operands_) {
    operand->Print(st_stream, depth + 1);
  }
}

void STConcat::AddOperand(std::shared_ptr<STExpr> operand) {
  operands_.push_back(operand);
}

STKleeneStar::STKleeneStar(std::shared_ptr<STExpr> expr)
    : expr_(expr) {}

void STKleeneStar::Print(std::ostream* st_stream, int depth) {
  PRINT_DASHES(st_stream, depth);
  *st_stream << "KleeneStar:\n";
  expr_->Print(st_stream, depth + 1);
}

STSymbol::STSymbol(char value)
    : value_(value) {}

void STSymbol::Print(std::ostream* st_stream, int depth) {
  PRINT_DASHES(st_stream, depth);
  *st_stream << "Symbol: " << value_ << "\n";
}

} // namespace parser
} // namespace regex_plus