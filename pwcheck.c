#include <stdio.h>
#include <stdlib.h>
#define VEL 200

typedef char poleCharu[VEL];

/*

funkce vypis_heslo vypise heslo.

*/

void vypis_heslo(poleCharu vstup)
{
    for (int i = 0; vstup[i] != '\0'; i++)
    {
        putchar(vstup[i]);
    }
    printf("\n");
}

/*

funkce resetuj_heslo vymaze ulozene heslo.

*/

void resetuj_heslo(poleCharu vstup)
{
    for (int i = 1; vstup[i] != '\0'; i++)
    {
        vstup[i] = 0;
    }
}

/*

MSL - MyStringLengh vrati mi delku stringu.

*/

int MSL(poleCharu vstup)
{
    int lengh = 0;
    while (vstup[lengh] != '\0')
    {
        lengh++;
    }
    return lengh;
}

/*

Funkce level nam zkontroluje zda argument level je z validnich hodnot a pokud neni vrati -1

*/

int level(char **vstup)
{
    int navrat=0;
    for (int i = 0; vstup[1][i]!='\0' ; i++)
    {
            navrat = navrat * 10 + vstup[1][i] - '0';;
    }
    if (navrat>4 || navrat<1)
    {
        navrat = -1;
        fprintf(stderr, "ERROR_LVL bezpecnosti neni validni hodnota \n ");
    }

    return navrat;
}

/*

funkce param nam otestuje, zda je param z validnich hodnot a vrati nam ciselnou hodnotu paramu

*/

long long int param(char **vstup)
{
    long long int navrat=0;
    for (long long int i = 0; vstup[2][i]!='\0' ; i++)
    {   if (vstup[2][i] >='0' && vstup[2][i] <= '9')
        {
            navrat = navrat * 10 + vstup[2][i] - '0';
        }
        else
        {
            break;
        }
    }
    if (navrat<1)
    {
        navrat = 0;
        fprintf(stderr, "ERROR_Param neni validni hodnota \n ");
    }

    return navrat;
}
/*

funkce IsStatOn nam zda je spravne zadan argument na statistiku
*/

int IsStatOn(char **vstup)
{
    char stat[] = "--stats";
    int i = 0;
    int navrat = 1;
    while (vstup[3][i] != '\0')
    {
        if (vstup[3][i] != stat[i])
        {
            navrat = -1;
            return navrat;
        }
        i++;
    }
    return navrat;
}
/*

funkce provedStatistiku nam provede statistiku

*/


void provedStatistiku(poleCharu vstup, poleCharu ncharsArray, int *nchars, int *min, float *avglen, float *avgcount, float *avg)
{
    /*

    ve avg vemu maximalni delky znaku a podelim je poctem hesel

    */

    *avglen = MSL(vstup) + *avglen;
    *avgcount = *avgcount + 1;
    *avg = (*avglen / *avgcount);

    /*

    ve min spocitam vsechny znaky a porovnam je s min, pokud je min vetsi prohodim ho.

    */

    int isMin = MSL(vstup);

    if (*min != 0)
    {
        if (*min > isMin)
        {
            *min = isMin;
        }
    }

    else
    {
        *min = isMin;
    }

    /*

    nchars si zjistim tak, ze vsechny znaky nactu do pole, promazu duplicitni znaky a nasledne je spocitam

    */

    if (ncharsArray[0] == '\0')
    {
        for (int i = 0; vstup[i] != '\0'; i++)
        {
            ncharsArray[i] = vstup[i];
        }
    }

    else
    {
        int delkaNchar = MSL(ncharsArray);

        for (int i = 0; vstup[i] != '\0'; i++)
        {
            ncharsArray[i + delkaNchar] = vstup[i];
        }
    }

    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; ncharsArray[j + 1] != '\0'; j++)
        {
            if (ncharsArray[j + 1] < ncharsArray[j])
            {
                int tmp = ncharsArray[j + 1];
                ncharsArray[j + 1] = ncharsArray[j];
                ncharsArray[j] = tmp;
            }
        }
    }

    for (int i = 0; i < 200 - 1; i++)
    {
        for (int j = 0; ncharsArray[j + 1] != '\0'; j++)
        {
            if (ncharsArray[j] == ncharsArray[j + 1])
            {
                ncharsArray[j + 1] = ncharsArray[j + 2];
            }
        }
    }
    *nchars = MSL(ncharsArray);
}

