#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>

#define MAX_BUF		1000
#define MAX_EVENTS	5
#define SIGNATURE       4800000
#define ONE             2400000
#define ZERO            1200000
#define NOSEND          1200000

typedef enum {INIT, NOSIG, BEGIN, END} sig_state;

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
	char buf[MAX_BUF];
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

		count++;

//		printf("fd = %d; events %s %s %s\n", ev.data.fd,
//				(ev.events & EPOLLIN) ? "EPOLLIN" : "",
//				(ev.events & EPOLLHUP) ? "EPOLLHUP" : "",
//				(ev.events & EPOLLERR) ? "EPOLLERR" : "");

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
		//			printf("signature received\n");
					arr[i] = 200;
			        } else if (diff[i].tv_nsec >= LOW_LEN(ONE) && diff[i].tv_nsec <= HIGH_LEN(ONE)) {
		            		arr[i] = 1;
	//				write(STDOUT_FILENO, ".. , ", 6);
		    		} else if (diff[i].tv_nsec >= LOW_LEN(ZERO) && diff[i].tv_nsec <= HIGH_LEN(ZERO)) {
	                 		arr[i] = 0;
	//				write(STDOUT_FILENO, "## , ", 6);
				}
				
				++i;
				if (i == 9) {
					//printf("I am breaking\n");
					break;
				}
				state = BEGIN;
			}
		} else if (ev.events & (EPOLLHUP | EPOLLERR)) {
			if (close(ev.data.fd) == -1) {
				fprintf(stderr, "close() failed\n");
				exit(EXIT_FAILURE);
			}
		}
	}

//	printf("Range for sign = %ld to % ld\n", LOW_LEN(SIGNATURE), HIGH_LEN(SIGNATURE));
//	printf("Range for one  = %ld to % ld\n", LOW_LEN(ONE), HIGH_LEN(ONE));
//	printf("Range for zero = %ld to % ld\n", LOW_LEN(ZERO), HIGH_LEN(ZERO));

	printf("\n");
	printf("\t%s ", (arr[0] == 200 ? "SIGNATURE" : ""));
	for (i = 1; i < 9; i++) {
//		printf("diff[%d].sec = %ld   ::  diff[%d].nsec = %ld\n", i, diff[i].tv_sec, i, diff[i].tv_nsec);
		printf(" %d ", arr[i]);
	}
	printf("\n\n");
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
