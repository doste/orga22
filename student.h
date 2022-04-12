#ifndef STUDENT_H
#define STUDENT_H

#define NAME_LEN    21
#define NUM_CALIFICATIONS   3

#include "stack.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

extern stack_t *stack;

typedef struct student
{
    char name[NAME_LEN];                        // 21
    uint32_t dni;                               // 4
    uint8_t califications[NUM_CALIFICATIONS];   // 3
    int16_t concept;                            // 2
} student_t;
//sizeof(student_t) = 36


typedef struct studentp
{
    char name[NAME_LEN];
    uint32_t dni;
    uint8_t califications[NUM_CALIFICATIONS];
    int16_t concept;
} __attribute__((packed)) studentp_t;
// sizeof(studentp_t) = 30

/* A definir en student.c */
void printStudent();
void printStudentp();

#endif