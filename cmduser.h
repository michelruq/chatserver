#pragma once

#include "user/user.h"

class CmdUser
{
   public:
     CmdUser(std::string originalString) : _incomingString(originalString)
     {
     }

     CmdUser(User user) :
	     _outgoingString (_cmdwrite
		          + _loginString + user.GetUserLogin() 
			  + _nameString + user.GetUserName()
			  + _passwordString + user.GetUserPassword()
			  + _end)

     {
     }

     bool isWriteCmdCorrect()
     {
	 return (_incomingString.find(_cmdwrite) == 0);
     }

     bool isReadCmdCorrect()
     {
          return (_incomingString.find(_cmdread) == 0);
     }
     std::string GetString()
     {
        return _outgoingString;
     }
     std::string GetLogin()
     {
        size_t start = _incomingString.find(_loginString) + _loginString.size();
	size_t length = _incomingString.find(_nameString) - start;
        return _incomingString.substr(start, length); 
     }
     std::string GetName()
     {
        size_t start = _incomingString.find(_nameString) + _nameString.size();
	size_t length = _incomingString.find(_passwordString) - start;
        return _incomingString.substr(start, length); 
     }
     std::string GetPassword()
     {
        size_t start = _incomingString.find(_passwordString) + _passwordString.size();
	size_t length = _incomingString.find(_end) - start;
        return _incomingString.substr(start, length); 
     }

     std::string WrapRequestForRead(const std::string& requestForReading)
     {
        return _cmdread + _itemnumberId + requestForReading + _end;
     }

     std::string ParseRequestForReading()
     {
        size_t start = _incomingString.find(_itemnumberId) + _itemnumberId.size();
        size_t length = _incomingString.find(_end) - start;
        return _incomingString.substr(start, length);	
     }

   private:
     const std::string _cmdwrite = "userwrite";
     const std::string _cmdread = "userread";
     const std::string _loginString = "login:";
     const std::string _nameString = "name:";
     const std::string _passwordString = "password:";
     const std::string _itemnumberId = "itemnumber:";
     const std::string _end = "end";

     std::string _incomingString;
     std::string _outgoingString;
};


