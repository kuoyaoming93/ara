// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1() {
  VSET(3,e32,m1);
  VLOAD_F32(v2,_f(0.1).i,_f(-0.2).i,_f(3.14159265).i);
  VLOAD_F32(v3,_f(0.1).i, _f(0.2).i,_f(3.14159265).i);
  VLOAD_F32(v1,_f(0.7).i,_f(0.9).i,_f(1.124).i);
  __asm__ volatile("vfnmsac.vv v1, v2, v3");
  VEC_CMP_F32(1,v1,_f(0.69).i,_f(0.94).i,_f(-8.74560547).i);
}

// void TEST_CASE2() {
//   VSET(3,e32,m1);
//   VLOAD_F32(v2,_f(0.1).i,_f(-0.2).i,_f(3.14159265).i);
//   VLOAD_F32(v3,_f(0.1).i, _f(0.2).i,_f(3.14159265).i);
//   VLOAD_F32(v1,_f(0.7).i,_f(0.9).i,_f(1.124).i);
//   VLOAD_U32(v0,6,0,0);
//   __asm__ volatile("vfnmsac.vv v1, v2, v3, v0.t");
//   VEC_CMP_F32(2,v1,_f(0.7).i,_f(0.94).i,_f(-8.74560547).i);
// }

void TEST_CASE3() {
  VSET(3,e32,m1);
  VLOAD_F32(v2,_f(0.1).i,_f(-0.2).i,_f(3.14159265).i);
  FLOAD32(f10,_f(1.67).i);
  VLOAD_F32(v1,_f(0.7).i,_f(0.9).i,_f(1.124).i);
  __asm__ volatile("vfnmsac.vf v1, f10, v2");
  VEC_CMP_F32(3,v1,_f(0.533).i,_f(1.234).i,_f(-4.122459726).i);
}

// void TEST_CASE4() {
//   VSET(3,e32,m1);
//   VLOAD_F32(v2,_f(0.1).i,_f(-0.2).i,_f(3.14159265).i);
//   FLOAD32(f10,_f(1.67).i);
//   VLOAD_F32(v1,_f(0.7).i,_f(0.9).i,_f(1.124).i);
//   VLOAD_U32(v0,6,0,0);
//   __asm__ volatile("vfnmsac.vf v1, f10, v2, v0.t");
//   VEC_CMP_F32(4,v1,_f(0.7).i,_f(1.234).i,_f(-4.122459726).i);
// }

int main(void){
  INIT_CHECK();
  enable_vec();
  enable_fp();
  TEST_CASE1();
  TEST_CASE3();
  // TEST_CASE2();
  // TEST_CASE4();
  EXIT_CHECK();
}
