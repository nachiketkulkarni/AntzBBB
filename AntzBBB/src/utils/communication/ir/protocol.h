#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define STOP            "0"
#define RUN             "1"

/* Time to send in usecs */
#define	SIGNATURE	4800000
#define ONE		2400000
#define ZERO		1200000
#define NOSEND		1200000

#define MAX_PERIOD	"26315"	// 38 kHZ = 26315 ns
#define DUTY		"13157"	// MAX_PERIOD / 2

#endif	// _PROTOCOL_H_
