#include <cstring>
#include <iostream>
#include <fstream>

#include "src/parser/parser.h"
#include "src/parser/st-nodes.h"
#include "src/nfa/nfa.h"
#include "src/main/ezOptionParser.h"

using namespace regex_plus;

int main(int argc, const char* argv[]) {
  ez::ezOptionParser opt;
  opt.overview = "Regex Plus regular expression engine";
  opt.syntax = "./regex-dev [OPTIONS] [REGEX]";
  opt.example = "./regex-dev -s -n \"(0|(1(01*(00)*0)*1)*)*\"\n";

  opt.add(
    "", // Default.
    0, // Required?
    0, // Number of args expected.
    0, // Delimiter if expecting multiple args.
    "Display usage instructions.\n", // Help description.
    "-h",     // Flag token. 
    "--help"  // Flag token.
  );

  opt.add(
    "", // Default.
    0, // Required?
    0, // Number of args expected.
    0, // Delimiter if expecting multiple args.
    "Print syntax tree to stdout.\n", // Help description.
    "-s",     // Flag token. 
    "--print-syntax-tree"  // Flag token.
  );

  opt.add(
    "", // Default.
    0, // Required?
    0, // Number of args expected.
    0, // Delimiter if expecting multiple args.
    "Print NFA to stdout.\n", // Help description.
    "-n",     // Flag token. 
    "--print-nfa"  // Flag token.
  );

  opt.parse(argc, argv);

  if (opt.isSet("-h")) {
  	std::string usage;
    opt.getUsage(usage);
    std::cout << usage;
    return 1;
  }

  std::ostream* st_stream = nullptr;
  std::ostream* nfa_stream = nullptr;

  if (opt.isSet("-s")) {
    st_stream = &std::cout;
  }

  std::ofstream* file = nullptr;

  if (opt.isSet("-n")) {
    //nfa_stream = &std::cout;
    file = new std::ofstream("./nfa.json");
    nfa_stream = file;
  }

  if (opt.lastArgs.size() == 0) {
    std::cout << "No regex specified\n\n";
    std::string usage;
    opt.getUsage(usage);
    std::cout << usage;
    return 1;
  }

  const char* regex_arg = opt.lastArgs[0]->c_str();

  char* buffer = new char[strlen(regex_arg) + 1];
  buffer[strlen(regex_arg)] = '\0';
  strncpy(buffer, regex_arg, strlen(regex_arg));
  
  parser::Parser parser(buffer, st_stream);
  std::shared_ptr<parser::STExpr> syntax_tree = parser.Parse();

  nfa::NFA* nfa = nfa::NFA::FromSyntaxTree(syntax_tree, nfa_stream);

  delete nfa;

  delete file;

  return 0;
}
