#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>


typedef enum { false, true } bool;

typedef struct bloc_image{
	bool toutnoir;
	struct bloc_image * fils[4];
} bloc_image;

typedef bloc_image *image;


/*************************************************/
/*************************************************/
/* 3.2 */
/*************************************************/
/*************************************************/


/*************************************************/
/* 1�Construction */
/*************************************************/
image construit_blanc() {
	return NULL;
}

image construit_noir() {
	image tmp = (image)malloc(sizeof(bloc_image));
	tmp->toutnoir= true;
	tmp->fils[0] = NULL;
	tmp->fils[1] = NULL;
	tmp->fils[2] = NULL;
	tmp->fils[3] = NULL;
	return tmp;
}

image construit_composee(image i1,image i2,image i3,image i4) {
	image tmp = (image)malloc(sizeof(bloc_image));
	tmp->toutnoir = false;
	tmp->fils[0] = i1;
	tmp->fils[1] = i2;
	tmp->fils[2] = i3;
	tmp->fils[3] = i4;
	return tmp;
}

/*************************************************/
/* 2�Affichage */
/*************************************************/
void AI_Simple(image img) {
	if (img==NULL) {
		printf("B");
	}
	else if (img->toutnoir) {
		printf("N");
	}
	else{
		printf(".");
		AI_Simple(img->fils[0]);
		AI_Simple(img->fils[1]);
		AI_Simple(img->fils[2]);
		AI_Simple(img->fils[3]);
	}
}

void ProfAux(image img,int* cpt) {
	if (img == NULL) {
		printf("B%d ",*cpt);
	}
	else if (img->toutnoir) {
		printf("N%d ",*cpt);
	}
	else {
		printf(".%d ",*cpt);
		int pp=*cpt+1;
		ProfAux(img->fils[0],&pp);
		ProfAux(img->fils[1],&pp);
		ProfAux(img->fils[2],&pp);
		ProfAux(img->fils[3],&pp);
	}
}

void AI_Profondeur(image img) {
	int cpt = 0;
	ProfAux(img, &cpt);
}

/*************************************************/
/* 3�Est_noir ; Est_Blanche */
/*************************************************/
bool est_noir(image img) {
	if ((img == NULL)) {
		return false;
	}else{
		return (img->toutnoir)
			||(est_noir(img->fils[0])
				&& est_noir(img->fils[1])
				&& est_noir(img->fils[2])
				&& est_noir(img->fils[3]));
	}
}

bool est_blanche(image img) {
	if (img == NULL)
		return true;
	else if (img->toutnoir)
		return false;
	else{
		return (est_blanche(img->fils[0]) 
				&& est_blanche(img->fils[1]) 
				&& est_blanche(img->fils[2]) 
				&& est_blanche(img->fils[3])
				);
	}
}

/*************************************************/
/* 4�Copie */
/*************************************************/
image copie(image img) {
	if (img == NULL)
		return construit_blanc();
	else if (img->toutnoir)
		return construit_noir();
	else {
		return  construit_composee(
					copie(img->fils[0]),
					copie(img->fils[1]),
					copie(img->fils[2]),
					copie(img->fils[3])
				);
	}
}

/*************************************************/
/* 5�Aire */
/*************************************************/
double aire(image img) {
	if (img == NULL)
		return 0;
	else if (img->toutnoir)
		return 1;
	else {
		return (aire(img->fils[0])
				+ aire(img->fils[1])
				+ aire(img->fils[2])
				+ aire(img->fils[3])
				)/4;
	}
}

