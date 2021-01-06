//**********************************************************************************
// See LICENSE for license details.
//
// Description
// -------------
// Assembly-based test which targets 32-bit or 64-bit RISC-V CPUs
// Each test will compare for expected results.  Three results are possible:
//
// PASS:    When all tests are complete and passing, x10 (a0) register is loaded
//          with 0x0 for PASS, and then we reach our freedom metal exit routine
//          and spin.  The exit routine has an output code that is assigned
//          based on the PASS/FAIL value returned to it.  
// FAIL:    If a failure occurs, x10 (a0) register is loaded with 0x1 for FAIL, 
//          and then we reach our freedom metal exit routine and spin.  The exit 
//          routine has an output code that is assigned based on the PASS/FAIL 
//          value returned to it.
// TRAP:    If there is a trap to an exception handler for an unknown condition,
//          we will not return the PASS or FAIL return value, and the code 
//          will spin continuously.
//**********************************************************************************

#include "riscv_asm.h"

// -----------------------
// ---- Start of main ----
// -----------------------
ASM_ENTRY

//-------------------------------------------------------------
// Addition tests - Arithmetic
//-------------------------------------------------------------

    TEST_RR_OP( 1002,  add, 0x00000000, 0x00000000, 0x00000000 );
    TEST_RR_OP( 1003,  add, 0x00000002, 0x00000001, 0x00000001 );
    TEST_RR_OP( 1004,  add, 0x0000000a, 0x00000003, 0x00000007 );

    TEST_RR_OP( 1005,  add, 0xffffffffffff8000, 0x0000000000000000, 0xffffffffffff8000 );
    TEST_RR_OP( 1006,  add, 0xffffffff80000000, 0xffffffff80000000, 0x00000000 );
    TEST_RR_OP( 1007,  add, 0xffffffff7fff8000, 0xffffffff80000000, 0xffffffffffff8000 );

    TEST_RR_OP( 1008,  add, 0x0000000000007fff, 0x0000000000000000, 0x0000000000007fff );
    TEST_RR_OP( 1009,  add, 0x000000007fffffff, 0x000000007fffffff, 0x0000000000000000 );
    TEST_RR_OP( 1010, add, 0x0000000080007ffe, 0x000000007fffffff, 0x0000000000007fff );

    TEST_RR_OP( 1011, add, 0xffffffff80007fff, 0xffffffff80000000, 0x0000000000007fff );
    TEST_RR_OP( 1012, add, 0x000000007fff7fff, 0x000000007fffffff, 0xffffffffffff8000 );

    TEST_RR_OP( 1013, add, 0xffffffffffffffff, 0x0000000000000000, 0xffffffffffffffff );
    TEST_RR_OP( 1014, add, 0x0000000000000000, 0xffffffffffffffff, 0x0000000000000001 );
    TEST_RR_OP( 1015, add, 0xfffffffffffffffe, 0xffffffffffffffff, 0xffffffffffffffff );

    TEST_RR_OP( 10016, add, 0x0000000080000000, 0x0000000000000001, 0x000000007fffffff );

//-------------------------------------------------------------
// Addition tests - Source/Destination tests
//-------------------------------------------------------------

    TEST_RR_SRC1_EQ_DEST( 1017, add, 24, 13, 11 );
    TEST_RR_SRC2_EQ_DEST( 1018, add, 25, 14, 11 );
    TEST_RR_SRC12_EQ_DEST( 1019, add, 26, 13 );

