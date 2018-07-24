#ifndef RISCV_MBI_H
#define RISCV_MBI_H

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#include "encoding.h"

#if __riscv_xlen == 32
#define LX LW
#define SX SW
#define REGBYTES 4
#elif __riscv_xlen == 64
#define LX LD
#define SX SD
#define REGBYTES 8
#endif

#define STR1(x) #x
#define STR(x) STR1(x)
#define TRAP_SAVE_REGS 16
#define TRAP_CTX_SIZE (TRAP_SAVE_REGS * REGBYTES)
#define EXPAND_STACK(size)   "addi sp,sp," STR(-size) "\n"
#define CONTRACT_STACK(size)  "addi sp,sp," STR(size) "\n"
#define SAVE_REG(reg,offset) STR(SX) " " STR(reg) ", " STR(offset) "*" STR(REGBYTES)"(sp)\n"
#define RSTR_REG(reg,offset) STR(LX) " " STR(reg) ", " STR(offset) "*" STR(REGBYTES)"(sp)\n"

static inline int64_t misa() { return read_csr(misa); }
static inline int has_ext(char ext) { return misa() & (1 << (ext - 'a')); }
static inline int xlen() { return misa() < 0 ? 64 : 32; }

typedef void (*trap_fn)(uintptr_t mcause, uintptr_t mepc);
void default_trap_handler(uintptr_t mcause, uintptr_t mepc);
void register_trap_fn(trap_fn fn);
void mtvec_entry(void);

int* csr_enum_array();
const char** csr_name_array();
long read_csr_enum(int csrenum);
void write_csr_enum(int csrenum, long value);

enum {
	cause_misaligned_fetch     = 0,
	cause_fault_fetch          = 1,
	cause_illegal_instruction  = 2,
	cause_breakpoint           = 3,
	cause_misaligned_load      = 4,
	cause_fault_load           = 5,
	cause_misaligned_store     = 6,
	cause_fault_store          = 7,
	cause_user_ecall           = 8,
	cause_supervisor_ecall     = 9,
	cause_hypervisor_ecall     = 10,
	cause_machine_ecall        = 11,
	cause_exec_page_fault      = 12,
	cause_load_page_fault      = 13,
	cause_store_page_fault     = 15
};

enum {
	intr_u_software           = 0,
	intr_s_software           = 1,
	intr_h_software           = 2,
	intr_m_software           = 3,
	intr_u_timer              = 4,
	intr_s_timer              = 5,
	intr_h_timer              = 6,
	intr_m_timer              = 7,
	intr_u_external           = 8,
	intr_s_external           = 9,
	intr_h_external           = 10,
	intr_m_external           = 11,
};

enum {
	csr_none,
	csr_fflags,
	csr_frm,
	csr_fcsr,
	csr_mcycle,
	csr_minstret,
	csr_mcycleh,
	csr_minstreth,
	csr_cycle,
	csr_time,
	csr_instret,
	csr_cycleh,
	csr_timeh,
	csr_instreth,
	csr_mvendorid,
	csr_marchid,
	csr_mimpid,
	csr_mhartid,
	csr_mstatus,
	csr_misa,
	csr_medeleg,
	csr_mideleg,
	csr_mie,
	csr_mtvec,
	csr_mcounteren,
	csr_mscratch,
	csr_mepc,
	csr_mcause,
	csr_mtval,
	csr_mip,
};

#endif