/*************************************************/
/* 6�Meme_dessin */
/*************************************************/
/*Je Compare toutes les possibilites d'img1 avec toutes possibilites d'img2 separement*/
bool meme_dessin(image img1, image img2) {
	if ((img1 == NULL)) {
		if (img2 == NULL)
			return true;
		else if (img2->toutnoir)
			return false;
		else
			return meme_dessin(img1, img2->fils[0])
					&& meme_dessin(img1, img2->fils[1])
					&& meme_dessin(img1, img2->fils[2])
					&& meme_dessin(img1, img2->fils[3]);
	}
	else if (img1->toutnoir) {
		if (img2 == NULL)
			return false;
		else if (img2->toutnoir)
			return true;
		else
			return meme_dessin(img1, img2->fils[0])
			&& meme_dessin(img1, img2->fils[1])
			&& meme_dessin(img1, img2->fils[2])
			&& meme_dessin(img1, img2->fils[3]);
	}else {
		if (img2 == NULL)
			return false;
		else if (img2->toutnoir) {
			return meme_dessin(img1->fils[0], img2)
					&& meme_dessin(img1->fils[1], img2)
					&& meme_dessin(img1->fils[2], img2)
					&& meme_dessin(img1->fils[3], img2);
		}
		else
			return (meme_dessin(img1->fils[0], img2->fils[0]) 
					&& meme_dessin(img1->fils[1], img2->fils[1]) 
					&& meme_dessin(img1->fils[2], img2->fils[2]) 
					&& meme_dessin(img1->fils[3], img2->fils[3]));
	}
}

/*************************************************/
/* 7�Diff_2Images */
/*************************************************/
image Diff_2Images(image img1,image img2) {
	if (img1 == NULL) {
		return img2;
	}else if(img2==NULL){
		return img1;
	}
	else {
		if (img1->toutnoir) {
			if (img2->toutnoir)
				return construit_blanc();
			else
				return construit_composee(
						Diff_2Images(img1, img2->fils[0]), 
						Diff_2Images(img1, img2->fils[1]), 
						Diff_2Images(img1, img2->fils[2]), 
						Diff_2Images(img1, img2->fils[3]));
		}else if(img2->toutnoir)
			return construit_composee(
						Diff_2Images(img1->fils[0], img2), 
						Diff_2Images(img1->fils[1], img2), 
						Diff_2Images(img1->fils[2], img2), 
						Diff_2Images(img1->fils[3], img2));
		else
			return construit_composee(
						Diff_2Images(img1->fils[0], img2->fils[0]), 
						Diff_2Images(img1->fils[1], img2->fils[1]), 
						Diff_2Images(img1->fils[2], img2->fils[2]), 
						Diff_2Images(img1->fils[3], img2->fils[3]));
	}
}

/*************************************************/
/* 8�Rendre les champs d'une image � la m�moire */
/*************************************************/
void RMemoire(image *img) {
	if ((*img) != NULL) {
		if (!(*img)->toutnoir) {
			for (int i = 0; i < 4; i++) {
				RMemoire(&((*img)->fils[i]));
			}
		}
		free(*img);
		*img = NULL;
	}
}

/*************************************************/
/* 9�lecture au clavier */
/*************************************************/
image LClavier() {
	char s;
	scanf_s("%c", &s,1);
	if (s == 'B')
		return construit_blanc();
	else if (s == 'N')
		return construit_noir();
	else {
		image i1 = LClavier();
		image i2 = LClavier();
		image i3 = LClavier();
		image i4 = LClavier();
		return construit_composee(i1,i2,i3,i4);
	}
}

/*************************************************/
/* 10�CompteSousImagesPleines */
/*************************************************/

/* Cette procedure auxiliere verifie si un arbre est parfait
 * Et puis on recupere la hauteur de cet arbre par un pointeur.
 */
void estPleineBis(image img,bool* b,int* h) {
	if ((img == NULL) || (img->toutnoir)) {
		*b = true;
		*h = 0;
	}else {
		bool b1 = *b; int h1 = *h;
		bool b2 = *b; int h2 = *h;
		bool b3 = *b; int h3 = *h;
		bool b4 = *b; int h4 = *h;
		estPleineBis(img->fils[0], &b1, &h1);
		estPleineBis(img->fils[1], &b2, &h2);
		estPleineBis(img->fils[2], &b3, &h3);
		estPleineBis(img->fils[3], &b4, &h4);
		*b = b1&&b2&&b3&&b4&&(h1==h2)&&(h2==h3)&&(h3==h4);
		int t1 = h1 > h2 ? h1 : h2;
		int t2 = h3 > h4 ? h3 : h4;
		*h = (t1 > t2 ? t1 : t2 )+1;
	}

}

int CompteSousImagesPleines(image img, int hauteur) {
	if ((img == NULL)||(img->toutnoir)) {
		if (hauteur == 0)
			return 1;
		else return 0;
	}
	else {
		bool b;
		int h;
		estPleineBis(img, &b, &h);
		if ((h == hauteur)&&b) {
			return 1;
		}else {
			return CompteSousImagesPleines(img->fils[0], hauteur) +
				CompteSousImagesPleines(img->fils[1], hauteur) +
				CompteSousImagesPleines(img->fils[2], hauteur) +
				CompteSousImagesPleines(img->fils[3], hauteur);
		}
	}
}

