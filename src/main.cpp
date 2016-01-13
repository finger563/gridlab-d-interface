#include <cpr.h>

#include <stdio.h>
#include <iostream>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"


bool gld_interface(std::string gld_url,
		   std::string& object,  // in-out param
		   std::string& name,    // in-out param
		   std::string& value)   // in-out param
{
  std::cout << "Connecting to: " << gld_url << std::endl;
  auto r = cpr::Get(cpr::Url{gld_url});
  if (r.status_code >= 400) {
    std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
    return false;
  } else {
    std::cout << "Request took " << r.elapsed << std::endl;
  }
  
  if (r.text.length())
    {
      // parse xml here from r.text
      rapidxml::xml_document<> doc;
      doc.parse<0>((char *)r.text.c_str());

      rapidxml::xml_node<> *_type = doc.first_node("property");
      rapidxml::xml_node<> *_name, *_val, *_object;

      object = "";
      name = "";
      value = "";

      if (_type)
	{
	  _object = _type->first_node("object");
	  _name = _type->first_node("name");
	  _val = _type->first_node("value");
	  object = _object->value();
	  name = _name->value();
	  value = _val->value();
	  /*
	  std::cout << "Received:" <<
	    "\n\ttype = property" <<
	    "\n\tobject = " << _object->value() << 
	    "\n\tname = " << _name->value() << 
	    "\n\tvalue = " << _val->value() << std::endl;
	  */
	}
      else
	{
	  _type = doc.first_node("globalvar");
	  _name = _type->first_node("name");
	  _val = _type->first_node("value");
	  name = _name->value();
	  value = _val->value();
	  /*
	  std::cout << "Received:" <<
	    "\n\ttype = globalvar" <<
	    "\n\tname = " << _name->value() << 
	    "\n\tvalue = " << _val->value() << std::endl;
	  */
	}
    }
  return true;
}

int main(int argc, char** argv) {

  // parse cmd args
  std::string gld_url = "http://localhost:6267";
  if (argc > 1)
    {
      gld_url = "";
      for (int i=1; i<argc; i++)
	gld_url += argv[i] + std::string(" ");
    }

  // set up the sockets for interfacing

  // set up local vars
  int intf_retval = 0;
  std::string object, name, value;

  // while loop for event handling
  while (true)
    {
      intf_retval = gld_interface(gld_url, object, name, value);
      if (intf_retval) // everything went well
	{
	  std::cout << "Received:" <<
	    "\n\tobject = " << object << 
	    "\n\tname = " << name << 
	    "\n\tvalue = " << value << std::endl;
	}
    }

}
