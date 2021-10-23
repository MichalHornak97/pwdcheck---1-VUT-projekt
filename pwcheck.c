#include <stdio.h>
#define VEL 101
/***
 AlphabetTest

 Otestuje zda pole znaku obsahuje aspon jedno male a jedno velke pismenko.
 ***/
//int AlphabetTest();

int main(int argc, char **argv[])
{

    /* Nasledujici algorytmus nam nacita znaky na vstupu, nez narazi na konec radku a uklada je do pole.
     * skontroluje zda nacteny znak odpovida povolenemu znaku hned na vstupu (porovnani provadi s decimalni hodnotou znaku podla ASCII tabulky),
     pokud neodpovida ihned zahodi radek v poli.
    * otestuje zda pole neni vetsi nez 100, v pripade ze je ihned zahodi radek. */
    int c=0;
    char heslo[VEL]="0";
    while ((c = getchar()) != EOF)
    {
         printf("%c", c);
        while ((c = getchar()) != 10) /* 10 == numerická hodnota noveho radku*/
        {
                            int pozice = 0;
            if ((c = getchar()) >= 32 && (c = getchar()) <= 126)
            {
                //printf("Znak C je %c %d \n", c, c);
                heslo[pozice] = c;
                //printf("Heslo je %c %d \n", heslo[pozice], heslo[pozice]);
                //putchar(heslo[pozice]);                 
            }
            if (pozice<101)
            {
                pozice++;
            }
            else{
                break;
            }
  
        }  
    }


    if (argc >= 2 && argc < 5)
    {
        if (argv[1][0] == "2")
        {
            /* code */
        }
    }
    else
    {
        fprintf(stderr, "Error - Nepovoleny pocet argumentu!");
    }
    return 0;
}