/*

Prvni pravidlo zkontroluje zda text obsahuje aspon jedno male pismenko a jedno velke pismenko.

*/

int pravidlo1(poleCharu vstup)
{
    int malePismenka = 0;
    int velkePismenka = 0;
    int pravdivost = 0;
    for (int i = 0; vstup[i] != '\0'; i++)
    {
        if ((vstup[i] >= 'a') && (vstup[i] <= 'z'))
        {
            malePismenka = 1;
        };
        if ((vstup[i] >= 'A') && (vstup[i] <= 'Z'))
        {
            velkePismenka = 1;
        };
    }
    pravdivost = malePismenka + velkePismenka;
    if (pravdivost == 2)
    {
        return pravdivost;
    }
    else
    {
        return 0;
    }
}

/*

Druhe pravidlo kontroluje zda heslo je aspon z X skupin, ale protoze prvni pravidlo uz dve skupiny kontroluje, staci nam zavolat prvni pravidlo a zkontrolovat zbytek

*/

int pravidlo2(poleCharu vstup, int param)
{
    int cisla = 0;
    int specialniZnaky = 0;
    int pravdivost = 0;
        if (pravidlo1(vstup) == 2)
        {
            pravdivost = 2;
            for (int i = 0; vstup[i] != '\0'; i++)
            {
                if ((vstup[i] >= '0') && (vstup[i] <= '9'))
                {
                    cisla = 1;
                };
                if (((vstup[i] >= ' ') && (vstup[i] <= '/')) || ((vstup[i] >= ':') && (vstup[i] <= '@')) || ((vstup[i] >= '[') && (vstup[i] <= '`')) || ((vstup[i] >= '{') && (vstup[i] <= '~')))
                {
                    specialniZnaky = 1;
                };
            }
        }
        pravdivost = pravdivost + cisla + specialniZnaky;
        if (param > 4)
        {
            param = 4;
        }

        if (pravdivost >= param)
        {
            return 1;
        }
        else
        {
            return 0;
        }
}

/*

treti pravidlo kontroluje zda se neopakuji nektere znaky za sebou vickrat nez je limituje parametr.

*/

