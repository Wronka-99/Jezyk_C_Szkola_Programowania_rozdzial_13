/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DLUGOSC 40


int main(int argc, char *argv[])
{

    FILE *plik_we, *plik_wy;
    char znak;


    if(argc!=2)
    {
        printf("Podano złą liczbę argumentow.\n");
        exit(EXIT_FAILURE);
    }


    if((plik_we=fopen(argv[1],"r"))==NULL)
    {
        printf("Nie mozna otworzyc pliku o nazwie %s. \n", argv[1]);
        exit(EXIT_FAILURE);
    }


    while((znak=getc(plik_we))!=EOF)
        putc(znak,stdout);

    rewind(plik_we);

    while((znak=getc(plik_we))!=EOF)
    {
        putchar(znak);
    }


    fclose(plik_we);
    //fclose(plik_wy);

    return 0;
}

*/



//PIERWSZE ZADANIE

/*
#include <stdio.h>
#include <stdlib.h>


int main()
{
    char znak;

    FILE *wp;
    char plik_we[40];
    unsigned long licznik=0;

    if((scanf("%s",plik_we))==0)
        puts("Nie pobrano nazwy pliku.");


    if((wp=fopen(plik_we,"r"))==NULL)
    {
        printf("Nie mozna otworzyc pliku o nazwie %s. \n", plik_we);
        exit(EXIT_FAILURE);
    }

    
    while((znak=getc(wp))!=EOF)
    {
        putc(znak,stdout);
        licznik++;
    }

    printf("Plik o nazwie %s zawiera %ld znakow. \n", plik_we, licznik);
    fclose(wp);


    return 0;
}

*/



//DRUGIE ZADANIE

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DLUGOSC 40


