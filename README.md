# example-hca-metal

Sifive deliver a high level of API for the cryptographic function call SCL (SiFive Cryptographic Librarie). The HCA is the Hardware Cryptographic Accelerator for this librarie.

This example show how to connect the HCA, but instead of using the high level of SCL API, we will use the low level function (when hardware feature will be available)

This example perform some AES-ECB, AES-CCM, AES-GCM cryptographic operation with test vector and verify the attended result.

it perform also SHA256 and SHA224 on "well formated" buffer (it is the upper API that is in charge to format the "human" entry to the "well formated" buffer for the HCA)

it perform a TRNG initialization and get some random Data.