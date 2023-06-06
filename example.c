// #include "blake3.h"
// #include <errno.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

// int main(void) {
//   // Initialize the hasher.
//   blake3_hasher hasher;
//   blake3_hasher_init(&hasher);
//   // i love you
//   unsigned char buf[10] = {105,32,108,111,118,101,32,121,111,117};
//   blake3_hasher_update(&hasher, buf, 10);
//   // Finalize the hash. BLAKE3_OUT_LEN is the default output length, 32 bytes.
//   uint8_t output[BLAKE3_OUT_LEN];
//   blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);

//   // Print the hash as hexadecimal.
//   // 955f029a3a4e26f64e607c076d0382f1122de1852be1f8083a14be942b37bd2a
//   for (size_t i = 0; i < BLAKE3_OUT_LEN; i++) {
//     printf("%02x", output[i]);
//   }
//   printf("\n");
//   return 0;
// }

#include "blake3.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BYTES 1024

unsigned char hex2int(char c)
{
  if (c >= '0' && c <= '9')
  {
    return c - '0';
  }
  else
  {
    return 10 + c - 'a';
  }
}

// 0000000007ffffffffffffffffffffffffffffffffffffffffffffffffffffff  set target
// 00000000049ee5699ee1f5b8316e0ddc6fcddebc90b78d50011f325743859e59  hash
int main(void)
{
  // char hex_str[]"00a016fae14f0010
  // 0000000000000000000000000000000000000000000000005015770d00000000
  // 00a016fae165001f
  // 00000000000000000000000000000000000000000000000036aa311e00000000
  // char hex_str[] = "00a016fae165001fb8f200000000000000000005b9ff55383a79235081f821a3eef515606b4c858b5993125d996dcff83e3cbeacc912b21fa6257a0acb78ffed5e7b75c8a60dd238bc258f48be74f981775dcc8308642d7483f32d6b488b6057f2d807e508828458059649cc000000000000007d8fa67a44e05a72fce712d0c16e77d386cd5804a6996f76edd0c16b7a8801000000000000000000000000000000000000000000000000000036aa311e00000000";
  // char hex_str[] = "00a016fae14f0010b7f200000000000000000070a9772a0dcf2abafc3ec43697b8639dc9802543db11ed7ad627509b5e44de3f4f101cc052e053a8bc87ac22051059787d177aa9b7891cd05ffb857ebd06b960fea6e61c57ed36ab4084e33b2cdbd8484db6b55b2143b6a260000000000000007d5fa49afe59db618cc9c7f1902f10e6d6d31f591a69e5485536526a7a880100000000000000000000000000000000000000000000000000005015770d00000000";

  // 000000000000000000000000000000000000000000000000705bcf5900000000
  // 00a2ec7dec9c0030
  // 00000000000000000000000000000000000000000000000063aaa22c00000000
  // 00a2ec7dec9d0059
  // 0000000001ffffffffffffffffffffffffffffffffffffffffffffffffffffff  set target
  // 00000000007f56b9979d5c478c83829a91b6a046e8ed640e6c8a68eed18e6aba  hash1
  // 00000000007f56b9979d5c478c83829a91b6a046e8ed640e6c8a68eed18e6aba  hash2
  // char randomness[] = "00a2ec7dec9d0059";
  // char graffiti[] = "00000000000000000000000000000000000000000000000063aaa22c00000000";
  // char randomness[] = "00a2ec7dec9c0030";
  // char graffiti[] = "000000000000000000000000000000000000000000000000705bcf5900000000";
  // char hex_str[] = "0000000000000000d7030100000000000000005c7701ff2824b52ebfa00997fbecca23ee921690e078ce2491a9bbb3411fb62ab302931292a2908a1807c34b03f48ef5a91821a6488374a128765a3078a9c0898c1a55290decfc67e7cd14e44f1031df99fec2dc8772aa21bd0000000000000063331fa6c69965e3d4b991a7e5e33cbc3fe7a670d30ed073b438a59489880100000000000000000000000000000000000000000000000000000000000000000000";
  // // char hex_str[] = "00a2ec7dec9c0030d7030100000000000000005c7701ff2824b52ebfa00997fbecca23ee921690e078ce2491a9bbb3411fb62ab302931292a2908a1807c34b03f48ef5a91821a6488374a128765a3078a9c0898c1a55290decfc67e7cd14e44f1031df99fec2dc8772aa21bd0000000000000063331fa6c69965e3d4b991a7e5e33cbc3fe7a670d30ed073b438a5948988010000000000000000000000000000000000000000000000000000705bcf5900000000";
  char randomness[] = "00a0a575c7890037";
  char graffiti[] = "00000000000000000000000000000000000000000000000079251f2f00000000";
  char hex_str[] = "0000000000000000890a01000000000000000028cec3d0b55e055db653e40e77f84734d3d24ca78260af5d2581049d3dcb99466644ffb142a0fdebda566d32c2bcbc8116089400d26ee090122ea5d6e8a604bf6e1f4e9e97b8f69802f987c6a93e96bb931120a494a7dacb90000000000000006b425eb14a0f48f9ffed2730723140fce74f07d7f50686a783c96dc08f880100000000000000000000000000000000000000000000000000000000000000000000";

  for (int i = 0; i < strlen(randomness); i++)
  {
    hex_str[i] = randomness[i];
  }
  for (int i = 0; i < strlen(graffiti); i++)
  {
    hex_str[strlen(hex_str) - strlen(graffiti) + i] = graffiti[i];
  }
  printf("%s\n", hex_str);
  unsigned char bytes[MAX_BYTES];
  memset(bytes, 0, MAX_BYTES);

  int byte_len = strlen(hex_str) / 2;

  for (int i = 0; i < byte_len; i++)
  {
    // printf("%u ", hex2int(hex_str[2*i])<<4 + hex2int(hex_str[2*i]));
    // printf("%u %u ", hex2int(hex_str[2*i]) << 4, hex2int(hex_str[2*i+1]));
    bytes[i] = (hex2int(hex_str[2 * i]) << 4) ^ (hex2int(hex_str[2 * i + 1]));
    // sscanf(hex_str + 2 * i, "%2hhx", &hex_str[i]);
    printf("%02x", bytes[i]);
  }
  printf("\n");
  // bytes[180] = '\0'
  // for (int i = 0; i < sizeof(bytes); ++i)
  // {
  //   printf("%u ", bytes[i]);
  // }

  // Initialize the hasher.
  blake3_hasher hasher;
  blake3_hasher_init(&hasher);
  blake3_hasher_update(&hasher, bytes, 180);
  uint8_t output[BLAKE3_OUT_LEN];
  blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);
  // // i love you
  // unsigned char buf[10] = {105, 32, 108, 111, 118, 101, 32, 121, 111, 117};
  // blake3_hasher_update(&hasher, bytes, 180);
  // Finalize the hash. BLAKE3_OUT_LEN is the default output length, 32 bytes.
  for (size_t i = 0; i < BLAKE3_OUT_LEN; i++)
  {
    printf("%02x", output[i]);
  }
  printf("\n");
  return 0;

  // Print the hash as hexadecimal.
  // 955f029a3a4e26f64e607c076d0382f1122de1852be1f8083a14be942b37bd2a
  // for (size_t i = 0; i < BLAKE3_OUT_LEN; i++)
  // {
  //   printf("%02x", output[i]);
  // }
  // printf("\n");
  // return 0;
}

// 3140fce74f07d7f50686a783c96dc08f8801000000000000000000000000000000000000000000000000000079251f2f00000000000000000000000000000000
// 3140fce74f07d7f50686a783c96dc08f8801000000000000000000000000000000000000000000000000000079251f2f00000000