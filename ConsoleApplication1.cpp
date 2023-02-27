// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Init(char MINES[10][10], char JEU[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            JEU[i][j] = '-';
            MINES[i][j] = '0';
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void AfficheJeu(char JEU[10][10])
{
    printf("\n\n");
    printf("   | 1  2  3  4  5  6  7  8  9  10\n");
    printf("___|______________________________\n");
    for (int i = 0; i < 10; i++)
    {
        if (i < 9)
            printf(" %d | ", i + 1);
        else
            printf("%d | ", i + 1);
        for (int j = 0; j < 10; j++)
        {
            printf("%c  ", JEU[i][j]);
        }
        printf("\n");
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void AfficheMines(char MINES[10][10])
{
    printf("\n\n");
    printf("   | 1  2  3  4  5  6  7  8  9  10\n");
    printf("___|______________________________\n");
    for (int i = 0; i < 10; i++)
    {
        if (i < 9)
            printf(" %d | ", i + 1);
        else
            printf("%d | ", i + 1);
        for (int j = 0; j < 10; j++)
        {
            printf("%c  ", MINES[i][j]);
        }
        printf("\n");
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void PlaceMines(char MINES[10][10])
{
    int Pmines;
    int NbMines = 10;
    srand(time(NULL));
    for (Pmines = 0; Pmines < NbMines; Pmines++)
    {
        int i = rand() % 10;
        int j = rand() % 10;
        if (MINES[i][j] == '0')
        {
            MINES[i][j] = 'X';
        }
        else
        {
            NbMines++;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CompteMines(char MINES[10][10])
{
    int i, j, nbMines;

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            nbMines = 0;
            if (MINES[i][j] == '0' && MINES[i][j] != 'X')
            {
                // Compter les mines autour de la case vide
                int k, l;
                for (k = i - 1; k <= i + 1; k++)
                {
                    for (l = j - 1; l <= j + 1; l++)
                    {
                        if (k >= 0 && k < 10 && l >= 0 && l < 10 && MINES[k][l] == 'X')
                        {
                            nbMines++;
                        }
                    }
                }
                if (nbMines > 0)
                {
                    MINES[i][j] = '0' + nbMines;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void DecouvrirCase(char MINES[10][10], char JEU[10][10], int i, int j)
{
    if (MINES[i][j] == 'X')
    {
        AfficheMines(MINES);
        printf("Apprend à jouer mon reuf\n");
        exit(0);
    }
    else if (MINES[i][j] != ' ')
    {
        JEU[i][j] = MINES[i][j];
    }
    else
    {
        JEU[i][j] = ' ';
        int k, l;
        for (k = i - 1; k <= i + 1; k++)
        {
            for (l = j - 1; l <= j + 1; l++)
            {
                if (k >= 0 && k < 10 && l >= 0 && l < 10 && JEU[k][l] == '-')
                {
                    DecouvrirCase(MINES, JEU, k, l);
                }
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void PlacerDrapeau(char JEU[10][10], int i, int j) {
    JEU[i][j] = 'F';
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Choisir(int choix, char MINES[10][10], char JEU[10][10])
{
    int i, j;
    printf("\n\nVeuillez entrer la case choisie (numero de ligne [espace] numero de colonne):\t");
    scanf_s("%d %d", &i, &j);
    printf("Vous avez choisi la case (%d,%d).\ Que voulez-vous faire ?\n", i, j);
    i = i - 1;
    j = j - 1;
    printf("\t1. Decouvrir une case\n");
    printf("\t2. Placer un drapeau\n");
    do
    {
        printf("\t\tVotre choix : ");
        scanf_s("%d", &choix);
    } while (choix < 0 || choix>2);

    if (choix == 1)
    {
        DecouvrirCase(MINES, JEU, i, j);
        AfficheJeu(JEU);
    }
    else if (choix == 2)
    {
        PlacerDrapeau(JEU, i, j);
        AfficheJeu(JEU);
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int EstTermine(char JEU[10][10], char MINES[10][10]) {
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            // Vérifie si la case n'a pas été révélée et ne contient pas de mine
            if (JEU[i][j] == '-' && MINES[i][j] != 'X') {
                return 0; // La partie n'est pas terminée
            }
        }
    }
    printf("GG mec!");
    return 1; // Toutes les cases qui ne contiennent pas de mine ont été révélées, la partie est terminée
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int main()
{
    int choix{};//choix d'une case
    char JEU[10][10];//grille de jeu
    char MINES[10][10];//grille avec les mines
    Init(MINES, JEU);
    AfficheJeu(JEU);
    PlaceMines(MINES);
    CompteMines(MINES);
    while (!EstTermine(JEU, MINES))
    {
        Choisir(choix, MINES, JEU);
    }

    return 0;
}
 