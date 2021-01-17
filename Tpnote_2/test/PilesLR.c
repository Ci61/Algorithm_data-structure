#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <assert.h>
/*************************************************/
/* */
/* sucre syntaxique */
/* */
/*************************************************/
#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { false, true } bool;

/*************************************************/
/* */
/* definition type liste */
/* */
/*************************************************/
typedef struct Bloc
{
	int nombre;
	struct Bloc *suivant;
} Bloc;
typedef Bloc *Liste;

typedef struct BlocListe
{
	Liste elem;
	struct BlocListe *suivant;
} BlocListe;
typedef BlocListe *LDL;

/*************************************************/
/* */
/* predeclarations */
/* */
/*************************************************/
/* initialise une Liste vide */
void initVide(Liste *L);
/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);
/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);
/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);
/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);
/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);
/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);
/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);
/* longueur en recursif et en iteratif */
int longueur_rec(Liste l);
int longueur_iter(Liste l);
/* Elimination du dernier element en recursif et en iteratif */
/* VD est la sousprocedure utilitaire de la version recursive */
void VD(Liste *L);
void VireDernier_rec(Liste *L);
void VireDernier_iter(Liste *L);

/*************************************************/
/* */
/* briques de base */
/* */
/*************************************************/
void initVide(Liste *L)
{
	*L = NULL;
}

bool estVide(Liste l)
{
	return l == NULL;
}

int premier(Liste l)
{	return l->nombre;}

Liste ajoute(int x, Liste l){
	Liste tmp = (Liste)malloc(sizeof(Bloc));
	tmp->nombre = x;
	tmp->suivant = l;
	return tmp;
}

void empile(int x, Liste *L)
{
	*L = ajoute(x, *L);
}

Liste suite(Liste l)
{
	return l->suivant;
}

void depile(Liste *L)
{
	Liste tmp = *L;
	*L = suite(*L);
	free(tmp);
}

/*************************************************/
/* */
/* Affiche, avec les briques de base */
/* */
/*************************************************/
void affiche_rec(Liste l)
{
	if (estVide(l))
		printf("\n");
	else
	{
		printf("%d ", premier(l));
		affiche_rec(suite(l));
	}
}
void affiche_iter(Liste l)
{
	Liste L2 = l;
	while (!estVide(L2))
	{
		printf("%d ", premier(L2));
		L2 = suite(L2);
	}
	printf("\n");
}

/*************************************************/
/* */
/* Longueur, sans les briques de base */
/* */
/*************************************************/
int longueur_rec(Liste l)
{
	if (l == NULL)
		return 0;
	else return (1 + longueur_rec(l->suivant));
}
int longueur_iter(Liste l)
{
	Liste P = l;
	int cpt = 0;
	while (P ISNOT NULL)
	{
		P = P->suivant;
		cpt++;
	}
	return cpt;
}

/*************************************************/
/* */
/* VireDernier, */
/* sans les briques de base, */
/* ni le "->" */
/* */
/*************************************************/
void VD(Liste *L)
// *L non NULL ie liste non vide
{
	if (((**L).suivant) == NULL)
		depile(L); // moralement : depile(& (*L)) ;
	else VD(&((**L).suivant));
}
void VireDernier_rec(Liste *L)
{
	if ((*L) ISNOT NULL)
		VD(L); // moralement : VD(& (*L)) ;
}

void VireDernier_iter(Liste *L)
{
	if ((*L) ISNOT NULL)
	{
		while (((**L).suivant) ISNOT NULL)
			L = &((**L).suivant);
		free(*L);
		*L = NULL;
	}
}
/*************************************************/
/* */
/* Libere la memoire */
/* */
/*************************************************/
void VideListe(Liste *L)
{
	if (NOT(estVide(*L)))
	{
		depile(L);
		VideListe(L);
	}

}

void poup(Liste l)
{
	printf("Double Affichage \n");
	affiche_rec(l);
	affiche_iter(l);
	printf("Longueur en double %d %d \n\n",
		longueur_rec(l),
		longueur_iter(l)
	);
}


/*************************************************/
/* 1°DebutDeuxIdentique */
/* 2°QueDesZeros */
/*************************************************/
bool DebutDeuxIdentique(Liste l ) {
	if (!estVide(l) && !estVide(suite(l)))
		return premier(l) == premier(suite(l));
	else {
		return false;
	}
}

bool QueDesZeros(Liste l) {
	if (estVide(l))
		return true;
	else {
		return premier(l) == 0 AND QueDesZeros(suite(l));
	}
}

