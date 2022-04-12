#include "stack.h"
#include <stdlib.h>

uint32_t pop(stack_t *stack)
{
    uint32_t value = *(stack->esp);
    if (stack->esp < stack->ebp)
        stack->esp += 1;
    return value;
}

void push(stack_t *stack, uint32_t data)
{
    //printf("push\n");        // hace 44 push en total
    stack->esp -= 1;
    *(stack->esp) = data;
}

void createFrame2(stack_t *stack)
{
    unsigned numStackPos = sizeof(stack->ebp) / sizeof(uint32_t);

    printf("sizeof(stack->ebp) = %zu\n", sizeof(stack->ebp));

    uint32_t* ebpDir = (uint32_t *) &(stack->ebp);

    printf("ebpDir = %p\n", ebpDir);
    printf("stack->ebp = %p\n", stack->ebp);
    printf("*ebpDir = %p\n", *ebpDir);

    uint32_t * tempEsp = stack->esp;

    printf("tempEsp = %p\n", tempEsp);

    printf("data a pushear = %d\n", ebpDir[0]);
    printf("data a pushear = %d\n", ebpDir[1]);

    for (int i=0; i<numStackPos; ++i) {
        stack->push(stack, ebpDir[i]);
        printf("stack->esp = %p\n", stack->esp);
    }

    
    printf("stack->ebp despues = %p\n", stack->ebp);

    printf("stack->esp despues = %p\n", stack->esp);


    stack->ebp = tempEsp;

    printf("stack->ebp al final  = %p\n", stack->ebp);

    printf("stack->esp al final = %p\n", stack->esp);
}

void createFrame(stack_t *stack)
{
    // quiero calcular cuantos bloques del stack voy a necesitar para
    // guardar la addrr del ebp
    // cada bloque del stack mide 32bit(4bytes) y la addrr es un puntero
    // asique mide 8 bytes entonces voy a necesitar 2 bloques
    // numStackPos = 2
    unsigned numStackPos = sizeof(stack->ebp) / sizeof(uint32_t);

    // ebpDir apunta a la addrr del stack->ebp (que a la vez es un puntero)
    uint32_t* ebpDir = (uint32_t *) &(stack->ebp);

    //printf("stack->ebp = %p\n", stack->ebp);       
    //printf("*ebpDir = %p\n", *ebpDir);
    //printf("sizeof(*ebpDir) = %zu\n", sizeof(*ebpDir));

    // para ver bien el problema:
    // cuando hago ese printf me da: stack->ebp = 0x559aec98f46c
    // y *ebpDir = 0xec98f46c
    // entonces justamente ahi esta el problema. ebpDir solo me puede
    // guardar la mitad de toda esa addrr
    // sizeof(*ebpDir) = 4 y sizeof(&(stack->ebp)) = 8

    // entonces lo que tengo que hacer es: guardarme esa addrr
    // no solo en el ebpDir, sino tambien en la posicion de memoria
    // contigua a ebpDir, osea ebpDir+1

    // y al stack pusheo eso

    //printf("*(ebpDir+1) = %p\n", *(ebpDir+1) );
    //printf("sizeof(*(ebpDir+1)) = %zu\n", sizeof(*(ebpDir+1)));
    // siguiendo con el ejemplo de arriba, ahora
    // *(ebpDir+1) = 0x559a
    // y sizeof(*(ebpDir+1)) = 4
    // osea la otra mitad

    uint32_t * tempEsp = stack->esp;

    for (int i=0; i<numStackPos; ++i) {
        stack->push(stack, ebpDir[i]);
    }

    stack->ebp = tempEsp;
    
    //printf("stack->ebp al final  = %p\n", stack->ebp);

    //printf("stack->esp al final = %p\n", stack->esp);
}

stack_t * createStack(size_t size)
{
    stack_t *stack = malloc(sizeof(stack_t));

    size_t totalSize = size * sizeof(uint32_t);

    stack->_stackMem = malloc(totalSize);
    stack->ebp = stack->_stackMem + size - 1;  // La base del stack es la dirección más grande.
    stack->esp = stack->ebp;

    stack->pop = pop;
    stack->push = push;
    stack->createFrame = createFrame;

    //printf("createStack: esp : %p\n", stack->esp);
    //printf("createStack: ebp : %p\n", stack->ebp);

    return stack;
}

void myCall(stack_t *stack, void (*func)())
{
    //printf("stack->ebp entrando a myCall  = %p\n", stack->ebp);
    func();

    unsigned numStackPos = sizeof(stack->ebp) / sizeof(uint32_t);
    uint32_t* ebpDir = (uint32_t *) &(stack->ebp);

    for (int i=(numStackPos-1); i>=0; --i)
        ebpDir[i] = stack->pop(stack);

    //printf("stack->ebp saliendo de myCall  = %p\n", stack->ebp);

}