/*************************************************/
/* 11�Arrondit une image aux pixels de taille 1/2^k*/
/*************************************************/
void arrondit(image *img,int k) {
	if (0 < k 
		&& (*img != NULL) 
		&& !((*img)->toutnoir))
	{
		k -= 1;
		arrondit(&((*img)->fils[0]), k);
		arrondit(&((*img)->fils[1]), k);
		arrondit(&((*img)->fils[2]), k);
		arrondit(&((*img)->fils[3]), k);
	}
	else if (k == 0
		&& (*img != NULL)
		&& !((*img)->toutnoir))
	{
		if (aire(*img)>0.25) {
			free(*img);
			*img = construit_noir();
		}
		else {
			free(*img);
			*img = construit_blanc();
		}
	}
}

/*************************************************/
/* 12� (procedure qui TRANSFORME une image en son negatif) */
/*************************************************/
void negatif(image *img) {
	if (*img == NULL) {
		*img = construit_noir();
	}
	else if ((*img)->toutnoir) {
		free(*img);
		*img = construit_blanc();
	}
	else {
		for (int i = 0; i < 4; i++) {
			negatif(&((*img)->fils[i]));
		}
	}
}

/*************************************************/
/* 13� Simplifier la repr�sentation d'une image */
/*************************************************/
void simplifie(image *img) {
	if (!(*img == NULL) && !((*img)->toutnoir)) {
		if ((*img)->fils[0] == NULL
			&& (*img)->fils[1] == NULL
			&& (*img)->fils[2] == NULL
			&& (*img)->fils[3] == NULL)
		{
			free(*img);
			*img = construit_blanc();

		}
		else if ((*img)->fils[0] != NULL
			&& (*img)->fils[1] != NULL
			&& (*img)->fils[2] != NULL
			&& (*img)->fils[3] != NULL
			&& (*img)->fils[0]->toutnoir
			&& (*img)->fils[1]->toutnoir
			&& (*img)->fils[2]->toutnoir
			&& (*img)->fils[3]->toutnoir)
		{
			free(*img);
			*img = construit_noir();
		}
		else {
			simplifie(&((*img)->fils[0]));
			simplifie(&((*img)->fils[1]));
			simplifie(&((*img)->fils[2]));
			simplifie(&((*img)->fils[3]));
		}
	}
}

/*************************************************/
/* 14�Affichage 2^k pixel*/
/*************************************************/

/*L'affichage en 2k n'est pas realise entierement,
* chaque partie de l'image sont affich�e s�parement.
*/
void AI_2k(image img, int* k) {
	if (*k > 0) {
		int d = (int)pow(2, (*k));
		for (int i = 0; i < d; i++) {
			if (img == NULL) {
				for (int j = 0; j < d; j++) {
					printf(".");
				}
				printf("\n");
			}
			else if (img->toutnoir) {
				for (int j = 0; j < d; j++)
					printf("8");
				printf("\n");
			}
			else {
				int kk = (*k) - 1;
				AI_2k(img->fils[0], &kk);
				AI_2k(img->fils[1], &kk);
				AI_2k(img->fils[2], &kk);
				AI_2k(img->fils[3], &kk);
				break;
			}
		}
	}
	else if (*k == 0) {
		if (img == NULL)
			printf(".");
		else if (img->toutnoir)
			printf("8");
		else
			printf("-");
	}
}

