#ifndef CONSTSSTRUCTURES
#define CONSTSSTRUCTURES

#include "..\Stack_accessories\stack_defense_includes.h"

int const POISON_ = INT_MAX;
unsigned long long int const Canary_value = ULONG_MAX;
long long const Default_Stack_Lenth = 8;
const unsigned long Hash_Default = 5381;

typedef int Every_type;
typedef unsigned long long int Type_of_canary;

int const Exaggeration = 2;
enum Errors {Non_info = -1, Everything_is_correct = 1, There_is_an_error = 0};
enum Print {print, not_print};

struct Stack{

    Type_of_canary canary1 = Canary_value;

    Every_type* data = NULL;

    size_t capacity = -1;
    size_t exile = -8;

    unsigned long hash = POISON_;

    Type_of_canary canary2 = Canary_value;
};

#endif