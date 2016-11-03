/*
 * Result.h
 *
 * Created: 21.01.2016 01:32:50
 *  Author: Henrik
 */ 


#ifndef RESULT_H_
#define RESULT_H_

#include <stdint.h>

typedef uint8_t RESULT;
typedef uint8_t BOOL;

#define R_OK				0
#define R_M_NOT_INIT		1 //modul not initialized
#define R_NULL				2 // pointer zu null
#define R_BUFF_NOT_READY	3
#define R_INVALID_PARAM		4
#define R_TIMEOUT			5
#define R_ALREADY_INIT		6
#define R_STRING_TO_LONG	7
#define R_ENGINE_ERROR		8

#define FAILED(r) (r != R_OK)
#define SUCCEDED(r) (r == R_OK)
#define TRUE 1
#define FALSE 0
#define NULL (void*)0

#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)

#define clamp(val, mi, ma) min(ma, max(mi, val))

void SetError(RESULT res);

#endif /* RESULT_H_ */