int main() {
	
	/*Test Aire*/
	//image ar1 = construit_composee(B, B, B, construit_composee(B, B, B, construit_composee(B, B, B, construit_composee(B, B, B, construit_composee(B, B, B, N)))));
	//image ar2 = construit_composee(N, B, N, construit_composee(N, B, N, B));
	//printf("%f",aire(ar2));

	/*Test Simplification*/
	//image simp= construit_composee(construit_composee(construit_noir(), construit_noir(), construit_composee(construit_noir(), construit_noir(), construit_noir(), construit_noir()), construit_noir()), construit_composee(construit_blanc(), construit_blanc(), construit_blanc(), construit_blanc()), construit_noir(), construit_composee(construit_blanc(), construit_noir(), construit_blanc(), construit_noir()));
	//AI_Simple(simp); printf("\n");
	//simplifie(&simp);
	//AI_Simple(simp);
	
	/*Tester si deux images repr�sentent le m�me dessin */
	//image md1= construit_composee(construit_noir(), construit_blanc(), construit_noir(), construit_composee(construit_blanc(), construit_blanc(), construit_blanc(), construit_composee(construit_noir(), construit_noir(), construit_noir(), construit_noir())));
	//image md2 = construit_composee(
	//	construit_composee(construit_noir(), construit_noir(), construit_noir(), 
	//		construit_composee(construit_noir(), construit_noir(), construit_noir(), 
	//			construit_composee(construit_noir(), construit_noir(), construit_noir(), construit_noir()))),
	//	construit_blanc(), construit_noir(),
	//	construit_composee(construit_blanc(),
	//		construit_composee(construit_blanc(), construit_blanc(), construit_blanc(), construit_blanc()),
	//		construit_blanc(), construit_noir()));
	//AI_Simple(md1);	printf("\n");
	//AI_Simple(md2);	printf("\n");
	//printf("%d", meme_dessin(md1, md2));
	//
	/*Test N�gatif*/
	//AI_Simple(i3);	printf("\n");
	//negatif(&i3);
	//AI_Simple(i3);	printf("\n");
	
	/*Test Diff�rence de deux images*/
	//image diff1 = construit_composee(construit_noir(), construit_blanc(), construit_blanc(), construit_noir());
	//image diff2 = construit_composee(construit_noir(), construit_noir(), construit_noir(), construit_noir());
	//AI_Simple(diff1); printf("\n");
	//AI_Simple(diff2); printf("\n");
	//image tmpDiff = Diff_2Images(diff1, diff2);
	//AI_Simple(tmpDiff); printf("\n");

	/*Test : Rendre une image � la m�moire */
	//image rm = construit_composee(N, B, construit_composee(N, B, N, B), B);
	//AI_Simple(rm); printf("\n");
	//RMemoire(&rm);
	//AI_Simple(rm); printf("\n");
	//printf("%d", est_blanche(rm)); printf("\n");

	/*Test CompteSousImagesPleines*/
	//image csip = construit_composee(construit_composee(construit_blanc(), construit_blanc(), construit_noir(), construit_blanc()), construit_composee(construit_noir(), construit_noir(),construit_blanc(), construit_noir()), construit_composee(construit_blanc(), construit_blanc(), construit_blanc(), construit_noir()), construit_composee(construit_noir(), construit_noir(), construit_noir(),construit_blanc()));
	//image csip = LClavier(); 
	//printf("%d\n", CompteSousImagesPleines(csip, 2));
	//printf("%d", CompteSousImagesPleines(construit_noir(), 0));

	/*Test Arrondit*/
	//image imgAr = construit_composee(construit_blanc(), construit_composee(construit_noir(), construit_noir(), construit_blanc(), construit_noir()), construit_composee(construit_noir(), construit_blanc(), construit_noir(), construit_noir()), construit_composee(construit_blanc(), construit_noir(), construit_noir(), construit_noir()));
	////image imgAr = construit_composee(construit_noir(),construit_noir(), construit_noir(), construit_blanc());
	//AI_Simple(imgAr); printf("\n");
	//arrondit(&imgAr, 0);
	//AI_Simple(imgAr); printf("\n");


	/*Test Affichage 2^k*/
	
	image img2k = construit_composee(construit_blanc(), construit_composee(construit_noir(), construit_noir(), construit_blanc(), construit_noir()), construit_composee(construit_noir(), construit_blanc(), construit_noir(), construit_noir()), construit_composee(construit_blanc(), construit_noir(), construit_noir(), construit_noir()));
	AI_Simple(img2k); printf("\n");
	int k = 3;
	//int len = (int)pow(2, k);
	//char ** a;
	//a = (char**)malloc(len * sizeof(char*));
	//for (int i = 0; i < len; i++) {
	//	a[i] = (char*)malloc(len * sizeof(char));
	//}

	AI_2k(img2k, &k);
	//printf2k(&a, len);


	Sleep(1000000000);
	return 0;
}

