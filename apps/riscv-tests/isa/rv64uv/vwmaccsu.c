// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1() {
  VSET(16, e16, m1);
  VLOAD_16(v6, 0x30dc, 0x7235, 0xd5f6, 0xa008, 0x6e79, 0xa159, 0xa05c, 0x5914, 0xd06f, 0x69c5, 0x9475, 0x5625, 0xa5bd, 0x7be7, 0x823c, 0x5fb2);
  VSET(16, e8, m1);
  VLOAD_8(v2, 0xb6, 0xbb, 0xb6, 0x57, 0xf9, 0x7c, 0xbf, 0x62, 0x1a, 0xeb, 0xa4, 0x34, 0xde, 0x96, 0x80, 0xe6);
  VLOAD_8(v4, 0x26, 0xea, 0xe8, 0x85, 0x2e, 0xf1, 0x46, 0x8f, 0x68, 0x29, 0xbb, 0x9b, 0xec, 0x5c, 0x8e, 0x77);
  asm volatile("vwmaccsu.vv v6, v2, v4");
  VSET(16, e16, m1);
  VCMP_I16(1, v6, 0x25e0, 0x3323, 0x92e6, 0xcd3b, 0x6d37, 0x1615, 0x8e96, 0x8fd2, 0xdaff, 0x6668, 0x5141, 0x75a1, 0x8665, 0x55cf, 0x3b3c, 0x539c);

  VSET(16, e32, m1);
  VLOAD_32(v6, 0xdbc5b23d, 0x86bd7dad, 0xb744b5c2, 0xc32f4a47, 0x237edfc4, 0x5d6e851a, 0xbd3110cd, 0x18c61b57, 0x7ade2943, 0x7e4f5ed6, 0x90e5ba77, 0xce45b744, 0x82d1976e, 0xa88bb4e1, 0x989fbb9a, 0xab29da17);
  VSET(16, e16, m1);
  VLOAD_16(v2, 0x23fb, 0xcee7, 0xa704, 0xc00f, 0xed9f, 0x2cf0, 0x4b53, 0xc0ba, 0x775b, 0x557c, 0x57b7, 0xbb06, 0xf9ba, 0x178f, 0xec73, 0x8240);
  VLOAD_16(v4, 0xad9d, 0x104d, 0xdc56, 0x96af, 0x8c68, 0x1d25, 0x2d70, 0x467a, 0xc27c, 0x96e2, 0x1c85, 0xe8b6, 0xf7e0, 0xd069, 0x0bca, 0x4f36);
  asm volatile("vwmaccsu.vv v6, v2, v4");
  VSET(16, e32, m1);
  VCMP_I32(2, v6, 0xf42c622c, 0x839d2928, 0x6aae411a, 0x9d8c5e88, 0x196a5c5c, 0x628c33ca, 0xca8f9c1d, 0x075acffb, 0xd58aef57, 0xb0b17e4e, 0x9aab508a, 0x8f921d88, 0x7cbe902e, 0xbbb98e88, 0x97b93f58, 0x84411397);

  VSET(16, e64, m1);
  VLOAD_64(v6, 0xf8e162af4fefb46a, 0x8e859cff3b076a9d, 0xa7279ec622e749eb, 0x67bbdace6d6bf1a9, 0xf2090d8d3b00e5b8, 0x9259e92430c5a337, 0x7cc51e4cc8fd46c6, 0xe5c6946a8e9787fd, 0x0d36e747a75534cc, 0x9c1a70c0989504f9, 0xa7b0f15e7b51c000, 0x4566f8ffa299d104, 0xf385b581a4c1c25b, 0xb067f1a7621f9cdd, 0x54ffc96dc442d7b5, 0x3fc18a6aa65ab8d5);
  VSET(16, e32, m1);
  VLOAD_32(v2, 0x189138d0, 0xe2f3f48f, 0x58448029, 0x44298d07, 0x6f6b15cf, 0x13e9cf30, 0x23b6edb8, 0xd532420a, 0xdab302ee, 0xa5e6854e, 0x538f91b0, 0xc5d4db0e, 0xbc6d31b3, 0x754d418c, 0x96198b07, 0xf54f785a);
  VLOAD_32(v4, 0x52d1517d, 0xa592227e, 0xbb122792, 0x531a3046, 0x88193da7, 0x13db3502, 0x64efb3f9, 0x55c57a21, 0x31cd5a79, 0x5c0b4048, 0x899cfb88, 0xfab9de9d, 0x6fa41232, 0x9462cda3, 0x0f8de6ea, 0x8064029f);
  asm volatile("vwmaccsu.vv v6, v2, v4");
  VSET(16, e64, m1);
  VCMP_I64(3, v6, 0x00d3fd4343a241fa, 0x7bbc44d6fa22c6ff, 0xe7a7ead9df60a04d, 0x7ddc4c9a72efd193, 0x2d44ed6d874572c1, 0x93e550a88e8e3197, 0x8ada040c3cea26be, 0xd76f3f99213ccf47, 0x05f53f01db8f434a, 0x7bb552f0a51802e9, 0xd49c03ec9aaeb580, 0x0c6e9b2885384c9a, 0xd60dbf3493400d51, 0xf465e158f7657501, 0x4e90951ee65f361b, 0x3a651986a4cf2cbb);
}

