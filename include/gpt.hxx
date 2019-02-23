// Standards and definitions for gpt
// can be found here:
// https://uefi.org/sites/default/files/resources/UEFI%20Spec%202_7_A%20Sept%206.pdf
constexpr auto GUID_SIZE = 16;
constexpr auto LEGACY_MBR_LEGACY_SIZE = 512;
constexpr auto EFIPART = 0x5452415020494645;
constexpr auto UEFI_OS_TYPE = 0xEF;
constexpr auto PARTITION_NAME_SIZE = 72;

using guid_t = std::uint8_t[GUID_SIZE];

#pragma pack(push, 1)
struct legacy_primary_mbr_s {
  const std::uint8_t boot_indicator{0};
  const std::uint8_t starting_chs[3] = {0x02, 0x00, 0x00};
  const std::uint8_t os_type{0xEF};
  const std::uint8_t ending_chs[3] = {0xFF, 0xFF, 0xFF};
  const std::uint32_t starting_lba{1};
  const std::uint32_t size_in_lba{0xFFFFFFFF};
};

struct {
  const std::uint8_t unused[446] = {0};
  const legacy_primary_mbr_s primary_mbr{};
  const std::uint8_t partition_record[48] = {0};
  const std::uint16_t signature{0xAA55};
} legacy_lba_0;

struct attribute_s {
  const std::uint8_t required_partition {1} : 0;
  const std::uint8_t required_partition {0} : 1;
  const std::uint8_t required_partition {0} : 2;
  const std::uint8_t required_partition {0} : 3;
  const std::uint8_t zero[7];
};

template <auto size_of_partion_entry>
struct lba_partition_entry_s {
  const guid_t partition_type_guid{};
  const guid_t unique_partition_guid{};
  const std::uint64_t starting_lba{};
  const std::uint64_t ending_lba{};
  const std::uint64_t attributes{};
  const char partition_name[PARTITION_NAME_SIZE] = {0};
  const std::uint8_t reserved[size_of_partition_entry - 128] = {0};
};

template <int block_size, auto last_usable = 2ull> struct gpt_primary_header_s {
  const std::uint64_t signature{EFIPART};
  const std::uint32_t revision{0x00010000};
  const std::uint32_t header_size;
  const std::uint32_t
      crc32; // set this field to zero, then compute crc on header size
  const std::uint32_t reserved_0{0};
  const std::uint64_t my_lba{1};
  const std::uint64_t alternate_lba{last_usable};
  const std::uint64_t first_usable_lba{1};
  const std::uint64_t last_usable_lba{last_usable};
  const guid_t guid;
  const lba_partition_entry_s *lba_partition_entry;
  const std::uint32_t number_of_partition_entries;
  const std::uint32_t size_of_partition_entry;
  const std::uint32_t partition_entry_array_crc32;
  const std::uint32_t reserved_1[block_size - 92] = {0};
};
#pragma pack(pop)

namespace gpt {};
