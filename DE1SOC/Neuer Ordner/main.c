#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> //file control options
#include <sys/mman.h> //memory management declarations (mmap)
#include "hwlib.h" //??
#include "socal/socal.h" // main function, read,write etc
#include "socal/hps.h" //  HPS components
#include "socal/alt_gpio.h"
#include "hps_0.h"


#define REG_BASE 0xFF200000
#define REG_SPAN 0x00200000  // 2megabytes space

void *virtual_base;
void *led_addr;
void *sw_addr;
int fd;
int switches;
int main(){
fd=open ( "/dev/mem", (O_RDWR|O_SYNC));
virtual_base= mmap(NULL, REG_SPAN,(PROT_READ|PROT_WRITE),MAP_SHARED,fd,REG_BASE);
sw_addr= virtual_base + PIO_1_BASE;
led_addr=virtual_base+ PIO_0_BASE;

while(1){
switches=*(uint32_t *)sw_addr;
*(uint32_t *)led_addr=switches;
usleep(100*10000);
printf("%u\n", switches);
}
return 0;
}