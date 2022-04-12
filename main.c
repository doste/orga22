#include <stdio.h>
#include <stdlib.h>


#include "stack.h"
#include "student.h"

stack_t *stack;

int main()
{
    stack = createStack(100);

    student_t stud1 = {
        .name = "Steve Balmer",
        .dni = 12345678,
        .califications = {3,2,1},
        .concept = -2,
    };

    studentp_t stud2 = {
        .name = "Linus Torvalds",
        .dni = 23456789,
        .califications = {9,7,8},
        .concept = 1,
    };


    uint32_t *studp;

    // Hint: ver 'createFrame'
    stack->createFrame(stack);


    // Push student stud2

    // stud2Dir es un puntero a uint32_t (4bytes) entonces el compilador ya sabe que cuando
    // hacemos *(stud2Dir + 3) ese +3 seria sumarle 3 posiciones de 4 bytes cada una
    // entonces sabemos que el miembro name de stud2 esta en los primeros 21 bytes, bueno
    // pero podemos movernos de a 4 nomas, entonces para el name vamos atener que agarrarnos los 24 bytes
    // pero a la vez entre el byte 21 y byte 25 esta el miembro dni, y entre 25 y 28 califications
    // y entre 28 y 30 concept
    // 30 bytes no nos podemos agarrar (no es multiplo de 4) entonces nos agarramos 32 

    uint32_t student2Parts = (sizeof(studentp_t) / sizeof(uint32_t) ) + 1;
    //uint32_t student2Parts = 8;
    uint32_t *stud2Dir = (uint32_t *)&stud2;
    for (int i = student2Parts - 1; i >= 0; i--) {
        stack->push(stack, *(stud2Dir + i));
    }


    // Push random value
    uint32_t value = 42;
    stack->push(stack,value);

    // createFrame para el stud1
    stack->createFrame(stack);

    // Push student stud1
    uint32_t student1Parts = sizeof(student_t) / sizeof(uint32_t);
    uint32_t *stud1Dir = (uint32_t *) &stud1;
    for (int i = student1Parts - 1; i >= 0; i--) {
        stack->push(stack, *(stud1Dir+i));
    }

    //printf("en main() despues de pushear todo esp apunta a %p\n", stack->esp);
    // aca marca una direccion que cuando le resto a la direccion que tenia el esp en createStack, me da 176
    // 176 / 4 = 44 osea me da bien. hice 44 pusheadas en total


    // Print student st1 y st2

    void (*prStudpt)() = printStudent;
    myCall(stack, prStudpt);

    //printStudent();

    // A qué apunta el esp???
    //printf("en main() esp apunta a %p\n", stack->esp);

    // al valor 42 pusheado antes de stud1
    // lo imprimo desde aca mismo
    uint32_t val = stack->pop(stack);
    
    //uint32_t val = stack->ebp - 36;
    //uint32_t val = *((stack->esp)-1);
    printf("Valor: %d\n----------\n", val);

    //stack->pop(stack);






    prStudpt = printStudentp;
    myCall(stack, prStudpt);

    //printStudentp();

    //printf("en main() despues de todo ebp apunta a %p\n", stack->ebp);


    free(stack); // Alcanza?

    // no
    free(stack->_stackMem);

    return 0;
}
