#include "..\Stack_accessories\stack_defense_includes.h"
#include "..\Stack_accessories\stack_defense_constsstructures.h"
#include "..\Stack_accessories\stack_defense_prototypes.h"

#define DEBUG

int Debug_version(const char* stg){

    if(stg == NULL)
        return There_is_an_error;

    #ifdef DEBUG

        printf("%s", stg);

    #endif

    return Everything_is_correct;

}

int Introduction(const char* fun){

    if(fun == NULL)
        return There_is_an_error;

    #ifdef DEBUG

        printf("%s started...\n", fun);

    #endif

    return Everything_is_correct;
}

int Ending(const char* fun){

    if(fun == NULL)
        return There_is_an_error;

    #ifdef DEBUG

        printf("\t\t----%s ended...\n\n", fun);

    #endif

    return Everything_is_correct;
}

int StackCtor_long_version (Stack* stk, const char* const name){

    Set_Blue_on_Blue_Colour;

    Intro();

    Set_White_Colour;

    if (StackVer(stk, name, not_print) & (1 << 1))

        return There_is_an_error;

    stk -> capacity = Default_Stack_Lenth;

    size_t canary_size = sizeof(Type_of_canary);

    size_t lenth_of_the_stack_in_bytes = (Division(Default_Stack_Lenth, canary_size) + 2) * canary_size;

    stk -> data = (Every_type *)(malloc(lenth_of_the_stack_in_bytes));

    *(Type_of_canary *)((intptr_t) stk -> data) = Canary_value;

    stk -> data += Division(canary_size, sizeof(Every_type));

    Stk_offset(stk);

    stk -> exile = 0;

    stk -> canary1 = Canary_value;
    stk -> canary2 = Canary_value;

    stk -> hash = Hash_Default;

    Set_Blue_on_Blue_Colour;

    End();

    Set_White_Colour;

    return Everything_is_correct;
}

int StackDtor_long_version (Stack* stk, const char* const name){

    Set_Blue_on_Blue_Colour;

    Intro();

    Set_White_Colour;

    if (StackVer(stk, name, print))

        return There_is_an_error;

    free(stk -> data);

    stk -> capacity = POISON_;
    stk -> exile = POISON_;

    stk -> canary1 = 0;

    stk -> canary2 = 0;

    stk -> hash = POISON_;

    stk = NULL;

    Set_Blue_on_Blue_Colour;

    End();

    Set_White_Colour;

    return Everything_is_correct;
}

Errors Stack_push_long_version (Stack * stk, Every_type variable, const char* const name){

    Set_Blue_Colour;

    Intro();

    Set_White_Colour;

    if(StackVer(stk, name, print))
        return There_is_an_error;

    if (stk -> exile == stk -> capacity){

        stk -> capacity *= 2;
    }

    Stk_offset(stk);

    stk -> data [stk -> exile ++] = variable;

    stk -> hash = Hash(stk);

    Set_Blue_Colour;

    End();

    Set_White_Colour;

    return Everything_is_correct;

}

Every_type StackPop_long_version(Stack* stk, const char* const name){

    Set_Blue_Colour;

    Intro();

    Set_White_Colour;

    Every_type returning = POISON_;

    if(!StackVer(stk, name, print)){

        stk -> data [stk -> exile --] = POISON_;

        returning = stk -> data [stk -> exile];

        stk -> data [stk -> exile] = POISON_;

        if (stk -> exile * 4 < stk -> capacity and stk -> capacity > Default_Stack_Lenth){

            stk -> capacity /= 2;

            Stk_offset(stk);
        }
    }

    stk -> hash = Hash(stk);

    Set_Blue_Colour;

    End();

    Set_White_Colour;

    return returning;
}

int StackVerification(const Stack* stk, const char* const name,\
                      const char* const type, size_t line, const char* const fun, Print parameter){
    Set_Green_Colour;

    Intro();

    Set_White_Colour;

    unsigned int error = 0;

    if(!stk)
        error |= 1 << 1;

    else{

        if(stk -> exile > stk -> capacity)
            error |= 1 << 3;

        if(!stk -> data)
            error |= 1 << 2;

        else{

            if(* Canary_left(stk) != Canary_value)
                error |= 1 << 4;

            if(* Canary_right(stk) != Canary_value)
                error |= 1 << 5;

            if(stk -> hash != Hash(stk))
                error |= 1 << 8;
        }

        if(stk -> canary1 != Canary_value)
            error |= 1 << 6;

        if(stk -> canary2 != Canary_value)
            error |= 1 << 7;
    }


    if(parameter == print)
        Printing_errors(error, name, type, line, fun);

    Set_Green_Colour;

    End();

    Set_White_Colour;

    return error;
}