/*************************************************/
/* 3°SousEnsemble */
/*************************************************/
bool prefixe(Liste l1, Liste l2) {
	if (estVide(l1))
		return true;
	else if (estVide(l2))
		return false;
	else
		return premier(l1) == premier(l2) AND prefixe(suite(l1), suite(l2));
}

bool SousEnsemble(Liste l1, Liste l2) {
	while(NOT(estVide(l2))){
		if (NOT(prefixe(l1, l2)))
			return SousEnsemble(l1, suite(l2));
		else
			return true;
	}
	return false;
}

/*************************************************/
/* 4°Permutations */
/*************************************************/

/* */
/* briques Liste de liste de base */
/* */

void initVideLDL(LDL *ldl)
{
	*ldl = NULL;
}

bool estVideLDL(LDL ldl)
{
	return ldl == NULL;
}

Liste premierLDL(LDL ldl)
{
	return ldl->elem;
}

LDL ajouteLDL(Liste l, LDL ldl) {
	LDL tmp = (LDL)malloc(sizeof(BlocListe));
	tmp->elem = l;
	tmp->suivant = ldl;
	return tmp;
}

void empileLDL(Liste l, LDL *ldl)
{
	*ldl = ajouteLDL(l, *ldl);
}

LDL suiteLDL(LDL ldl)
{
	return ldl->suivant;
}

void depileLDL(LDL *ldl)
{
	LDL tmp = *ldl;
	*ldl = suiteLDL(*ldl);
	free(tmp);
}

void affiche_LDL(LDL ldl)
{
	if (estVideLDL(ldl))
		printf("\n");
	else
	{
		affiche_rec(premierLDL(ldl));
		affiche_LDL(suiteLDL(ldl));
	}
}

/* */
/* briques des fonctions */
/* */

LDL concatene(LDL ldl1, LDL ldl2) {
	if (estVideLDL(ldl1))
		return ldl2;
	else if (estVideLDL(ldl2))
		return ldl1;
	else
		return ajouteLDL(premierLDL(ldl1), concatene(suiteLDL(ldl1), ldl2));
}

LDL AETTL(int n, LDL ldl) {
	if (estVideLDL(ldl))
		return ldl;
	else
		return ajouteLDL(ajoute(n, premierLDL(ldl)), AETTL(n, suiteLDL(ldl)));
}

LDL ATP(int n, Liste l) {
	if (estVide(l)) {
		LDL tmp;
		initVideLDL(&tmp);
		empile(n,&l);
		empileLDL(l,&tmp);
		return tmp;
	}
	else {
		return ajouteLDL(ajoute(n, l), AETTL(premier(l), ATP(n, suite(l))));
	}
	
}

LDL ATPTL(int n, LDL ldl) {
		return ldl;
	else
		return concatene(ATP(n, premierLDL(ldl)), ATPTL(n, suiteLDL(ldl)));
}

LDL permutation(int n) {
	if (n == 0) {
		Liste l;
		LDL ldl;
		initVide(&l);
		initVideLDL(&ldl);
		empileLDL(l, &ldl);
		return ldl;
	}
	else
		return ATPTL(n, permutation(n - 1));
}


/*************************************************/
/* 5°EliminePositionsPaires */
/*************************************************/
void EliminePositionsPaires(Liste *l) {
	if (!estVide(*l)&&!estVide(suite(*l))) {
			depile(&(*l)->suivant);//on enlève l'élément à la position paire ici
			EliminePositionsPaires(&((*l)->suivant));
	}
}

/*************************************************/
/* 6°Begaye */
/*************************************************/
void Begaye(Liste *l) {
	if (!estVide(*l)) {
		if ((*l)->nombre > 0) {
			int x = (*l)->nombre;
			empile (x, l);
			Begaye(&(**(&(**l).suivant)).suivant);
		}
		else if ((*l)->nombre <= 0) {
			depile(l);
			Begaye(l);
		}
	}
}

/*************************************************/
/* 7°MaxZerosConsecutifs */
/*************************************************/
int MZC_Viter(Liste l) {
	if (estVide(l))
		return 0;
	else {
		Liste m = l;
		int cpt = 0;
		int MaxZero = 0;
		while(!estVide(m)){
			if ((m->nombre == 0) && (!estVide(suite(m))) && (suite(m)->nombre == 0)) {
				cpt++;
				m = m->suivant;
			}
			else if ((m->nombre == 0) && (!estVide(suite(m))) && (suite(m)->nombre != 0)) {
				cpt++;
				if (cpt > MaxZero)
					MaxZero = cpt;
				m = m->suivant;
			}else {
				cpt = 0;
				m = m->suivant;
			}
		}
		return MaxZero;
	}
}

