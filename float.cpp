#include <fenv.h>
#include <math.h>
#include <stdio.h>
#pragma STDC FENV_ACCESS on

int main()
{
    fesetround(FE_UPWARD);
    float x = 0;
    for (int i = 0; i < (1 << 25); ++i)
    {
        ++x;
    }
    printf("%f\n", x);
}
