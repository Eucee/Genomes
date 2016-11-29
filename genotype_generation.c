#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// ** Fonctions appelées lors de la génération de génotypes aléatoires **

//Fonction tirage aleatoire dans l'intervalle [a,b[
int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}

//Fonction génération de loci aléatoire avec positions ambigues
void tirage_avec_ambiguite(int* genotype, int* haplotype1, int* haplotype2, int position, int* adr_nbLociAmbigus)
{
	int lociAleatoire, lociAmbHap=0;

	lociAleatoire = rand_a_b(0,3);

	if (lociAleatoire == 1 || lociAleatoire == 0)
	{
		genotype[position] = lociAleatoire;
		haplotype1[position] = lociAleatoire;
		haplotype2[position] = lociAleatoire;
		printf("\nAmb pour 0 ou 1: %d", *adr_nbLociAmbigus);
	}
	else if (lociAleatoire == 2)//Si un loci ambigu dans la séquence, sélection aléatoire du 0 ou du 1 pour les haplotypes générés
	{
		genotype[position] = lociAleatoire;
		lociAmbHap = rand_a_b(0, 2) ;
		haplotype1[position] = lociAmbHap;
		if (lociAmbHap == 0)
		{
			haplotype2[position] = 1;
		}else if (lociAmbHap == 1)
		{
			haplotype2[position] = 0;

		}
		*adr_nbLociAmbigus=*adr_nbLociAmbigus+1;
		printf("\nAmb pour 2: %d", *adr_nbLociAmbigus);
	}
}

//Fonction génération de loci aléatoire sans positions ambigues
void tirage_sans_ambiguite(int* genotype, int* haplotype1, int* haplotype2, int position)
{
	int lociAleatoire=0;
	lociAleatoire = rand_a_b(0, 2) ; //Tirage aléatoire dans l'intervalle [0, 2[
	if (lociAleatoire == 1 || lociAleatoire == 0)
	{
		genotype[position] = lociAleatoire ;
		haplotype1[position] = lociAleatoire;
		haplotype2 [position] = lociAleatoire;
	}
}

//Fonction génération aléatoire des positions d'un génome
void tirage_loci_aleatoire(int* genotype, int* haplotype1, int* haplotype2, int tailleGenotype, int maxLociAmbigus)
{
	int nbLociAmbigus = 0;
	int position = 1;

	for (position = 0; position < tailleGenotype; position ++)
	{
		if (nbLociAmbigus < maxLociAmbigus)
		{
		    printf("\nbof");
			tirage_avec_ambiguite(genotype, haplotype1, haplotype2, position, &nbLociAmbigus);
		}
		else if (nbLociAmbigus >= maxLociAmbigus)
		{
		    printf("\nok");
			tirage_sans_ambiguite(genotype, haplotype1, haplotype2, position);
		}
	}
}

//Fonction génération aléatoire d'un génotypes pour chacun des individus
void generation_genotype_aleatoire(int nbIndividus, int tailleGenotype, int maxLociAmbigus)
{
	//Initialisation des tableaux de génotype et d'haplotypes
	int* genotype = NULL;
	int* haplotype1 = NULL;
	int* haplotype2 = NULL;

	//Allocations de mémoire
	genotype = malloc(tailleGenotype * sizeof(int));
	haplotype1 = malloc(tailleGenotype * sizeof(int));
	haplotype2 = malloc(tailleGenotype * sizeof(int));

	//Initialisation compteur du nombre d'individus
	int individu=1;

	//Boucle de génération aléatoire de génotype et d'haplotypes pour chacun des individus
	for (individu = 1; individu <= nbIndividus; individu ++)
	{
		tirage_loci_aleatoire(genotype, haplotype1, haplotype2, tailleGenotype, maxLociAmbigus);
		//tirage_loci_ambigu(genotype, haplotype1, haplotype2, tailleGenotype, maxLociAmbigus);

		//Affichages du génotype et des haplotypes générés pour chaque individu
		printf("\n\nGenotype Individu %d : ", individu);
		affiche_tableau(genotype, tailleGenotype);
		printf("\nHaplotype 1  : ");
		affiche_tableau(haplotype1, tailleGenotype);
		printf("\nHaplotype 2 : ");
		affiche_tableau(haplotype2, tailleGenotype);
	}

	free(genotype);
	free(haplotype1);
	free(haplotype2);
}

//Fonction affichage contenu de tableau
void affiche_tableau(int tableau[], int tailleTableau)
{
	int i;

	for (i = 0 ; i < tailleTableau ; i++)
	{
		printf("%d", tableau[i]);
	}

}

int main()
{
	srand(time(NULL));

	int nbIndividus=12, tailleGenotype=10, maxLociAmbigus=3;/*

	//L'utilisateur choisi le nombre d'individu, la taille des génotypes et le maximum de loci ambigus souhaité
	printf("Entrez le nombre d'individus : "); scanf("%d", &nbIndividus);
	printf("Entrez la taille des génotypes : "); scanf("%d", &tailleGenotype);
	printf("Entrez le nombre maximum de loci ambigu d'un génotype : "); scanf("%d", &maxLociAmbigus);*/


	//Appel de la fonction de génération aléatoire de génotypes et d'haplotypes
	generation_genotype_aleatoire(nbIndividus, tailleGenotype, maxLociAmbigus);
	printf("\n");

	return 0;
}




