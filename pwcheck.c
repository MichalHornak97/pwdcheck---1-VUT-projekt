#include <stdio.h>
#include <stdlib.h>
#define VEL 101

typedef char poleCharu[VEL];

void vypis_heslo(poleCharu vstup)
{
    for(int i = 1; vstup[i] != '\0'; i++)
    {
        putchar(vstup[i]);
    }
}

void resetuj_heslo(poleCharu *vstup)
{
    for(int i = 1; *vstup[i] != '\0'; i++)
    {
        *vstup[i]=0;
    }
}


int main()
{
    int vstupni_text;
    poleCharu heslo;
    int index = 1;

    while((vstupni_text = getchar()) != EOF)
    {
        heslo[index]=vstupni_text;
	
        if(heslo[index]=='\n')
        {
            if(index>=VEL)
            {
            resetuj_heslo(&heslo);
            index = 0;
            }
            else{
            vypis_heslo(heslo);
            resetuj_heslo(&heslo);
            index = 0;
            }
        }
	index++;        
    }

    return 0;
}
