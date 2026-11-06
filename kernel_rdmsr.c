#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>


#include "rdmsr.h"

MODULE_LICENSE("GPL");

/* This function is executed on module load, i.e. when you run:

	$ sudo insmod kernel_rdmsr.ko
*/
static int __init rdmsr_init(void) {
	printk(KERN_INFO "Hello, kernel space!\n");

	static const uint64_t msr[] = {MSR_MICROCODE_VERSION, MSR_SYSCALLTABLE_COMPAT, MSR_TIMESTAMP_COUNTER};
	for (int i = 0; i < ARRAY_SIZE(msr); i++){
  	uint64_t value = __assembly_rdmsr(msr[i]);
  	printk(KERN_INFO "value at %llu = %llu\n", msr[i], value);
	}

	return 0;
}

/* This function is executed on module unload, i.e. when you run
	$ sudo rmmod [-f] kernel_rdmsr
*/
static void __exit rdmsr_exit(void) {
	 printk(KERN_INFO "Goodbye, kernel space!\n");
}

module_init(rdmsr_init);
module_exit(rdmsr_exit);