//-------------------------------------------------------------
// Addition tests - Bypassing tests
//-------------------------------------------------------------

    TEST_RR_DEST_BYPASS( 1020, 0, add, 24, 13, 11 );
    TEST_RR_DEST_BYPASS( 1021, 1, add, 25, 14, 11 );
    TEST_RR_DEST_BYPASS( 1022, 2, add, 26, 15, 11 );

    TEST_RR_SRC12_BYPASS( 1023, 0, 0, add, 24, 13, 11 );
    TEST_RR_SRC12_BYPASS( 1024, 0, 1, add, 25, 14, 11 );
    TEST_RR_SRC12_BYPASS( 1025, 0, 2, add, 26, 15, 11 );
    TEST_RR_SRC12_BYPASS( 1026, 1, 0, add, 24, 13, 11 );
    TEST_RR_SRC12_BYPASS( 1027, 1, 1, add, 25, 14, 11 );
    TEST_RR_SRC12_BYPASS( 1028, 2, 0, add, 26, 15, 11 );

    TEST_RR_SRC21_BYPASS( 1029, 0, 0, add, 24, 13, 11 );
    TEST_RR_SRC21_BYPASS( 1030, 0, 1, add, 25, 14, 11 );
    TEST_RR_SRC21_BYPASS( 1031, 0, 2, add, 26, 15, 11 );
    TEST_RR_SRC21_BYPASS( 1032, 1, 0, add, 24, 13, 11 );
    TEST_RR_SRC21_BYPASS( 1033, 1, 1, add, 25, 14, 11 );
    TEST_RR_SRC21_BYPASS( 1034, 2, 0, add, 26, 15, 11 );

    TEST_RR_ZEROSRC1( 1035, add, 15, 15 );
    TEST_RR_ZEROSRC2( 1036, add, 32, 32 );
    TEST_RR_ZEROSRC12( 1037, add, 0 );
    TEST_RR_ZERODEST( 1038, add, 16, 30 );

//-------------------------------------------------------------
// Multiply tests - Arithmetic 
//-------------------------------------------------------------

#if __riscv_xlen == 64

    TEST_RR_OP( 2002,  mul, 0x0000000000001200, 0x0000000000007e00, 0x6db6db6db6db6db7 );
    TEST_RR_OP( 2003,  mul, 0x0000000000001240, 0x0000000000007fc0, 0x6db6db6db6db6db7 );

    TEST_RR_OP( 2004,  mul, 0x00000000, 0x00000000, 0x00000000 );
    TEST_RR_OP( 2005,  mul, 0x00000001, 0x00000001, 0x00000001 );
    TEST_RR_OP( 2006,  mul, 0x00000015, 0x00000003, 0x00000007 );

    TEST_RR_OP( 2007,  mul, 0x0000000000000000, 0x0000000000000000, 0xffffffffffff8000 );
    TEST_RR_OP( 2008,  mul, 0x0000000000000000, 0xffffffff80000000, 0x00000000 );
    TEST_RR_OP( 2009,  mul, 0x0000400000000000, 0xffffffff80000000, 0xffffffffffff8000 );

    TEST_RR_OP( 2010,  mul, 0x000000000000ff7f, 0xaaaaaaaaaaaaaaab, 0x000000000002fe7d );
    TEST_RR_OP( 2011,  mul, 0x000000000000ff7f, 0x000000000002fe7d, 0xaaaaaaaaaaaaaaab );

#else

    TEST_RR_OP( 2002,  mul, 0x00001200, 0x00007e00, 0xb6db6db7 );
    TEST_RR_OP( 2003,  mul, 0x00001240, 0x00007fc0, 0xb6db6db7 );

    TEST_RR_OP( 2004,  mul, 0x00000000, 0x00000000, 0x00000000 );
    TEST_RR_OP( 2005,  mul, 0x00000001, 0x00000001, 0x00000001 );
    TEST_RR_OP( 2006,  mul, 0x00000015, 0x00000003, 0x00000007 );

    TEST_RR_OP( 2007,  mul, 0x00000000, 0x00000000, 0xffff8000 );
    TEST_RR_OP( 2008,  mul, 0x00000000, 0x80000000, 0x00000000 );
    TEST_RR_OP( 2009,  mul, 0x00000000, 0x80000000, 0xffff8000 );

    TEST_RR_OP(2010,  mul, 0x0000ff7f, 0xaaaaaaab, 0x0002fe7d );
    TEST_RR_OP(2011,  mul, 0x0000ff7f, 0x0002fe7d, 0xaaaaaaab );

    TEST_RR_OP(2012,  mul, 0x00000000, 0xff000000, 0xff000000 );

    TEST_RR_OP(2013,  mul, 0x00000001, 0xffffffff, 0xffffffff );
    TEST_RR_OP(2014,  mul, 0xffffffff, 0xffffffff, 0x00000001 );
    TEST_RR_OP(2015,  mul, 0xffffffff, 0x00000001, 0xffffffff );

