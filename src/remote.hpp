#ifndef REMOTE_HPP
#define REMOTE_HPP

#include "ConnectionSubsys.hpp"
#include "splitstring.hpp"

#include <stdio.h>
#include <iostream>

struct gld_obj
{
  bool has_data;
  std::string type;
  std::string object;
  std::string name;
  std::string value;
};

class Options {
public:
  std::string server_ip;
  long server_port;

  Options() {
    server_ip = "127.0.0.1";
    server_port = 7777;
  }

  int Parse(int argc, char **argv) {
    for (int i=0; i < argc; i++)
      {
	if (!strcmp(argv[i], "--server_ip"))
	  {
	    server_ip = argv[i+1];
	  }
	if (!strcmp(argv[i], "--server_port"))
	  {
	    server_port = atoi(argv[i+1]);
	  }
	if (!strcmp(argv[i], "--help"))
	  {
	    std::cout << "usage: \n\t" << argv[0] << "\n"
	      "\t\t --server_ip <ipv4/6 address of server>\n"
	      "\t\t --server_port <port number of server>\n";
	    return -1;
	  }
      }
    return 0;
  }
  
  void Print() {
    std::cout << "Options():\n";
    std::cout << "\t server ip address\t\t: " << server_ip.c_str() << std::endl;
    std::cout << "\t server port number\t\t: " << server_port << std::endl;
  }
};

#endif
