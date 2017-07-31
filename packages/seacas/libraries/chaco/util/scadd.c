/*
 * Copyright (c) 2005 National Technology & Engineering Solutions
 * of Sandia, LLC (NTESS).  Under the terms of Contract DE-NA0003525 with
 * NTESS, the U.S. Government retains certain rights in this software.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 *     * Neither the name of NTESS nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* Scaled add - fills double vec1 with vec1 + alpha*vec2 over range*/
void scadd(double *vec1, int beg, int end, double fac, double *vec2)
{
  int i;

  vec1 = vec1 + beg;
  vec2 = vec2 + beg;
  for (i = end - beg + 1; i; i--) {
    (*vec1++) += fac * (*vec2++);
  }
}

/* Scaled add - fills float vec1 with vec1 + alpha*vec2 over range*/
void scadd_float(float *vec1, int beg, int end, float fac, float *vec2)
{
  int i;

  vec1 = vec1 + beg;
  vec2 = vec2 + beg;
  for (i = end - beg + 1; i; i--) {
    (*vec1++) += fac * (*vec2++);
  }
}

/* Scaled add - fills double vec1 with vec1 + alpha*vec2 where vec2 is float */
void scadd_mixed(double *vec1, int beg, int end, double fac, float *vec2)
{
  int i;

  vec1 = vec1 + beg;
  vec2 = vec2 + beg;
  for (i = end - beg + 1; i; i--) {
    (*vec1++) += fac * (*vec2++);
  }
}
