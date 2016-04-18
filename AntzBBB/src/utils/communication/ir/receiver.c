#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#include "protocol.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>


typedef enum {INIT, NOSIG, BEGIN, DONE, END} sig_state;

#define TOLERANCE		0.27
#define LOW_LEN(ns)		(int) (ns * (1.0 - TOLERANCE))
#define HIGH_LEN(ns)		(int) (ns * (1.0 + TOLERANCE))
#define NSEC_TO_USEC(ns)	(int) (ns / 1000)	

struct timespec ts_diff(struct timespec old, struct timespec new);
int arr[9] = {44, 44, 44, 44, 44, 44, 44, 44, 44};

int
main()
{
	int epfd, ready, fd, s, j, numOpenFds;
	struct epoll_event ev;
	struct epoll_event events;
	int count = 0;
	struct timespec start, end, diff[9];
	sig_state state = NOSIG;
	int usec = 0;
	int i = 0;

	char *file = "/sys/class/gpio/gpio30/value";

	memset(&start, 0, sizeof(struct timespec));
	memset(&end, 0, sizeof(struct timespec));
	memset(&diff, 0, sizeof(struct timespec));
	epfd = epoll_create(5);
	if (epfd == -1) {
		fprintf(stderr, "epoll_create() failed\n");
		exit(EXIT_FAILURE);
	}

	fd = open(file, O_NONBLOCK | O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open() failed\n");
		strerror(errno);
		exit(EXIT_FAILURE);
	}

	ev.events = EPOLLIN | EPOLLET | EPOLLPRI;
	ev.data.fd = fd;

	if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
		fprintf(stderr, "epoll_ctl() failed\n");
		exit(EXIT_FAILURE);
	}


	while(1) {
		ready = epoll_wait(epfd, &events, 1, -1);
		if (ready == -1) {
			if (errno == EINTR) {
				fprintf(stderr, "SIGINT received\n");
				exit(EXIT_FAILURE);
			} else {
				fprintf(stderr, "epoll_wait() failed\n");
				exit(EXIT_FAILURE);
			}
		}

		if (ev.events & EPOLLIN) {
			if (state == NOSIG) {
				state = BEGIN;
				continue;
			} else if (state == BEGIN) {
				clock_gettime(CLOCK_REALTIME, &start);
				state = END;
				continue;
			} else if (state == END) {
				clock_gettime(CLOCK_REALTIME, &end);
				
				diff[i] = ts_diff(start, end);
				if (diff[i].tv_nsec >= LOW_LEN(SIGNATURE) && diff[i].tv_nsec <= HIGH_LEN(SIGNATURE)) {
					arr[i] = 200;
			        } else if (diff[i].tv_nsec >= LOW_LEN(ONE) && diff[i].tv_nsec <= HIGH_LEN(ONE)) {
		            		arr[i] = 1;
		    		} else if (diff[i].tv_nsec >= LOW_LEN(ZERO) && diff[i].tv_nsec <= HIGH_LEN(ZERO)) {
	                 		arr[i] = 0;
				}
				
				++i;
				state = BEGIN;
				if (i == 9) {
					for (cnt = 1; cnt < 9; cnt++) {
						mask |= arr[cnt];
						mask <<= cnt - 1;
						num_received |= mask;
						mask = 0;
					}
					printf("Received: %d", num_received);
					for (cnt = 0; cnt < 9; cnt++) {
						arr[cnt] = 44;
					}
					if (num_received == 0) {
						printf("breaking\n");
						break;
					}
					num_received = 0;
					mask = 0;
					i = 0;

					continue;
				}
			}
		} else if (ev.events & (EPOLLHUP | EPOLLERR)) {
			if (close(ev.data.fd) == -1) {
				fprintf(stderr, "close() failed\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	return 0;
}

struct timespec
ts_diff(struct timespec old, struct timespec new)
{
	struct timespec ts_diff;

	if (old.tv_nsec > new.tv_nsec) {
		ts_diff.tv_nsec = (1E9 - old.tv_nsec) + new.tv_nsec;
		ts_diff.tv_sec = new.tv_sec - (old.tv_sec + 1);
	} else {
		ts_diff.tv_nsec = new.tv_nsec - old.tv_nsec;
		ts_diff.tv_sec = new.tv_sec - old.tv_sec;
	}

	return ts_diff;
}
