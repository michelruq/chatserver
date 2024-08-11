#include <iostream>

#include "tcpserver.h" 
#include "cmduser.h"
#include "cmdmessage.h"
#include "user/user.h"
#include "message/message.h"
#include "database/mysqlclient.h"
#include "database/databasehandle.h"
#include "database/databasetable.h"

void foo()
{
  std::string temp;
  TcpServer oTcpServer;
  MySqlClient oMySqlClient;
  DataBaseHandle oDataBaseHandle(oMySqlClient, "localhost", "test_user", "test_password", "test_database");
  DataBaseTable oUserTable(oDataBaseHandle, "users", " first_name, login, password ", "users_id");
  DataBaseTable oMessageTable(oDataBaseHandle, "messages", " _from, _to, _text ", "messages_id");
  while(1)
  {
     temp = "";
     oTcpServer.recieveFrom(temp);
     if(temp == "end")
     {
	oUserTable.MakeSelectAllTable();
	oMessageTable.MakeSelectAllTable();
	std::cout << "client Exited." << std::endl;
	std::cout << "Server is Exiting..!" << std::endl;
	break;
     }
     std::cout << "Data received from client: " << temp << std::endl;   
     CmdUser oIncomingCmdUser(temp);
     CmdMessage oIncomingCmdMessage(temp);
     if (oIncomingCmdUser.isWriteCmdCorrect())
     {
        std::cout << "login is: " << oIncomingCmdUser.GetLogin() << std::endl;
        std::cout << "name is: " << oIncomingCmdUser.GetName() << std::endl;
       	std::cout << "password is: " << oIncomingCmdUser.GetPassword() << std::endl;
        User UserCheck{oIncomingCmdUser.GetLogin(), oIncomingCmdUser.GetPassword(), oIncomingCmdUser.GetName()};
	oUserTable.MakeInsertIntoTable(oIncomingCmdUser.GetName(), oIncomingCmdUser.GetLogin(), oIncomingCmdUser.GetPassword()); 
	CmdUser oOutgoingCmdUser(UserCheck);
	std::cout << oOutgoingCmdUser.GetString() << std::endl;
	temp = "Thank you for user!";
     }
     else if (oIncomingCmdMessage.isWriteCmdCorrect())
     {
        std::cout << "message from: " << oIncomingCmdMessage.GetFrom() << std::endl;
        std::cout << "message to: " << oIncomingCmdMessage.GetTo() << std::endl;
       	std::cout << "text is: " << oIncomingCmdMessage.GetText() << std::endl;
	Message MessageCheck{oIncomingCmdMessage.GetFrom(), oIncomingCmdMessage.GetTo(), oIncomingCmdMessage.GetText()};
	oMessageTable.MakeInsertIntoTable(oIncomingCmdMessage.GetFrom(), oIncomingCmdMessage.GetTo(), oIncomingCmdMessage.GetText());
	CmdMessage oOutgoingCmdMessage(MessageCheck);
	std::cout << oOutgoingCmdMessage.GetString() << std::endl;
	temp = "Thank you for message!";  
     }
     else if(oIncomingCmdUser.isReadCmdCorrect())
     {
       	std::string itemnumber = oIncomingCmdUser.ParseRequestForReading();
        int number = std::stoi(itemnumber) + 1;
	if(number <= oUserTable.GetTableSize())
	{
	   std::string first_field;
	   std::string second_field;
	   std::string third_field;
	   oUserTable.MakeSelectFromTable(first_field, second_field, third_field, number);
           User UserCheck{third_field, second_field, first_field};
	   CmdUser oOutgoingCmdUser(UserCheck);
           temp = oOutgoingCmdUser.GetString();
	}
	else
	{
           temp = "";
  	}
     }
     else if(oIncomingCmdMessage.isReadCmdCorrect())
     {
        std::string itemnumber = oIncomingCmdMessage.ParseRequestForReading();
        int number = std::stoi(itemnumber) + 1;
	if(number <= oMessageTable.GetTableSize())
	{
           std::string first_field;
	   std::string second_field;
	   std::string third_field;
	   oMessageTable.MakeSelectFromTable(first_field, second_field, third_field, number);
           Message MessageCheck{first_field, second_field, third_field};
	   CmdMessage oOutgoingCmdMessage(MessageCheck);
           temp = oOutgoingCmdMessage.GetString();
	}
	else
	{
           temp = "";
  	}
     }
     else
     {
        temp = "";
        std::cout << "Enter the message you want to send to the client" << std::endl;
        std::getline(std::cin, temp);
     }
     if(oTcpServer.sendTo(temp) >= 0)
     {
	 std::cout << "Data successfully sent to the client.!" << std::endl;
     }
   }
}

int main (int argc, char* argv[])
{
   foo();
   return 0;
}