#endif 

//-------------------------------------------------------------
// Multiply tests - Source/Destination tests
//-------------------------------------------------------------

    TEST_RR_SRC1_EQ_DEST( 3002, mul, 143, 13, 11 );
    TEST_RR_SRC2_EQ_DEST( 3003, mul, 154, 14, 11 );
    TEST_RR_SRC12_EQ_DEST( 3004, mul, 169, 13 );

//-------------------------------------------------------------
// Multiply tests - Bypassing tests
//-------------------------------------------------------------

    TEST_RR_DEST_BYPASS( 3005, 0, mul, 143, 13, 11 );
    TEST_RR_DEST_BYPASS( 3006, 1, mul, 154, 14, 11 );
    TEST_RR_DEST_BYPASS( 3007, 2, mul, 165, 15, 11 );

    TEST_RR_SRC12_BYPASS( 3008, 0, 0, mul, 143, 13, 11 );
    TEST_RR_SRC12_BYPASS( 3009, 0, 1, mul, 154, 14, 11 );
    TEST_RR_SRC12_BYPASS( 3010, 0, 2, mul, 165, 15, 11 );
    TEST_RR_SRC12_BYPASS( 3011, 1, 0, mul, 143, 13, 11 );
    TEST_RR_SRC12_BYPASS( 3012, 1, 1, mul, 154, 14, 11 );
    TEST_RR_SRC12_BYPASS( 3013, 2, 0, mul, 165, 15, 11 );

    TEST_RR_SRC21_BYPASS( 3014, 0, 0, mul, 143, 13, 11 );
    TEST_RR_SRC21_BYPASS( 3015, 0, 1, mul, 154, 14, 11 );
    TEST_RR_SRC21_BYPASS( 3016, 0, 2, mul, 165, 15, 11 );
    TEST_RR_SRC21_BYPASS( 3017, 1, 0, mul, 143, 13, 11 );
    TEST_RR_SRC21_BYPASS( 3018, 1, 1, mul, 154, 14, 11 );
    TEST_RR_SRC21_BYPASS( 3019, 2, 0, mul, 165, 15, 11 );

    TEST_RR_ZEROSRC1( 3020, mul, 0, 31 );
    TEST_RR_ZEROSRC2( 3021, mul, 0, 32 );
    TEST_RR_ZEROSRC12( 3022, mul, 0 );
    TEST_RR_ZERODEST( 3023, mul, 33, 34 );

//-------------------------------------------------------------
// Exclusive OR tests - Logical tests
//-------------------------------------------------------------

    TEST_RR_OP( 4002, xor, 0xf00ff00f, 0xff00ff00, 0x0f0f0f0f );
    TEST_RR_OP( 4003, xor, 0xff00ff00, 0x0ff00ff0, 0xf0f0f0f0 );
    TEST_RR_OP( 4004, xor, 0x0ff00ff0, 0x00ff00ff, 0x0f0f0f0f );
    TEST_RR_OP( 4005, xor, 0x00ff00ff, 0xf00ff00f, 0xf0f0f0f0 );

//-------------------------------------------------------------
// Exclusive OR tests - Source/Destination tests
//-------------------------------------------------------------

    TEST_RR_SRC1_EQ_DEST( 4006, xor, 0xf00ff00f, 0xff00ff00, 0x0f0f0f0f );
    TEST_RR_SRC2_EQ_DEST( 4007, xor, 0xf00ff00f, 0xff00ff00, 0x0f0f0f0f );
    TEST_RR_SRC12_EQ_DEST( 4008, xor, 0x00000000, 0xff00ff00 );

