#ifndef PROTOTYPES
#define PROTOTUPES

#include "..\Stack_accessories\stack_defense_includes.h"
#include "..\Stack_accessories\stack_defense_constsstructures.h"

#define Name(variable) #variable

#define Set_Red_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4)
#define Set_Blue_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3)
#define Set_White_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15)
#define Set_Blue_on_Blue_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),19)
#define Set_Green_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2)
#define Set_Yellow_Colour SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6)

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
int Stk_offset(Stack * stk);

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

//hash
unsigned long Hash(const Stack *stk);

#endif