/**
 * @file simpleFileParser.hpp
 * @author Sebastian Schmittner <sebastian@schmittner.pw>
 * @version 1.0.2015-12-06
 *
 * @section DESCRIPTION
 *
 * This simple Parser reads files/streams line by line that and parses
 * them for key = value pairs. Parsing is done via regular expressions
 * and is hence rather flexible.
 *
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License and a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef _SIMPLEFILEPARSER_HPP
#define _SIMPLEFILEPARSER_HPP

#include <iostream> //forward declarations for iostream
#include <fstream>

#include <string>


class SimpleFileParser{
private:

  bool close_my_stream;
  std::istream* in_stream;

  /// this default uses '=' as the deliminator and '#' as the comment char
  // \\s whitespace [ \t\r\n\f]
  // \\w word [A-Za-z0-9_]
  std::string reg_exp;

  //if non-capturing groups are used properly those can be kept at 1/2:
  size_t key_id=1;
  size_t value_id=2;
  

  SimpleFileParser(){};

    SimpleFileParser(bool p_close_my_stream,
		   std::istream* p_in_stream,
		   const std::string& p_reg_exp,
		     size_t p_key_id,
		     size_t p_value_id)
    :close_my_stream(p_close_my_stream),
     in_stream(p_in_stream),
     reg_exp(p_reg_exp),
     key_id(p_key_id),
     value_id(p_value_id){};

    SimpleFileParser(bool p_close_my_stream,
		   std::istream* p_in_stream,
		   const std::string& p_deliminator,
		   const std::string& p_comment)
    :SimpleFileParser(p_close_my_stream,
		      p_in_stream,
		      std::string("\\s*(\\w+(?: \\w+)*)\\s*")
		      + p_deliminator
		      + std::string("\\s*(\\w+(?: \\w+)*)\\s*(")
		      +  p_comment
		      + std::string(".*)*"),
		      1,
		      2){}; 


  SimpleFileParser(bool p_close_my_stream,
		   std::istream* p_in_stream)
    :SimpleFileParser(p_close_my_stream,
		      p_in_stream,
		      "=",
		      "#"){};
  

public:

  /// pass the stream to read from
  SimpleFileParser(std::istream* p_in_stream)
    :SimpleFileParser(false, p_in_stream){};
  
  /// pass the stream to read from, the deliminators, and comment starting characters
  SimpleFileParser(std::istream* p_in_stream, const std::string& p_deliminator, const std::string& p_comment)
    :SimpleFileParser(false, p_in_stream, p_deliminator, p_comment){}

  
  /// pass the file name to read from
  SimpleFileParser(const char * p_in_file_name)
    :SimpleFileParser(true,new std::ifstream(p_in_file_name)){}
  
  /// pass the stream to read from, the deliminators, and comment starting characters
  SimpleFileParser(const char * p_in_file_name, const std::string& p_deliminator, const std::string& p_comment)
    :SimpleFileParser(true,new std::ifstream(p_in_file_name), p_deliminator, p_comment){}


  /// pass filename and specify regexp and the ids of the matching groups explicitly
  SimpleFileParser(const char * p_in_file_name, const std::string& p_reg_exp,size_t p_key_id, size_t p_value_id)
    :SimpleFileParser(true,new std::ifstream(p_in_file_name), p_reg_exp, p_key_id, p_value_id){}

    /// pass filename and specify regexp and the ids of the matching groups explicitly
  SimpleFileParser(std::istream* p_in_stream, const std::string& p_reg_exp, size_t p_key_id, size_t p_value_id)
    :SimpleFileParser(false,p_in_stream, p_reg_exp,p_key_id,p_value_id){}


  /// will only close the stream if it was opened by the constructor
  ~SimpleFileParser(){
    if(close_my_stream){
      (dynamic_cast<std::ifstream*>(in_stream))->close();
      delete in_stream;
    }
  }

  std::string get_reg_exp(){return reg_exp;}
  // void set_reg_exp(const std::string& p_reg_exp){reg_exp=p_reg_exp;}

  /// returns false if no more key/value pairs are found and otherwise
  /// sets r_key and r_value to contain the next pair found and
  /// returns true.  can be used as in while(get(key,value)){...}
  bool get(std::string * const r_key, std::string * const r_value);  

  
};


#endif

