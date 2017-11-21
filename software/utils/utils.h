unsigned long mtime_lo(void);
int setringbits(int trim, int div );
unsigned long __attribute__((noinline)) cpu_freq(size_t n);
int setpllbits(int pll_r, int pll_f, int pll_q);
int setpll(unsigned long int freq);
int setpwm(int pwmno);
void print_cpu_freq();
int getprimes(unsigned long int pmax);
int getpi();
void uart_set(size_t baud_rate);
char wait_for_keypress();
char check_for_keypress();
int wait_ms(int wtime);
int turn_stuff_off();
int clock_stat();

#define BAUDRATE 115200
//#define BAUDRATE 57600

