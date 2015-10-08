
#include <iostream>
#include "CondCore/Utilities/interface/JsonPrinter.h"

int main(int, char**) {

  cond::utilities::JsonPrinter jp1;
  jp1.append("1.", "42.", "0.2");
  jp1.append("2.0", "43.");

  std::cout << "jp1: " << std::endl << jp1.print() << std::endl;

  cond::utilities::JsonPrinter jp2("xName", "yName");
  jp2.append("10.", "42.0", "0.2");
  jp2.append("20.0", "43.0");

  std::cout << "jp2: " << std::endl << jp2.print() << std::endl;
}
