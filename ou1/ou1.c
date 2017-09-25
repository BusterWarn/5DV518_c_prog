//Övningsuppgift 1
//Buster Hultgren Wärn
//Senast ändrad: 2017-09-01

#include <stdio.h>


//Läser upp val som användaren har att göra i programmet
//Returnerar användaren val
int options (double exRate) {

	int option = 0;
	
	printf("1. Set exchange rate in SEK (current rate: %5.2f)\n", exRate);
	printf("2. Read prices in the foreign currency\n");
	printf("3. End\n\n");
	
	printf("Give your choice (1 - 3): ");
	scanf("%d", &option);
	printf("\n");
	
	return option;
}


//Läser in nuvarande exRate -> förändrar den med användarens input
//Returnerar nya exRate
double changeEx(double exc) {

	printf("Give exchange rate: ");
	scanf("%lf", &exc);
	printf("\n");
	return exc;
}


//Läser in nuvarande exRate -> kollar "utländkst" pris som användaren ger i input
//Läser upp pris i "utländsk" valuta och SEK.
double checkPrice (double exc) {

	double price = 0;
	double priceTotal = 0;

	while (price >= 0) {

		printf("Give price (finish with < 0): ");
		scanf("%lf", &price);

		if (price > 0) {

		priceTotal = priceTotal + price;
		}
	}

	printf("\n\nSum in foreign currenct: %5.2lf\n", priceTotal);
	printf("Sum in SEK: %5.2lf\n\n", priceTotal * exc);
	return 0;
}


int main (void) {

	int currOption = 0;
	double exRate = 1.00;
	
	printf("Your shopping assistant\n\n");
	
	//While loop som som styr tar in användarens val (options funktionen)
	//bestämmer vilken funktion (beroende på valet) som skall köras härnäst
	while (currOption != 3) {
    
		currOption = options (exRate);
		
		if (currOption == 1) {

			exRate = changeEx (exRate);
			
		} else if (currOption == 2) {

			checkPrice(exRate);

		} else if (currOption == 3) {

			//Programmet avslutas
			printf("End of program!\n");

		} else {

			printf("Not a valid choice\n\n");

		}
	}
	return 0;
}