void TEST_CASE2() {
  VSET(16, e16, m1);
  VLOAD_16(v6, 0x30dc, 0x7235, 0xd5f6, 0xa008, 0x6e79, 0xa159, 0xa05c, 0x5914, 0xd06f, 0x69c5, 0x9475, 0x5625, 0xa5bd, 0x7be7, 0x823c, 0x5fb2);
  VSET(16, e8, m1);
  VLOAD_8(v2, 0xb6, 0xbb, 0xb6, 0x57, 0xf9, 0x7c, 0xbf, 0x62, 0x1a, 0xeb, 0xa4, 0x34, 0xde, 0x96, 0x80, 0xe6);
  VLOAD_8(v4, 0x26, 0xea, 0xe8, 0x85, 0x2e, 0xf1, 0x46, 0x8f, 0x68, 0x29, 0xbb, 0x9b, 0xec, 0x5c, 0x8e, 0x77);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vwmaccsu.vv v6, v2, v4, v0.t");
  VSET(16, e16, m1);
  VCMP_I16(4, v6, 0x30dc, 0x3323, 0xd5f6, 0xcd3b, 0x6e79, 0x1615, 0xa05c, 0x8fd2, 0xd06f, 0x6668, 0x9475, 0x75a1, 0xa5bd, 0x55cf, 0x823c, 0x539c);

  VSET(16, e32, m1);
  VLOAD_32(v6, 0xdbc5b23d, 0x86bd7dad, 0xb744b5c2, 0xc32f4a47, 0x237edfc4, 0x5d6e851a, 0xbd3110cd, 0x18c61b57, 0x7ade2943, 0x7e4f5ed6, 0x90e5ba77, 0xce45b744, 0x82d1976e, 0xa88bb4e1, 0x989fbb9a, 0xab29da17);
  VSET(16, e16, m1);
  VLOAD_16(v2, 0x23fb, 0xcee7, 0xa704, 0xc00f, 0xed9f, 0x2cf0, 0x4b53, 0xc0ba, 0x775b, 0x557c, 0x57b7, 0xbb06, 0xf9ba, 0x178f, 0xec73, 0x8240);
  VLOAD_16(v4, 0xad9d, 0x104d, 0xdc56, 0x96af, 0x8c68, 0x1d25, 0x2d70, 0x467a, 0xc27c, 0x96e2, 0x1c85, 0xe8b6, 0xf7e0, 0xd069, 0x0bca, 0x4f36);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vwmaccsu.vv v6, v2, v4, v0.t");
  VSET(16, e32, m1);
  VCMP_I32(5, v6, 0xdbc5b23d, 0x839d2928, 0xb744b5c2, 0x9d8c5e88, 0x237edfc4, 0x628c33ca, 0xbd3110cd, 0x075acffb, 0x7ade2943, 0xb0b17e4e, 0x90e5ba77, 0x8f921d88, 0x82d1976e, 0xbbb98e88, 0x989fbb9a, 0x84411397);

  VSET(16, e64, m1);
  VLOAD_64(v6, 0xf8e162af4fefb46a, 0x8e859cff3b076a9d, 0xa7279ec622e749eb, 0x67bbdace6d6bf1a9, 0xf2090d8d3b00e5b8, 0x9259e92430c5a337, 0x7cc51e4cc8fd46c6, 0xe5c6946a8e9787fd, 0x0d36e747a75534cc, 0x9c1a70c0989504f9, 0xa7b0f15e7b51c000, 0x4566f8ffa299d104, 0xf385b581a4c1c25b, 0xb067f1a7621f9cdd, 0x54ffc96dc442d7b5, 0x3fc18a6aa65ab8d5);
  VSET(16, e32, m1);
  VLOAD_32(v2, 0x189138d0, 0xe2f3f48f, 0x58448029, 0x44298d07, 0x6f6b15cf, 0x13e9cf30, 0x23b6edb8, 0xd532420a, 0xdab302ee, 0xa5e6854e, 0x538f91b0, 0xc5d4db0e, 0xbc6d31b3, 0x754d418c, 0x96198b07, 0xf54f785a);
  VLOAD_32(v4, 0x52d1517d, 0xa592227e, 0xbb122792, 0x531a3046, 0x88193da7, 0x13db3502, 0x64efb3f9, 0x55c57a21, 0x31cd5a79, 0x5c0b4048, 0x899cfb88, 0xfab9de9d, 0x6fa41232, 0x9462cda3, 0x0f8de6ea, 0x8064029f);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vwmaccsu.vv v6, v2, v4, v0.t");
  VSET(16, e64, m1);
  VCMP_I64(6, v6, 0xf8e162af4fefb46a, 0x7bbc44d6fa22c6ff, 0xa7279ec622e749eb, 0x7ddc4c9a72efd193, 0xf2090d8d3b00e5b8, 0x93e550a88e8e3197, 0x7cc51e4cc8fd46c6, 0xd76f3f99213ccf47, 0x0d36e747a75534cc, 0x7bb552f0a51802e9, 0xa7b0f15e7b51c000, 0x0c6e9b2885384c9a, 0xf385b581a4c1c25b, 0xf465e158f7657501, 0x54ffc96dc442d7b5, 0x3a651986a4cf2cbb);
}

