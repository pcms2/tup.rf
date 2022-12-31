#ifndef TUP_GEN_HPP
#define TUP_GEN_HPP
#include <string>

#include "config.hpp"
#include "vtformat.h"
#include "parse.hpp"


std::string htmlCommentComments(comment &o) {
  using namespace std;
  vector<comment> v; db.getCommentComments(o.cid, v);

  std::string res;

  for(comment &e : v) {
    user author; db.getUser(e.uid, author);
    res += vtformat(
    "<div id=\"comment_%1\" class=\"comment blogComment\">"
    " <div id=\"commentInfo_%1\" class=\"commentInfo\">"
    "   <a href=\"/user/%2\" title=\"Автор\" id=\"commentInfoAuthor_%1\" class=\"commentInfoItem commentInfoAuthor\">%3</a>"
    "   <span title=\"Время создания\" id=\"commentInfoTime_%1\" class=\"commentInfoItem commentInfoTime\">%4</span>"
    "   <span title=\"Дата создания\" id=\"commentInfoDate_1\" class=\"commentInfoItem commentInfoDate\">%5</span>"
    " </div>"
    " <div class=\"commentContent\">"
    "   %6"
    " </div>"
    " <div class=\"commentComments\">",
    e.cid,
    author.tuid,
    author.name,
    e.timecr,
    e.timecr,
    e.text
    );
    res += htmlCommentComments(e);
    res += "</div>";
    res += "</div>";
  }

  return res;
}

std::string htmlBlogPostComments(blogPost &o) {
  using namespace std;
  vector<comment> v; db.getBlogPostComments(o.bpid, v);
  
  string res;

  for(comment &e : v) {
    user author; db.getUser(e.uid, author);
    res += vtformat(
    "<div id=\"comment_%1\" class=\"comment blogComment\">"
    " <div id=\"commentInfo_%1\" class=\"commentInfo\">"
    "   <a href=\"/user/%2\" title=\"Автор\" id=\"commentInfoAuthor_%1\" class=\"commentInfoItem commentInfoAuthor\">%3</a>"
    "   <span title=\"Время создания\" id=\"commentInfoTime_%1\" class=\"commentInfoItem commentInfoTime\">%4</span>"
    "   <span title=\"Дата создания\" id=\"commentInfoDate_1\" class=\"commentInfoItem commentInfoDate\">%5</span>"
    " </div>"
    " <div class=\"commentContent\">"
    "   %6"
    " </div>"
    " <div class=\"commentComments\">",
    e.cid,
    author.tuid,
    author.name,
    e.timecr,
    e.timecr,
    e.text
    );
    res += htmlCommentComments(e);
    res += "  </div>";
    res += "</div>";
  }

  return res;
}

std::string htmlBLogPost(blogPost &e) {
  user author; db.getUser(e.uid, author);
  return vtformat(
    "<div id=\"blogPost_%1\" class=\"blogPost\">"
    " <a href=\"/blogPost/%1\" id=\"blogPostTitle_%1\" class=\"blogPostTitle\">"
    "   %2"
    " </a>"
    " <div id=\"blogPostInfo_%1\" class=\"blogPostInfo\">"
    "   <a href=\"/user/%3\" title=\"Автор\" id=\"blogPostInfoAuthor_%1\" class=\"blogPostInfoItem blogPostInfoAuthor\">%4</a>"
    "   <span title=\"Дата создания\" id=\"blogPostInfoDate_%1\" class=\"blogPostInfoItem blogPostInfoDate\">%5</span>"
    "   <span title=\"Время создания\" id=\"blogPostInfoTime_%1\" class=\"blogPostInfoItem blogPostInfoTime\">%6</span>"
    " </div>"
    " <div id=\"blogPostContent_%1\" class=\"blogPostContent\">"
    "   %7"
    " </div>"
    " <div id=\"blogPostButtons_%1\" class=\"blogPostButtons\">"
    "   <a href=\"/blogPost/%1#comments\" id=\"blogPostButtonComment_%1\" class=\"blogPostButton blogPostButtonComment\">Комментарии</a>"
    " </div>"
    "</div>",
    e.bpid,
    e.title,
    author.tuid,
    author.name,
    e.timecr,
    e.timecr,
    e.text
  );
}

