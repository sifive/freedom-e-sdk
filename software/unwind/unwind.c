/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#if 0
int main() {
    printf("Hello, World!\n");
}
#endif
#include <unwind.h>
_Unwind_Reason_Code bt_func (struct _Unwind_Context *ct, void *arg)
{
  printf ("WTF\n");
  long addr = _Unwind_GetIP (ct);
  printf ("BT! addr=%lx\n", addr);
}
void foo(){
  printf ("start backtrace\n");
  _Unwind_Backtrace(bt_func, NULL);
  printf ("backtrace done\n");
}
int main()
{
  printf ("main\n");
  foo();
  printf ("main done\n");
  return 0;
}
