#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int main()
{
        srand((unsigned int)time(0x0));
        int counter = 53, j=0, x;
        while(counter)
        {
                do{
                        x = rand()%52;
                        printf("%d , ", x);
                } while (x <= j);
                printf("%d , ", x);
                ++j;
                x=j;
                --counter;
        }
        return 0;
}
