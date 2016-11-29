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


//Fonction affichage contenu de tableau
void affiche_tableau(int tableau[], int tailleTableau)
{
	int i;

	for (i = 0 ; i < tailleTableau ; i++)
	{
		printf("%d", tableau[i]);
	}

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
    //free(pos_locus_ambigu); //BUG à la compil
    //free(deja_fait);
}

void tirage_haplotypes(int* genotype, int* haplotype1, int* haplotype2, int tailleGenotype)
{
    int position;
    int lociAmbHap;

    for (position = 0; position < tailleGenotype; position ++)
    {
        lociAmbHap=0;

        haplotype1[position] = genotype[position];
        haplotype2[position] = genotype[position];

		if(genotype[position]==2){

            lociAmbHap = rand_a_b(0, 2) ;
            haplotype1[position] = lociAmbHap;
            if (lociAmbHap == 0) { haplotype2[position] = 1;
            }else//(lociAmbHap == 1)
            { haplotype2[position] = 0;}
		}
    }
}

void nouveaux_tirages_si_doublon(int* genotype1, int* genotype2, int* haplotype1, int* haplotype2, int tailleGenotype, int maxLociAmbigus){

    int similaire = 0;
    int i;

    //1ere verification de similarité entre genotype
    for(i = 0; i < tailleGenotype; i++){

        if (genotype1[i] == genotype2[i]) similaire++;
    }

    if(similaire == tailleGenotype){

        do{//nouveau tirage s'il sont similaires
            similaire = 0;

            tirage_loci_aleatoire(genotype2, tailleGenotype);
            tirage_loci_ambigu(genotype2, tailleGenotype, maxLociAmbigus);
            tirage_haplotypes(genotype2, haplotype1, haplotype2, tailleGenotype);

            for(i = 0; i < tailleGenotype; i++){

                if (genotype1[i] == genotype2[i]) similaire++;
            }

        }while(similaire == tailleGenotype); //on prévoit le cas d'un troisième (ou plus!) tirage similaire
      }
    //affiche_tableau(genotype1, tailleGenotype);
    //affiche_tableau(genotype2, tailleGenotype);
}


//Fonction génération aléatoire d'un génotypes pour chacun des individus
void generation_genotype_aleatoire(int nbIndividus, int tailleGenotype, int maxLociAmbigus)
{
	//Initialisation des tableaux de génotype et d'haplotypes
	int** liste_geno = NULL;
	int** liste_haplo1 = NULL;
	int** liste_haplo2 = NULL;

	//Allocations de mémoire
	liste_geno = (int**)malloc((nbIndividus) * sizeof (int*));
	liste_haplo1 = (int**)malloc((nbIndividus) * sizeof (int*));
	liste_haplo2 = (int**)malloc((nbIndividus) * sizeof (int*));

	//Initialisation compteur du nombre d'individus
	int individu, individu2;

	//Boucle de génération aléatoire de génotype et d'haplotypes pour chacun des individus
	for (individu = 0; individu < nbIndividus; individu ++)
	{

        liste_geno[individu] = (int*)malloc(tailleGenotype * sizeof(int));
        liste_haplo1[individu] = (int*)malloc(tailleGenotype * sizeof(int));
        liste_haplo2[individu] = (int*)malloc(tailleGenotype * sizeof(int));

	    tirage_loci_aleatoire(liste_geno[individu], tailleGenotype);
        tirage_loci_ambigu(liste_geno[individu], tailleGenotype, maxLociAmbigus);
        tirage_haplotypes(liste_geno[individu], liste_haplo1[individu], liste_haplo2[individu], tailleGenotype);


		//Affichages du génotype et des haplotypes générés pour chaque individu
		printf("\n\n===Individu %d ===", individu+1);
		printf("\nGenotype    : ");
		affiche_tableau(liste_geno[individu], tailleGenotype);
		printf("\nHaplotype 1 : ");
		affiche_tableau(liste_haplo1[individu], tailleGenotype);
		printf("\nHaplotype 2 : ");
		affiche_tableau(liste_haplo2[individu], tailleGenotype);
	}
/*
	for (individu = 0; individu < nbIndividus; individu ++){
        for(individu2 = 0; individu2 < nbIndividus; individu2++){
        //possibilite d optimiser pour eviter de comparer liste_geno[i] avec lui meme
        nouveaux_tirages_si_doublon(liste_geno[individu], liste_geno[individu2], liste_haplo1[individu2], liste_haplo1[individu2],tailleGenotype, maxLociAmbigus);
        //complexite de type taille_locus^3 (3eme boucle for dans la fct)
        //possibilite d optimiser en evitant une comparaison 2 a 2 mais plutot de type "diviser pour regner" ?
	    }
	}*/

	//libération de mémoire alloué dynamiquement
	for (individu = 1; individu <= nbIndividus; individu ++){
           free(liste_geno[individu]);
           free(liste_haplo1[individu]);
           free(liste_haplo2[individu]);
	}
	free(liste_geno);
	free(liste_haplo1);
	free(liste_haplo2);
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




