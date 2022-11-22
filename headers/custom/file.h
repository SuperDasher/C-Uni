#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

long file_size(FILE *file)
{
	long current_position = ftell(file);
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, current_position, SEEK_SET);
	return size;
}

#endif /* FILE_H */
