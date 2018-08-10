#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cassert>

#include "parser.h"

#define DEBUG

namespace {

using TFTraceProfiler::JSONObj;

enum state_t {
  ROOT_LEVEL,
  PARSING_OBJ_LEVEL,
  PARSING_ARG_LEVEL
};

std::string strip_quote(std::string str) {
  std::string ret;
  size_t start, end;

  start = str.find("\"") + 1;
  end = str.find("\"", start) - 1;
  ret = str.substr(start, end-start+1);

  return ret;
}

size_t str_to_sizet(std::string str) {
  size_t ret;
  std::stringstream ss(str);
  ss >> ret;
  return ret;
}

// parse str and populate obj
void
parseKeyVal(std::string str, JSONObj &obj, state_t state)
{
  size_t pos = str.find(":");
  assert(pos!=std::string::npos);
  std::string key = str.substr(0, pos+1);
  std::string val = str.substr(pos+1);

  key = strip_quote(key);

  if (key=="name" && state==PARSING_OBJ_LEVEL) {
    obj.name = strip_quote(val);
  } else if (key=="name" && state==PARSING_ARG_LEVEL) {
    obj.op_name = strip_quote(val);
  } else if (key=="ph") {
    obj.ph = strip_quote(val);
  } else if (key=="pid") {
    obj.pid = str_to_sizet(val);
  } else if (key=="tid") {
    obj.tid = str_to_sizet(val);
  } else if (key=="ts") {
    obj.ts = str_to_sizet(val);
  } else if (key=="op") {
    obj.op_type = strip_quote(val);
  } else if (key=="dur") {
    obj.dur = str_to_sizet(val);
  } else {
    // TODO: parse op_inputs
  }
}

} // anonymous namespace

namespace TFTraceProfiler {

void
Parser::parse(std::string file_name)
{
  std::ifstream is(file_name.c_str(), std::ifstream::in);
  state_t state = ROOT_LEVEL;

  // JSONObjs are after '['
  std::string str;
  getline(is, str, '[');

  JSONObj obj;
  std::string keyval_str;
  char c;
  while( is.get(c) ) {

    // parsing and populate obj
    if (state!=ROOT_LEVEL) {
      if (c==',' || c=='}') { // indicate end of keyval_str
        parseKeyVal(keyval_str, obj, state);
        keyval_str.clear();
      } else {
        keyval_str += c;
      }
    }

    // state transition
    switch(state) {
    case ROOT_LEVEL:
      if (c=='{') {
        state = PARSING_OBJ_LEVEL;
        obj = JSONObj(); // reset obj
      }
      break;

    case PARSING_OBJ_LEVEL:
      if (c=='{') {
        state = PARSING_ARG_LEVEL;
        keyval_str.clear();
      } else if (c=='}') {
        state = ROOT_LEVEL;
        objects_.push_back(obj);
#ifdef DEBUG
        std::cerr << obj.debugStr();
        std::cerr << std::endl;
#endif
      }
      break;

    case PARSING_ARG_LEVEL:
      if (c=='}') {
        state = PARSING_OBJ_LEVEL;
        // consume ',' right after "args": {...}
        bool res = is.get(c);
        assert(res);
        assert(c==',');
      }
      assert(c!='{');
      break;
    } // end of switch

  } // end while
}

}; // namespace TFTraceProfiler

