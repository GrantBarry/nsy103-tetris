


#include <stdio.h>

int main(void) {
	float ai_height_weight = 1.0;
	float ai_line_weight = -20.0;
	float ai_empty_blocks_weight = 10.0;
	char command_line[1024];

	for (ai_height_weight = 0.1; ai_height_weight < 10.0; ai_height_weight+=0.1) {
		for (ai_line_weight = -50.0; ai_line_weight < 5.0; ai_line_weight+=1.0) {
			for (ai_empty_blocks_weight = 0.0; ai_empty_blocks_weight < 50.0; ai_empty_blocks_weight+=0.5) {
				sprintf(command_line, "./bin/gba_tetris -s 1.1.1.1 -h %f -l %f -e %f", ai_height_weight, ai_line_weight, ai_empty_blocks_weight);
				system(command_line);
			}
		}
	}

	return 0;
}
