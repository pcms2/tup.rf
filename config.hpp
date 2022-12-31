#ifndef TUP_CONFIG_HPP
#define TUP_CONFIG_HPP

#include "db.hpp"

#define SOCKET_PATH "127.0.0.1:9000"

#define DB_ADDRESS "jdbc:mariadb://localhost:3306/tup"
#define DB_LOGIN "root"
#define DB_PASSWORD "root"

tupDB db(DB_ADDRESS, DB_LOGIN, DB_PASSWORD);


#endif