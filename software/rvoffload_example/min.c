/* Copy from cmsis min */

#include <stdio.h>
#include <stdint.h>

#define MAX_BLOCKSIZE 32

float src_buf_f32[MAX_BLOCKSIZE] = {
  -0.4325648115282207, -1.6655843782380970, 0.1253323064748307,  0.2876764203585489,  -1.1464713506814637,
  1.1909154656429988,  1.1891642016521031,  -0.0376332765933176, 0.3272923614086541,  0.1746391428209245,
  -0.1867085776814394, 0.7257905482933027,  -0.5883165430141887, 2.1831858181971011,  -0.1363958830865957,
  0.1139313135208096,  1.0667682113591888,  0.0592814605236053,  -0.0956484054836690, -0.8323494636500225,
  0.2944108163926404,  -1.3361818579378040, 0.7143245518189522,  1.6235620644462707,  -0.6917757017022868,
  0.8579966728282626,  1.2540014216025324,  -1.5937295764474768, -1.4409644319010200, 0.5711476236581780,
  -0.3998855777153632, -8.6899973754643451
};

float result_f32_gold;
uint32_t result_index_gold = 0;

void riscv_min_f32_gold(float *pSrc, uint32_t blockSize, float *pResult, uint32_t *pIndex)
{
  float minVal1, out; /* Temporary variables to store the output value. */
  uint32_t blkCnt, outIndex; /* loop counter */

  /* Initialise the index value to zero. */
  outIndex = 0u;
  /* Load first input value that act as reference value for comparision */
  out = *pSrc++;

  blkCnt = (blockSize - 1u);
  while (blkCnt > 0) {
    /* Initialize minVal to the next consecutive values one by one */
    minVal1 = *pSrc++;

    /* compare for the minimum value */
    if (out > minVal1) {
      /* Update the minimum value and it's index */
      out = minVal1;
      outIndex = blockSize - blkCnt;
    }

    blkCnt--;
  }

  /* Store the minimum value and it's index into destination pointers */
  *pResult = out;
  *pIndex = outIndex;
}

int main() {
  riscv_min_f32_gold(src_buf_f32, MAX_BLOCKSIZE, &result_f32_gold, &result_index_gold);
  return (int)result_f32_gold;
}
