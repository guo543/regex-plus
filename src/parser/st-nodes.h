#ifndef ST_NODES_H_
#define ST_NODES_H_

#include <vector>
#include <memory>

namespace regex_plus {
namespace parser {

/*
 * Base class of all syntax tree nodes
 */
class STExpr {
 public:
  virtual void Print(std::ostream* st_stream, int depth) = 0;

 protected:
  STExpr() {};
};

class STUnion : public STExpr {
 public:
  STUnion();
  void Print(std::ostream* st_stream, int depth) override;

  void AddOperand(std::shared_ptr<STExpr> operand);

 private:
  std::vector<std::shared_ptr<STExpr>> operands_;
};

class STConcat : public STExpr {
 public:
  STConcat();
  void Print(std::ostream* st_stream, int depth) override;

  void AddOperand(std::shared_ptr<STExpr> operand);

 private:
  std::vector<std::shared_ptr<STExpr>> operands_;
};

class STKleeneStar : public STExpr {
 public:
  STKleeneStar(std::shared_ptr<STExpr> expr);
  void Print(std::ostream* st_stream, int depth) override;

 private:
  std::shared_ptr<STExpr> expr_;
};

class STSymbol : public STExpr {
 public:
  STSymbol(char value);
  void Print(std::ostream* st_stream, int depth) override;
  
 private:
  char value_;
};

} // namespace parser {
} // namespace regex_plus

#endif