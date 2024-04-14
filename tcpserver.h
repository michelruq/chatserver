#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "buffer.h"

#define MESSAGE_LENGTH 1024
#define PORT 7777

class TcpServer
{
   public:
      TcpServer(): oBuffer(MESSAGE_LENGTH) 
      {
         sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
         if(sockert_file_descriptor == -1)
         {
            std::cout << "Socket creation failed.!" << std::endl;
            exit(1);
         }
         serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
         serveraddress.sin_port = htons(PORT);
         serveraddress.sin_family = AF_INET;
         int bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
        if(bind_status == -1)
        {
	   std::cout << "Socket binding failed.!" << std::endl;
           exit(1);
        }
        int connection_status = listen(sockert_file_descriptor, 5);
        if(connection_status == -1)
        {
	   std::cout << "Socket is unable to listen for new connections.!" << std::endl;
           exit(1);
        }  
        else
        {
	   std::cout << "Server is listening for new connection: " << std::endl;
        }
        length = sizeof(client);
        connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);
        if(connection == -1)
        {
	   std::cout << "Server is unable to accept the data from client.!" << std::endl;
           exit(1);
        }
      }

      ~TcpServer()
      {
          std::cout << "Connection with the client closed.!" << std::endl;
	  close(sockert_file_descriptor);
      }
      
      ssize_t sendTo(std::string incomingString)
      {
	 oBuffer.serialize(incomingString);
         return write(connection, oBuffer.getPointerToBuffer(), oBuffer.getBufferSize());
      }

      void recieveFrom(std::string & outgoingString)
      {
	 oBuffer.clear();
         read(connection, oBuffer.getPointerToBuffer(), oBuffer.getBufferSize());
	 oBuffer.deserialize(outgoingString);
      }

   private:
      int sockert_file_descriptor;
      struct sockaddr_in serveraddress;
      struct sockaddr_in client;
      socklen_t length;
     
      int connection;
          
      Buffer oBuffer;
};

