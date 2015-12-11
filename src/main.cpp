#include <cpr.h>

#include <stdio.h>
#include <iostream>

int main(int argc, char** argv) {
  std::string _url = "http://www.httpbin.org/get";
  if (argc > 1)
    _url = argv[1];
  std::cout << "Connecting to: " << _url << std::endl;
  auto r = cpr::Get(cpr::Url{_url});
  if (r.status_code >= 400) {
    std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
  } else {
    std::cout << "Request took " << r.elapsed << std::endl;
    std::cout << "Header:" << std::endl << r.header["content-type"] << std::endl;
    std::cout << "Body:" << std::endl << r.text << std::endl;
  }
}

