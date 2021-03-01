// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1() {
  VSET(12, e8, m1);
  VLOAD_8(v2, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0);
  VLOAD_8(v3, 0xf0, 0x03, 0xf0, 0xf0, 0x03, 0xf0, 0xf0, 0x03, 0xf0, 0xf0, 0x03, 0xf0);
  asm volatile("vand.vv v1, v2, v3");
  VCMP_U8(1, v1, 0xf0, 0x01, 0xf0, 0xf0, 0x01, 0xf0, 0xf0, 0x01, 0xf0, 0xf0, 0x01, 0xf0);

  VSET(12, e16, m1);
  VLOAD_16(v2, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0);
  VLOAD_16(v3, 0xff00, 0x0003, 0xf0f0, 0xff00, 0x0003, 0xf0f0, 0xff00, 0x0003, 0xf0f0, 0xff00, 0x0003, 0xf0f0);
  asm volatile("vand.vv v1, v2, v3");
  VCMP_U16(2, v1, 0xff00, 0x0001, 0xf0f0, 0xff00, 0x0001, 0xf0f0, 0xff00, 0x0001, 0xf0f0, 0xff00, 0x0001, 0xf0f0);

  VSET(12, e32, m1);
  VLOAD_32(v2, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0);
  VLOAD_32(v3, 0xffff0000, 0x00000003, 0xf0f0f0f0, 0xffff0000, 0x00000003, 0xf0f0f0f0, 0xffff0000, 0x00000003, 0xf0f0f0f0, 0xffff0000, 0x00000003, 0xf0f0f0f0);
  asm volatile("vand.vv v1, v2, v3");
  VCMP_U32(3, v1, 0xffff0000, 0x00000001, 0xf0f0f0f0, 0xffff0000, 0x00000001, 0xf0f0f0f0, 0xffff0000, 0x00000001, 0xf0f0f0f0, 0xffff0000, 0x00000001, 0xf0f0f0f0);

  VSET(12, e64, m1);
  VLOAD_64(v2, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0);
  VLOAD_64(v3, 0xffffffff00000000, 0x0000000000000003, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0x0000000000000003, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0x0000000000000003, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0x0000000000000003, 0xf0f0f0f0f0f0f0f0);
  asm volatile("vand.vv v1, v2, v3");
  VCMP_U64(4, v1, 0xffffffff00000000, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0);
}

