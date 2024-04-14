#pragma once
#include <string>

class User
{
private:
   std::string _login;
   std::string _password;
   std::string _name;

public:
   User() = default;
   User(const std::string& login, const std::string& password, const std::string& name) :
        _login{login}, _password{password}, _name{name} {}
        
   const std::string& GetUserLogin() const {return _login;}   
   
   const std::string& GetUserPassword() const {return _password;}
   void SetUserPassword(const std::string& password) {_password = password;} 
   
   const std::string& GetUserName() const {return _name;}
   void SetUserName(const std::string& name) {_name = name;} 

};