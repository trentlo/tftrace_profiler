#include <iostream>
#include <parser.h>
#include <analyzer.h>

using TFTraceProfiler::Parser;
using TFTraceProfiler::Analyzer;

int main()
{
  std::cout << "Parsing ./timeline.json" << std::endl;

  Parser parser;
  parser.parse("./timeline.json");

  Analyzer analyzer(*parser.getObjs());
  analyzer.analyze();

  return 0;
}

