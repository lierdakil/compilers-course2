#include "driver.h"
#include "parser.tab.hh"
#include <clocale>
#include <iostream>
#include <sstream>

int main() {
  std::ios::sync_with_stdio(false);
  auto loc = std::locale(std::locale(""), "C", std::locale::numeric);
  std::locale::global(loc);
  std::wcin.imbue(std::locale());
  std::wcout.imbue(std::locale());
  std::wcerr.imbue(std::locale());
  std::wstring line;
  Driver::symt_t symtable;
  Driver::funt_t funtable;
  SynTree syntree;
  while (!std::getline(std::wcin, line).eof()) {
    Driver drv(symtable, funtable, syntree, line);
    drv.result = 0;
    yy::parser parser(drv);
    // parser.set_debug_level(true);
    auto res = parser.parse();
    if (res != 0) {
      std::wcerr << L"Parser returned error " << res << std::endl;
    } else {
      std::wcout << "Result is: " << drv.result << std::endl;
    }
  }
  return 0;
}
