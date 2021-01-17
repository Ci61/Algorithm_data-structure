#include <stdio.h>
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
/**2°**/
/**************************************************************/
float PuissanceFL(float x, int n) {
	float res = 1.0;
	int i = 0;
	for (i = 0; i < n; i++)
		res *= x;
	return res;
}

double PuissanceDB(double x, int n) {
	double res = 1.0;
	int i = 0;
	for (i = 0; i < n; i++)
		res *= x;
	return res;
}

/*On fait plusieurs tests d'un coup*/
void test_Puissance(int MAX) {
	for (int k = 1; k < MAX; k++) {
		double x = (double)(1 + pow(10, -k));
		int n = (int)pow(10, k);
		printf("%f^%d=%f\n",x,n, Puissance(x, n));
	}
}
/*Obsevation: plus le k est grand, le résultat de (1 + 10^k)^(10^k) est plus proche du constant "e"*/


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
	/*Test e*/
	//calcul_e();
	
	/*Test puissance*/
	//test_Puissance(8);

	/*Test Ackermann*/
	//printf("%d\n", ack_V1(3, 3));
	//printf("%d\n", ack_V2(3, 3));

	/*Test réel*/
	//printf("%f\n", reel_Iter(100));
	//printf("%f\n", reel_Rec(100));

	Sleep(10000000);
	return 0;
} 