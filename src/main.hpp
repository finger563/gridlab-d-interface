#ifndef MAIN_HPP
#define MAIN_HPP

#include "ConnectionSubsys.hpp"
#include "splitstring.hpp"

#include <boost/network/protocol/http/client.hpp>

#include <stdio.h>
#include <iostream>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

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
  long recv_timeout;
  std::string gld_ip;
  std::string gld_port;

  Options() {
    server_ip = "127.0.0.1";
    server_port = 7777;
    recv_timeout = 10;
    gld_ip = "localhost";
    gld_port = "6267";
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
	if (!strcmp(argv[i], "--recv_timeout"))
	  {
	    recv_timeout = atoi(argv[i+1]);
	  }
	if (!strcmp(argv[i], "--gld_ip"))
	  {
	    gld_ip = argv[i+1];
	  }
	if (!strcmp(argv[i], "--gld_port"))
	  {
	    gld_port = argv[i+1];
	  }
	if (!strcmp(argv[i], "--help"))
	  {
	    std::cout << "usage: \n\t" << argv[0] << "\n"
	      "\t\t --server_ip <ipv4/6 address of server>\n"
	      "\t\t --server_port <port number of server>\n";
	      "\t\t --recv_timeout <timeout in seconds>\n";
	      "\t\t --gld_ip <ipv4/6 address of gld>\n"
	      "\t\t --gld_port <port number of gld>\n";
	    return -1;
	  }
      }
    return 0;
  }
  
  void Print() {
    std::cout << "Options():\n";
    std::cout << "\t server ip address\t\t: " << server_ip.c_str() << std::endl;
    std::cout << "\t server port number\t\t: " << server_port << std::endl;
    std::cout << "\t receive timeout\t\t: " << recv_timeout << std::endl;
    std::cout << "\t gld ip address\t\t\t: " << gld_ip.c_str() << std::endl;
    std::cout << "\t gld port number\t\t: " << gld_port.c_str() << std::endl;
  }
};

#endif
