#include <parser.h>
#include <iostream>

using TFTraceProfiler::Parser;

int main()
{
  std::cout << "Parsing ./timeline.json" << std::endl;

  Parser parser;
  parser.parse("./timeline.json");

  return 0;
}

