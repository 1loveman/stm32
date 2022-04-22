#ifndef __RTC_H__
#define __RTC_H__

#include"sys.h"

extern u8 rmin,rsec;

void RTC_First_Config(void);
void RTC_Config(void);
u8 RTC_Get(void);
#endif
