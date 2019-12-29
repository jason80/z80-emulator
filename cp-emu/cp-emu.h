#ifndef __CP_EMU_H
#define __CP_EMU_H

#include <inttypes.h>

typedef struct {
	uint16_t program_start;
} config_t;

extern config_t config;

int load_config(int argc, char** argv);

#endif
