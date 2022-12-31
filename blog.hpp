#ifndef TUP_BLOG_HPP
#define TUP_BLOG_HPP

#include <fcgiapp.h>
#include <fcgio.h>
#include <string>

#include "config.hpp"
#include "parse.hpp"
#include "gen.hpp"

void blogPostR(FCGX_Request request, std::map<std::string, std::string> get, std::map<std::string, std::string> post, std::map<std::string, std::string> cookie) {
  using namespace std;

  string uri = FCGX_GetParam("REQUEST_URI", request.envp);
  uri = uri.substr(10); // /blogPost/

  string tbpid;
  for(char &c : uri) {
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
      tbpid.push_back(c);
    }
    else break;
  }

  blogPost bp;
  if(isNumber(tbpid) && tbpid.size() <= 9) {
    if(!db.getBlogPost(stoi(tbpid), bp)) {
      cout << resp404();
      return;
    }
  }
  else {
    cout << resp423();
    return;
  }

  user author; db.getUser(bp.uid, author);


  cout << 
  vtformat(
    "Status: 200\r\n"
    "Content-type: text/html; charset=utf-8\r\n"
    "\r\n"
    "<!DOCTYPE html>"
    "<html lang=\"ru\">"
    "<head>"
    " <meta charset=\"UTF-8\">"
    " <link rel=\"stylesheet\" href=\"/css/blog.css\">"
    " <link rel=\"stylesheet\" href=\"/css/header.css\">"
    " <link rel=\"stylesheet\" href=\"/css/index.css\">"
    " <title>\"%1\" от %2 - Typuщво.Блоги</title>"
    "</head>"
    "<body>", bp.title, author.tuid) << htmlFooter() << "\r\n" <<
    "<div id=\"content\">"
    "<div id=\"contentLeft\"></div><!--"
    "--><div id=\"contentCenter\">" << "\r\n" <<
    htmlBlogPostWithComments(bp) << "\r\n";
}


void blogR(FCGX_Request request, std::map<std::string, std::string> get, std::map<std::string, std::string> post, std::map<std::string, std::string> cookie) {
  using namespace std;

  string uri = FCGX_GetParam("REQUEST_URI", request.envp);
  uri = uri.substr(6); // /blog/

  string tbid;
  for(char &c : uri) {
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
      tbid.push_back(c);
    }
    else break;
  }

  blog b;
  if(isNumber(tbid) && tbid.size() <= 9) {
    if(!db.getBlog(stoi(tbid), b)) {
      cout << resp404();
      return;
    }
  }
  else {
    if(!db.getBlog(tbid, b)) {
      cout << resp404();
      return;
    }
  }

  std::cout << 
  vtformat(
    "Status: 200\r\n"
    "Content-type: text/html; charset=utf-8\r\n"
    "\r\n"
    "<!DOCTYPE html>"
    "<html lang=\"ru\">"
    "<head>"
    " <meta charset=\"UTF-8\">"
    " <link rel=\"stylesheet\" href=\"/css/blog.css\">"
    " <link rel=\"stylesheet\" href=\"/css/header.css\">"
    " <link rel=\"stylesheet\" href=\"/css/index.css\">"
    " <title>%1 - Typuщво.Блоги</title>"
    "</head>"
    "<body>", b.name) << htmlFooter() << "\r\n" <<
    "<div id=\"content\">"
    "<div id=\"contentLeft\"></div><!--"
    "--><div id=\"contentCenter\">" <<
  htmlBlogTitle(b) << "\r\n";

  vector<blogPost> v;
  db.getBlogBlogPost(b.bid, v);
  
  for(blogPost &e : v) {
    cout << htmlBLogPost(e) << "\r\n";
  }

  cout <<
  "</div><!--"
 "--><div id=\"contentRight\"></div>"
  "</div>";
}


void indexR(FCGX_Request request, std::map<std::string, std::string> get, std::map<std::string, std::string> post, std::map<std::string, std::string> cookie) {
  using namespace std;

  blog b; db.getBlog(1,b);

  std::cout << 
  vtformat(
    "Status: 200\r\n"
    "Content-type: text/html; charset=utf-8\r\n"
    "\r\n"
    "<!DOCTYPE html>"
    "<html lang=\"ru\">"
    "<head>"
    " <meta charset=\"UTF-8\">"
    " <link rel=\"stylesheet\" href=\"/css/blog.css\">"
    " <link rel=\"stylesheet\" href=\"/css/header.css\">"
    " <link rel=\"stylesheet\" href=\"/css/index.css\">"
    " <title>%1 - Typuщво.Блоги</title>"
    "</head>"
    "<body>", b.name) << htmlFooter() << "\r\n" <<
    "<div id=\"content\">"
    "<div id=\"contentLeft\"></div><!--"
    "--><div id=\"contentCenter\">";
  
  vector<blogPost> v;
  db.getBlogBlogPost(b.bid, v);
  
  for(blogPost &e : v) {
    cout << htmlBLogPost(e) << "\r\n";
  }

  cout <<
  "</div><!--"
 "--><div id=\"contentRight\"></div>"
  "</div>";


}


#endif