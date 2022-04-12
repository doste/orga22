#include "student.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


/*  QUEREMOS IMPRIMIR:
(random value)
(stud1)
----------
(stud2)
----------


Valor: 42
Nombre: Steve Balmer
dni: 12345678
Calificaciones: 3, 2, 1,
Concepto: -2
----------
Nombre: Linus Torvalds
dni: 23456789
Calificaciones: 9, 7, 8,
Concepto: 1
----------
*/

void printStudent()
{
    //printf("al entrar a printStudent() esp apunta a %p\n", stack->esp);
    /* Imprime por consola una estructura de tipo student_t
    */
    uint32_t studentParts = sizeof(student_t) / sizeof(uint32_t); 

    uint32_t *studDir = malloc(sizeof(uint32_t) * studentParts);

    for (int i = 0; i < studentParts; i++) {
        //studDir[i] = stack->pop(stack);
        *(studDir+i) = stack->pop(stack);
    }

    student_t *stud1 = (student_t *)studDir;
    printf("Nombre: %s\n", stud1->name);
    printf("dni: %d\n", stud1->dni);
    printf("Calificaciones: ");
    for(int c = 0; c < ( sizeof(stud1->califications) / sizeof(uint8_t)); c++) {
        printf("%d, ", stud1->califications[c]);
    }
    printf("\n");
    printf("Concepto : %d\n", stud1->concept);
    printf("----------\n");

    //printf("al irse de printStudent() esp apunta a %p\n", stack->esp);
    //printf("ahi esta %d\n", *(stack->esp));
    // stack->esp se mueve 36 posiciones . perfecto

    //printf("esp saliendo de printStudent: %p\n", stack->esp);
    //printf("ebp saliendo de printStudent: %p\n", stack->ebp);
}

void printStudentp()
{
    /* Imprime por consola una estructura de tipo studentp_t
    */

    uint32_t *studDir = malloc(sizeof(uint32_t) * 8);


    for (int i = 0; i <= 8; i++) {
        //studDir[i] = stack->pop(stack);
        *(studDir+i) = stack->pop(stack);
    }
    
    //*studDir = stack->pop(stack);

    studentp_t *stud2 = (studentp_t *)studDir;
    printf("Nombre: %s\n", stud2->name);
    printf("dni: %d\n", stud2->dni);
    printf("Calificaciones: ");
    for(int c = 0; c < ( sizeof(stud2->califications) / sizeof(uint8_t)); c++) {
        printf("%d, ", stud2->califications[c]);
    }
    printf("\n");
    printf("Concepto : %d\n", stud2->concept);
    printf("----------\n");
    
}
