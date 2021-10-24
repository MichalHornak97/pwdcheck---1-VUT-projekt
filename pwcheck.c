#include <stdio.h>
#include <stdlib.h>
#define VEL 101

typedef char poleCharu[VEL];

void vypis_heslo(poleCharu vstup)
{
    for(int i = 0; vstup[i] != '\0'; i++)
    {
        putchar(vstup[i]);
    }
}

void resetuj_heslo(poleCharu *vstup)
{
    for(int i = 0; *vstup[i] != '\0'; i++)
    {
        *vstup[i]=0;
    }
}


int main()
{
    int vstupni_text;
    poleCharu heslo;
    int index = 0;

    while((vstupni_text = getchar()) != EOF)
    {
        heslo[index]=vstupni_text;
	
        if(heslo[index]=='\n')
        {
            if(index>=VEL)
            {
            index = -1;
            resetuj_heslo(&heslo);
            }
            else{
            vypis_heslo(heslo);
            index = -1;
            resetuj_heslo(&heslo);
            }
        }
	index++;        
    }

    return 0;
}
