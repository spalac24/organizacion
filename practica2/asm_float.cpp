#include <stdio.h>
#include <iostream>

using namespace std;

int main() {

    float arg1, arg2, add, sub, mul, div ;
    int tag = 0;
    printf( "Enter two numbers : " );
    scanf("%f %f",&arg1,&arg2);

    /* Perform floating point Addition, Subtraction, Multiplication & Division */
    __asm__ ( "fld %1;"
              "fld %2;"
              "faddp;"
              "fstp %0;" : "=m" (add) : "m" (arg1), "m" (arg2) ) ;

    __asm__ ( "fld %2;"
              "fld %1;"
              "fsubp;"
              "fstp %0;" : "=m" (sub) : "m" (arg1), "m" (arg2) ) ;

    __asm__ ( "fld %1;"
              "fld %2;"
              "fmulp;"
              "fstp %0;" : "=m" (mul) : "m" (arg1), "m" (arg2) ) ;

    __asm__ ( "fld %2;"
              "fld %1;"
              "fdivp;"
              "fstp %0;" : "=m" (div) : "m" (arg1), "m" (arg2) ) ;
    
    printf( "%f + %f = %f\n", arg1, arg2, add );
    printf( "%f - %f = %f\n", arg1, arg2, sub );
    printf( "%f * %f = %f\n", arg1, arg2, mul );
    printf( "%f / %f = %f\n", arg1, arg2, div );

    return 0 ;
}
