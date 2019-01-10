//
// benchutils.h
//
//  Contains various utility functions for bench-level testing
//  of Freedom Everywhere SOCs
//

extern uint32_t lfosc_freq;
extern int print_to_uart1;
extern void _putc();
extern uint64_t rd64cycle();
extern uint32_t lfsr32();
extern uint32_t measure_cpu_freq();
extern void hang_hfout();
extern char _getc();
extern void _puts();
extern void _puti();
extern void _puti1k();
extern void _puth();
extern int errpt ();
extern void nanosleep();
extern void wait_ms();
extern void wait_lfclicks();
extern void setringbits();
extern void setpllbits();
extern void setpll();
extern void otp_get_lock();
extern void otp_release_lock();
extern void otp_begin_write();
extern void otp_end_write();
extern void otp_write_word();
extern uint32_t otp_read_word();
extern uint32_t zap_ones();
extern uint32_t otp_write_array_once();
extern int otp_write_array();
extern uint32_t measure_lfosc_freq();
extern void bench_rstclk();
extern void uart_set();
