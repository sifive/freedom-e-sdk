#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "probe.h"

static uintptr_t save_mcause;

#if 1
void remove_this_function_and_see_what_happens(uintptr_t mcause, uintptr_t mepc)
{
	printf("remove_this_function_and_see_what_happens\n");
	write_csr(mepc, mepc + 4);
}
#endif

static void trap_save_cause(uintptr_t mcause, uintptr_t mepc)
{
	save_mcause = mcause;
	write_csr(mepc, mepc + 4);
}

static void append_ext(char *str, char ext)
{
	char *s = str + strlen(str);
	if (has_ext(ext)) {
		*s = ext;
		*(++s) = '\0';
	}
}

static const char* isa_string()
{
	static char str[32];
	snprintf(str, sizeof(str), "rv%d", xlen());
	append_ext(str, 'i');
	append_ext(str, 'm');
	append_ext(str, 'a');
	append_ext(str, 'f');
	append_ext(str, 'd');
	append_ext(str, 'c');
	append_ext(str, 's');
	append_ext(str, 'u');
	return str;
}

static void probe_all_csrs()
{
	int *csrenum = csr_enum_array();
	const char **csrnames = csr_name_array();
	const char* ws = "               ";
	register_trap_fn(trap_save_cause);
	while (*csrenum != csr_none) {
		save_mcause = -1;
		long value = read_csr_enum(*csrenum);
		const char* csrname = csrnames[*csrenum];
		if (save_mcause != -1) {
			printf("csr: %s%s (not supported) cause=%d\n",
				csrname, ws + strlen(csrname), save_mcause);
		} else {
			printf("csr: %s%s 0x%lx\n",
				csrname, ws + strlen(csrname), value);
		}
		csrenum++;
	}
}

int main()
{
	write_csr(mtvec, (uintptr_t)mtvec_entry);
	printf("isa: %s\n", isa_string());
	probe_all_csrs();
	printf("\n");
	return 0;
}
