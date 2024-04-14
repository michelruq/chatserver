#include <iostream>

#include "tcpserver.h" 
#include "cmduser.h"
#include "cmdmessage.h"
#include "user/user.h"
#include "message/message.h"
#include <vector>

std::vector<User> UserContainer;
std::vector<Message> MessageContainer;

void foo()
{
  std::string temp;
  TcpServer oTcpServer;
  while(1)
  {
     temp = "";
     oTcpServer.recieveFrom(temp);
     if(temp == "end")
     {
	for(User& it : UserContainer)
	{
           std::cout << "Login is: " << it.GetUserLogin() << " ";
	   std::cout << "Name is: " << it.GetUserName() << " "; 
	   std::cout << "Password is: " << it.GetUserPassword() << std::endl;
	}
	for(Message& it : MessageContainer)
	{
           std::cout << "Message from: " << it.GetFrom() << " ";
	   std::cout << "Message to: " << it.GetTo() << " "; 
	   std::cout << "Message is: " << it.GetText() << std::endl;

	}
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
	UserContainer.push_back(User{oIncomingCmdUser.GetLogin(), oIncomingCmdUser.GetPassword(), oIncomingCmdUser.GetName()});
	CmdUser oOutgoingCmdUser(UserContainer.at(UserContainer.size() - 1));
	std::cout << oOutgoingCmdUser.GetString() << std::endl;
	temp = "Thank you for user!";
     }
     else if (oIncomingCmdMessage.isWriteCmdCorrect())
     {
        std::cout << "message from: " << oIncomingCmdMessage.GetFrom() << std::endl;
        std::cout << "message to: " << oIncomingCmdMessage.GetTo() << std::endl;
       	std::cout << "text is: " << oIncomingCmdMessage.GetText() << std::endl;
	MessageContainer.push_back(Message{oIncomingCmdMessage.GetFrom(), oIncomingCmdMessage.GetTo(), oIncomingCmdMessage.GetText()});
	CmdMessage oOutgoingCmdMessage(MessageContainer.at(MessageContainer.size() - 1));
	std::cout << oOutgoingCmdMessage.GetString() << std::endl;
	temp = "Thank you for message!";  
     }
     else if(oIncomingCmdUser.isReadCmdCorrect())
     {
       	std::string itemnumber = oIncomingCmdUser.ParseRequestForReading();
        int number = std::stoi(itemnumber);
	if(number < UserContainer.size())
	{
           CmdUser oOutgoingCmdUser(UserContainer.at(number));
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
        int number = std::stoi(itemnumber);
	if(number < MessageContainer.size())
	{
           CmdMessage oOutgoingCmdMessage(MessageContainer.at(number));
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
   User admin1("admin1", "!1234", "master");
   User admin2("admin2", "!4321", "submaster");
   UserContainer.push_back(admin1);
   UserContainer.push_back(admin2);
   Message helloFromAdmin1("admin1", "all", "Hello all from master");
   Message helloFromAdmin2("admin2", "all", "Hello all from submaster");
   MessageContainer.push_back(helloFromAdmin1);
   MessageContainer.push_back(helloFromAdmin2);
   foo();
   return 0;
}