int pravidlo3(poleCharu vstup, int param)
{
    int pocitadloSekvence = 0;
    int pravdivost = 0;
    if (pravidlo2(vstup, param) == 1)
    {
        if (param == 1)
        {
            return pravdivost;
        }

        for (int i = 0; vstup[i] != '\0'; i++)
        {
            if (vstup[i] == vstup[i + 1])
            {
                pocitadloSekvence++;
                if (pocitadloSekvence == param - 1)
                {
                    pravdivost = 1;
                }
            }
            else
            {
                pocitadloSekvence = 0;
            }
        }
    }
    else
    {
        return 0;
    }
    if (pravdivost == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*

ctvrte pravidlo nam kontroluje zda nejaky podretec se neobjevuje v hesle dvakrat.

cast hesla o velikosti param si nactu do pomocneho pole a srovnavam s puvodnim polem

testuju to ale az o jednu pozici dal nez co nacitam do testovaciho pole

neni potreba testovat pozdejsi casti hesla s kusy co jsou pred ni protoze algoritmus by uz drive odhalil ze se opakuji.

Testovaci pole potom opakovane testuji na zbytku hesla

pokud algoritmus nalezne stejnou cast hesla jako v testovacim poli vrati nam -1

*/

int pravidlo4(poleCharu vstup, int param)
{

    int pravdivost = 1;
    if (pravidlo3(vstup, param) == 1)
    {
        int posun = 0;
        poleCharu testovaciPole;
        int opakuj = 0;
        while (opakuj < (MSL(vstup) - param))
        {
            int test = 0;
            int indexTestPole = 0;
            while (indexTestPole < param)
            {
                testovaciPole[indexTestPole] = vstup[opakuj + indexTestPole];
                indexTestPole++;
                testovaciPole[param] = '\0';
            }
            posun = opakuj;

            while (posun < (MSL(vstup) - param))
            {
                if (vstup[posun + 1] == testovaciPole[0])
                {
                    for (int testsubstringu = 0; testsubstringu < MSL(testovaciPole); testsubstringu++)
                    {
                        if (vstup[posun + 1 + testsubstringu] == testovaciPole[testsubstringu])
                        {
                            test++;
                            if (test == param)
                            {
                                pravdivost = -1;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    test = 0;
                }
                posun++;
            }
            opakuj++;
        }
    }
    else
    {
        pravdivost = -1;
    }
    return pravdivost;
}

int main(int argc, char *argv[])
{
poleCharu ncharsArray;
int nchars = 0;
int min = 0;
float avglen = 0;
float avgcount = 0;
float avg = 0;

    /*

    detekce zda je zadany spravny pocet argumentu

    minimalni pocet argumentu zde, je 3 a maximalni 4

    vse mimo tenhle rozsah bude chyba

    */

    if ((argc == 3) || (argc == 4))
    {
    }
    else
    {
        fprintf(stderr, "ERROR_Nespravny pocet parametru \n");
        return -1;
    }

    /*

    detekce zda argumenty level a param je z validnich hodnot

    */

    if (level(argv) == -1)
    {
        return -1;
        fprintf(stderr,"level je neplatna hodnota \n");
    }

    if (param(argv) == 0)
    {
        return -1;
        fprintf(stderr, "param je neplatna hodnota\n");
    }

    /*

    nacteni hesla a nasledna manipulace s nim

    */

    int vstupni_text;
    poleCharu heslo;
    int index = 0;

    while ((vstupni_text = getchar()) != EOF)
    {
        heslo[index] = vstupni_text;
            //test zda heslo neni delsi nez povoleny znaky
            if (index >= 101)
            {
                fprintf(stderr, "ERROR_Heslo je prilis dlouhe");
                return -1;
            }
        if (heslo[index] == '\n')
        {
            heslo[index] = '\0';
            //v tomto bode to nacetlo prvni heslo vcetne znaku \n, ktere sme nasledne nahradily za \0
            //dale testujeme jestli chceme statistiku, drive to nemelo smysl protoze sme nemely heslo na kterem by sme tu statistiku delaly
            if (argc == 4)
            {
                if (IsStatOn(argv) == 1)
                {
                    provedStatistiku(heslo, ncharsArray, &nchars, &min, &avglen, &avgcount, &avg);
                }
                else
                {
                    fprintf(stderr,"ERROR_Neplatny argument --stats");
                    return -1;
                }
            }

            //v tomhle bode se zacnou aplikovat pravidla podle zadaneho lvlu
            switch (level(argv))
            {
            case 1:
                if (pravidlo1(heslo) == 2)
                {
                    vypis_heslo(heslo);
                    resetuj_heslo(heslo);
                    index = -1;
                }
                else
                {
                    resetuj_heslo(heslo);
                    index = -1;
                }
                break;
            case 2:
                if (pravidlo2(heslo, param(argv)) == 1)
                {
                    vypis_heslo(heslo);
                    resetuj_heslo(heslo);
                    index = -1;
                }
                else
                {
                    resetuj_heslo(heslo);
                    index = -1;
                }
                break;
            case 3:
                if (pravidlo3(heslo, param(argv)) == 1)
                {
                    vypis_heslo(heslo);
                    resetuj_heslo(heslo);
                    index = -1;
                }
                else
                {
                    resetuj_heslo(heslo);
                    index = -1;
                }
                break;
            case 4:
                if (pravidlo4(heslo, param(argv)) == 1)
                {
                    vypis_heslo(heslo);
                    resetuj_heslo(heslo);
                    index = -1;
                }
                else
                {
                    resetuj_heslo(heslo);
                    index = -1;
                }
                break;
            }

        }
        index++;
    }
    //vypsani statistiky na konci kodu.
    if (argc == 4)
    {

        if (IsStatOn(argv) == 1)
        {
            printf("Statistika:\n");
            printf("Ruznych znaku: %d\n", nchars);
            printf("Minimalni delka: %d\n", min);
            printf("Prumerna delka: %0.1f\n", avg);
        }
    }

    return 0;
}
