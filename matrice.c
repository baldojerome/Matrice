
#include <stdio.h>
#include <stdlib.h>


//creation d'une structure pour recuperer plus facilement colonne et ligne
//type pointeur sur pointeur pour  creer un tableau de pointeurs 
//l'objectif est de  creer pour chaque ligne un tableau de pointeurs
//d'ou le pointeur sur pointeur pour pouvoir acceder directement aux valeurs. 
typedef struct{
    int ligne;
    int colonne;
    int rang;
    int **p;
}Matrice;

//on soustrait pour avoir le nombre d'espaces pour agencer la matrice
void nbrEspace(int ref, int nbre0)
{
    int nbtotal;
    nbtotal = ref-nbre0; 
    for(int i = 0; i < nbtotal; i++)
    {
        printf(" ");
    }
}
//calcul du rang du nombre (ex: 1000 donne 4 rangs et 1 donne 1 rang) afin de realiser affichage correct
int RangMax(int nbrMax)
{
   int indice = 0;
   
   if(nbrMax >= 0 && nbrMax <= 9)
   {
       indice = 1;
   }
   else if(nbrMax >= 10 && nbrMax <= 99)
   {
       indice = 2;
   }
   else if(nbrMax >= 100 && nbrMax <= 999)
   {
       indice = 3;
   }
   else if(nbrMax >= 1000 && nbrMax <= 9999)
   {
       indice = 4;
   }
   else
   {
       return 1;
   }
   
    return indice;
}

//remplissage des indices pour la matrice nouvellement cree
Matrice remplissage(Matrice m)
{
    Matrice rempli = m;
    int nbrMax = 0;
    for(int i = 0; i <rempli.ligne; i++)
    {
        for(int j = 0; j< rempli.colonne; j++)
        {
            printf("Indice de la matrice [%d][%d] : ", i+1, j+1);//eviter indice 0
            scanf("%d", &rempli.p[i][j]);
            if(nbrMax < rempli.p[i][j])
            {
                nbrMax = rempli.p[i][j];
            }
        }
    }
    rempli.rang = RangMax(nbrMax);  
    
    return rempli;

}

Matrice creation()
{
    Matrice m;
    
    printf("Rentrez le nombre de lignes et de colonnes.\n");
    scanf("%d %d", &m.ligne, &m.colonne);
    m.rang = 0;
    m.p = malloc(m.ligne*sizeof(int*)); 
    //allocation mémoire pour le nombre de ligne 
    //p servira de pointeurs sur pointeurs 
    if(m.p) //test reussite malloc
    {
        for(int i = 0; i <m.ligne; i++)
        {
    //allocation mémoire pour chaque ligne en fonction du nombre de colonnes
            m.p[i] = malloc(m.colonne*sizeof(int));
            if(!m.p[i]) // test réussite malloc
            {
                printf("erreur malloc colonne");
            }
        }
    }
    else
    {
        printf("erreur malloc ligne.");
    }
    
    return m;
}

void afficher(Matrice m)
{
   
    int ref = m.rang;
    int nbre0;

    for(int i = 0; i <m.ligne; i++)
            {
                printf("|");
                for(int j = 0; j< m.colonne; j++)
                {
                    nbre0 = RangMax(m.p[i][j]);                  
                    nbrEspace(ref, nbre0);
                    printf("%d", m.p[i][j]);
                    printf("|");
                    
                }
                printf("\n");
            }
    
}
//liberation memoire suite aux mallocs
void liberer(Matrice m)
{
    int colonne = m.colonne;
    int ligne = m.ligne;
    if (m.p != NULL) //test pour ne pas liberer uen seconde fois la memoire 
    {
        for(int i = 0; i < ligne; i++)
        {
            free(m.p[i]); 
        } 
        free(m.p); //m.p = NULL;
    }
    else
    {
        printf("erreur suppression deja realisee.\n");
    }    
}

int main()
{
    Matrice m;
    m = creation();
    m = remplissage(m);
    afficher(m);
    liberer(m); //libérer mémoire car malloc 
    return 0;
}
