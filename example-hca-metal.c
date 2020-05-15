/* Copyright 2020 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <metal/io.h>
#include <metal/machine/platform.h>
#include <metal/cpu.h>

#include <api/scl_api.h>
#include <api/scl_hca.h>

#define UNIT32_BE(data, k)      ( (*(data + k) << 24) + (*(data + k + 1) << 16) + (*(data + k + 2) << 8) + (*(data + k + 3)) )

// Key 2b7e151628aed2a6abf7158809cf4f3c
uint64_t key128[4]  = {
    0,
    0,
    0xabf7158809cf4f3c,
    0x2b7e151628aed2a6
};

// Key 2b7e151628aed2a6abf7158809cf4f3c
uint8_t key8[32]  __attribute__ ((aligned (8))) = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3c, 0x4f, 0xcf, 0x09, 0x88, 0x15, 0xf7, 0xab,
    0xa6, 0xd2, 0xae, 0x28, 0x16, 0x15, 0x7e, 0x2b
};

uint64_t key128_2[4] = {
    0,
    0,
    0x08090a0b0c0d0e0f,
    0x0001020304050607
};

uint64_t NIST_key128_GCM[4] = {
    0,
    0,
    0x87ecc760bd8ec184,
    0x48b7f337cdf92526
};

uint64_t NIST_IV_GCM[2] = {
    0x3c3e05b200000000,
    0x3e894ebb16ce82a5
};

uint64_t NIST_AAD_GCM[6] = {
    0xa96eb5e132042405,
    0x7d924cfd37b3d046,
    0xeb41f25827574649,
    0xc8731e06509787bb,
    0x4c584bb007312234,
    0x5e884d69871f7763
};

uint64_t NIST_DATA_GCM[4] = {
    0xc39c2eb9acfabc0d,
    0xbb2bac67a4709430,
    0x57997d548a8f0603,
    0x456c80d30aa1734e
};

uint64_t NIST_DATA_GCM_expected[4] = {
    0x7e9baf1ce7df97d1,
    0xd263228b8ce051f6,
    0x5130c7d13c3ab2e7,
    0x0cd5f3bc97236205
};

uint64_t NIST_TAG_GCM_expected[2] = {
    0x6d026d7d2ed1aa9c,
    0x71446737ca1fa92e
};

uint64_t NIST_key128_CCM[4] = {
    0,
    0,
    0x85d6e2b77ec3d4f2,
    0x35b403a152120970
};

uint64_t NIST_IV_CCM[2] = {
    0xc347a293aa000000,
    0xdaa423bf9256c3fc
};

uint64_t NIST_AAD_CCM[4] = {
    0x1e479e1a51182bb0,
    0xd3c0ed74e5f25e4c,
    0x0,
    0x18698ec267269149
};

uint64_t NIST_DATA_CCM[4] = {
    0x0909a3b8c0029b62,
    0x7dd7396db6613eb8,
    0x0,
    0x4912aabedda0659b
};

uint64_t NIST_DATA_CCM_expected[4] = {
    0x22502ed6f4861af7,
    0x5b00cf8a66baa7fe,
    0x0000000000000000,
    0x1fa64b550d643f95
};

uint64_t NIST_TAG_CCM_expected[2] = {
    0x0604b58d92dacd3f,
    0xeee82c19ecba3428
};

uint64_t plaintext_le_NIST[2] = {
    0xe93d7e117393172a,
    0x6bc1bee22e409f96
};

uint64_t plaintext_le[2] = {
    0x8899aabbccddeeff,
    0x0011223344556677
};

uint8_t plaintext_8_be[16] __attribute__ ((aligned (8))) = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
};

// 69c4e0d86a7b0430d8cdb78070b4c55a
uint64_t ciphertext_le_expected[2] = {
    0xd8cdb78070b4c55a,
    0x69c4e0d86a7b0430
};

// IV: f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff
uint64_t F51_IV[2] = {
    0xf8f9fafbfcfdfeff,
    0xf0f1f2f3f4f5f6f7,
};

// 6bc1bee22e409f96e93d7e117393172a ae2d8a571e03ac9c9eb76fac45af8e51 30c81c46a35ce411e5fbc1191a0a52ef
uint64_t F51_plaintext_le[6] = {
    0xe93d7e117393172a,
    0x6bc1bee22e409f96,
    0x9eb76fac45af8e51,
    0xae2d8a571e03ac9c,
    0xe5fbc1191a0a52ef,
    0x30c81c46a35ce411
};

// 874d6191b620e3261bef6864990db6ce 9806f66b7970fdff8617187bb9fffdff 5ae4df3edbd5d35e5b4f09020db03eab
uint64_t F51_ciphertext_le_expected[6] = {
    0x1bef6864990db6ce,
    0x874d6191b620e326,
    0x8617187bb9fffdff,
    0x9806f66b7970fdff,
    0x5b4f09020db03eab,
    0x5ae4df3edbd5d35e
};

uint64_t MsgL24B512[8] = {
    0x6162638000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000018
};

uint64_t SHA256_expected[4] = {
    0xb410ff61f20015ad,
    0xb00361A396177a9c,
    0x414140de5dae2223,
    0xba7816bf8f01cfea
};

uint64_t SHA224_expected[4] = {
    0xbda0b3f7e36c9da7,
    0xbda255b32aadbce4,
    0x3405d8228642a477,
    0x0000000023097d22   
};

uint64_t MsgL24B1024[16] = {
    0x6162638000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000018
};

#define CCM_TQ(t, q)     (t + (q <<4))

#if METAL_SIFIVE_HCA_VERSION >= HCA_VERSION(0,5,0)
metal_scl_t metal_sifive_scl = {
# if defined(HCA_HAS_AES)        
    .aes_func = {
        .setkey = scl_hca_aes_setkey,
        .setiv  = scl_hca_aes_setiv,
        .cipher = scl_hca_aes_cipher,
#  if defined(HCA_HAS_AESMAC)
        .auth = scl_hca_aes_auth
#  else
        .auth = default_aes_auth
#  endif
    },
# else
    .aes_func = {
        .setkey = default_aes_setkey,
        .setiv  = default_aes_setiv,
        .cipher = default_aes_cipher,
        .auth = default_aes_auth
    },
# endif
# if defined(HCA_HAS_SHA)
    .hash_func = {
        .sha = scl_hca_sha
    },
# else
    .hash_func = {
        .sha = default_sha
    },
# endif
# if defined(HCA_HAS_TRNG)
    .trng_func = {
#  if defined(HCA_BYPASS_TRNG)
        .init = default_trng_init,
        .get_data = default_trng_getdata
#  else
        .init = scl_hca_trng_init,
        .get_data = scl_hca_trng_getdata
#  endif
    },
# else
    .trng_func = {
        .init = default_trng_init,
        .get_data = default_trng_getdata
    },
# endif
    .hca_base = METAL_SIFIVE_HCA_0_BASE_ADDRESS
};
#else
metal_scl_t metal_sifive_scl = {
    .aes_func = {
        .setkey = default_aes_setkey,
        .setiv  = default_aes_setiv,
        .cipher = default_aes_cipher,
        .auth = default_aes_auth
    },
    .hash_func = {
        .sha = default_sha
    },
    .trng_func = {
        .init = default_trng_init,
        .get_data = default_trng_getdata
    },
    .hca_base = 0
};
#endif



/*
 * Main
 */
