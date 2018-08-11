#include <parser.h>
#include <map>

namespace TFTraceProfiler {

class Analyzer {
public:
  Analyzer(const std::vector<JSONObj> &objs)
  : objs_(objs)
  {}

  void analyze();

private:
  // map op_type to accumulated duration
  std::map<std::string, size_t> total_duration_;

  const std::vector<JSONObj> &objs_;
};

}; // namespace TFTraceProfiler

