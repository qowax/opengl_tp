#include "vue_gaussien.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>


using namespace std;

Vue_Gaussien::Vue_Gaussien(Controleur& _controleur)
	: Vue("FILTRE GAUSSIEN"), appControleur(_controleur)
{
	appControleur.ajouterObservateur(this);
}

void Vue_Gaussien::notify()
{
	if (appControleur.ecranActuel() == 3)
	{
		display();
	}
}

void Vue_Gaussien::display()
{
	clear();
	int parametre = 1;
	int fini = 0;
	while (fini == 0)
	{
		Vue::afficher();
		COORD coord;

		//Affichage ProgressBar
		cout << "\tIntensite: " << endl << "\t\t";
		cout << endl << "                                                     |" << endl << "\t\t";
		coord.X = 12;
		coord.Y = 4;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		cout << "|";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
		for (int i = 0; i <= parametre - 1; i++)
		{
			cout << " ";
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 199);

		//D�tection de l'appui de touches
		int killer = 0;
		int touche = 0;
		while (killer == 0)
		{
			switch ((touche = _getch())) {
			case 13: //ENTREE
				cout << endl << endl << "\t    ..." << endl;
				appControleur.filtreGaussien(parametre);
				appControleur.modifierEcran(0);
				fini = 1;
				killer = 1;
				break;
			case 75: //GAUCHE
				if (parametre != 1)
				{
					parametre--;
				}
				killer = 1;
				break;
			case 77: //DROITE
				if (parametre != 40)
				{
					parametre++;
				}
				killer = 1;
				break;
			}
		}

		//Modification coordonn�es curseur (pour �viter de clear() � chaque pression de touche fl�ch�e et faire scintiller l'�cran)
		coord.X = 0;
		coord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
}