/*Sous fonction avec 3 arguments*/
int MZC_VRec1_Aux(Liste l,int cpt,int MaxZero) {
	if (estVide(l))
		return MaxZero;
	else {
		if ((l->nombre == 0) && (!estVide(suite(l))) && (suite(l)->nombre == 0)) {
			cpt++;
			return MZC_VRec1_Aux(suite(l), cpt, MaxZero);
		}
		else if ((l->nombre == 0) && (!estVide(suite(l))) && (suite(l)->nombre != 0)) {
			cpt++;
			if (cpt > MaxZero)
				MaxZero = cpt;
			return MZC_VRec1_Aux(suite(l), cpt, MaxZero);
		}
		else {
			return MZC_VRec1_Aux(suite(l), 0, MaxZero);
		}
	}
}

int MZC_VRec1(Liste l) {
	int cpt = 0;
	int MaxZero = 0;
	return MZC_VRec1_Aux(l, cpt, MaxZero);
}

/*Sous fonction avec 2 arguments*/
void MZC_VRec2_Aux(Liste l, int *cpt,int *MaxZero) {
	//printf("cpt: %d; Maxzero: %d \n",*cpt,*MaxZero);
	if (estVide(l)) {
		*cpt = 0;
		*MaxZero = 0;
	}else{
		MZC_VRec2_Aux(suite(l), cpt, MaxZero);
		if ((l->nombre == 0)) {
			(*cpt)+=1;
			if (*cpt > *MaxZero) {
				*MaxZero = *cpt;
			}
		}
		else {
			*cpt = 0;
		}
	}
}

int MZC_VRec2(Liste l) {
	int cpt = (int)malloc(sizeof(int));
	int MaxZero = (int)malloc(sizeof(int));
	MZC_VRec2_Aux(l, &cpt, &MaxZero);
	return MaxZero;
	free(cpt);
	free(MaxZero);
}

/*************************************************/
/* 8°EstPalindrome */
/*************************************************/
void EP_aux(Liste *p,Liste l,bool *res) {
	if (estVide(l)) {
		*res = true;
	}
	else {
		EP_aux(p, suite(l),res);
		if (premier(*p) != premier(l)) {
			*res = false;
		}
		*p = (*p)->suivant;
		
	}
}

bool EstPalindrome(Liste l) {
	Liste p = l;
	bool res= (bool)malloc(sizeof(int));;
	EP_aux(&p,l, &res);
	return res;
}

/*************************************************/
/* 9°SommeAvantApres */
/*************************************************/
 void SAA_aux(Liste l, int pre,int *post, bool *res) {
	 if (estVide(l)) {
		 *res = false;
		 *post = 0;
	 } else {
		 pre += premier(l);
		 SAA_aux(suite(l), pre, post,res);
		 if ((pre) == (*post))
			 *res=true;
		 (*post) += premier(l);
	 }
 }

 bool SommeAvantApres(Liste l) {
	 bool res;
	 int post;
	 SAA_aux(l, 0, &post, &res);
	 return res;
 }

/*************************************************/
/* Implementation des files*/
/*************************************************/

 typedef Liste *File;
 
 void initFile(File *file)
 {
	 *file = NULL;
 }


 /*Dans une file, la structure de données est basée sur le principe "premier entré, premier sorti" */
 void ajouteFiles(File *pfile,int item) {
	 
	if ((*pfile)==NULL){
		/*Si la file est vide, on va créer une liste avec un seul bloc dont son bloc suivant est lui-même */
		 *pfile = (File)malloc(sizeof(Liste));
		 (*(*pfile)) = (Liste)malloc(sizeof(Bloc));
		 (*(*pfile))->nombre = item;
		 (*(*pfile))->suivant = *(*pfile);
	}else{
		 /*si la liste n'est pas vide, on ajoute un nouveau bloc à la fin de la et il pointe vers le premier bloc créé de la liste */
		 Liste tmp = (Liste)malloc(sizeof(Bloc));
		 tmp->nombre = item;
		 tmp->suivant = (*(*pfile))->suivant;
		 (*(*pfile))->suivant = tmp;
		 *(*pfile) = tmp;
	}
 }


 //void aff_file_iter(Liste l)
 //{
	// if (l == NULL)
	//	 printf("NULL");
	// else {
	//	 int i = l->nombre;
	//	 printf("%d  ", i);
	//	 l = l->suivant;
	//	 while (l->nombre != i) {
	//		 printf("%d  ", l->nombre);
	//		 l = l->suivant;
	//	 }
	// }

 //}

void sortirFiles(File *pfile, int* x) {
	if ((*pfile) ISNOT NULL) {
		if ((**pfile)->suivant== (**pfile)){
			free(**pfile);
			**pfile = NULL;
		}
		else {
			*x = (**pfile)->nombre;
			Liste tmp = (**pfile)->suivant;
			depile(&((**pfile)->suivant));
			tmp = **pfile;
		}
	}
}

