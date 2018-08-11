#include <analyzer.h>
#include <iostream>
#include <map>
#include <iomanip>
#include <algorithm>

namespace TFTraceProfiler {

void Analyzer::analyze()
{
  size_t min_ts = UINT64_MAX;
  size_t max_ts = 0;

  for (const JSONObj &o : objs_) {
    // only account for complete event
    if (o.ph != "X") {
      continue;
    }

    max_ts = std::max(o.ts, max_ts);
    min_ts = std::min(o.ts, min_ts);

    auto it = total_duration_.find(o.op_type);
    if (it!=total_duration_.end()) {
      it->second += o.dur;
    } else {
      total_duration_.insert(std::pair<std::string, size_t>(o.op_type, o.dur));
    }
  }

  size_t elapsed_time = max_ts - min_ts;

  std::multimap<size_t, std::string> flip_map;
  size_t duration_sum = 0;
  for (auto i : total_duration_) {
    flip_map.insert(std::pair<size_t, std::string>(i.second, i.first));
    duration_sum += i.second;
  }

  // dump analysis results
  std::cout << std::setw(10) << " total elapsed time = "
            << elapsed_time/1000 << " ms"
            << std::endl;;

  size_t id = 0;
  auto i = flip_map.rbegin();
  for (; i!=flip_map.rend(); ++i, ++id) {
    // print only first 30 op_types
    if (id >= 30) {
      break;
    }
    std::string op_type = i->second;
    size_t dur = i->first;
    std::cout << std::setw(30) << op_type << " : "
              << std::setw(10) << dur << " us"
              << " (" << (double)dur/(double)elapsed_time * 100.0 << "%)"
              << std::endl;;
  }
}

}; // namespace TFTraceProfiler

