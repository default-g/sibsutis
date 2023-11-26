#include <stdio.h>
#include <sys/sysinfo.h>
/**
  struct sysinfo {
               long uptime;             // Seconds since boot 
               unsigned long loads[3];  // 1, 5, and 15 minute load averages 
               unsigned long totalram;  // Total usable main memory size 
               unsigned long freeram;   // Available memory size 
               unsigned long sharedram; // Amount of shared memory 
               unsigned long bufferram; // Memory used by buffers 
               unsigned long totalswap; // Total swap space size 
               unsigned long freeswap;  // Swap space still available 
               unsigned short procs;    // Number of current processes 
               unsigned long totalhigh; // Total high memory size 
               unsigned long freehigh;  // Available high memory size 
               unsigned int mem_unit;   // Memory unit size in bytes 
               char _f[20-2*sizeof(long)-sizeof(int)];
                                        // Padding to 64 bytes 
           };
 **/


int main() {

int *a

struct sysinfo system;

sysinfo(&system);

printf("Размер блока памяти в байтах : %u \n", system.mem_unit);
printf("Общий объем верхней памяти : %lu \n", system.totalhigh);
printf("Доступный объем верхней памяти : %lu \n", system.freehigh);
printf("Общий используемый объем памяти : %lu \n", system.totalram);
printf("Доступный объем памяти: %lu \n", system.freeram);
printf("Объём общей памяти: %lu \n", system.sharedram);
printf("Память буферов: %lu \n", system.bufferram);
printf("Общий размер пространства подкачки: %lu \n", system.totalswap);
printf("Доступное пространство подкачки: %lu \n", system.freeswap);


return 0;
}