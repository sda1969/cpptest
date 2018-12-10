/*
 * cfilereadtest.cpp
 *
 *  Created on: 9 окт. 2018 г.
 *      Author: user
 */

#include <stdio.h>

namespace freadtest {

constexpr int BUFF_SIZE = 1024;
constexpr int NUM_OF_LINES = 3;

void freadtest_run(){
	FILE *fp;
	char linebuffer[BUFF_SIZE];
	int cnt = 0;
	int regpull[NUM_OF_LINES];

	if ((fp=fopen("thrs.txt", "r")) == NULL) {
		printf ("Cannot open file. thrs.txt\n");
		return;
	}

	while (!feof(fp) && (fgets(linebuffer, BUFF_SIZE, fp) != NULL)){
		printf("testline: %s", linebuffer);
		if (linebuffer[0] == '#') continue;
		int d1, d2;
		if (2 != sscanf(linebuffer, "%d %d", &d1, &d2)){
			printf("format error\n");
			return;
		}
		regpull[cnt] = ((d1 & 0x3ff) << 10) + (d2 & 0x3ff);

		if (++cnt >= NUM_OF_LINES) break;
	}
	if (cnt != NUM_OF_LINES){
		printf("not enough lines\n");
		return;
	}
	fclose(fp);

	for(int i = 0; i < NUM_OF_LINES; i++){
		printf("%08X\n", regpull[i]);
		//actual write to registers
	}

}

}


