#include <cpr.h>

#include <stdio.h>
#include <iostream>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

int main(int argc, char** argv) {
  std::string _url = "http://localhost:6267";
  if (argc > 1)
    {
      _url = "";
      for (int i=1; i<argc; i++)
	_url += argv[i] + std::string(" ");
    }
  std::cout << "Connecting to: " << _url << std::endl;
  auto r = cpr::Get(cpr::Url{_url});
  if (r.status_code >= 400) {
    std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
  } else {
    std::cout << "Request took " << r.elapsed << std::endl;
  }
  
  if (r.text.length())
    {
      // parse xml here from r.text
      rapidxml::xml_document<> doc;
      doc.parse<0>((char *)r.text.c_str());

      rapidxml::xml_node<> *type = doc.first_node("property");
      rapidxml::xml_node<> *name, *val, *object;
      if (type)
	{
	  object = type->first_node("object");
	  name = type->first_node("name");
	  val = type->first_node("value");
	  std::cout << "Received:" <<
	    "\n\ttype = property" <<
	    "\n\tobject = " << object->value() << 
	    "\n\tname = " << name->value() << 
	    "\n\tvalue = " << val->value() << std::endl;
	}
      else
	{
	  type = doc.first_node("globalvar");
	  name = type->first_node("name");
	  val = type->first_node("value");
	  std::cout << "Received:" <<
	    "\n\ttype = globalvar" <<
	    "\n\tname = " << name->value() << 
	    "\n\tvalue = " << val->value() << std::endl;
	}
    }
}