int Printing_errors(int const errors, const char* name,\
                        const char* type, size_t line, const char* fun){

    if(fun == NULL or type == NULL or name == NULL)
        return There_is_an_error;

    if(!errors){

        Set_White_Colour;

        Debug_version("----OK\n");
    }

    if(errors & (1 << 1)){

        Set_Red_Colour;

        printf("\tError in line %d, expected not-NON <\"%s\" Type \"%s\"> in function \"%s\"\n\n",\
                               line,                   name,       type,               fun);
    }

    if(errors & (1 << 2)){

        Set_Red_Colour;

        printf("\tError in line %d, expected not-NON <\"%s -> data\" Type \"%s\"> in function \"%s\"\n\n",\
                               line,                   name,               type,               fun);
    }

    if(errors & (1 << 3)){

        Set_Red_Colour;

        printf("\tError in line %d, expected  <(%s -> exile <= %s -> capacity) Type \"%s\"> in function \"%s\"\n\n",\
                               line,            name,           name,                "size_t",           fun);
    }

    if(errors & (1 << 4)){

        Set_Red_Colour;

        printf("\tError in line %d, expected correct left Canary in function \"%s\"\n\n",\
                               line,                                          fun);
    }

    if(errors & (1 << 5)){

        Set_Red_Colour;

        printf("\tError in line %d, expected correct right Canary in function \"%s\"\n\n",\
                               line,                                           fun);
    }

    if(errors & (1 << 6)){

        Set_Red_Colour;

        printf("\tError in line %d, expected  <Correct (%s -> canary1) Type \"%s\"> in function \"%s\"\n\n",\
                               line,                  name,            "Canary_value",           fun);
    }

    if(errors & (1 << 7)){

        Set_Red_Colour;

        printf("\tError in line %d, expected  <Correct (%s -> canary2) Type \"%s\"> in function \"%s\"\n\n",\
                               line,                  name,            "Canary_value",           fun);
    }

    if (errors & (1 << 8)){

        Set_Red_Colour;

        printf("\tError in line %d, expected  <Correct (%s -> hash) Type \"%s\"> in function \"%s\"\n\n",\
                               line,                  name,            "long int",           fun);
    }

    Set_White_Colour;

    return Everything_is_correct;
}

int StackDump(Stack const * stk, const char* const name, const char* const file, size_t line){

    Intro();

    if (StackVer(stk, name, print))

        return There_is_an_error;

    printf("________________________________\n\n");

    printf("Stack [%p] named \"%s\"\n\t from file main.cpp(%u)\n\t called from  %s (%u)\n"\
            , stk, name, __LINE__, file, line);

    printf("{\n\tsize = %d\n\tcapacity = %d\n\t", stk -> exile, stk -> capacity);

    Set_Yellow_Colour;

    printf("data[%p]\n\t\t", stk -> data);

    printf("{\n");

    Set_Green_Colour;

    for(size_t i = 0; i < stk -> exile; i++){

        printf("\t\t*[%u] = %d\n", i, stk -> data [i]);

    }

    for(size_t i = stk -> exile; i < stk -> capacity; i ++){

        printf("\t\t [%u] = %d (poison)\n", i, stk -> data[i]);
    }

    Set_Yellow_Colour;

    printf("\t\t}");

    Set_White_Colour;

    printf("\n}\n------------------------------------\n\n");

    End();

    return Everything_is_correct;
}

size_t Division(size_t numerator, size_t denominator){

    if(numerator % denominator)

        return numerator / denominator + 1;

    return numerator / denominator;
}

int Stk_offset(Stack * stk){

    Set_Blue_Colour;
    Intro();
    Set_White_Colour;

    size_t stk_elem_size = sizeof(Every_type);
    size_t canary_size = sizeof(Type_of_canary);


    size_t stk_in_sizes_of_canaries = Division(stk_elem_size * stk -> capacity, canary_size) + 2;
    size_t lenth_of_the_stack_in_bytes = stk_in_sizes_of_canaries * canary_size;
    size_t left_canary = ((intptr_t)stk -> data - stk_elem_size * Division(canary_size, stk_elem_size));


    stk -> data = (Every_type *) realloc((Type_of_canary *)left_canary, lenth_of_the_stack_in_bytes);

    size_t canary2 = ((intptr_t) stk -> data + (stk_in_sizes_of_canaries - 1) * canary_size);

    *(Type_of_canary *)canary2 = Canary_value;

    int real_start_of_stk = (Division((intptr_t) stk -> data + canary_size, stk_elem_size) * stk_elem_size);

    stk -> data = (Every_type*)real_start_of_stk;

    Set_Blue_Colour;
    End();
    Set_White_Colour;

    return Everything_is_correct;
}

Type_of_canary * Canary_left (const Stack* stk){

    assert(stk != NULL);
    assert(stk ->data != NULL);

    return (Type_of_canary *)((intptr_t) stk -> data / sizeof(Type_of_canary) * sizeof(Type_of_canary)) - 1;
}

Type_of_canary * Canary_right (const Stack* stk){

    Intro();

    assert(stk -> data != NULL);

    size_t canary_size = sizeof(Type_of_canary);

    size_t lenth_of_stack_in_canaries = Division(sizeof(Every_type) * stk -> capacity, canary_size) * canary_size;

    size_t canary2 = (intptr_t) stk -> data / canary_size * canary_size + lenth_of_stack_in_canaries;

    End();

    return (Type_of_canary *)canary2;
}

unsigned long Hash(const Stack *stk)
{
    if (stk == NULL || stk -> data == NULL)
        return POISON_;

    unsigned long hash = Hash_Default;

    for(size_t c = 0; c < stk -> exile; c ++)
        hash = ((hash << 5) + hash) + stk -> data [c];

    return hash;
}

