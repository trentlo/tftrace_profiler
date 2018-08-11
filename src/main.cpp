#include <iostream>
#include <parser.h>
#include <analyzer.h>

using TFTraceProfiler::Parser;
using TFTraceProfiler::Analyzer;

int main(int argc, char *argv[])
{
  if (argc!=2) {
    std::string command(argv[0]);
    std::cout << "Expected command usage: "
              << command << " ${JSON_FILE}"
              << std::endl;
    return -1;
  }

  std::string json_file(argv[1]);

  std::cout << "Parsing " << json_file << std::endl;

  Parser parser;
  parser.parse(json_file);

  Analyzer analyzer(*parser.getObjs());
  analyzer.analyze();

  return 0;
}

