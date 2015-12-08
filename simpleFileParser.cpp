/**
 * @file simpleFileParser.cpp
 * @author Sebastian Schmittner <sebastian@schmittner.pw>
 * @version 1.0.2015-12-06
 *
 * @section DESCRIPTION
 *
 * Implementation of the parser. For Details see header.
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


#include "simpleFileParser.hpp"

#include <iostream>
#include <exception>
#include <regex>

bool SimpleFileParser::get(std::string * const r_key, std::string * const r_value){
  std::string line;

  if(! *in_stream){
    throw(new std::ios_base::failure("Error: Bad stream."));
  }

  while(std::getline(*in_stream, line)){
      std::regex re(reg_exp); //default is std::regex_constants::ECMAScript 

      std::smatch match;
      if (std::regex_match(line, match, re) && match.length() >= 3) {

	size_t cur=0;
	//		std::cout << "Matching groups:" << std::endl; 	//< debugging
	for(std::smatch::iterator it = match.begin(); it != match.end(); ++it){
	  //	  std::cout << *it << std::endl; 	//< debugging

	  if(cur == key_id){
	    *r_key = *it;
	  }
	  if(cur == value_id){
	    *r_value = *it;
	  }
	  ++cur;
	}

        return true;
      }

  }//wend

  return false;
}
