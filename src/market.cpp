#include "remote.hpp"

int main(int argc, char** argv) {

  // parse cmd args
  Options options;
  if ( options.Parse(argc,argv) == -1 )
    return -1;
  options.Print();

  // set up the sockets for interfacing
  Connection* interface;
  if ( options.server_ip.find(":") != std::string::npos )
    interface = new IPV6_Connection();
  else
    interface = new IPV4_Connection();
  interface->serverIP = options.server_ip;
  interface->serverPort = options.server_port;
  if ( interface->Initialize(false) != 0 ) {
    printf("ERROR: Couldn't initialize interface!\n");
    return -1;
  }

  // set up local vars
  double timerDelay = 0.5;
  timespec timeout, remaining;
  // set up the demand schedule structure here

  // while loop for event handling
  while (true)
    {
      std::string message;

      message = "SET:property,Market_1,fixed_price,100MW";

      interface->Send( message.c_str(),
		       message.length() );

      if ( timerDelay > 0 ) {
	double fractpart,intpart;
	fractpart = modf(timerDelay,&intpart);
	timeout.tv_sec = (unsigned long long)(intpart);
	timeout.tv_nsec = (unsigned long)(fractpart*1000000000.0);
	int return_code = nanosleep (&timeout, &remaining);
      }
      break;
    }
}
