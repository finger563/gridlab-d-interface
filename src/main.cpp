#include <cpr.h>

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

bool gld_interface(std::string gld_url,
		   gld_obj& ret_obj)   // in-out param
{
  ret_obj.has_data = false;
  ret_obj.type = "";
  ret_obj.object = "";
  ret_obj.name = "";
  ret_obj.value = "";

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
  gld_obj object;

  // while loop for event handling
  //while (true)
    {
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
