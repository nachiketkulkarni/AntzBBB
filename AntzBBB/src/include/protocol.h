/*
 * This protocol and some of the IR communication code is taken from
 * original protocol and code developed by Zhi Xing and Gaurav Roy Puli.
 * The original implementation can be found at:
 * 	https://github.com/zxing01/Antz/tree/master/Antz/component
 */

#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define STOP            "0"
#define RUN             "1"

/* Time to send in usecs */
#define	SIGNATURE	1200000	
#define ONE		600000	
#define ZERO		300000	
#define NOSEND		300000	

#define MAX_PERIOD	"26315"	// 38 kHZ = 26315 ns
#define DUTY		"13157"	// MAX_PERIOD / 2  

#endif	// _PROTOCOL_H_
