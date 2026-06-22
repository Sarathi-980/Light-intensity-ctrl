#ifndef LDR_H
#define LDR_H

#include "adc.h"
#include "f103c6t6_regs.h"


#define LDR_DARK_THRESHOLD       (1200U)
#define LDR_BRIGHT_THRESHOLD     (3000U)

typedef enum {
    DAYLIGHT_DARK = 0U,
    DAYLIGHT_LOW_BRIGHT,
    DAYLIGHT_BRIGHT
}   daylight_t;

daylight_t daylight_status();

#endif