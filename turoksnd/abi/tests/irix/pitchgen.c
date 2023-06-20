#include <math.h>
#include <stdio.h>

main() 
{
    int i;
    double ratio;

    printf("float _pitchTable[] = {\n");
    
    for (i = -11; i < 12; i++) {
        ratio = pow(2, ((double)i)/12.0);
        printf("\t%.10f, /* %2d\t */\n", ratio, i);
    }
    printf("};\n");
    
}
