#include ".\Stack_accessories\stack_defense_includes.h"
#include ".\Stack_accessories\stack_defense_constsstructures.h"
#include ".\Stack_accessories\stack_defense_prototypes.h"

//---------------------------------------------------------------------------- start of main

int main(){

    Stack * S = NULL;

    Stack stk = {};

    StackDUMP(&stk);

    StackCtor(&stk);

    StackDUMP(&stk);

    StackPush(&stk, 40);
    StackDUMP(S);

    StackPush(&stk, 41);
    StackDUMP(&stk);

    StackPush(&stk, 42);
    StackDUMP(&stk);

    StackPop(&stk);
    StackDUMP(&stk);

    printf("%100d\n", StackPop(&stk));
    StackDUMP(&stk);

    StackDtor(&stk);


    printf("1EEEEEEEEEEEEEEEeeeedfsdgdsf\n");

}

//---------------------------------------------------------------------------- end of main


