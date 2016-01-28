#include "main.hpp"

bool gld_interface(std::string gld_url,
		   gld_obj& ret_obj)   // in-out param
{
  ret_obj.has_data = false;
  ret_obj.type = "";
  ret_obj.object = "";
  ret_obj.name = "";
  ret_obj.value = "";

  std::cout << "Connecting to: " << gld_url << std::endl;

  using namespace boost::network;
  http::client client;
  http::client::request request(gld_url);
  request << header("Connection", "close");
  http::client::response response = client.get(request);
  std::cout << body(response) << std::endl;

  std::string text = body(response);
  
  if (text.length())
    {
      // parse xml here from r.text
      rapidxml::xml_document<> doc;
      doc.parse<0>((char *)text.c_str());

      rapidxml::xml_node<> *_type = doc.first_node("property");
      rapidxml::xml_node<> *_name, *_val, *_object;

      if (_type)
	{
	  _object = _type->first_node("object");
	  _name = _type->first_node("name");
	  _val = _type->first_node("value");

	  ret_obj.has_data = true;
	  ret_obj.type = "property";
	  ret_obj.object = _object->value();
	  ret_obj.name = _name->value();
	  ret_obj.value = _val->value();
	}
      else
	{
	  _type = doc.first_node("globalvar");
	  _name = _type->first_node("name");
	  _val = _type->first_node("value");

	  ret_obj.has_data = true;
	  ret_obj.type = "globalvar";
	  ret_obj.name = _name->value();
	  ret_obj.value = _val->value();
	}
    }
  return true;
}

int main(int argc, char** argv) {

  // parse cmd args
  Options options;
  if (options.Parse(argc, argv) == -1)
    return -1;
  options.Print();

  // set up local vars
  int intf_retval = 0;
  int messageSize = 1024;
  char messageData[messageSize + 1];
  char tmpBuf[1024];
  std::string gld_url_base = "http://" + 
    options.gld_ip + ":" + 
    options.gld_port + "/";
  gld_obj object;

  // set up the sockets for interfacing
  Connection* interface;
  if ( options.server_ip.find(":") != std::string::npos )
    interface = new IPV6_Connection();
  else
    interface = new IPV4_Connection();
  interface->serverIP = options.server_ip;
  interface->serverPort = options.server_port;
  if ( interface->Initialize(true) != 0 ) {
    std::cout << "ERROR: Couldn't initialize interface!\n";
    return -1;
  }

  // while loop for event handling
  while (true)
    {
      memset(messageData, 0, messageSize + 1);

      bool setValue = false;
      std::string type, obj, name, value;

      if ( interface->Receive(messageData, messageSize) > 0 )
	{
	  // parse the message here
	  // message = {SET:,GET:}<type>,<object>,<name>,<value>
	  splitstring message = splitstring(messageData + 4);
	  std::vector<std::string> splits = message.split(',');
	  type = splits[0];
	  obj = splits[1];
	  name = splits[2];
	  value = splits[3];

	  if (!strncmp(messageData,"SET:",4)) 
	    {
	      setValue = true;
	    }
	  else if (!strncmp(messageData,"GET:",4))
	    {
	      setValue = false;
	    }

	  std::string gld_url = gld_url_base + obj + "/" + name;
	  if (setValue)
	    gld_url += "=" + value;

	  intf_retval = gld_interface(gld_url, object);
	  if (intf_retval) // everything went well
	    {
	      if (object.has_data)
		{
		  std::cout << "Received:" <<
		    "\n\ttype = " << object.type << 
		    "\n\tobject = " << object.object << 
		    "\n\tname = " << object.name << 
		    "\n\tvalue = " << object.value << std::endl;
		}
	    }
	}
    }

}
