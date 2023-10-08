#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<limits.h>
#include<windows.h>

int const POISON_ = INT_MAX;
unsigned long long const Canary_value = ULLONG_MAX;
long long const Default_Stack_Lenth = 8;

typedef int Every_type;
typedef unsigned long long int Type_of_canary;

int const Exaggeration = 2;
enum Errors {Non_info = -1, Everything_is_correct = 1, There_is_an_error = 0};
enum Print {print, not_print};

#define Name(variable) #variable

#define Set_Red_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4)
#define Set_Blue_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3)
#define Set_White_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15)
#define Set_Blue_on_Blue_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),19)
#define Set_Green_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2)
#define Set_Yellow_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6)

struct Stack{

    Every_type* data = NULL;

    size_t capacity = -1;
    size_t exile = -8;
};

//General information
int Introduction(const char* fun);
int Ending(const char* fun);
int Debug_version(const char* stg);

#define Intro() Introduction(__FUNCTION__)
#define End() Ending(__FUNCTION__)

//Constructing and Destructing
int StackCtor_long_version (Stack* stk, const char* const name);
int StackDtor_long_version (Stack* stk, const char* const name);

#define StackCtor(on_variable) StackCtor_long_version(on_variable, Name(on_variable))
#define Checking_NULL(index, name_var, type_var) Checking_NON((int*)index, name_var, type_var, __LINE__, __FUNCTION__)
#define StackDtor(on_variable) StackDtor_long_version(on_variable, Name(on_variable))

//Pop and Push
Errors Stack_push_long_version (Stack * stk, Every_type variable, const char* const name);
Every_type StackPop_long_version(Stack* stk, const char* const name);

size_t Division(size_t numerator, size_t denominator);
int Stk_offset(Stack * stk, const char* const name);

#define StackPush(stk, variable) Stack_push_long_version(stk, variable, Name(stk))
#define StackPop(stk) StackPop_long_version(stk, Name(stk))

//Canaries
Type_of_canary * Canary_left (const Stack* stk);
Type_of_canary * Canary_right (const Stack* stk);


//Verification
int StackVerification(const Stack* stk, const char* name,\
                      const char* type, size_t line, const char* fun, Print parameter);
int Printing_errors(int const errors, const char* name,\
                        const char* type, size_t line, const char* fun);

#define StackVer(stk, name, parameter) StackVerification(stk, name, Name(Stack*), __LINE__, __FUNCTION__, parameter)

//Outputting
int StackDump(Stack const * stk, const char* const name, const char* const file, size_t line);

#define StackDUMP(stk) StackDump(stk, Name(stk), __FILE__, __LINE__)

#define DEBUG

//---------------------------------------------------------------------------- start of main

int main(){

    Stack * S = NULL;

    Stack stk = {};

    StackDUMP(&stk);

    StackCtor(&stk);

    printf("main: %p\n", stk. data);

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




}

//---------------------------------------------------------------------------- end of main

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

    *(Type_of_canary *)((int) stk -> data) = Canary_value;

    stk -> data += Division(canary_size, sizeof(Every_type));

    Stk_offset(stk, (const char* const) name);

    stk -> exile = 0;

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

    Stk_offset(stk, name);

    stk -> data [stk -> exile ++] = variable;

    //printf("\t data: %p,  e: %u,  c: %u\n", stk -> data, stk -> exile, stk -> capacity);

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

            Stk_offset(stk, name);
        }
    }

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
        }
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

    bool printed_info = false;

    if(!errors){

        Set_White_Colour;

        Debug_version("----OK\n");

        printed_info = true;
    }

    if(errors & (1 << 1)){

        Set_Red_Colour;

        printf("\tError in line %d, expected not-NON <\"%s\" Type \"%s\"> in function \"%s\"\n\n",\
                               line,                   name,       type,               fun);
        printed_info = true;
    }

    if(errors & (1 << 2)){

        Set_Red_Colour;

        printf("\tError in line %d, expected not-NON <\"%s -> data\" Type \"%s\"> in function \"%s\"\n\n",\
                               line,                   name,               type,               fun);
        printed_info = true;
    }

    if(errors & (1 << 3)){

        Set_Red_Colour;

        printf("\tError in line %d, expected  <(%s -> exile <= %s -> capacity) Type \"%s\"> in function \"%s\"\n\n",\
                               line,            name,           name,                "size_t",           fun);
        printed_info = true;
    }

    if (!printed_info){

        Set_Red_Colour;

        printf("There is an undefined error\n\n");

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

int Stk_offset(Stack * stk, const char* const name){

    Set_Blue_Colour;
    Intro();
    Set_White_Colour;

    size_t stk_elem_size = sizeof(Every_type);
    size_t canary_size = sizeof(Type_of_canary);


    size_t stk_in_sizes_of_canaries = Division(stk_elem_size * stk -> capacity, canary_size) + 2;
    size_t lenth_of_the_stack_in_bytes = stk_in_sizes_of_canaries * canary_size;
    size_t left_canary = ((int)stk -> data - stk_elem_size * Division(canary_size, stk_elem_size));


    stk -> data = (Every_type *) realloc((Type_of_canary *)left_canary, lenth_of_the_stack_in_bytes);

    size_t canary2 = ((int) stk -> data + (stk_in_sizes_of_canaries - 1) * canary_size);

    *(Type_of_canary *)canary2 = Canary_value;

    int real_start_of_stk = (Division((int) stk -> data + canary_size, stk_elem_size) * stk_elem_size);

    stk -> data = (Every_type*)real_start_of_stk;

    Set_Blue_Colour;
    End();
    Set_White_Colour;

    return Everything_is_correct;
}

Type_of_canary * Canary_left (const Stack* stk){

    return (Type_of_canary *)((int) stk -> data / sizeof(Type_of_canary) * sizeof(Type_of_canary)) - 1;
}

Type_of_canary * Canary_right (const Stack* stk){

    Intro();

    printf("stk -> capacity = %u, stk -> exile = %u, stk -> data %%p: %p\n\n",stk -> capacity, stk -> exile, stk -> data);
    assert(stk -> data != NULL);

    size_t canary_size = sizeof(Type_of_canary);

    size_t lenth_of_stack_in_canaries = Division(sizeof(Every_type) * stk -> capacity, canary_size) * canary_size;

    printf("%u\n", lenth_of_stack_in_canaries);
printf("%u\n", canary_size);

    size_t canary2 = (int) stk -> data / canary_size * canary_size + lenth_of_stack_in_canaries;

    return (Type_of_canary *)canary2;

    End();
}


