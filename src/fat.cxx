#include <iostream>
#include <fstream>

#include "fat.hxx"

int main() {
  fat::v32::boot_sector_32_s <>bs32{};
 // fat::v32::boot_sector_32_s <>bs32_default{};
 // fat::v32::file_info_t <>info;
  // std::cin.read(reinterpret_cast<char *>(&bs32),sizeof(bs32));
 // std::cin.read(reinterpret_cast<char *>(&info),sizeof(info));
  // Set these as defaults
//  bs32..sectors_per_cluster = bs32_default..sectors_per_cluster;
//  bs32..number_of_file_allocation_tables = bs32_default..number_of_file_allocation_tables;
//  bs32..media_type = bs32_default..media_type;
//  bs32..fatsize_32 = bs32_default..fatsize_32;
//  bs32..root_cluster = bs32_default..root_cluster;
//  bs32..info = bs32_default..info;
//  bs32..backup_boot_sector = bs32_default..backup_boot_sector;
//  
//  std::cout << std::string{reinterpret_cast<char *>(bs32.oem_name)};
} 
