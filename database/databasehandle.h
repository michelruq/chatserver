#pragma once
#include <string>
#include "mysqlclient.h"

class DataBaseHandle
{
   public:
     DataBaseHandle(MySqlClient& _oMySqlClient,
		    const std::string& localHost,   
		    const std::string& userName,
		    const std::string& password,
		    const std::string& database) : oMySqlClient(_oMySqlClient)
     {
        if(!mysql_real_connect(oMySqlClient.GetClientHandle(), 
				localHost.c_str(), 
				userName.c_str(), 
				password.c_str(), 
				database.c_str(), 0, NULL, 0))
	{
	   std::cout << "Error: can't connect to database " << mysql_error(oMySqlClient.GetClientHandle()) << std::endl;
	}
	else
	{
           std::cout << "Success!" << std::endl;
	}
     }

     MYSQL* GetClientHandle()
     {
        return oMySqlClient.GetClientHandle(); 
     }
   private:
     MySqlClient& oMySqlClient;	   
};

