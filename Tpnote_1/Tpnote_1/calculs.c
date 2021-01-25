#include <stdio.h>
/*le math.h sert à faire des tests dans le main, il n'est utilisé dans auncune fonction.*/
#include <math.h>
#include <windows.h>

/**************************************************************/
/**1°Calculez e en utilisant la somme des inverses des factorielles**/
/**************************************************************/
double calcul_e() {
	int i = 1,tmp = 1;
	double e = 1;
	while (1.0/tmp >= 1e-6){
		e += 1.0 / tmp;
		i++;
		tmp *= i;
	}
	return e;
}

/**************************************************************/
/**2° Puissance**/
/**************************************************************/
/*Float: version complexite quadratique*/
float PS_Fl_Quad(float x, long n) {
	float res = 1.0;
	if (n > 0) {
		for (long i = 0; i < n; i++)
			res *= x;
	}
	else if (n < 0) {
		for (long i = 0; i < -n; i++)
			res =res*( 1.0 / x);
	}
	return res;
}

/*Float: Version complexite linéaire*/
float PS_Fl_Lin(float x, long n) {
	if (n == 0)
		return 1.0;
	else if (n < 0)
		return 1.0 / PS_Fl_Lin(x,-n);
	else
		return x * PS_Fl_Lin(x, (n - 1));
}

/*Float: Version complexite log*/
float PS_Fl_log(float x, long n, float r) {
	//printf("%d\n",n);
	if (n == 0)
		return r;
	else {
		if (n % 2 == 0)
			return PS_Fl_log(x*x, n / 2, r);
		else
			return PS_Fl_log(x*x, n / 2, r*x);
	}
}


/*Double: version complexite quadratique*/
double PS_DB_Quad(double x, long n) {	
	double res = 1.0;
	if (n > 0) {
		for (long i = 0; i < n; i++)
			res *= x;
	}
	else if (n < 0) {
		for (long i = 0; i < -n; i++)
			res *=1.0 / x;
	}
	return res;
}

/*Double: Version complexite lineaire*/
double PS_DB_Lin(double x, long n) {
	if (n == 0)
		return 1.0;
	else if (n < 0)
		return 1.0 / PS_DB_Lin(x,-n);
	else
		return x * PS_DB_Lin(x, (n - 1));
}

/*Double: Version complexite log*/
double PS_DB_log(double x, long n, double r) {
	if (n == 0)
		return r;
	else {
		if (n % 2 == 0)
			return PS_DB_log(x*x, n / 2, r);
		else
			return PS_DB_log(x*x,n/2,r*x);
	}
}

/**************************************************************/
/**3°les deux methodes pour calculer la fonction d'Ackermann**/
/**************************************************************/
int ack_V1(int m, int n)
{
	if (m == 0)
		return n + 1;
	else if (n == 0)
		return ack_V1(m - 1, 1);
	else
		return ack_V1(m - 1, ack_V1(m, n - 1));
}

int ack_V2(int m, int n) {
	while (m != 0) {
		if (n == 0) n = 1;
		else {
			n = ack_V2(m, n - 1);
		}
		m--;
	}
	return n + 1;
}

/**************************************************************/
/**4°reels**/
/**************************************************************/

/**Pseudo-code**/
//reel(in:int n) :double
//	double res = 1;
//	while (n > 0) {
//		res = res + 1.0 / res;
//		n--;
//	}
//	rendre res;

double reel_Iter(int n) {
	double res = 1.0;
	while (n > 0) {
		res = res + 1.0 / res;
		n--;
	}
	return res;
}

double reel_Rec(int n) {
	if (n == 0)
		return 1;
	else {
		double tmp = reel_Rec(n - 1);
		return tmp + 1.0 / tmp;
	}
}

int main() {
	/**************************************************************/
	/*Test e*/
	//calcul_e();
	/**************************************************************/
	
	/**************************************************************/
	/*Test puissance*/
	/*Je definie la valeur maximale de k */
	int MAX = 4;
	/* On fait la comparaison des resultats avec une boucle,
	 * J'utilise la fonction pow(x,y) pour initilaiser les valeurs a tester
	 */
	for (int k = 1; k < MAX; k++) {
		float xf = (float)(1.0 + pow(10, -k));
		double xd = (double)(1.0 + pow(10, -k));
		long n = (long)pow(10, k);
		printf("Resultat du type float pour calculer %f^%d= \n", xf, n);
		printf("Complexite quadratique: %f\n", PS_Fl_Quad(xf, n));
		printf("Complexite lineaire: %f\n", PS_Fl_Lin(xf, n));
		printf("Complexite ln: %f\n", PS_Fl_log(xf, n, 1.0));
		printf("Resultat du type double pour calculer %f^%d= \n", xd, n);
		printf("Double qudratique: %lf^%d=%lf\n", xd, n, PS_DB_Quad(xd, n));
		printf("Double lineaire: %lf^%d=%lf\n", xd, n, PS_DB_Lin(xd, n));
		printf("Double log: %lf^%d=%lf\n", xd, n, PS_DB_log(xd, n, 1.0));
		printf("\n");

	}

	/*Conclusion sur la comparaison:
		1. Plus le k est grand,
		   le resultat de (1 + 10^k)^(10^k) est plus proche du constant "e".
		2. Le resultat du type double est plus precis que celui du type float
		3. Pour les resultats de type float,
		   plus la valeur de "10^k" est grande,
		   le resultat de la version ayant une complexite en ln est plus precis,
		   par rapport aux autres versions de float.
	*/
	/**************************************************************/


	/**************************************************************/
	/*Test Ackermann*/
	//printf("%d\n", ack_V1(3, 3));
	//printf("%d\n", ack_V2(3, 3));
	/**************************************************************/

	/**************************************************************/
	/*Test réel*/
	//printf("%f\n", reel_Iter(100));
	//printf("%f\n", reel_Rec(100));
	/**************************************************************/

	Sleep(10000000);
	return 0;
} 