int main(int argc, char *argv[])
{

    FILE *plik_we, *plik_wy;
    char znak;
    unsigned long rozmiar=0;


    if(argc!=3)
    {
        printf("Podano złą liczbę argumentow.\n");
        exit(EXIT_FAILURE);
    }


    if((plik_we=fopen(argv[1],"r"))==NULL)
    {
        printf("Nie mozna otworzyc pliku o nazwie %s. \n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if((plik_wy=fopen(argv[2],"w"))==NULL)
    {
        printf("Nie mozna otworzyc pliku o nazwie %s. \n", argv[2]);
        exit(EXIT_FAILURE);
    }


    fseek(plik_we,0L,SEEK_END);
    rozmiar=ftell(plik_we);
    rewind(plik_we);

    fwrite(plik_we,sizeof(char),rozmiar,plik_wy);
    
    fclose(plik_we);
    fclose(plik_wy);

    return 0;
}


*/



//TRZECIE ZADANIE


/*
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main()
{
    int znak;
    int znak_pom;

    FILE *wp;
    FILE *wy;

    char plik_we[40];
    char plik_wy[40];


    unsigned long licznik=0;

    puts("Podaj nazwe pliku wejsciowego.");
    scanf("%s",plik_we);

    puts("Podaj nazwe pliku wyjsciowego.");
    scanf("%s",plik_wy);

    if((wp=fopen(plik_we,"r"))==NULL)
    {
        printf("Nie mozna otworzyc pliku o nazwie %s. \n", plik_we);
        exit(EXIT_FAILURE);
    }


    if((wy=fopen(plik_wy,"w+"))==NULL)
    {
        printf("Nie mozna otworzyc pliku o nazwie %s. \n", plik_wy);
        exit(EXIT_FAILURE);
    }

    
    while((znak=getc(wp))!=EOF)
    {
        if(isalpha(znak)!=false)
            znak_pom=toupper(znak);
        else
            znak_pom=znak;

        putc(znak_pom, stdout);
        fprintf(wy,"%c",znak_pom);
        licznik++;
    }

    printf("Plik o nazwie %s zawiera %ld znakow. \n", plik_we, licznik);
    fclose(wp);
    fclose(wy);


    return 0;
}

*/


//PIĄTE ZADANIE - nie działa 

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ROZMIAR_BUF 4096
#define DLAN 50

void dopisz(FILE *zrodlo, FILE *cel);
char *wczytaj(char *z, int ile);


int main(int argc, char *argv[])
{

    FILE *pd, *pz;
    int pliki=0;
    char plik_doc[DLAN];
    char plik_zro[DLAN];
    int ch;

    wczytaj(argv[2],DLAN);

    if((pd=fopen(argv[1], "a"))==NULL)
    {
        fprintf(stderr,"Blad otwarcia %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(setvbuf(pd, NULL, _IOFBF, ROZMIAR_BUF)!=0)
    {
        fputs("Nie mozna utworzyc bufora wyjsciowego\n", stderr);
        exit(EXIT_FAILURE);
    }


    while(wczytaj(argv[1], DLAN)&& *argv[1]!='\0')
    {
        if(strcmp(argv[1], argv[2])==0)
        {
            fputs("Nie mozna dopisac pliku do siebie\n", stderr);
        }
        else if((pz=fopen(argv[1], "r"))==NULL)
        {
            fprintf(stderr, "Blad otwarcia pliku %s \n ", argv[1]);
        }
        else
        {
            if(setvbuf(pz,NULL,_IOFBF, ROZMIAR_BUF)!=0)
            {
                fputs("Nie mozna utworzyc bufora wejsciowego\n", stderr);
                continue;
            }

            dopisz(pz,pd);

            if(ferror(pz)!=0)
                fprintf(stderr,"Blad odczytu pliku %s \n", argv[1]);

            if(ferror(pd)!=0)
                fprintf(stderr,"Blad odczytu pliku %s \n", argv[2]);

            fclose(pz);
            pliki++;
            printf("Pliki %s dopisany. \n", argv[1]);
            puts("Kolejny plik (pusty wiersz k onczy program):");
            
        }
    }

    printf("Koniec. Dopisano %d plikow.\n", pliki);
    rewind(pd);
    printf("%s zawiera: \n", argv[2]);

    while((ch=getc(pd))!= EOF)
        putchar(ch);

    puts("Koniec.");
    fclose(pd);
    return 0;
}

void dopisz(FILE *zrodlo, FILE *cel)
{
    size_t bajty;
    static char temp[ROZMIAR_BUF];

    while((bajty=fread(temp,sizeof(char),ROZMIAR_BUF,zrodlo))>0)
        fwrite(temp,sizeof(char), bajty, cel);
}



char *wczytaj(char *z, int ile)
{
    char *wynik;
    char *tutaj;

    wynik=fgets(z,ile, stdin);

    if(wynik)
    {
        tutaj=strchr(z,'\n');

        if(tutaj)
            *tutaj='\0';
        else
            while(getchar()!='\n')
                continue;
    }
    return wynik;
}

*/



//SZÓSTE ZADANIE 

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DL 40

int main()
{
    FILE *we, *wy;
    int ch;
    char nazwa_we[DL];
    char nazwa_wy[DL];
    int licznik=0;

    printf("Podaj nazwe pliku zrodlowego: ");
    scanf("%s", nazwa_we);

    if((we=fopen(nazwa_we, "r"))==NULL)
    {
        fprintf(stderr, "Nie moglem otworzyc pliku \"%s\". \n", nazwa_we );
        exit(EXIT_FAILURE);
    }

    strncpy(nazwa_wy,nazwa_we, DL-5);
    nazwa_wy[DL-5]='\0';
    strcat(nazwa_wy,".red");

    if((wy=fopen(nazwa_wy,"w"))==NULL)
    {
        fprintf(stderr, "Nie mozna utworzyc pliku wyjsciowego. \n");
        exit(EXIT_FAILURE);
    }

    while((ch=getc(we))!=EOF)
        if(licznik++%3==0)
            putc(ch,wy);

    if(fclose(we) !=0 || fclose(wy) != 0)
        fprintf(stderr, "Blad przy zamykaniu plikow. \n");

    return 0;
}

*/


//SIÓDME ZADANIE 

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 256

char *wczytaj(char *z, int ile);

int main(int argc, char *argv[])
{

    FILE *plik1, *plik2;
    char bufor1[MAX_SIZE];
    char bufor2[MAX_SIZE];

    if((plik1=fopen(argv[1], "r"))==NULL)
    {
        fprintf(stderr, "Nie moglem otworzyc pliku \"%s\". \n", argv[1]);
        exit(EXIT_FAILURE);
    }


    if((plik2=fopen(argv[2], "r"))==NULL)
    {
        fprintf(stderr, "Nie moglem otworzyc pliku \"%s\". \n", argv[2]);
        exit(EXIT_FAILURE);
    }

    while((fgets(bufor1,MAX_SIZE, plik1)!=NULL)&&(fgets(bufor2,MAX_SIZE, plik2)!=NULL))
    {
        if(bufor1!=NULL)
        {
            wczytaj(bufor1, MAX_SIZE);
            printf("%s ",bufor1);
        }
        
         if(bufor2!=NULL)
         {
            wczytaj(bufor2, MAX_SIZE);
            printf("%s ",bufor2);
         }

        putchar('\n');
        

    }

    return 0;
}


char *wczytaj(char *z, int ile)
{
    char *wynik;
    char *tutaj;
    

    if(z!=NULL)
    {
        tutaj=strchr(z,'\n');

        if(tutaj)
            *tutaj='\0';
        else
            while(getchar()!='\n')
                continue;
    }
    return z;
}

*/




//ÓSME ZADANIE 

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 256

char *wczytaj(char *z, int ile);

int main(int argc, char *argv[])
{

    FILE *plik1;
    char znak_szuk, znak_pobrany;
    char bufor1[MAX_SIZE];
    bool tryb=false;
    int licznik=0;
    FILE *tab_wsk_pliki[argc-2];
    znak_szuk=*argv[1];

    if(argc>2)
    {
        
        

        for(int i=2; i<argc; i++)
        {
            if((tab_wsk_pliki[i-2]=fopen(argv[i], "r"))==NULL)
            {
                fprintf(stderr, "Nie moglem otworzyc pliku \"%s\". \n", argv[i]);
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        tryb=true;
    }




    if(tryb==false)
    {
        for(int i=2; i<argc; i++)
        {
            licznik=0;

            while((znak_pobrany=getc(tab_wsk_pliki[i-2]))!=EOF)
            {
                if(znak_pobrany==znak_szuk)
                {   
                    printf("Znaleziono znak %c w pliku %s %d raz.\n",znak_pobrany, argv[i],++licznik);
                }
                fclose(tab_wsk_pliki[i-2]);
            }
        }
    }
    else
    {
        
            puts("Podaj nazwe pliku.");

            while(scanf("%s", bufor1)!=0)
            {
                if((plik1=fopen(bufor1, "r"))==NULL)
                {
                    fprintf(stderr, "Nie moglem otworzyc pliku \"%s\". \n", bufor1);
                    exit(EXIT_FAILURE);
                }

                licznik=0;

                while((znak_pobrany=getc(plik1))!=EOF)
                {
                    if(znak_pobrany==znak_szuk)
                    {   
                        printf("Znaleziono znak %c w pliku %s %d raz.\n",znak_pobrany, bufor1,++licznik);
                    }
                }

                puts("Podaj nazwe pliku.");
            } 
    }
    

    return 0;
}

*/




//ZADANIE DZIESIĄTE
/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 256



int main(int argc, char *argv[])
{

    FILE *plik1;
    char znak_pobrany;
    char bufor1[MAX_SIZE];
    long int przesuniecie=0;
    long int koniec=0;
    
   

    
            puts("Podaj nazwe pliku.");
            scanf("%s", bufor1);

            if((plik1=fopen(bufor1, "r"))==NULL)
            {
                fprintf(stderr, "Nie moglem otworzyc pliku \"%s\". \n", bufor1);
                exit(EXIT_FAILURE);
            }

            puts("Podaj przesuniecie (offset).");

            fseek(plik1,0L,SEEK_END);
            koniec=ftell(plik1);
            fseek(plik1,0L,SEEK_SET);

           while(scanf("%ld",&przesuniecie)!=-1)
          {
                
                fseek(plik1, przesuniecie, SEEK_CUR);
                
                if(ftell(plik1)>=koniec)
                    exit(EXIT_FAILURE);

                while((znak_pobrany=getc(plik1))!='\n')
                 {
                    //znak_pobrany=getc(plik1);
                    putchar(znak_pobrany);
                 }
                

                puts("\nPodaj przesuniecie (offset).");
             
            } 
    

    fclose(plik1);
    

    return 0;
}
*/


//ZADANIE JEDENASTE

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 256



int main(int argc, char *argv[])
{

    FILE *plik1;
    char znak_pobrany;
    char bufor1[MAX_SIZE];
    char bufor2[MAX_SIZE];

    
   

    if(argv[1]!=NULL)
    {
        strcpy(bufor1,argv[1]);
        puts("Poprawnie wczytano podane slowo.");
    }


    if((plik1=fopen(argv[2], "r"))==NULL)
    {
        fprintf(stderr, "Nie moglem otworzyc pliku \"%s\". \n", bufor1);
        exit(EXIT_FAILURE);
    }




    while(fgets(bufor2, MAX_SIZE, plik1)!=NULL)
    {
        bufor2[strcspn(bufor2,"\n")]=0;
        printf("Wczytane slowo z pliku \"%s\". \n", bufor2);   
        
        if(strstr(bufor2,bufor1)!=NULL)
        {
            printf("Znaleziono lancuch \"%s\" w pliku %s. \n", bufor1, argv[2]);
        }     
    } 
    

    fclose(plik1);
    

    return 0;
}

*/



//ZADANIE DWUNASTE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>





int main(int argc, char *argv[])
{

    FILE *plik1;
    int wym_x=0;
    int wym_y=0;
    char znak_pobrany;
    int wartosc;
    



    
   //Wczytywanie pliku


    if((plik1=fopen(argv[1], "r"))==NULL)
    {
        fprintf(stderr, "Nie moglem otworzyc pliku \"%s\". \n", argv[1]);
        exit(EXIT_FAILURE);
    }

    //Alokacja wymaganej pamięci

    while((znak_pobrany=getc(plik1))!='\n')
        wym_x++;


    rewind(plik1);


    while((znak_pobrany=getc(plik1))!=EOF)
        if(znak_pobrany=='\n')
            wym_y++;
   

    rewind(plik1);

    int obraz_1[wym_y][wym_x];
    char obraz_2[wym_y][wym_x+1];
    char bufor_1[wym_x+1];

    for( int y=0; y<wym_y; y++)
    {
        for(int x=0; x<wym_x; x++)
        {
            znak_pobrany=getc(plik1);
            obraz_1[y][x]=znak_pobrany-48; 
        }
        getc(plik1);
    }


    for( int y=0; y<wym_y; y++)
    {
        for(int x=0; x<wym_x; x++)
            printf("%d ",obraz_1[y][x]);

        putchar('\n');
    }


    for( int y=0; y<wym_y; y++)
    {
        for(int x=0; x<wym_x; x++)
            bufor_1[x]=obraz_1[y][x]+48;
        
        bufor_1[wym_x]='\0';
        printf("Strlen of bufor: %ld \n", strlen(bufor_1));
        strncpy(obraz_2[y],bufor_1,wym_x);

        //putchar('\n');
    }

    fprintf(stdout,"Wymiar x: %d, wymiar y: %d .\n",wym_x,wym_y);





    fclose(plik1);
    

    return 0;
}


