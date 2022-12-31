#ifndef TUP_DB_HPP
#define TUP_DB_HPP

#include <mariadb/conncpp.hpp>
#include <string>

struct user {
  int uid;
  std::string tuid;
  std::string name;
  bool verificated;
  std::string vermsg;
};

struct blog {
  int bid;
  std::string tbid;
  std::string name;
  bool verificated;
  std::string vermsg;
};

struct blogPost {
  int bpid;
  int uid;
  std::string timecr;
  std::string title;
  std::string text;
  std::string tags;
};

struct comment {
  int cid;
  int uid;
  std::string timecr;
  int pid;
  bool forBlog;
  bool forComment;
  std::string text;
};

class tupDB {
private:
  std::unique_ptr<sql::Connection> conn;
  sql::Driver* driver;
  sql::SQLString url;
  sql::Properties properties;

public:

  tupDB(std::string _url, std::string user, std::string password) {
    driver = sql::mariadb::get_driver_instance();
    // url = "jdbc:mariadb://localhost:3306/tupischvo";
    url = _url;
    properties = {{"user", user}, {"password", password}};
    conn = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
  }

  bool getUser(int uid, user &e) {
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::string req = "select * from users where uid = '" + std::to_string(uid) + "'";
    sql::ResultSet *res = stmnt->executeQuery(req);

    if(res->next()) {
      e.uid = res->getInt(1);
      e.tuid = res->getString(2);
      e.name = res->getString(3);
      e.verificated = res->getInt(4);
      e.vermsg = res->getString(5);
      return true;
    }
    return false;
  }

  bool getUser(std::string tuid, user &e) {
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::string req = "select * from users where tuid = '" + tuid + "'";
    sql::ResultSet *res = stmnt->executeQuery(req);

    if(res->next()) {
      e.uid = res->getInt(1);
      e.tuid = res->getString(2);
      e.name = res->getString(3);
      e.verificated = res->getInt(4);
      e.vermsg = res->getString(5);
      return true;
    }
    return false;
  }

  bool getBlog(int bid, blog &e) {
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::string req = "select * from blogs where bid = '" + std::to_string(bid) + "'";
    sql::ResultSet *res = stmnt->executeQuery(req);

    if(res->next()) {
      e.bid = res->getInt(1);
      e.tbid = res->getString(2);
      e.name = res->getString(3);
      e.verificated = res->getInt(4);
      e.vermsg = res->getString(5);
      return true;
    }
    return false;
  }

  bool getBlog(std::string tbid, blog &e) {
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::string req = "select * from blogs where tbid = '" + tbid + "'";
    sql::ResultSet *res = stmnt->executeQuery(req);

    if(res->next()) {
      e.bid = res->getInt(1);
      e.tbid = res->getString(2);
      e.name = res->getString(3);
      e.verificated = res->getInt(4);
      e.vermsg = res->getString(5);
      return true;
    }
    return false;
  }

  bool getBlogPost(int bpid, blogPost &e) {
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::string req = "select * from blogPosts where bpid = '" + std::to_string(bpid) + "'";
    sql::ResultSet *res = stmnt->executeQuery(req);

    if(res->next()) {
      e.bpid = res->getInt(1);
      e.uid = res->getInt(2);
      e.timecr = res->getString(3);
      e.title = res->getString(4);
      e.text = res->getString(5);
      e.tags = res->getString(6);
      return true;
    }
    return false;
  }

  bool getBlogBlogPost(int bid, std::vector<blogPost> &v) {
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::string req = "select * from blogBlogPosts where bid = '" + std::to_string(bid) + "' ORDER BY bpid DESC";
    sql::ResultSet *res = stmnt->executeQuery(req);

    while(res->next()) {
      int bpid = res->getInt(2);
      v.emplace_back();
      getBlogPost(bpid, v.back());
    }
    return true;
  }

  bool getBlogPostComments(int bpid, std::vector<comment> &v) {
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::string req = "select * from comments where pid = '" + std::to_string(bpid) + "' AND forBlog = '1' ORDER BY cid DESC";
    sql::ResultSet *res = stmnt->executeQuery(req);

    while(res->next()) {
      v.emplace_back();
      comment &e = v.back();

      e.cid = res->getInt(1);
      e.uid = res->getInt(2);
      e.timecr = res->getString(3);
      e.pid = res->getInt(4);
      e.forBlog = res->getInt(5);
      e.forComment = res->getInt(6);
      e.text = res->getString(7);
    }
    return true;
  }

  bool getCommentComments(int cid, std::vector<comment> &v) {
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::string req = "select * from comments where pid = '" + std::to_string(cid) + "' AND forComment = '1' ORDER BY cid DESC";
    sql::ResultSet *res = stmnt->executeQuery(req);

    while(res->next()) {
      v.emplace_back();
      comment &e = v.back();

      e.cid = res->getInt(1);
      e.uid = res->getInt(2);
      e.timecr = res->getString(3);
      e.pid = res->getInt(4);
      e.forBlog = res->getInt(5);
      e.forComment = res->getInt(6);
      e.text = res->getString(7);
    }
    return true;
  }

//   bool getBlogsForUserWrite(uint32_t id, std::vector<blog> &v) {
//     std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
//     std::string req = "select * from canWrite where userID = '" + std::to_string(id) + "'";
//     sql::ResultSet *res = stmnt->executeQuery(req);

//     while(res->next()) {
//       int blogID = res->getInt(2);
//       blog e;
//       if(!getBlog(blogID, e)) return false;
//       v.push_back(e);
//     }
//     return true;
//   }

//   bool getBlogPostByID(int id, blogPost &e) {
//     std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
//     std::string req = "select * from blogPosts where id = '" + std::to_string(id) + "'";
//     sql::ResultSet *res = stmnt->executeQuery(req);

//     if(res->next()) {
//       e.id = res->getInt(1);
//       e.authorId = res->getInt(2);
//       e.time = res->getString(3);
//       e.title = res->getString(4);
//       e.data = to_string(res->getBlob(5));
//       return true;
//     }
//     return false;
//   }

//   bool getBlogPostsByBlogID(int id, std::vector<blogPost> &v) {
//     std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
//     std::string req = "select * from blog_BlogPost where blogID = '" + std::to_string(id) + "'";
//     sql::ResultSet *res = stmnt->executeQuery(req);

//     std::vector<int> z;
//     while(res->next()) {
//       z.push_back(res->getInt(2));
//     }

//     for(auto &i : z) {
//       v.push_back(blogPost());
//       getBlogPostByID(i, v.back());
//     }
//     return 0;
//   }
};

#endif