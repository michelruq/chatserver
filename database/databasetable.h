#pragma once
#include <string>
#include "databasehandle.h"

class DataBaseTable
{
   private:
      DataBaseHandle& oDataBaseHandle;
      std::string query_insert_start;
      std::string query_select_start;
      std::string query_short_select;
      const std::string apostrophe = "'";
      const std::string closeBracket = ") ";
      const std::string openBracket = " (";
      const std::string comma = ", ";      

   public:
      DataBaseTable(DataBaseHandle& _oDataBaseHandle,
		        const std::string& tableName,
	                const std::string& parameters,
	                const std::string& selector) : oDataBaseHandle(_oDataBaseHandle)
      {
         query_insert_start = "INSERT INTO " + tableName + openBracket + parameters + closeBracket +" VALUES";
         query_select_start = "SELECT" + parameters + " from " + tableName + " where " + selector + " = ";
         query_short_select = "SELECT * from " + tableName;	 
      }	      

      void MakeInsertIntoTable (const std::string& firstField, const std::string& secondField, const std::string& thirdField)
      {
         std::string query = query_insert_start + openBracket +
		              apostrophe + firstField + apostrophe + comma +
			      apostrophe + secondField + apostrophe + comma +
			      apostrophe + thirdField + apostrophe + closeBracket;
	
	 mysql_query(oDataBaseHandle.GetClientHandle(), query.c_str());
      }

      void MakeSelectFromTable (std::string& firstField, std::string& secondField, std::string& thirdField, int at)
      {
         MYSQL_ROW row;
	 MYSQL_RES* res;
	 std::string query = query_select_start + std::to_string(at);
          
	 mysql_query(oDataBaseHandle.GetClientHandle(), query.c_str());
         
         if(res = mysql_store_result(oDataBaseHandle.GetClientHandle()))
	 {
            row = mysql_fetch_row(res);
            firstField = row[0];
	    secondField = row[1];
	    thirdField = row[2];
	 }	 
      }
      
      int GetTableSize()
      {
         MYSQL_ROW row;
	 MYSQL_RES* res;
	 int count = 0;
         mysql_query(oDataBaseHandle.GetClientHandle(), query_short_select.c_str());
         if(res = mysql_store_result(oDataBaseHandle.GetClientHandle()))
	 {
            count =  mysql_num_rows(res);
         }
	 return count;
      } 

      void MakeSelectAllTable()
      {
         MYSQL_ROW row;
	 MYSQL_RES* res;
         mysql_query(oDataBaseHandle.GetClientHandle(), query_short_select.c_str());
         if(res = mysql_store_result(oDataBaseHandle.GetClientHandle()))
	 {
            while(row = mysql_fetch_row(res))
	    {
               for(unsigned int i = 0; i < mysql_num_fields(res); ++i)
	       {
                  std::cout << row[i] << " "; 
	       }
	       std::cout << std::endl;
	    }
         }
      }
};
