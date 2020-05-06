#include <stdio.h>
#include <math.h>

int get_rate_drop_factor(int x, int y, int z);
int CalcProb2(int a, int b);
double get_kg_rate_conc(double e, int f, int g, int h);
int get_units_conc(int i, int j, int k);
int fig_drops_min(int xi, int yi, int zi);
int fig_ml_hr(int aii, int bii);
int by_weight(double eiii, int fiii, int giii, int hiii);
int by_units(int iiv, int jiv, int kiv);

int main(){
	
	//Variable of main menu
	int problem = 0; // Problem number
	
	//Variable of Problem 1
	int pro1_rate = 0; 
	int pro1_drop = 0; 
	int pro1_output = 0; 
	
	//Variable of Problem 2
	int hours = 0; 
	int pro2_output = 0; 
	
	//Variable of Problem 3
	double mg_per_kg_per_hr = 0.0; 
	int PaitientWeight = 0; 
	int mg_per_ml = 0; 
	int pro3_output = 0; 
	
	//Variable of Problem 4
	int units_per_hour = 0; 
	int units_per_ml = 0; 
	int pro4_output = 0; 
	
	do{ 
		problem = get_problem();

		if(problem == 1)
			get_rate_drop_factor(pro1_drop, pro1_rate, pro1_output);
		else if(problem == 2)
			CalcProb2(hours, pro2_output);
		else if(problem == 3)
			get_kg_rate_conc(mg_per_kg_per_hr, PaitientWeight, mg_per_ml, pro3_output);			
		else if(problem == 4)
			get_units_conc(units_per_hour, units_per_ml, pro4_output);	
		else if(problem == 5)
			break;
	}while(1);
	
	return 0;
}

int get_problem(){
	int problem;
	
	//Main Menu
	printf("\n\n INTRAVENOUS RATE ASSASSTANT");
	printf("\n\n Enter the number of the problem you wish to solve.");
	printf("\n     GIVEN A MEDICAL ORDER IN              CALCULATE RATE IN");
	printf("\n (1) ml/hr & tubing drop factor            drops / min");
	printf("\n (2) 1 L for n hr                          ml / hr");
	printf("\n (3) mg/kg/hr & concentration in mg/ml     ml / hr");	
	printf("\n (4) units/hr & concentration in units/ml  ml / hr");	
	printf("\n (5) QUIT\n");
	printf("\n Problem =>");
	scanf("%d", &problem);
	return problem;
}

//Problem 1
int get_rate_drop_factor(int x, int y, int z){
	int result = 0;
	printf("\nEnter rate in ml/hr=>");
	scanf("%d", &x);
	printf("Enter tubing's drop factor(drops/ml)=>");
	scanf("%d", &y);
	
	result = fig_drops_min(x, y, z);
	printf("The drop rate per minute is %d.\n", result);
	return result;
}

//Problem 2
int CalcProb2(int a, int b){
	int result = 0;
	printf("\nEnter number of hours=>");
	scanf("%d", &a);
	
	result = fig_ml_hr(a, b);
	printf("The rate in mililiters per hour is %d.", result);
	return result;
}

//Problem 3
double get_kg_rate_conc(double e, int f, int g, int h){
	int result = 0;
	
	printf("\nEnter rate in mg/kg/hr=>");
	scanf("%lf", &e);
	printf("Enter patient weight in kg=>");
	scanf("%d", &f);
	printf("Enter concentration in mg/ml=>");
	scanf("%d", &g);
	
	result = by_weight(e, f, g, h);
	printf("The rate in mililiters per hour is %d.\n", result);
	return result;
}

//Problem 4
int get_units_conc(int i, int j, int k){
	
	int result = 0;	
	printf("\nEnter rate in units/hr=>");
	scanf("%d", &i);
	printf("Enter concentration in units/ml=>");
	scanf("%d", &j);
	
	result = by_units(i, j, k);
	printf("The rate in mililiters per hour is %d.\n", result);
	return result;
} 

//Problem 1 Formula
int fig_drops_min(int xi, int yi, int zi){
	zi = round((double)xi * (double)yi / 60.0);
	return zi;
}

//Problem 2 Formula
int fig_ml_hr(int aii, int bii){
	int result = 0;
	bii = 1000 / aii;
	return bii;
}

//Problem3 Fomula
int by_weight(double eiii, int fiii, int giii, int hiii){
	hiii = (eiii * fiii) / giii;
	return hiii;
}

//Problem4 Fomula
int by_units(int iiv, int jiv, int kiv){
	kiv = iiv / jiv;
	return kiv;
}