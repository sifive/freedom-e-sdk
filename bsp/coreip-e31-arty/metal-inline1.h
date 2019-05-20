#ifndef ASSEMBLY

#ifndef COREIP_E31_ARTY1_INLINE_H
#define COREIP_E31_ARTY1_INLINE_H

#include <metal/machine.h>

/* From global_external_interrupts */
struct __metal_driver_sifive_global_external_interrupts0 __metal_dt_global_external_interrupts = {
    .irc.vtable = &__metal_driver_vtable_sifive_global_external_interrupts0.global0_vtable,
    .init_done = 0,
};

/* --------------------- sifive_global_external_interrupts0 ------------ */
extern inline int __metal_driver_sifive_global_external_interrupts0_init_done( );
extern inline struct metal_interrupt * __metal_driver_sifive_global_external_interrupts0_interrupt_parent(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_global_external_interrupts0_num_interrupts(struct metal_interrupt *controller);
extern inline int __metal_driver_sifive_global_external_interrupts0_interrupt_lines(struct metal_interrupt *controller, int idx);


/* --------------------- sifive_gpio_button ------------ */
extern inline struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_gpio_button_gpio(struct metal_button *button);
extern inline int __metal_driver_sifive_gpio_button_pin(struct metal_button *button);
extern inline struct metal_interrupt * __metal_driver_sifive_gpio_button_interrupt_controller(struct metal_button *button);
extern inline int __metal_driver_sifive_gpio_button_interrupt_line(struct metal_button *button);
extern inline char * __metal_driver_sifive_gpio_button_label(struct metal_button *button);


/* --------------------- sifive_gpio_led ------------ */
extern inline struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_gpio_led_gpio(struct metal_led *led);
extern inline int __metal_driver_sifive_gpio_led_pin(struct metal_led *led);
extern inline char * __metal_driver_sifive_gpio_led_label(struct metal_led *led);


/* --------------------- sifive_gpio_switch ------------ */
extern inline struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_gpio_switch_gpio(struct metal_switch *flip);
extern inline int __metal_driver_sifive_gpio_switch_pin(struct metal_switch *flip);
extern inline struct metal_interrupt * __metal_driver_sifive_gpio_switch_interrupt_controller(struct metal_switch *flip);
extern inline int __metal_driver_sifive_gpio_switch_interrupt_line(struct metal_switch *flip);
extern inline char * __metal_driver_sifive_gpio_switch_label(struct metal_switch *flip);


#endif /* COREIP_E31_ARTY1_INLINE_H*/
#endif /* ! ASSEMBLY */
