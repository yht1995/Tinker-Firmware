#ifndef __CMDPROCESS_H_
#define __CMDPROCESS_H_

#include <mbed.h>
#include "cmdline/cmdline.h"

int SubscribeHandler(int argc, char *argv[]);
int EnableHandler(int argc, char *argv[]);
int SetSpeedHandler(int argc, char *argv[]);
int SetPosHandler(int argc, char *argv[]);
#endif
