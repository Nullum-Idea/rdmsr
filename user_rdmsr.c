#include <stdio.h>

#include "rdmsr.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

int main(void)
{
	printf("Hello, user space!\n");

	static const uint64_t msr[] = {MSR_MICROCODE_VERSION, MSR_SYSCALLTABLE_COMPAT, MSR_TIMESTAMP_COUNTER};
	for (int i = 0; i < ARRAY_SIZE(msr); i++){
  	uint64_t value = __assembly_rdmsr(msr[i]);
  	printf("value at %lu = %lu\n", msr[i], value);
	}

	printf("Goodbye, user space!\n");
	return 0;
}
