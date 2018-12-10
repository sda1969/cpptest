/*
 * regextest.cpp
 *
 *  Created on: 27 июн. 2017 г.
 *      Author: user
 */
#include <iostream>
#include <string>
#include <regex>

namespace rgx {

void regextest_run(){

  std::string s ("there is a needle in this haystack");
  std::cout << "@@@@@@@@@\n";

  std::regex r ("\\bnee(.{3}).*\\bi(.)", std::regex::ECMAScript);// with syntax option);
  std::smatch m;
  std::regex_search ( s, m, r );
  if (m.ready()) {
	  std::cout << "match size " << m.size() << std::endl;
	  for(auto x: m){
		  std::cout << x.str() << std::endl;
	  }
	  std::cout << "prefix: [" << m.prefix() << "]\n";
	  std::cout << "suffix: [" << m.suffix() << "]\n";
  }
}

}


