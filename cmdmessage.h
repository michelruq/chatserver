#pragma once

#include "message/message.h"

class CmdMessage
{
   public:
     CmdMessage(std::string originalString) : _incomingString(originalString)
     {
     }

     CmdMessage(Message message) :
	     _outgoingString (_cmdwrite
		          + _fromString + message.GetFrom() 
			  + _toString + message.GetTo()
			  + _textString + message.GetText()
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

     std::string GetString()
     {
        return _outgoingString;
     }
     std::string GetFrom()
     {
        size_t start = _incomingString.find(_fromString) + _fromString.size();
	size_t length = _incomingString.find(_toString) - start;
        return _incomingString.substr(start, length); 
     }
     std::string GetTo()
     {
        size_t start = _incomingString.find(_toString) + _toString.size();
	size_t length = _incomingString.find(_textString) - start;
        return _incomingString.substr(start, length); 
     }
     std::string GetText()
     {
        size_t start = _incomingString.find(_textString) + _textString.size();
	size_t length = _incomingString.find(_end) - start;
        return _incomingString.substr(start, length); 
     }

   private:
     const std::string _cmdwrite = "messagewrite";
     const std::string _cmdread = "messageread";
     const std::string _toString = "to:";
     const std::string _fromString = "from:";
     const std::string _textString = "text:";
     const std::string _itemnumberId = "itemnumber:";
     const std::string _end = "end";

     std::string _incomingString;
     std::string _outgoingString;
};


