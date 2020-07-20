#define _GNU_SOURCE
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

char s[1000002];
static bool zeros[1000002];
static bool twos[1000002];

int main(int argc, char **argv) {
	char *sp=s;
	size_t buffer_size=sizeof s;
	ssize_t const people=getline(&sp, &buffer_size, stdin)-1;
	s[people]=0;
	{
		int val, left_zero, right_zero;

		for(int i = 0; i < people; ++i) {
			val = s[i] - '0';
			zeros[i] = val == 0 ? true : false;
			twos[i] = val > 1 ? true : false;
		}

		for(int i = 0; i < people; ++i) {
			left_zero = right_zero = -1;
			if (twos[i]) {
				if (zeros[i]) {
					zeros[i] = false;
				} else {
					for(int j = i -1; j > -1; j--) {
						if (zeros[j]) {
							left_zero = j;
							break;
						}
					}
					for(int j = i + 1; j < people; j++) {
						if (zeros[j]) {
							right_zero = j;
							break;
						}
					}
					if (left_zero > -1) {
						zeros[left_zero] = false;
					}
					if (right_zero > -1) {
						zeros[right_zero] = false;
					} else {
						right_zero = people;
					}

					twos[i] = false;
					zeros[left_zero + right_zero - i] = true;
				}
			}
		}

		for(int k = 0; k < people; ++k) {
			putchar(zeros[k] ? '0' : '1');
		}
		putchar('\n');
	}
	return 0;
}
