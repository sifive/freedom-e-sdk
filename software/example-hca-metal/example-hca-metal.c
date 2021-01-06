/* Copyright 2020 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <metal/io.h>
#include <metal/machine/platform.h>
#include <metal/cpu.h>

#include <api/scl_api.h>
#include <api/hardware/scl_hca.h>

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

// d3c0ed74e5f25e4c 1e479e1a51182bb0 18698ec267269149
uint64_t NIST_AAD_CCM[3] = {
    0x1e479e1a51182bb0,
    0xd3c0ed74e5f25e4c,
    0x18698ec267269149
};

uint64_t NIST_DATA_CCM[3] = {
    0x0909a3b8c0029b62,
    0x7dd7396db6613eb8,
    0x4912aabedda0659b
};

uint64_t NIST_DATA_CCM_expected[3] = {
    0x22502ed6f4861af7,
    0x5b00cf8a66baa7fe,
    0x1fa64b550d643f95
};

uint64_t NIST_TAG_CCM_expected[2] = {
    0x0604b58d92dacd3f,
    0xeee82c19ecba3428
};

/*********************************/
uint64_t NIST_key128_CCM2[4] = {
    0,
    0,
    0x4a3dedb19d20f6c8,
    0x2ebf60f0969013a5
};

uint64_t NIST_IV_CCM2[2] = {
    0x23ff870add000000,
    0x1de8c5e21f9db331
};

// d3c0ed74e5f25e4c 1e479e1a51182bb0 18698ec267269149
uint64_t NIST_AAD_CCM2[4] = {
    0x1136285d10b47a45,
    0xe1de6c6119d7db47,
    0xef6a22b055295603,
    0x0221b16978569190
};

uint64_t NIST_TAG_CCM2_expected[2] = {
    0xd11abe5ed704b880,
    0x0ead29ef205fbb86
};
/*********************************/

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

uint8_t message[] __attribute__((aligned(8))) =
    "abc";

/*
uint64_t SHA256_expected[4] = {
    0xeacf018fbf1678ba,
    0x2322ae5dde404141,
    0x9c7a1796a36103b0,
    0xad1500f261ff10b4
};
*/
uint8_t SHA256_expected[32] = {
    0xBA, 0x78, 0x16, 0xBF, 0x8F, 0x01, 0xCF, 0xEA,
    0x41, 0x41, 0x40, 0xDE, 0x5D, 0xAE, 0x22, 0x23,
    0xB0, 0x03, 0x61, 0xA3, 0x96, 0x17, 0x7A, 0x9C,
    0xB4, 0x10, 0xFF, 0x61, 0xF2, 0x00, 0x15, 0xAD};


/*
uint64_t SHA224_expected[4] = {
    0xbda0b3f7e36c9da7,
    0xbda255b32aadbce4,
    0x3405d8228642a477,
    0x0000000023097d22   
};
*/
uint8_t SHA224_expected[28] __attribute__((aligned(8))) = {
    0x23, 0x09, 0x7D, 0x22, 0x34, 0x05, 0xD8, 0x22, 
    0x86, 0x42, 0xA4, 0x77, 0xBD, 0xA2, 0x55, 0xB3, 
    0x2A, 0xAD, 0xBC, 0xE4, 0xBD, 0xA0, 0xB3, 0xF7, 
    0xE3, 0x6C, 0x9D, 0xA7
};

#define CCM_TQ(t, q)     ((uint8_t)((uint8_t)(t & 0xF) + (uint8_t)(q << 4)))

#if METAL_SIFIVE_HCA_VERSION >= HCA_VERSION(0,5,0)
metal_scl_t metal_sifive_scl = {
# if defined(HCA_HAS_AES)        
    .aes_func = {
        .setkey = hca_aes_setkey,
        .setiv  = hca_aes_setiv,
        .cipher = hca_aes_cipher,
#  if defined(HCA_HAS_AESMAC)
        .auth_init = hca_aes_auth_init, 
        .auth_core = hca_aes_auth_core,
        .auth_finish = hca_aes_auth_finish
#  else
        .auth_init = default_aes_auth_init, 
        .auth_core = default_aes_auth_core,
        .auth_finish = default_aes_auth_finish
#  endif
    },
# else
    .aes_func = {
        .setkey = default_aes_setkey,
        .setiv  = default_aes_setiv,
        .cipher = default_aes_cipher,
        .auth_init = default_aes_auth_init, 
        .auth_core = default_aes_auth_core,
        .auth_finish = default_aes_auth_finish
    },
# endif
# if defined(HCA_HAS_SHA)
    .hash_func = {
        .sha_init = hca_sha_init, 
        .sha_core = hca_sha_core,
        .sha_finish = hca_sha_finish
    },
# else
    .hash_func = {
        .sha_init = default_sha_init, 
        .sha_core = default_sha_core,
        .sha_finish = default_sha_finish
    },
# endif
# if defined(HCA_HAS_TRNG)
    .trng_func = {
#  if defined(HCA_BYPASS_TRNG)
        .init = default_trng_init,
        .get_data = default_trng_getdata
#  else
        .init = hca_trng_init,
        .get_data = hca_trng_getdata
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
        .auth_init = default_aes_auth_init, 
        .auth_core = default_aes_auth_core,
        .auth_finish = default_aes_auth_finish
    },
    .hash_func = {
        .sha_init = default_sha_init, 
        .sha_core = default_sha_core,
        .sha_finish = default_sha_finish
    },
    .trng_func = {
        .init = default_trng_init,
        .get_data = default_trng_getdata
    },
    .hca_base = 0
};
#endif

