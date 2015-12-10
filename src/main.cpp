#include <cpr.h>

#include <stdio.h>
#include <iostream>

int main(int argc, char** argv) {
  auto r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
		    cpr::Authentication{"user", "pass"},
		    cpr::Parameters{{"anon", "true"}, {"key", "value"}});
  std::cout << r.status_code << std::endl;                  // 200
  std::cout << r.header["content-type"] << std::endl;      // application/json; charset=utf-8
  std::cout << r.text << std::endl;                         // JSON text string
}

