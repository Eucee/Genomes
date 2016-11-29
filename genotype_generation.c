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




//Fonction génération aléatoire des positions d'un génome
void tirage_loci_aleatoire(int* genotype, int tailleGenotype)
{
	int position;
	int lociAleatoire=0;

	for (position = 0; position < tailleGenotype; position ++)
	{

	lociAleatoire = rand_a_b(0, 2) ; //Tirage aléatoire dans l'intervalle [0, 2[
    genotype[position] = lociAleatoire ;

	}
}

//Fonction génération aléatoire des positions d'un génome
void tirage_loci_ambigu(int* genotype, int tailleGenotype, int maxLociAmbigus)
{
	int i;
    int* pos_locus_ambigu = NULL;
	int* deja_fait = NULL;

	//afficherVect(locus, taille_locus);
	pos_locus_ambigu = malloc((maxLociAmbigus) * sizeof (int));
	deja_fait = malloc((tailleGenotype) * sizeof (int));

    for(i = 0; i < maxLociAmbigus; i++){
        do{
            pos_locus_ambigu[i] = rand_a_b(0, tailleGenotype) ;
        }while(deja_fait[pos_locus_ambigu[i]] == 1);

        deja_fait[pos_locus_ambigu[i]]  = 1;
        genotype[pos_locus_ambigu[i]] = 2;
        //afficherVect(locus, taille_locus);
    }
}

void tirage_haplotypes(int* genotype, int* haplotype1, int* haplotype2, int tailleGenotype)
{
    int position;

    for (position = 0; position < tailleGenotype; position ++)
    {

        int lociAmbHap=0;
        lociAmbHap = rand_a_b(0, 2) ;
		haplotype1[position] = lociAmbHap;
		if (lociAmbHap == 0)
		{
			haplotype2[position] = 1;
		}else{
			haplotype2[position] = 0;
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
		tirage_loci_aleatoire(genotype, tailleGenotype);
		tirage_loci_ambigu(genotype, tailleGenotype, maxLociAmbigus);
		tirage_haplotypes(genotype, haplotype1, haplotype2, tailleGenotype);

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




