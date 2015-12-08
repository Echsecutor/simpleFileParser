/**
 * @file simpleFileParser_T.cpp
 * @author Sebastian Schmittner <sebastian@schmittner.pw>
 * @version 1.0.2015-12-06
 *
 * @section DESCRIPTION
 *
 * Unit test for the simpleFileParser.
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


int main(int args, char *arg[]){

  const char * file1 = "simpleFileParser_T_1.cfg";
  std::cout << "\nUnit test for the simpleFileParser\nTrying to read " << file1 << std::endl;


  SimpleFileParser SP(file1);


  //  SP.set_reg_exp("[abc]");

  std::cout << "Regular expression : " << SP.get_reg_exp()<<std::endl;

  std::string key,value;

  while(SP.get(&key,&value)){
    std::cout << "found key/value pair: (" << key << ", " << value << ")"<< std::endl;
  }


  return 0;
}
