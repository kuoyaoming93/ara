// Copyright 2020 ETH Zurich and University of Bologna.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Author: Matteo Perotti, ETH Zurich

// Define Matrix dimensions:
// o = i ° f, with i=[MxN], f=[FxF], o=[MxN]
// The filter is a square matrix, and F is odd

// Matrices defined in data.S
extern int64_t i[] __attribute__((
    aligned(4 * NR_LANES))); // [ (M+floor(F/2)) * (N+floor(F/2)) ]
extern int64_t f[] __attribute__((aligned(4 * NR_LANES)));        // [ F*F ]
extern int64_t o[] __attribute__((aligned(4 * NR_LANES)));        // [ M*N ]
extern int64_t golden_o[] __attribute__((aligned(4 * NR_LANES))); // [ M*N ]
// M, N, F defined in data.S
extern int64_t M;
extern int64_t N;
extern int64_t F;

int main() {
  // Measure runtime with a hot cache
  start_timer();
  if (F == 3)
    iconv2d_3x3(o, i, f, M, N, F);
  else if (F == 5)
    iconv2d_5x5(o, i, f, M, N, F);
  else if (F == 7)
    iconv2d_7x7(o, i, f, M, N, F);
  else {
    printf("Error: the filter size is different from 3 or 5 or 7.\n");
    return -1;
  }
  stop_timer();

  int64_t runtime = get_timer();
  float performance = F * F * M * N / (runtime);
  printf("[performance]: %d %f\n", F, performance);

  return 0;
}
