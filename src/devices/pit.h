#ifndef _PIT_H
#define _PIT_H

#include "types.h"


class PIT{
    private:
    uint_16 counters[3];    //canals 0-2
    uint_16 reload[3];      //
    uint_8 control_word;    //
    uint_8 access_mode[3];  //
    bool latched[3];        //
    uint_8 output[3];       //
}; 
#endif