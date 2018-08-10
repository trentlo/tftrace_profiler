#pragma once

#include <vector>
#include <string>
#include <sstream>

namespace TFTraceProfiler {

struct JSONObj {
  std::string name; // event name
  std::string ph; // event type; ph stands for phase somehow
  size_t pid = 0;
  size_t tid = 0;
  size_t ts = 0; // time in usecs
  size_t dur = 0; // duration

  // args, representing op
  std::vector<std::string> op_inputs;
  std::string op_name;
  std::string op_type;

  std::string debugStr() {
    std::stringstream ss;

    ss << "JSONObj " << name << std::endl;
    ss << "\tph " << ph << std::endl;
    ss << "\tpid " << pid << std::endl;
    ss << "\ttid " << tid << std::endl;
    ss << "\tts " << name << std::endl;
    ss << "\tdur " << dur << std::endl;
    ss << "\top_name " << op_name << std::endl;
    ss << "\top_type " << op_type << std::endl;

    return ss.str();
  }
};

class Parser {
public:
  // getter
  const std::vector<JSONObj> *getObjs() { return &objects_; }

  // parse the file and populate objects_
  void parse(std::string file_name);


private:
  std::vector<JSONObj> objects_;

};

}; // namespace TFTraceProfiler
