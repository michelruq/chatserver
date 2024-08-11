#pragma once
#include <iostream>
#include <mysql/mysql.h>

class MySqlClient
{
   public:
      MySqlClient()
      {
         mysql_init(&mysql);
      }
  
      ~MySqlClient()
      {
         mysql_close(&mysql);
      }

      MYSQL* GetClientHandle()
      {
	 return &mysql;     
      }      

   private:
      MYSQL mysql;   
};
