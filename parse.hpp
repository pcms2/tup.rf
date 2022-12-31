#ifndef TNIX_PARSE_HPP
#define TNIX_PARSE_HPP
#include <sstream>
#include <fstream>
#include <string>
#include <map>

std::string fileToString(std::string path) {
  using namespace std;
  string line;
  stringstream res;
  ifstream in;
  in.open(path);
  while(getline(in,line))
    res << line << '\n';
  return res.str();
}

bool isCyfra(char c) {
  return (c>='0' && c<='9');
}

bool isNumber(std::string s) {
  bool ok = 1;
  for(char &c : s) {
    ok &= (c>='0' && c<='9');
  }
  return ok;
}

std::pair<char,std::map<std::string, std::string>> parseGetParams(std::string s) {
  using namespace std;
  map<string, string> res;
  s.push_back('&');

  bool started = false, readVal = false;
  string key, val;
  for(char &c : s) {
    if(c == '?') {
      started = 1;
      continue;
    }
    if(!started) continue;
    
    if(c == '&') {
      res[key] = val;
      key.clear();
      val.clear();
      readVal = false;
    }
    else if(c == '=') {
      if(readVal)
        return {-1, {}};
      readVal = true;
    }
    else {
      if(readVal) val.push_back(c);
      else key.push_back(c);
    }
  }

  return {0, res};
}

bool isPrefix(std::string a, std::string b) {
  return a.substr(0,b.size()) == b;
}


#endif