void TEST_CASE3() {
  VSET(16, e16, m1);
  VLOAD_16(v6, 0xadd2, 0x2112, 0xbbc6, 0xd113, 0xc6f7, 0xbd07, 0xfd9a, 0x0c0e, 0xe110, 0xe81b, 0xb432, 0x5c2c, 0x4da9, 0x8c48, 0x6f94, 0x6250);
  VSET(16, e8, m1);
  int64_t scalar = 5;
  VLOAD_8(v4, 0xfe, 0xd1, 0xc2, 0x3b, 0x79, 0x2f, 0xf5, 0xe8, 0x7f, 0x4b, 0x64, 0x57, 0x2b, 0x4f, 0x4e, 0xda);
  asm volatile("vwmaccsu.vx v6, %[A], v4" :: [A] "r" (scalar));
  VSET(16, e16, m1);
  VCMP_I16(7, v6, 0xb2c8, 0x2527, 0xbf90, 0xd23a, 0xc954, 0xbdf2, 0x0263, 0x1096, 0xe38b, 0xe992, 0xb626, 0x5ddf, 0x4e80, 0x8dd3, 0x711a, 0x6692);

  VSET(16, e32, m1);
  VLOAD_32(v6, 0x39d3ea89, 0x451d8e1a, 0x83edb2d7, 0xc1919ab3, 0x243c3d4d, 0xd4745be8, 0x50a58cbe, 0x53b75e9f, 0x2a648b62, 0xd74ce1cf, 0xa2c6a2e7, 0xc30eadb0, 0x7a908fb9, 0xd4455b56, 0x48109ee2, 0x2f5b537a);
  VSET(16, e16, m1);
  scalar = -5383;
  VLOAD_16(v4, 0x29f8, 0x6958, 0x6635, 0x03a0, 0x07bc, 0x4881, 0x7d4e, 0x37e3, 0x8370, 0x405f, 0x1f0d, 0x1252, 0xacf1, 0x06ee, 0x790d, 0x73af);
  asm volatile("vwmaccsu.vx v6, %[A], v4" :: [A] "r" (scalar));
  VSET(16, e32, m1);
  VCMP_I32(8, v6, 0x36616cc1, 0x3c7674b2, 0x7b888e64, 0xc1456153, 0x23999b29, 0xce7fcb61, 0x465ab99c, 0x4f20386a, 0x1f98c352, 0xd2035436, 0xa039b88c, 0xc18d7372, 0x6c5c1022, 0xd3b3a4d4, 0x3e1f3e87, 0x25daceb1);

  VSET(16, e64, m1);
  VLOAD_64(v6, 0xd860771ff910e8a1, 0xd8de9ddf3be66e90, 0xe55e25348ff4c406, 0x6ee24d9ebeda1c54, 0x78437fc8299017d1, 0x46a2833ed69dec1d, 0x0331761dcc2485b7, 0x99c00b7ecbecb5bf, 0xd68d230a95510605, 0x0e82f981980d47c8, 0x7bb0e1dd5f273626, 0x044cc7c24be55121, 0x341b063e01c35796, 0xb77a96fdf1826215, 0xdcbd3fe115470433, 0xc2797417b552325b);
  VSET(16, e32, m1);
  scalar = 6474219;
  VLOAD_32(v4, 0x53046c2d, 0x3b0c65ed, 0x6565f981, 0xaa4c1d70, 0x0a18c71e, 0xbc91ff46, 0xa52c32d1, 0x73cca3fc, 0xb2a7e5d2, 0x1939af0a, 0xe4fdb1f5, 0x783f5c5d, 0x3514c875, 0xce346d04, 0x68047428, 0x72ca548f);
  asm volatile("vwmaccsu.vx v6, %[A], v4" :: [A] "r" (scalar));
  VSET(16, e64, m1);
  VCMP_I64(9, v6, 0xd880804c10498af0, 0xd8f567313109141f, 0xe585463838d91671, 0x6f2405141ab61224, 0x7847653b1c216e5b, 0x46eb47de4add375f, 0x03713350939f4492, 0x99ecbb2b8c001a13, 0xd6d2143a6346dfcb, 0x0e8cb57c0c43cff6, 0x7c093f98e48cef0d, 0x047b2edbc92e1f80, 0x342f8210ca0537fd, 0xb7ca29b420c298c1, 0xdce563a087e10ceb, 0xc2a5c016503018a0);
}

