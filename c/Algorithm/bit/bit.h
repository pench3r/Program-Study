#ifndef __ALGORITHM_BIT__H
#define __ALGORITHM_BIT__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool IsOdd(int data);  

void ShowPrimeNum(int range);

int GetBit(unsigned char *buf, int position);

bool SetBit(unsigned char *buf, int position, int state);

void BitXor(unsigned char *buf1, unsigned char *buf2, unsigned char *buf3, int size);

#endif /* __ALGORITHM_BIT__H */
