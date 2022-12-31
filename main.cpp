#include <fcgiapp.h>
#include <fcgio.h>

#include <iostream>

#include "db.hpp"
#include "vtformat.h"
#include "parse.hpp"
#include "config.hpp"

#include "blog.hpp"

using namespace std;

bool checkpath(string a, string b) {
  return a.substr(0,b.size()) == b;
}


signed main(int argc, char *argv[]) {

  streambuf *cin_streambuf = cin.rdbuf();
  streambuf *cout_streambuf = cout.rdbuf();

  int socketId = FCGX_OpenSocket(SOCKET_PATH, 20);

  FCGX_Request request;

  FCGX_Init();
  FCGX_InitRequest(&request, socketId, 0);
  
  while(true) {
    if(FCGX_Accept_r(&request) < 0) {
      cerr << "[main.cpp] Ошибка: Запрос не принят\n";
      continue;
    }
    cerr << "[main.cpp] Лог: Запрос принят\n";

    fcgi_streambuf cin_fcgi_streambuf(request.in);
    fcgi_streambuf cout_fcgi_streambuf(request.out);
    cin.rdbuf(&cin_fcgi_streambuf);
    cout.rdbuf(&cout_fcgi_streambuf);

    auto [getpSt, get] = parseGetParams(FCGX_GetParam("REQUEST_URI", request.envp));
    map<string,string> post, cookie;

    string path = FCGX_GetParam("REQUEST_URI", request.envp);

    if(isPrefix(path, "/blogPost/")) blogPostR(request, get, post, cookie);
    else if(isPrefix(path, "/blog/")) {
      blogR(request, get, post, cookie);
    }
    else {
      indexR(request, get, post, cookie);
    }

    FCGX_Finish_r(&request);
    cerr << "[main.cpp] Лог: Запрос обработан\n";
  }

  return 0;
}