//-------------------------------------------------------------
// Exclusive OR tests - Bypassing tests
//-------------------------------------------------------------

    TEST_RR_DEST_BYPASS( 4009,  0, xor, 0xf00ff00f, 0xff00ff00, 0x0f0f0f0f );
    TEST_RR_DEST_BYPASS( 4010, 1, xor, 0xff00ff00, 0x0ff00ff0, 0xf0f0f0f0 );
    TEST_RR_DEST_BYPASS( 4011, 2, xor, 0x0ff00ff0, 0x00ff00ff, 0x0f0f0f0f );

    TEST_RR_SRC12_BYPASS( 4012, 0, 0, xor, 0xf00ff00f, 0xff00ff00, 0x0f0f0f0f );
    TEST_RR_SRC12_BYPASS( 4013, 0, 1, xor, 0xff00ff00, 0x0ff00ff0, 0xf0f0f0f0 );
    TEST_RR_SRC12_BYPASS( 4014, 0, 2, xor, 0x0ff00ff0, 0x00ff00ff, 0x0f0f0f0f );
    TEST_RR_SRC12_BYPASS( 4015, 1, 0, xor, 0xf00ff00f, 0xff00ff00, 0x0f0f0f0f );
    TEST_RR_SRC12_BYPASS( 4016, 1, 1, xor, 0xff00ff00, 0x0ff00ff0, 0xf0f0f0f0 );
    TEST_RR_SRC12_BYPASS( 4017, 2, 0, xor, 0x0ff00ff0, 0x00ff00ff, 0x0f0f0f0f );

    TEST_RR_SRC21_BYPASS( 4018, 0, 0, xor, 0xf00ff00f, 0xff00ff00, 0x0f0f0f0f );
    TEST_RR_SRC21_BYPASS( 4019, 0, 1, xor, 0xff00ff00, 0x0ff00ff0, 0xf0f0f0f0 );
    TEST_RR_SRC21_BYPASS( 4020, 0, 2, xor, 0x0ff00ff0, 0x00ff00ff, 0x0f0f0f0f );
    TEST_RR_SRC21_BYPASS( 4021, 1, 0, xor, 0xf00ff00f, 0xff00ff00, 0x0f0f0f0f );
    TEST_RR_SRC21_BYPASS( 4022, 1, 1, xor, 0xff00ff00, 0x0ff00ff0, 0xf0f0f0f0 );
    TEST_RR_SRC21_BYPASS( 4023, 2, 0, xor, 0x0ff00ff0, 0x00ff00ff, 0x0f0f0f0f );

    TEST_RR_ZEROSRC1( 4024, xor, 0xff00ff00, 0xff00ff00 );
    TEST_RR_ZEROSRC2( 4025, xor, 0x00ff00ff, 0x00ff00ff );
    TEST_RR_ZEROSRC12( 4026, xor, 0 );
    TEST_RR_ZERODEST( 4027, xor, 0x11111111, 0x22222222 );

//-------------------------------------------------------------
// Divide Instruction - Arithmetic tests
//-------------------------------------------------------------

    TEST_RR_OP( 5002, div,  3,  20,   6 );
    TEST_RR_OP( 5003, div, -3, -20,   6 );
    TEST_RR_OP( 5004, div, -3,  20,  -6 );
    TEST_RR_OP( 5005, div,  3, -20,  -6 );

    TEST_RR_OP( 5006, div, -1<<31, -1<<31,  1 );
    TEST_RR_OP( 5007, div, -1<<31, 1<<31, -1 );

    TEST_RR_OP( 5008, div, -1, -1<<31, 0 );
    TEST_RR_OP( 5009, div, -1,      1, 0 );
    TEST_RR_OP( 5010, div, -1,      0, 0 );

// ---------------------------------------------
// Test csr instruction
// csr - control and status registers
// ---------------------------------------------

    // Check that mcpuid reports the correct XLEN
    #if __riscv_xlen == 64
        TEST_CASE( 6002, a0, 0x2, csrr a0, misa; srl a0, a0, 62)
    #else
        TEST_CASE( 6002, a0, 0x1, csrr a0, misa; srl a0, a0, 30)
    #endif

    # Check that mhartid reports 0
    TEST_CASE( 6003, a0, 0x0, csrr a0, mhartid)

    # Check that reading the following CSRs doesn't cause an exception
    csrr a0, mimpid
    csrr a0, marchid
    csrr a0, mvendorid

    # Check that writing hte following CSRs doesn't cause an exception
    li t0, 0
    csrs mtvec, t0
    csrs mepc, t0

// If we have successfully made it here, load x10 (a0) with 0x0 to
// show PASS as our exit code and then spin.

ASM_EXIT    
// ---------------------
// ---- End of main ----
// ---------------------

// End of file    