std::string htmlBlogPostWithComments(blogPost &e) {
  user author; db.getUser(e.uid, author);
  std::string res = vtformat(
    "<div id=\"blogPost_%1\" class=\"blogPost\">"
    " <a href=\"/blogPost/%1\" id=\"blogPostTitle_%1\" class=\"blogPostTitle\">"
    "   %2"
    " </a>"
    " <div id=\"blogPostInfo_%1\" class=\"blogPostInfo\">"
    "   <a href=\"/user/%3\" title=\"Автор\" id=\"blogPostInfoAuthor_%1\" class=\"blogPostInfoItem blogPostInfoAuthor\">%4</a>"
    "   <span title=\"Дата создания\" id=\"blogPostInfoDate_%1\" class=\"blogPostInfoItem blogPostInfoDate\">%5</span>"
    "   <span title=\"Время создания\" id=\"blogPostInfoTime_%1\" class=\"blogPostInfoItem blogPostInfoTime\">%6</span>"
    " </div>"
    " <div id=\"blogPostContent_%1\" class=\"blogPostContent\">"
    "   %7"
    " </div>"
    " <div id=\"blogPostButtons_%1\" class=\"blogPostButtons\">"
    "   <a href=\"/blogPost/%1#comments\" id=\"blogPostButtonComment_%1\" class=\"blogPostButton blogPostButtonComment\">Комментарии</a>"
    " </div>"
    "<hr class=\"blogPostCommentsLine\">"
    "<div id=\"comments\" class=\"blogPostComments\">"
      "<div class=\"blogPostCommentsTitle\">Комментарии</div>",
    e.bpid,
    e.title,
    author.tuid,
    author.name,
    e.timecr,
    e.timecr,
    e.text
  );
  res += htmlBlogPostComments(e) + "</div>\r\n";
  return res;
}


std::string htmlFooter() {
  return
  "<header>"
  "  <div id=\"head\">"
  "    <div id=\"headLeft\">"
  "      <a href=\"/\"><span id=\"headLogo\">tnix.cf</span></a>"
  "      <a href=\"https://mos.ru/\"><span id=\"headTitle\">Официальный сайт Мера Москвы</span></a>"
  "    </div>"
  "  </div>"
  "    <ul id=\"headNav\">"
  "      <li class=\"headNavItem\">"
  "        <a href=\"/news/\">Новости</a>"
  "      </li>"
  "      <li class=\"headNavItem\">"
  "        <a href=\"/olymp/\">Олимпиады</a>"
  "      </li>"
  "      <li class=\"headNavItem\">"
  "        <a href=\"/products/\">Проекты</a>"
  "      </li>"
  "      <li class=\"headNavItem\">"
  "        <a href=\"/monocoin/\">MonoCoin</a>"
  "      </li>"
  "      <li class=\"headNavItem\">"
  "        <a href=\"https://www.donationalerts.com/r/ischvo\">Донат</a>"
  "      </li>"
  "      <li class=\"headNavItem\">"
  "        <a href=\"/about/\">Тупищво</a>"
  "      </li>"
  "      <li class=\"headNavItem\">"
  "        <a href=\"/feedback/\">Обратная связь</a>"
  "      </li>"
  "    </ul>"
  "</header>";
}

std::string htmlBlogTitle(blog &e) {
  std::string res = 
  vtformat("<h1 id=\"blogTitle_%1\" class=\"blogTitle\">%2 ", e.bid, e.name, e.vermsg);
  if(e.verificated) {
    res += vtformat(
      "<span title=\"%3\" id=\"verBlog_%1\"class=\"verBlog\">&#10003;</span>",
      e.bid, e.name, e.vermsg);
  }
  res += "</h1>";
  return res;
}

std::string resp400() {
  return 
  "Status: 400\r\n"
  "Content-type: text/html; charset=utf-8\r\n"
  "\r\n" +
  fileToString("html/errors/400.html");
}

std::string resp423() {
  return 
  "Status: 423\r\n"
  "Content-type: text/html; charset=utf-8\r\n"
  "\r\n" +
  fileToString("html/errors/423.html");
}

std::string resp401() {
  return 
  "Status: 401\r\n"
  "Content-type: text/html; charset=utf-8\r\n"
  "\r\n" +
  fileToString("html/errors/401.html");
}

std::string resp403() {
  return 
  "Status: 403\r\n"
  "Content-type: text/html; charset=utf-8\r\n"
  "\r\n" +
  fileToString("html/errors/403.html");
}

std::string resp404() {
  return 
  "Status: 404\r\n"
  "Content-type: text/html; charset=utf-8\r\n"
  "\r\n" +
  fileToString("html/errors/404.html");
}

#endif