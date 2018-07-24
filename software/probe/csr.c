#include <stdio.h>

#include "probe.h"

static int all_csr_enums[] = {
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
	csr_none,
};

static const char* all_csr_names[] = {
	"none",
	"fflags",
	"frm",
	"fcsr",
	"mcycle",
	"minstret",
	"mcycleh",
	"minstreth",
	"cycle",
	"time",
	"instret",
	"cycleh",
	"timeh",
	"instreth",
	"mvendorid",
	"marchid",
	"mimpid",
	"mhartid",
	"mstatus",
	"misa",
	"medeleg",
	"mideleg",
	"mie",
	"mtvec",
	"mcounteren",
	"mscratch",
	"mepc",
	"mcause",
	"mtval",
	"mip",
};

int* csr_enum_array()
{
	return all_csr_enums;
}

const char** csr_name_array()
{
	return all_csr_names;
}

long read_csr_enum(int csrenum)
{
	long result = -1;
	switch (csrenum) {
		case csr_fflags:     result = read_csr(0x001); break;
		case csr_frm:        result = read_csr(0x002); break;
		case csr_fcsr:       result = read_csr(0x003); break;
		case csr_mcycle:     result = read_csr(0xB00); break;
		case csr_minstret:   result = read_csr(0xB02); break;
		case csr_mcycleh:    result = read_csr(0xB80); break;
		case csr_minstreth:  result = read_csr(0xB82); break;
		case csr_cycle:      result = read_csr(0xC00); break;
		case csr_time:       result = read_csr(0xC01); break;
		case csr_instret:    result = read_csr(0xC02); break;
		case csr_cycleh:     result = read_csr(0xC80); break;
		case csr_timeh:      result = read_csr(0xC81); break;
		case csr_instreth:   result = read_csr(0xC82); break;
		case csr_mvendorid:  result = read_csr(0xF11); break;
		case csr_marchid:    result = read_csr(0xF12); break;
		case csr_mimpid:     result = read_csr(0xF13); break;
		case csr_mhartid:    result = read_csr(0xF14); break;
		case csr_mstatus:    result = read_csr(0x300); break;
		case csr_misa:       result = read_csr(0x301); break;
		case csr_medeleg:    result = read_csr(0x302); break;
		case csr_mideleg:    result = read_csr(0x303); break;
		case csr_mie:        result = read_csr(0x304); break;
		case csr_mtvec:      result = read_csr(0x305); break;
		case csr_mcounteren: result = read_csr(0x306); break;
		case csr_mscratch:   result = read_csr(0x340); break;
		case csr_mepc:       result = read_csr(0x341); break;
		case csr_mcause:     result = read_csr(0x342); break;
		case csr_mtval:      result = read_csr(0x343); break;
		case csr_mip:        result = read_csr(0x344); break;
		default: break;
	}
	return result;
}

void write_csr_enum(int csrenum, long value)
{
	switch (csrenum) {
		case csr_fflags:     write_csr(0x001, value); break;
		case csr_frm:        write_csr(0x002, value); break;
		case csr_fcsr:       write_csr(0x003, value); break;
		case csr_mcycle:     write_csr(0xB00, value); break;
		case csr_minstret:   write_csr(0xB02, value); break;
		case csr_mcycleh:    write_csr(0xB80, value); break;
		case csr_minstreth:  write_csr(0xB82, value); break;
		case csr_cycle:      write_csr(0xC00, value); break;
		case csr_time:       write_csr(0xC01, value); break;
		case csr_instret:    write_csr(0xC02, value); break;
		case csr_cycleh:     write_csr(0xC80, value); break;
		case csr_timeh:      write_csr(0xC81, value); break;
		case csr_instreth:   write_csr(0xC82, value); break;
		case csr_mvendorid:  write_csr(0xF11, value); break;
		case csr_marchid:    write_csr(0xF12, value); break;
		case csr_mimpid:     write_csr(0xF13, value); break;
		case csr_mhartid:    write_csr(0xF14, value); break;
		case csr_mstatus:    write_csr(0x300, value); break;
		case csr_misa:       write_csr(0x301, value); break;
		case csr_medeleg:    write_csr(0x302, value); break;
		case csr_mideleg:    write_csr(0x303, value); break;
		case csr_mie:        write_csr(0x304, value); break;
		case csr_mtvec:      write_csr(0x305, value); break;
		case csr_mcounteren: write_csr(0x306, value); break;
		case csr_mscratch:   write_csr(0x340, value); break;
		case csr_mepc:       write_csr(0x341, value); break;
		case csr_mcause:     write_csr(0x342, value); break;
		case csr_mtval:      write_csr(0x343, value); break;
		case csr_mip:        write_csr(0x344, value); break;
		default: break;
	}
}
