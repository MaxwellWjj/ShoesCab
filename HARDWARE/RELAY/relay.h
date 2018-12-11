#ifndef _RELAY_H_
#define _RELAY_H_

#include "public.h"
#include "sys.h"

#define Anion1 PCout(0)	// Anion1
#define Anion2 PCout(2)	// Anion2

#define Heat PCout(1)	// Heat

#define Light1 PFout(14)	// Light1
#define Light2 PFout(15)	// Light2

void Relay_Init(void);



#endif