aes_auth_ctx_t ctx_aes_auth = {0};
sha_ctx_t sha_ctx = {0};

/*
 * Main
 */
int main(int argc, char *argv[]) {
    uint32_t val;
    uint64_t oldcount, cyclecount;
    uint64_t tmp[8] = {0};
    uint64_t tag[2] = {0};
    uint64_t *ptr64;
    uint8_t *ptr8;
    size_t digest_len;
    size_t i;
    size_t len;

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
    if (SCL_OK == metal_sifive_scl.aes_func.setkey(&metal_sifive_scl, SCL_AES_KEY128, key128_2, SCL_ENCRYPT))
    {
        if (SCL_OK == metal_sifive_scl.aes_func.cipher(&metal_sifive_scl, SCL_AES_ECB, SCL_ENCRYPT, SCL_LITTLE_ENDIAN_MODE, (uint8_t *)plaintext_le, sizeof(plaintext_le), (uint8_t *)tmp))
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

    memset(tmp,0,8*sizeof(uint64_t));
    memset(tag,0,2*sizeof(uint64_t));
    printf("AES - CCM\n");
    oldcount = metal_cpu_get_timer(cpu);
    if (SCL_OK == metal_sifive_scl.aes_func.setkey(&metal_sifive_scl, SCL_AES_KEY128, NIST_key128_CCM2, SCL_ENCRYPT))
    {
        if (SCL_OK == metal_sifive_scl.aes_func.setiv(&metal_sifive_scl, NIST_IV_CCM2))
        {
            if (SCL_OK ==  metal_sifive_scl.aes_func.auth_init(&metal_sifive_scl, &ctx_aes_auth, SCL_AES_CCM, SCL_ENCRYPT, SCL_LITTLE_ENDIAN_MODE, CCM_TQ(7, 2), (uint8_t *)NIST_AAD_CCM2, sizeof(NIST_AAD_CCM2), 0) )
            {
                if (SCL_OK ==  metal_sifive_scl.aes_func.auth_finish(&metal_sifive_scl, &ctx_aes_auth, (uint8_t *)&tmp[2], tag) )
                {
                    cyclecount = metal_cpu_get_timer(cpu)-oldcount;

                    // Check TAG returned value
                    if ( (tag[0] != NIST_TAG_CCM2_expected[0]) || (tag[1] != NIST_TAG_CCM2_expected[1]) )
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
                    printf("AES - CCM Finish Error\n");
                }
            }
            else
            {
                printf("AES - CCM Init Error\n");
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
    printf("AES - CCM - 2\n");
    oldcount = metal_cpu_get_timer(cpu);
    if (SCL_OK == metal_sifive_scl.aes_func.setkey(&metal_sifive_scl, SCL_AES_KEY128, NIST_key128_CCM, SCL_ENCRYPT))
    {
        if (SCL_OK == metal_sifive_scl.aes_func.setiv(&metal_sifive_scl, NIST_IV_CCM))
        {
            if (SCL_OK ==  metal_sifive_scl.aes_func.auth_init(&metal_sifive_scl, &ctx_aes_auth, SCL_AES_CCM, SCL_ENCRYPT, SCL_LITTLE_ENDIAN_MODE, CCM_TQ(7, 2), (uint8_t *)NIST_AAD_CCM, sizeof(NIST_AAD_CCM), sizeof(NIST_DATA_CCM)) )
            {
                if (SCL_OK ==  metal_sifive_scl.aes_func.auth_core(&metal_sifive_scl, &ctx_aes_auth, (uint8_t *)NIST_DATA_CCM, sizeof(NIST_DATA_CCM), (uint8_t *)tmp, &len) )
                {
                    if (SCL_OK ==  metal_sifive_scl.aes_func.auth_finish(&metal_sifive_scl, &ctx_aes_auth, (uint8_t *)&tmp[len / sizeof(uint64_t)], tag) )
                    {
                        cyclecount = metal_cpu_get_timer(cpu)-oldcount;

                        // Check returned value
                        if ( (tmp[0] != NIST_DATA_CCM_expected[0]) || (tmp[1] != NIST_DATA_CCM_expected[1])
                            || (tmp[2] != NIST_DATA_CCM_expected[2]) )
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
                        printf("AES - CCM Finish Error\n");
                    }
                }
                else
                {
                    printf("AES - CCM Core Error\n");
                }
            }
            else
            {
                printf("AES - CCM Init Error\n");
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
    if (SCL_OK == metal_sifive_scl.aes_func.setkey(&metal_sifive_scl, SCL_AES_KEY128, NIST_key128_GCM, SCL_ENCRYPT))
    {
        if (SCL_OK == metal_sifive_scl.aes_func.setiv(&metal_sifive_scl, NIST_IV_GCM))
        {
            if (SCL_OK ==  metal_sifive_scl.aes_func.auth_init(&metal_sifive_scl, &ctx_aes_auth, SCL_AES_GCM, SCL_ENCRYPT, SCL_LITTLE_ENDIAN_MODE, 0, (uint8_t *)NIST_AAD_GCM, sizeof(NIST_AAD_GCM), sizeof(NIST_DATA_GCM)) )
            {
                if (SCL_OK ==  metal_sifive_scl.aes_func.auth_core(&metal_sifive_scl, &ctx_aes_auth, (uint8_t *)NIST_DATA_GCM, sizeof(NIST_DATA_GCM), (uint8_t *)tmp, &len) )
                {
                    if (SCL_OK ==  metal_sifive_scl.aes_func.auth_finish(&metal_sifive_scl, &ctx_aes_auth, NULL, tag) )
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
                        printf("AES - GCM Finish Error\n");
                    }
                }
                else
                {
                    printf("AES - GCM Core Error\n");
                }
            }
            else
            {
                printf("AES - GCM Init Error\n");
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
    digest_len = 32;
    oldcount = metal_cpu_get_timer(cpu);

    if (SCL_OK == metal_sifive_scl.hash_func.sha_init(&metal_sifive_scl, &sha_ctx, SCL_HASH_SHA256, SCL_BIG_ENDIAN_MODE))
    {
        if (SCL_OK == metal_sifive_scl.hash_func.sha_core(&metal_sifive_scl, &sha_ctx, message, sizeof(message) - 1 ))
        {
            if (SCL_OK == metal_sifive_scl.hash_func.sha_finish(&metal_sifive_scl, &sha_ctx, (uint8_t *)tmp, &digest_len))
            {
                cyclecount = metal_cpu_get_timer(cpu)-oldcount;

                ptr64 = (uint64_t *)SHA256_expected;
                // Check returned value
                if ( (tmp[0] != ptr64[0]) || (tmp[1] != ptr64[1])
                        || (tmp[2] != ptr64[2]) || (tmp[3] != ptr64[3]) )
                {
                    printf("SHA256 Wrong value returned\n");
                    return -1;
                }

                ptr8 = (uint8_t *)tmp;
                for (i=0; i<32;i++)
                {
                    if (!(i & 7))
                        printf(" ");
                    printf("%02X", ptr8[i]);
                }
                printf("\n");

                printf("cyc: %u\n", (unsigned int)cyclecount);
            }
            else
            {
                printf("SHA256 finish Error\n");
            }
        }
        else
        {
            printf("SHA256 core Error\n");
        }
    }
    else
    {
        printf("SHA256 init Error\n");
    }

    memset(tmp,0,8*sizeof(uint64_t));
    printf("SHA224\n");
    digest_len = 28;
    oldcount = metal_cpu_get_timer(cpu);
    if (SCL_OK == metal_sifive_scl.hash_func.sha_init(&metal_sifive_scl, &sha_ctx, SCL_HASH_SHA224, SCL_BIG_ENDIAN_MODE))
    {
        if (SCL_OK == metal_sifive_scl.hash_func.sha_core(&metal_sifive_scl, &sha_ctx, message, sizeof(message) - 1 ))
        {
            if (SCL_OK == metal_sifive_scl.hash_func.sha_finish(&metal_sifive_scl, &sha_ctx, (uint8_t *)tmp, &digest_len))
            {
                cyclecount = metal_cpu_get_timer(cpu)-oldcount;

                ptr64 = (uint64_t *)SHA224_expected;
                // Check returned value
                if ( (tmp[0] != ptr64[0]) || (tmp[1] != ptr64[1])
                        || (tmp[2] != ptr64[2])  )
                {
                    printf("SHA224 Wrong value returned\n");
                    return -1;
                }

                ptr8 = (uint8_t *)tmp;
                for (i=0; i<28;i++)
                {
                    if (!(i & 7))
                        printf(" ");
                    printf("%02X", ptr8[i]);
                }
                printf("\n");

                printf("cyc: %u\n", (unsigned int)cyclecount);
            }
            else
            {
                printf("SHA224 finish Error\n");
            }
        }
        else
        {
            printf("SHA224 core Error\n");
        }
    }
    else
    {
        printf("SHA224 init Error\n");
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

    return 0;
}
