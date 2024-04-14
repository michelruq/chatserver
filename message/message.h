#pragma once
#include <string>

class Message
{
private:
   std::string _from;
   std::string _to;
   std::string _text;

public:
    Message() = default;
    Message(const std::string& from, const std::string& to, const std::string& text) :
        _from{ from }, _to{ to }, _text{ text } {}
    Message& operator = (const Message& incomingValue)
    {
        if (&incomingValue == this)
        {
            return *this;
       }

        _to = incomingValue._to;
        _from = incomingValue._from;
        _text = incomingValue._text;

        return *this;
   }

   const std::string& GetFrom () const { return _from;}      
   const std::string& GetTo () const { return _to;} 
   const std::string& GetText () const { return _text;} 

};