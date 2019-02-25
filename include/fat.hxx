namespace fat {
#pragma pack(push, 1)
using jmp_inst_t = std::uint8_t[3];
using oem_name_t = std::uint8_t[8];
using bytes_per_sector_t = std::uint16_t;
using sectors_per_cluster_t = std::uint8_t;
using reserved_sectors_t = std::uint16_t;
using number_of_file_allocation_tables_t = std::uint8_t;
using root_entries_t = std::uint16_t;
using small_sectors_t = std::uint16_t;
enum class media_types_e { removable = std::uint8_t(0xf0), fixed = std::uint8_t(0xf8) };
using sectors_per_file_allocation_table_t = std::uint16_t;
using sectors_per_track_t = std::uint8_t;
using number_of_heads_t = std::uint8_t;
using hidden_sectors_t = std::uint32_t;
using sector_count_t = std::uint32_t;

template <auto fat_size_in_bytes = 268435456, auto sector_size = 512>
struct bios_param_block_t {
  bytes_per_sector_t bytes_per_sector{sector_size};
  // 4096 bytes per cluster is a standard
  sectors_per_cluster_t sectors_per_cluster{8};
  // Reserved sectors are used for aligning the start of data
  // to intergral multiples of cluster size.
  // Not sure what to put here
  reserved_sectors_t reserved_sectors{1};
  number_of_file_allocation_tables_t number_of_file_allocation_tables{1};
  // Required to be zero for fat32
  root_entries_t root_entries{0};
  // Required to be zero for fat32
  small_sectors_t small_sectors{0};
  media_types_e media_type{media_types_e::removable};
  // Required to be zero for fat32
  sectors_per_file_allocation_table_t sectors_per_file_allocation_table{0};
  // We're booting LBA not track geometry devices
  sectors_per_track_t sectors_per_track{0};
  // Again this may not be relevant with virtual drive
  number_of_heads_t number_of_heads{0};
  // Not sure what to put here
  hidden_sectors_t hidden_sectors{0x13};
  sector_count_t sector_count{fat_size_in_bytes / sector_size};
};


template <auto fat_size_in_bytes = 268435456, auto sector_size = 512>
struct boot_sector_s {
  jmp_inst_t jmp_inst{0xEB,0x32,0x90};
  oem_name_t oem_name{u'm',u'k',u'f',u's',u'.',u'f',u'a',u't'};
  bios_param_block_t <fat_size_in_bytes, sector_size>bios_param_block{};
};

inline namespace v32 {
template<auto bytes_per_section = 512>
using file_info_t = std::uint8_t[];
using fat_size32_t = std::uint32_t;
using ext_flags_t = std::uint8_t[2];
using version_t = std::uint16_t;
using root_cluster_t = std::uint32_t;
using info_t = std::uint16_t;
using backup_boot_sector_t = std::uint16_t;
using reserved_0_t = std::uint8_t[12];
using drive_number_t = std::uint8_t;
using reserved_1_t = std::uint8_t;
using extended_boot_signature_t = std::uint8_t;
using volume_serial_number_t = std::uint32_t;
using volume_label_t = std::uint8_t[11];
using file_system_type_t = std::uint64_t;
using na_0_t = std::uint8_t[420];
using signature_word_t = std::uint8_t[2];
using fat_entry_t = std::uint32_t;

// Number of sectors for fat
// Assuming 8 sectors or 1 cluster
// we get 4098 kb / 32 byte entries possible
// for our fat table
constexpr auto default_fat_size = 8;

template <auto byte_size = 4098>
struct fat_table_s {
  fat_entry_t reserved[2] = {0x0ffffff8,0x08000000};
  fat_entry_t root = 2;
  fat_entry_t rest[byte_size-sizeof(reserved)-sizeof(root)]{0};
};

template <auto sector_size> using na_1_t = std::uint8_t[sector_size - 512];
// bytes = 256MB
template <auto fat_size_in_bytes = 268435456, auto sector_size = 512>
struct bios_param_block32_t {
  bios_param_block_t<fat_size_in_bytes, sector_size> bpb{};
  fat_size32_t fatsize_32{default_fat_size};
  ext_flags_t ext_flags{0x64 | 0x01, 0x00};
  version_t version{0};
  root_cluster_t root_cluster{2};
  info_t info{1};
  backup_boot_sector_t backup_boot_sector{2};
  // First 8 sectors are used for first cluster
  reserved_0_t reserved_0 = {0};
  drive_number_t drive_number{0x13};
  reserved_1_t reserved_1{0};
  extended_boot_signature_t extended_boot_signature{0x29};
  volume_serial_number_t volume_serial_number{0};
  volume_label_t volume_label{u'N', u'O', u' ', u'N', u'A', u'M', u'E'};
  // Some BS Value for fs type
  file_system_type_t file_system{0x01};
  na_0_t na_0{0};
  // Will only work on little endian
  signature_word_t signature_word{0x55, 0xAA};
  na_1_t<sector_size> na_1{};
};
template <auto fat_size_in_bytes = 268435456, auto sector_size = 512>
struct boot_sector_32_s{
  jmp_inst_t jmp_inst{0xEB,0x32,0x90};
  oem_name_t oem_name{u'm',u'k',u'f',u's',u'.',u'f',u'a',u't'};
  bios_param_block32_t <fat_size_in_bytes,sector_size>bios_param_block32{};
};
} // namespace v32

#pragma pack(pop)
} // namespace fat