/*************************************************/
/* */
/* Main */
/* */
/*************************************************/

int main(int argc, char** argv){

	/*test DebutDeuxIdentique*/
	//Liste l1;
	//initVide(&l1);
	//empile(1, &l1);
	//empile(3, &l1);
	//printf("DebutDeuxIdentique l1:%d\n",DebutDeuxIdentique(l1));

	/*test QueDesZeros*/
	//Liste qdz;
	//initVide(&qdz);
	//empile(0, &qdz);
	//empile(0, &qdz);
	//empile(0, &qdz);
	//printf("QueDesZeros qdz:%d\n",  QueDesZeros(qdz));
	
	/*test SousEnsemble*/
	//Liste sse1,sse2;
	//initVide(&sse1);
	//initVide(&sse2);
	//empile(3, &sse1);
	//empile(2, &sse2);
	//empile(1, &sse1);
	//empile(5, &sse2);
	//empile(4, &sse2);
	//empile(3, &sse2);
	//empile(2, &sse2);
	//empile(1, &sse2);
	//affiche_iter(sse1);
	//affiche_iter(sse2);
	//printf("sse1 est SousEnsemble de sse2:%d\n", SousEnsemble(sse1,sse2));

	/*test Permutation*/
	//int n=4;
	//affiche_LDL(permutation(n));
	
	/*test EliminePositionsPaires*/
	//Liste epp;
	//initVide(&epp);
	//empile(3, &epp);
	//empile(8, &epp);
	//empile(8, &epp);
	//empile(6, &epp);
	//empile(1, &epp);
	//empile(7, &epp);
	//empile(2, &epp);
	//affiche_iter(epp);
	//EliminePositionsPaires(&epp);
	//affiche_iter(epp);

	/*test Begaye*/
	//Liste bag;
	//initVide(&bag);
	//empile(8,&bag);
	//empile(8, &bag);
	//empile(-2, &bag);
	//empile(6, &bag);
	//empile(0, &bag);
	//empile(1, &bag);
	//empile(2, &bag);
	//affiche_iter(bag);
	//Begaye(&bag);
	//affiche_iter(bag);

	/*test MaxZerosConsecutifs*/
	//Liste mzc1, mzc2;
	//initVide(&mzc1);
	//initVide(&mzc2);
	//empile(9, &mzc1);
	//empile(2, &mzc1);
	//empile(8, &mzc1);
	//empile(4, &mzc1);
	//empile(0, &mzc2);
	//empile(0, &mzc2);
	//empile(0, &mzc2);
	//empile(7, &mzc2);
	//empile(0, &mzc2);
	//empile(8, &mzc2);
	//empile(0, &mzc2);
	//empile(0, &mzc2);
	//empile(0, &mzc2);
	//empile(7, &mzc2);
	//empile(9, &mzc2);
	//affiche_iter(mzc1);
	//affiche_iter(mzc2);
	//printf("MZC_Viter_1: %d\n", MZC_Viter(mzc1));
	//printf("MZC_VRec1_1: %d\n", MZC_VRec1(mzc1));
	//printf("MZC_VRec2_1: %d\n", MZC_VRec2(mzc1));
	//printf("MZC_Viter_2: %d\n", MZC_Viter(mzc2));
	//printf("MZC_VRec1_2: %d\n", MZC_VRec1(mzc2));
	//printf("MZC_VRec2_2: %d\n", MZC_VRec2(mzc2));

	/*test EstPalindrome*/
	//Liste epd;
	//initVide(&epd);
	//empile(2, &epd);
	//empile(8, &epd);
	//empile(8, &epd);
	//empile(8, &epd);
	//empile(8, &epd);
	//empile(2, &epd);
	//affiche_iter(epd);
	//printf("EstPalindrome: %d",EstPalindrome(epd));
	
	/*test SommeAvantApres*/
	//Liste saa;
	//initVide(&saa);
	//empile(7, &saa);
	//empile(-2, &saa);
	//empile(4, &saa);
	//empile(0, &saa);
	//empile(3, &saa);
	//empile(2, &saa);
	//affiche_iter(saa);
	//printf("SommeAvantApres: %d", SommeAvantApres(saa));
	
	/*test File*/
	//File file;
	//initFile(&file);
	//ajouteFiles(&file, 3);
	////ajouteFiles(&file, 5);
	//aff_file_iter(*file);
	//int x;
	//sortirFiles(&file, &x);
	//printf("\n");
	//aff_file_iter(*file);
	Sleep(1000000000);
	return 0;
}
