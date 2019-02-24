#include <iostream>

#include "fat.hxx"

int main() {
  fat::v32::boot_sector_32_s <>bs32{};
  std::cin.read(reinterpret_cast<char *>(&bs32),sizeof(bs32));
  std::cout << std::string{reinterpret_cast<char *>(bs32.oem_name)};
} 