int main(int argc, char *argv[]) {
    uint32_t val;
    uint64_t oldcount, cyclecount;
    uint64_t tmp[8] = {0};
    uint8_t tmp8[64] = {0};
    uint64_t tag[2] = {0};
    uint64_t *ptr64;

	struct metal_cpu *cpu;
	cpu = metal_cpu_get(metal_cpu_get_current_hartid());

#if __riscv_xlen == 32
    uint32_t    *data;
#endif
#if __riscv_xlen == 64
    printf("HCA test arch=64!\n");
#elif __riscv_xlen == 32
    printf("HCA test arch=32!\n");
#endif
#if __riscv_xlen == 64
    printf("HCA base@ = 0x%016lX\n",metal_sifive_scl.hca_base);
#elif __riscv_xlen == 32
    printf("HCA base@ = 0x%08lX\n",metal_sifive_scl.hca_base);
#endif

    printf("AES - ECB\n");
    oldcount = metal_cpu_get_timer(cpu);
    if (SCL_OK == metal_sifive_scl.aes_func.setkey(&metal_sifive_scl, SCL_AES_KEY128, key128_2))
    {
        if (SCL_OK == metal_sifive_scl.aes_func.cipher(&metal_sifive_scl, SCL_AES_ECB, SCL_ENCRYPT, SCL_LITTLE_ENDIAN_MODE, 1, (uint8_t *)plaintext_le, (uint8_t *)tmp))
        {
            cyclecount = metal_cpu_get_timer(cpu)-oldcount;
            
            // Check returned value
            if ( (tmp[0] != ciphertext_le_expected[0]) || (tmp[1] != ciphertext_le_expected[1]) )
            {
                printf("AES - ECB Wrong value returned\n");
                return -1;
            }

#if __riscv_xlen == 64
            printf("0x%016lX 0x%016lX\n", *(tmp + 1), *tmp);
#elif __riscv_xlen == 32
            data = (uint32_t *)tmp;
            printf("0x%08lX%08lX 0x%08lX%08lX\n",*(data + 3), *(data + 2), *(data + 1), *data);
#endif
            printf("cyc: %u\n", (unsigned int)cyclecount);
        } 
        else
        {
            printf("AES - ECB Error\n");
        }
    }
    else 
    {
        printf("AES - setkey Error\n");
    }

    memset(tmp8,0,64*sizeof(uint8_t));
    printf("AES - ECB \n");
    oldcount = metal_cpu_get_timer(cpu);
    if (SCL_OK == metal_sifive_scl.aes_func.setkey(&metal_sifive_scl, SCL_AES_KEY128, key128_2))
    {
        if (SCL_OK == metal_sifive_scl.aes_func.cipher(&metal_sifive_scl, SCL_AES_ECB, SCL_ENCRYPT, SCL_BIG_ENDIAN_MODE, 1, plaintext_8_be, tmp8))
        {
            cyclecount = metal_cpu_get_timer(cpu)-oldcount;

            // Check returned value
            ptr64 = (uint64_t *)tmp;
            if ( (ptr64[0] != ciphertext_le_expected[0]) || (ptr64[1] != ciphertext_le_expected[1]) )
            {
                printf("AES - ECB Wrong value returned\n");
                return -1;
            }

            printf("0x%08X%08X 0x%08X%08X\n",UNIT32_BE(tmp8,0), UNIT32_BE(tmp8,4), UNIT32_BE(tmp8,8), UNIT32_BE(tmp8,12));
            printf("cyc: %u\n", (unsigned int)cyclecount);
        }
        else
        {
            printf("AES - ECB Error\n");
        }
    }
    else
    {
        printf("AES - setkey Error\n");
    }

    memset(tmp,0,8*sizeof(uint64_t));
    printf("AES - CTR\n");
    oldcount = metal_cpu_get_timer(cpu);
    if (SCL_OK == metal_sifive_scl.aes_func.setkey(&metal_sifive_scl, SCL_AES_KEY128, (uint64_t *)key8))
    {
        if (SCL_OK == metal_sifive_scl.aes_func.setiv(&metal_sifive_scl, F51_IV))
        {
            if (SCL_OK == metal_sifive_scl.aes_func.cipher(&metal_sifive_scl, SCL_AES_CTR, SCL_ENCRYPT, SCL_LITTLE_ENDIAN_MODE, 3, (uint8_t *)F51_plaintext_le, (uint8_t *)tmp))
            {
                cyclecount = metal_cpu_get_timer(cpu)-oldcount;

                // Check returned value
                if ( (tmp[0] != F51_ciphertext_le_expected[0]) || (tmp[1] != F51_ciphertext_le_expected[1])
                     || (tmp[2] != F51_ciphertext_le_expected[2]) || (tmp[3] != F51_ciphertext_le_expected[3]) 
                     || (tmp[4] != F51_ciphertext_le_expected[4]) || (tmp[5] != F51_ciphertext_le_expected[5]) )
                {
                    printf("AES - CTR Wrong value returned\n");
                    return -1;
                }

#if __riscv_xlen == 64
                printf("0x%016lX 0x%016lX\n", *(tmp + 1), *tmp);
                printf("0x%016lX 0x%016lX\n", *(tmp + 3), *(tmp + 2));
                printf("0x%016lX 0x%016lX\n", *(tmp + 5), *(tmp + 4));
#elif __riscv_xlen == 32
                data = (uint32_t *)tmp;
                printf("0x%08lX%08lX 0x%08lX%08lX\n",*(data + 3), *(data + 2), *(data + 1), *data);
                printf("0x%08lX%08lX 0x%08lX%08lX\n",*(data + 7), *(data + 6), *(data + 5), *(data + 4));
                printf("0x%08lX%08lX 0x%08lX%08lX\n",*(data + 11), *(data + 10), *(data + 9), *(data + 8));
#endif
                printf("cyc: %u\n", (unsigned int)cyclecount);
            }
            else
            {
                printf("AES - CTR Error\n");
            }
        }
        else
        {
            printf("AES - setIV Error\n");
        }
    }
    else
    {
        printf("AES - setkey Error\n");
    }


    memset(tmp,0,8*sizeof(uint64_t));
    memset(tag,0,2*sizeof(uint64_t));
    printf("AES - GCM\n");
    oldcount = metal_cpu_get_timer(cpu);
    if (SCL_OK == metal_sifive_scl.aes_func.setkey(&metal_sifive_scl, SCL_AES_KEY128, NIST_key128_GCM))
    {
        if (SCL_OK == metal_sifive_scl.aes_func.setiv(&metal_sifive_scl, NIST_IV_GCM))
        {
            if (SCL_OK == metal_sifive_scl.aes_func.auth(&metal_sifive_scl, SCL_AES_GCM, SCL_ENCRYPT, SCL_LITTLE_ENDIAN_MODE, 0, 48, (uint8_t *)NIST_AAD_GCM, 32, (uint8_t *)NIST_DATA_GCM, (uint8_t *)tmp, tag))
            {
                cyclecount = metal_cpu_get_timer(cpu)-oldcount;

                // Check returned value
                if ( (tmp[0] != NIST_DATA_GCM_expected[0]) || (tmp[1] != NIST_DATA_GCM_expected[1])
                     || (tmp[2] != NIST_DATA_GCM_expected[2]) || (tmp[3] != NIST_DATA_GCM_expected[3]) )
                {
                    printf("AES - GCM Wrong value returned\n");
                    return -1;
                }
                // Check TAG returned value
                if ( (tag[0] != NIST_TAG_GCM_expected[0]) || (tag[1] != NIST_TAG_GCM_expected[1]) )
                {
                    printf("AES - GCM Wrong TAG value returned\n");
                    return -1;
                }

#if __riscv_xlen == 64
                printf("Data:\n");
                printf("  0x%016lX 0x%016lX\n", *(tmp + 1), *tmp);
                printf("  0x%016lX 0x%016lX\n", *(tmp + 3), *(tmp + 2));
                printf("Tag:\n");
                printf("  0x%016lX 0x%016lX\n", *(tag + 1), *tag);
#elif __riscv_xlen == 32
                data = (uint32_t *)tmp;
                printf("Data:\n");
                printf("  0x%08lX%08lX 0x%08lX%08lX\n",*(data + 3), *(data + 2), *(data + 1), *data);
                printf("  0x%08lX%08lX 0x%08lX%08lX\n",*(data + 7), *(data + 6), *(data + 5), *(data + 4));
                data = (uint32_t *)tag;
                printf("Tag:\n");
                printf("  0x%08lX%08lX 0x%08lX%08lX\n",*(data + 3), *(data + 2), *(data + 1), *data);
#endif
                printf("cyc: %u\n", (unsigned int)cyclecount);
            }
            else
            {
                printf("AES - GCM Error\n");
            }
        }
        else
        {
            printf("AES - setIV Error\n");
        }
    }
    else
    {
        printf("AES - setkey Error\n");
    }


    memset(tmp,0,8*sizeof(uint64_t));
    memset(tag,0,2*sizeof(uint64_t));
    printf("AES - CCM\n");
    oldcount = metal_cpu_get_timer(cpu);
    if (SCL_OK == metal_sifive_scl.aes_func.setkey(&metal_sifive_scl, SCL_AES_KEY128, NIST_key128_CCM))
    {
        if (SCL_OK == metal_sifive_scl.aes_func.setiv(&metal_sifive_scl, NIST_IV_CCM))
        {
            if (SCL_OK == metal_sifive_scl.aes_func.auth(&metal_sifive_scl, SCL_AES_CCM, SCL_ENCRYPT, SCL_LITTLE_ENDIAN_MODE, CCM_TQ(7, 1), 24, (uint8_t *)NIST_AAD_CCM, 24, (uint8_t *)NIST_DATA_CCM, (uint8_t *)tmp, tag))
            {
                cyclecount = metal_cpu_get_timer(cpu)-oldcount;

                // Check returned value
                if ( (tmp[0] != NIST_DATA_CCM_expected[0]) || (tmp[1] != NIST_DATA_CCM_expected[1])
                     || (tmp[2] != NIST_DATA_CCM_expected[2]) || (tmp[3] != NIST_DATA_CCM_expected[3]) )
                {
                    printf("AES - CCM Wrong value returned\n");
                    return -1;
                }
                // Check TAG returned value
                if ( (tag[0] != NIST_TAG_CCM_expected[0]) || (tag[1] != NIST_TAG_CCM_expected[1]) )
                {
                    printf("AES - CCM Wrong TAG value returned\n");
                    return -1;
                }

#if __riscv_xlen == 64
                printf("Data:\n");
                printf("  0x%016lX 0x%016lX\n", *(tmp + 1), *tmp);
                printf("  0x%016lX 0x%016lX\n", *(tmp + 3), *(tmp + 2));
                printf("Tag:\n");
                printf("  0x%016lX 0x%016lX\n", *(tag + 1), *tag);
#elif __riscv_xlen == 32
                data = (uint32_t *)tmp;
                printf("Data:\n");
                printf("  0x%08lX%08lX 0x%08lX%08lX\n",*(data + 3), *(data + 2), *(data + 1), *data);
                printf("  0x%08lX%08lX 0x%08lX%08lX\n",*(data + 7), *(data + 6), *(data + 5), *(data + 4));
                data = (uint32_t *)tag;
                printf("Tag:\n");
                printf("  0x%08lX%08lX 0x%08lX%08lX\n",*(data + 3), *(data + 2), *(data + 1), *data);
#endif
                printf("cyc: %u\n", (unsigned int)cyclecount);
            }
            else
            {
                printf("AES - CCM Error\n");
            }
        }
        else
        {
            printf("AES - setIV Error\n");
        }
    }
    else
    {
        printf("AES - setkey Error\n");
    }

    memset(tmp,0,8*sizeof(uint64_t));
    printf("SHA256\n");
    oldcount = metal_cpu_get_timer(cpu);
    if (SCL_OK == metal_sifive_scl.hash_func.sha(&metal_sifive_scl, SCL_HASH_SHA256, SCL_LITTLE_ENDIAN_MODE, 1, (uint8_t *)MsgL24B512, (uint8_t *)tmp))
    {
        cyclecount = metal_cpu_get_timer(cpu)-oldcount;

        // Check returned value
        if ( (tmp[0] != SHA256_expected[0]) || (tmp[1] != SHA256_expected[1])
                || (tmp[2] != SHA256_expected[2]) || (tmp[3] != SHA256_expected[3]) )
        {
            printf("SHA256 Wrong value returned\n");
            return -1;
        }

#if __riscv_xlen == 64
        printf("0x%016lX 0x%016lX 0x%016lX 0x%016lX\n", *(tmp + 3), *(tmp + 2), *(tmp + 1), *tmp);
#elif __riscv_xlen == 32
        data = (uint32_t *)tmp;
        printf("0x%08lX%08lX 0x%08lX%08lX 0x%08lX%08lX 0x%08lX%08lX\n", *(data + 7), *(data + 6), *(data + 5), *(data + 4), *(data + 3), *(data + 2), *(data + 1), *data);
#endif
        printf("cyc: %u\n", (unsigned int)cyclecount);
    }
    else
    {
        printf("SHA256 Error\n");
    }

    memset(tmp,0,8*sizeof(uint64_t));
    printf("SHA224\n");
    oldcount = metal_cpu_get_timer(cpu);
    if (SCL_OK == metal_sifive_scl.hash_func.sha(&metal_sifive_scl, SCL_HASH_SHA224, SCL_LITTLE_ENDIAN_MODE, 1, (uint8_t *)MsgL24B512, (uint8_t *)tmp))
    {
        cyclecount = metal_cpu_get_timer(cpu)-oldcount;

        // Check returned value
        if ( (tmp[0] != SHA224_expected[0]) || (tmp[1] != SHA224_expected[1])
                || (tmp[2] != SHA224_expected[2]) || (tmp[3] != SHA224_expected[3]) )
        {
            printf("SHA224 Wrong value returned\n");
            return -1;
        }

#if __riscv_xlen == 64
        printf("0x%016lX 0x%016lX 0x%016lX 0x%016lX\n", *(tmp + 3), *(tmp + 2), *(tmp + 1), *tmp);
#elif __riscv_xlen == 32
        data = (uint32_t *)tmp;
        printf("0x%08lX%08lX 0x%08lX%08lX 0x%08lX%08lX 0x%08lX%08lX\n", *(data + 7), *(data + 6), *(data + 5), *(data + 4), *(data + 3), *(data + 2), *(data + 1), *data);
#endif
        printf("cyc: %u\n", (unsigned int)cyclecount);
    }
    else
    {
        printf("SHA224 Error\n");
    }


    memset(tmp,0,8*sizeof(uint64_t));
    printf("TRNG - TEST\n");
    oldcount = metal_cpu_get_timer(cpu);
    if (SCL_OK == metal_sifive_scl.trng_func.init(&metal_sifive_scl))
    {
        cyclecount = metal_cpu_get_timer(cpu)-oldcount;
        printf("     INIT cyc: %u\n", (unsigned int)cyclecount);

        oldcount = metal_cpu_get_timer(cpu);
        if (SCL_OK == metal_sifive_scl.trng_func.get_data(&metal_sifive_scl, &val))
        {
            cyclecount = metal_cpu_get_timer(cpu)-oldcount;
#if __riscv_xlen == 64
            printf("0x%08X\n", val);
#elif __riscv_xlen == 32
            printf("0x%08lX\n", val);
#endif
            printf("    get_data cyc: %u\n", (unsigned int)cyclecount);

            oldcount = metal_cpu_get_timer(cpu);
            if (SCL_OK == metal_sifive_scl.trng_func.get_data(&metal_sifive_scl, &val))
            {
                cyclecount = metal_cpu_get_timer(cpu)-oldcount;
#if __riscv_xlen == 64
                printf("0x%08X\n", val);
#elif __riscv_xlen == 32
                printf("0x%08lX\n", val);
#endif
                printf("    get_data cyc: %u\n", (unsigned int)cyclecount);
            }
            else
            {
                printf("TRNG - get_data Fail\n");   
            }

            oldcount = metal_cpu_get_timer(cpu);
            if (SCL_OK == metal_sifive_scl.trng_func.get_data(&metal_sifive_scl, &val))
            {
                cyclecount = metal_cpu_get_timer(cpu)-oldcount;
#if __riscv_xlen == 64
                printf("0x%08X\n", val);
#elif __riscv_xlen == 32
                printf("0x%08lX\n", val);
#endif
                printf("    get_data cyc: %u\n", (unsigned int)cyclecount);
            }
            else
            {
                printf("TRNG - get_data Fail\n");   
            }
        }
        else
        {
            printf("TRNG - get_data Fail\n");   
        }
    }
    else
    {
        printf("TRNG - Init Fail\n");   
    }
}
