//Buster Hultgren Wärn - dv17bhn
//Laboration 2
//A short program which select 3-11 judjes to score a competition.
//Highest, lowest and avarage score are to be printed on screen
#include <stdio.h>


//Function 1: writes information
void info (void) {
	
	printf("Program information\n");
	printf("The program reads in the number of judges and the score from each judge.\n");
	printf("Then it calculates the average score without regard to the lowest and\n");
	printf("highest judge score. Finally it prints the results (the highest, the\n");
	printf("lowest and the final average score).\n\n");

	return;
}


//Function 2: chooses number of judges between a competition
//Returns: number of judges
int electJudges (void) {
	int judges;
	
	do {
		printf("Number of judges (min 3 and max 10 judges)? ");
		scanf("%d", &judges);
	} while (judges < 3 || judges > 10);
	
	printf("\n");
	return judges;
}


//Function 3: reads score of judges -> points it to array
//Input: pointer/array of judges
void readScore (int nrOfJudges, double score[nrOfJudges]) {
	
	int i;
	for (i = 0; i < nrOfJudges; i++) {
		printf("Score from judge %d? ", i + 1);
		scanf("%lf", &score[i]);
	}
	printf("\n");

	return;
}


//Function 4: writes the score of the judges
//Input: array of judges and nr of judges
void writeScore (int nrOfJudges, double score[nrOfJudges]) {
	
	printf("Loaded scores:\n");

	int i;
	for (i = 0; i < nrOfJudges; i++) {
		printf("Judge %d: %.1f\n", i + 1, score[i]);
	}
	printf("\n");

	return;
}


//Function 5: calculates final scores stores it via pointers back to "original" adress
//Input: array of judges and nr of judges
//Input: adress to highScore, lowScre and avgScore (to be stored in pointers)
void calcScore (int nrOfJudges, double score[nrOfJudges], double *highScore, double *lowScore, double *avgScore) {
	
	int i;
	//Temporary local variable for low, high and avg scores
	double tempAvg;
	//temp low and high are given which are defined within the score array
	double tempHigh = score[0];
	double tempLow = score[0];
	
	//Looping through array of scores, adding high and low score
	for(i = 0; i < nrOfJudges; i++) {
		
		tempAvg = tempAvg + score[i];
		
		if (score[i] < tempLow) {
			
			tempLow = score[i];
		}
		
		if (score[i] > tempHigh) {
			
			tempHigh = score[i];
		}
	}
	
	//Calculating the avarage score without the high and low scores
	tempAvg = (tempAvg - tempHigh - tempLow) / (nrOfJudges - 2);
	
	//pointing scores (values) to original adresses
	*highScore = tempHigh;
	*lowScore = tempLow;
	*avgScore = tempAvg;

	return;
}


//Function 6: writes the calculated results to screen
//Input: adress to highScore, lowScre and avgScore (to be stored in pointers)
void writeFinalScore (double *highScore, double *lowScore, double *avgScore) {
	
	printf("Final result:\n");
	printf("Highest judge score: %.1f\n", *highScore);
	printf("Lowest judge score: %.1f\n", *lowScore);
	printf("Final average score: %.1f\n", *avgScore);

	return;
}


//Main function
int main(void) {
	
	int nrOfJudges;
	
	double highScore;
	double lowScore;
	double avgScore;
	
	info();
	
	//Reads number of judges before assigning them to array
	nrOfJudges = electJudges();
	double score[nrOfJudges];
	
	readScore(nrOfJudges, score);
	writeScore(nrOfJudges, score);
	calcScore(nrOfJudges, score, &highScore, &lowScore, &avgScore);
	writeFinalScore(&highScore, &lowScore, &avgScore);
	
	return 0;
}