#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>

void paging_init(void);
void page_fault_handler(uint32_t error_code, uint32_t fault_addr);

#endif