void TEST_CASE2() {
  VSET(12, e8, m1);
  VLOAD_8(v2, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0);
  VLOAD_8(v3, 0xf0, 0x03, 0xf0, 0xf0, 0x03, 0xf0, 0xf0, 0x03, 0xf0, 0xf0, 0x03, 0xf0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_8(v1, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef);
  asm volatile("vand.vv v1, v2, v3, v0.t");
  VCMP_U8(5, v1, 0xf0, 0xef, 0xf0, 0xf0, 0xef, 0xf0, 0xf0, 0xef, 0xf0, 0xf0, 0xef, 0xf0);

  VSET(12, e16, m1);
  VLOAD_16(v2, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0);
  VLOAD_16(v3, 0xff00, 0x0003, 0xf0f0, 0xff00, 0x0003, 0xf0f0, 0xff00, 0x0003, 0xf0f0, 0xff00, 0x0003, 0xf0f0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_16(v1, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef);
  asm volatile("vand.vv v1, v2, v3, v0.t");
  VCMP_U16(6, v1, 0xff00, 0xbeef, 0xf0f0, 0xff00, 0xbeef, 0xf0f0, 0xff00, 0xbeef, 0xf0f0, 0xff00, 0xbeef, 0xf0f0);

  VSET(12, e32, m1);
  VLOAD_32(v2, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0);
  VLOAD_32(v3, 0xffff0000, 0x00000003, 0xf0f0f0f0, 0xffff0000, 0x00000003, 0xf0f0f0f0, 0xffff0000, 0x00000003, 0xf0f0f0f0, 0xffff0000, 0x00000003, 0xf0f0f0f0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_32(v1, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef);
  asm volatile("vand.vv v1, v2, v3, v0.t");
  VCMP_U32(7, v1, 0xffff0000, 0xdeadbeef, 0xf0f0f0f0, 0xffff0000, 0xdeadbeef, 0xf0f0f0f0, 0xffff0000, 0xdeadbeef, 0xf0f0f0f0, 0xffff0000, 0xdeadbeef, 0xf0f0f0f0);

  VSET(12, e64, m1);
  VLOAD_64(v2, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0);
  VLOAD_64(v3, 0xffffffff00000000, 0x0000000000000003, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0x0000000000000003, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0x0000000000000003, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0x0000000000000003, 0xf0f0f0f0f0f0f0f0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_64(v1, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef);
  asm volatile("vand.vv v1, v2, v3, v0.t");
  VCMP_U64(8, v1, 0xffffffff00000000, 0xdeadbeefdeadbeef, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0xdeadbeefdeadbeef, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0xdeadbeefdeadbeef, 0xf0f0f0f0f0f0f0f0, 0xffffffff00000000, 0xdeadbeefdeadbeef, 0xf0f0f0f0f0f0f0f0);
}

void TEST_CASE3() {
  const uint64_t scalar = 0x0ff00ff00ff00ff0;

  VSET(12, e8, m1);
  VLOAD_8(v2, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0);
  asm volatile("vand.vx v1, v2, %[A]" :: [A] "r" (scalar));
  VCMP_U8(9, v1, 0xf0, 0x00, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0x00, 0xf0);

  VSET(12, e16, m1);
  VLOAD_16(v2, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0);
  asm volatile("vand.vx v1, v2, %[A]" :: [A] "r" (scalar));
  VCMP_U16(10, v1, 0x0ff0, 0x0000, 0x00f0, 0x0ff0, 0x0000, 0x00f0, 0x0ff0, 0x0000, 0x00f0, 0x0ff0, 0x0000, 0x00f0);

  VSET(12, e32, m1);
  VLOAD_32(v2, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0);
  asm volatile("vand.vx v1, v2, %[A]" :: [A] "r" (scalar));
  VCMP_U32(11, v1, 0x0ff00ff0, 0x00000000, 0x00f000f0, 0x0ff00ff0, 0x00000000, 0x00f000f0, 0x0ff00ff0, 0x00000000, 0x00f000f0, 0x0ff00ff0, 0x00000000, 0x00f000f0);

  VSET(12, e64, m1);
  VLOAD_64(v2, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0);
  asm volatile("vand.vx v1, v2, %[A]" :: [A] "r" (scalar));
  VCMP_U64(12, v1, 0x0ff00ff00ff00ff0, 0x0000000000000000, 0x00f000f000f000f0, 0x0ff00ff00ff00ff0, 0x0000000000000000, 0x00f000f000f000f0, 0x0ff00ff00ff00ff0, 0x0000000000000000, 0x00f000f000f000f0, 0x0ff00ff00ff00ff0, 0x0000000000000000, 0x00f000f000f000f0);
}

void TEST_CASE4() {
  const uint64_t scalar = 0x0ff00ff00ff00ff0;

  VSET(12, e8, m1);
  VLOAD_8(v2, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_8(v1, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef);
  asm volatile("vand.vx v1, v2, %[A], v0.t" :: [A] "r" (scalar));
  VCMP_U8(13, v1, 0xf0, 0xef, 0xf0, 0xf0, 0xef, 0xf0, 0xf0, 0xef, 0xf0, 0xf0, 0xef, 0xf0);

  VSET(12, e16, m1);
  VLOAD_16(v2, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_16(v1, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef);
  asm volatile("vand.vx v1, v2, %[A], v0.t" :: [A] "r" (scalar));
  VCMP_U16(14, v1, 0x0ff0, 0xbeef, 0x00f0, 0x0ff0, 0xbeef, 0x00f0, 0x0ff0, 0xbeef, 0x00f0, 0x0ff0, 0xbeef, 0x00f0);

  VSET(12, e32, m1);
  VLOAD_32(v2, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_32(v1, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef);
  asm volatile("vand.vx v1, v2, %[A], v0.t" :: [A] "r" (scalar));
  VCMP_U32(15, v1, 0x0ff00ff0, 0xdeadbeef, 0x00f000f0, 0x0ff00ff0, 0xdeadbeef, 0x00f000f0, 0x0ff00ff0, 0xdeadbeef, 0x00f000f0, 0x0ff00ff0, 0xdeadbeef, 0x00f000f0);

  VSET(12, e64, m1);
  VLOAD_64(v2, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_64(v1, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef);
  asm volatile("vand.vx v1, v2, %[A], v0.t" :: [A] "r" (scalar));
  VCMP_U64(16, v1, 0x0ff00ff00ff00ff0, 0xdeadbeefdeadbeef, 0x00f000f000f000f0, 0x0ff00ff00ff00ff0, 0xdeadbeefdeadbeef, 0x00f000f000f000f0, 0x0ff00ff00ff00ff0, 0xdeadbeefdeadbeef, 0x00f000f000f000f0, 0x0ff00ff00ff00ff0, 0xdeadbeefdeadbeef, 0x00f000f000f000f0);
}

void TEST_CASE5() {
  VSET(12, e8, m1);
  VLOAD_8(v2, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0);
  asm volatile("vand.vi v1, v2, 15");
  VCMP_U8(17, v1, 0x0f, 0x01, 0x00, 0x0f, 0x01, 0x00, 0x0f, 0x01, 0x00, 0x0f, 0x01, 0x00);

  VSET(12, e16, m1);
  VLOAD_16(v2, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0);
  asm volatile("vand.vi v1, v2, 15");
  VCMP_U16(18, v1, 0x000f, 0x0001, 0x0000, 0x000f, 0x0001, 0x0000, 0x000f, 0x0001, 0x0000, 0x000f, 0x0001, 0x0000);

  VSET(12, e32, m1);
  VLOAD_32(v2, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0);
  asm volatile("vand.vi v1, v2, 15");
  VCMP_U32(19, v1, 0x0000000f, 0x00000001, 0x00000000, 0x0000000f, 0x00000001, 0x00000000, 0x0000000f, 0x00000001, 0x00000000, 0x0000000f, 0x00000001, 0x00000000);

  VSET(12, e64, m1);
  VLOAD_64(v2, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0);
  asm volatile("vand.vi v1, v2, 15");
  VCMP_U64(20, v1, 0x000000000000000f, 0x0000000000000001, 0x0000000000000000, 0x000000000000000f, 0x0000000000000001, 0x0000000000000000, 0x000000000000000f, 0x0000000000000001, 0x0000000000000000, 0x000000000000000f, 0x0000000000000001, 0x0000000000000000);
}

void TEST_CASE6() {
  VSET(12, e8, m1);
  VLOAD_8(v2, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_8(v1, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef);
  asm volatile("vand.vi v1, v2, 15, v0.t");
  VCMP_U8(21, v1, 0x0f, 0xef, 0x00, 0x0f, 0xef, 0x00, 0x0f, 0xef, 0x00, 0x0f, 0xef, 0x00);

  VSET(12, e16, m1);
  VLOAD_16(v2, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0, 0xffff, 0x0001, 0xf0f0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_16(v1, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef);
  asm volatile("vand.vi v1, v2, 15, v0.t");
  VCMP_U16(22, v1, 0x000f, 0xbeef, 0x0000, 0x000f, 0xbeef, 0x0000, 0x000f, 0xbeef, 0x0000, 0x000f, 0xbeef, 0x0000);

  VSET(12, e32, m1);
  VLOAD_32(v2, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0, 0xffffffff, 0x00000001, 0xf0f0f0f0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_32(v1, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef);
  asm volatile("vand.vi v1, v2, 15, v0.t");
  VCMP_U32(23, v1, 0x0000000f, 0xdeadbeef, 0x00000000, 0x0000000f, 0xdeadbeef, 0x00000000, 0x0000000f, 0xdeadbeef, 0x00000000, 0x0000000f, 0xdeadbeef, 0x00000000);

  VSET(12, e64, m1);
  VLOAD_64(v2, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0, 0xffffffffffffffff, 0x0000000000000001, 0xf0f0f0f0f0f0f0f0);
  VLOAD_8(v0, 0x6D, 0x0B);
  VLOAD_64(v1, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef, 0xdeadbeefdeadbeef);
  asm volatile("vand.vi v1, v2, 15, v0.t");
  VCMP_U64(24, v1, 0x000000000000000f, 0xdeadbeefdeadbeef, 0x0000000000000000, 0x000000000000000f, 0xdeadbeefdeadbeef, 0x0000000000000000, 0x000000000000000f, 0xdeadbeefdeadbeef, 0x0000000000000000, 0x000000000000000f, 0xdeadbeefdeadbeef, 0x0000000000000000);
}

int main(void){
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();
  TEST_CASE5();
  TEST_CASE6();

  EXIT_CHECK();
}