void TEST_CASE4() {
  VSET(16, e16, m1);
  VLOAD_16(v6, 0xadd2, 0x2112, 0xbbc6, 0xd113, 0xc6f7, 0xbd07, 0xfd9a, 0x0c0e, 0xe110, 0xe81b, 0xb432, 0x5c2c, 0x4da9, 0x8c48, 0x6f94, 0x6250);
  VSET(16, e8, m1);
  int64_t scalar = 5;
  VLOAD_8(v4, 0xfe, 0xd1, 0xc2, 0x3b, 0x79, 0x2f, 0xf5, 0xe8, 0x7f, 0x4b, 0x64, 0x57, 0x2b, 0x4f, 0x4e, 0xda);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vwmaccsu.vx v6, %[A], v4, v0.t" :: [A] "r" (scalar));
  VSET(16, e16, m1);
  VCMP_I16(10, v6, 0xadd2, 0x2527, 0xbbc6, 0xd23a, 0xc6f7, 0xbdf2, 0xfd9a, 0x1096, 0xe110, 0xe992, 0xb432, 0x5ddf, 0x4da9, 0x8dd3, 0x6f94, 0x6692);

  VSET(16, e32, m1);
  VLOAD_32(v6, 0x39d3ea89, 0x451d8e1a, 0x83edb2d7, 0xc1919ab3, 0x243c3d4d, 0xd4745be8, 0x50a58cbe, 0x53b75e9f, 0x2a648b62, 0xd74ce1cf, 0xa2c6a2e7, 0xc30eadb0, 0x7a908fb9, 0xd4455b56, 0x48109ee2, 0x2f5b537a);
  VSET(16, e16, m1);
  scalar = -5383;
  VLOAD_16(v4, 0x29f8, 0x6958, 0x6635, 0x03a0, 0x07bc, 0x4881, 0x7d4e, 0x37e3, 0x8370, 0x405f, 0x1f0d, 0x1252, 0xacf1, 0x06ee, 0x790d, 0x73af);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vwmaccsu.vx v6, %[A], v4, v0.t" :: [A] "r" (scalar));
  VSET(16, e32, m1);
  VCMP_I32(11, v6, 0x39d3ea89, 0x3c7674b2, 0x83edb2d7, 0xc1456153, 0x243c3d4d, 0xce7fcb61, 0x50a58cbe, 0x4f20386a, 0x2a648b62, 0xd2035436, 0xa2c6a2e7, 0xc18d7372, 0x7a908fb9, 0xd3b3a4d4, 0x48109ee2, 0x25daceb1);

  VSET(16, e64, m1);
  VLOAD_64(v6, 0xd860771ff910e8a1, 0xd8de9ddf3be66e90, 0xe55e25348ff4c406, 0x6ee24d9ebeda1c54, 0x78437fc8299017d1, 0x46a2833ed69dec1d, 0x0331761dcc2485b7, 0x99c00b7ecbecb5bf, 0xd68d230a95510605, 0x0e82f981980d47c8, 0x7bb0e1dd5f273626, 0x044cc7c24be55121, 0x341b063e01c35796, 0xb77a96fdf1826215, 0xdcbd3fe115470433, 0xc2797417b552325b);
  VSET(16, e32, m1);
  scalar = 6474219;
  VLOAD_32(v4, 0x53046c2d, 0x3b0c65ed, 0x6565f981, 0xaa4c1d70, 0x0a18c71e, 0xbc91ff46, 0xa52c32d1, 0x73cca3fc, 0xb2a7e5d2, 0x1939af0a, 0xe4fdb1f5, 0x783f5c5d, 0x3514c875, 0xce346d04, 0x68047428, 0x72ca548f);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vwmaccsu.vx v6, %[A], v4, v0.t" :: [A] "r" (scalar));
  VSET(16, e64, m1);
  VCMP_I64(12, v6, 0xd860771ff910e8a1, 0xd8f567313109141f, 0xe55e25348ff4c406, 0x6f2405141ab61224, 0x78437fc8299017d1, 0x46eb47de4add375f, 0x0331761dcc2485b7, 0x99ecbb2b8c001a13, 0xd68d230a95510605, 0x0e8cb57c0c43cff6, 0x7bb0e1dd5f273626, 0x047b2edbc92e1f80, 0x341b063e01c35796, 0xb7ca29b420c298c1, 0xdcbd3fe115470433, 0xc2a5c016503018a0);
}

int main(void){
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();

  EXIT_CHECK();
}
