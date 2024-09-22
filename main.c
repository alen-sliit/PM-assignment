#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROUNDS 13
#define DICE 5
#define CATEGORIES 8

void rollDice();
void humanTurn();
int chooseCategory();
int getScore(int countOne, int countTwo, int countThree, int countFour, int countFive, int Category);
int calculateScore(int category);
int getScoreAKind(int Category);
int* getCardCount();
int isLargeStraight();
int isFullHouse();
int isSmallStraight();
int isYAHTZEE();
int computerTurn();
int optimalThinking();
int checkReroll();
int sumDice();
int maxDice();
int isNumberInArray(int arr[], int size, int number);


// Scoring categories
enum Categories { ONES = 1, TWOS, THREES, FOURS, FIVES, SIXES, THREE_OF_A_KIND, FOUR_OF_A_KIND, FULL_HOUSE, SMALL_STRAIGHT, LARGE_STRAIGHT, YAHTZEE, CHANCE };

int humanChosen[ROUNDS];
int computerChosen[ROUNDS];
int humanChosenCount;
int computerChosenCount;
int max, maxCategory1, maxCategory2;
int maxCount = 1;
int countArray[6];
int dice[DICE];
int humanScoreList[13] = {0};
int computerScoreList = {0};

int main() {
    int humanScore = 0, computerScore = 0;
    int category;

   // srand(time(NULL));
    
    printf("Welcome to Two-Player Yahtzee (Human vs Computer)\n");

    //Rounds 13
    for(int rounds; rounds < ROUNDS; rounds++){
        printf("------------Round %d------------\n", rounds + 1);
        printf("Human's turn:\n");
        humanTurn();
        category = chooseCategory();
        humanScore += calculateScore(category);
        system("clear");
        printf("Human's total score: %d\n", humanScore);

        printf("\nComputer's turn:\n");
        category = computerTurn();
        
        computerScore += calculateScore(category);
        printf("Computer's total score: %d\n", computerScore);
         
    }
    return 0;
}

void rollDice() {
    printf("Rolled dice: ");
    for (int i = 0; i < DICE; i++) {
        dice[i] = (rand() % 6) + 1;
        printf("%d ", dice[i]);
    }
    printf("\n");
}

void humanTurn() {
    rollDice();
    int reroll[DICE];
    int rerolls;
    
    for (int roll = 0; roll < 2; roll++) {  // Allow 2 rerolls (3 rolls total)
        do{
            printf("Do you want to re-roll? (0: No, 1: Yes): ");
            scanf("%d", &rerolls);
        }while (rerolls != 0 && rerolls != 1 );
        
        if (rerolls == 0) 
            break;
        
        for (int i = 0; i < DICE; i++) {
            do{
                printf("Keep die %d? (0: Re-roll, 1: Keep): ", dice[i]);
                scanf("%d", &reroll[i]);
            }while (reroll[i] != 0 && reroll[i] != 1 );
        }
        printf("Rolled dice: ");
        for (int i = 0; i < DICE; i++) {
            if (reroll[i] == 0) {
                dice[i] = (rand() % 6) + 1;  // Re-roll the selected dice
            }
            printf("%d ", dice[i]);
        }
        printf("\n");
        
    }
}

// Choose scoring category for human player
int chooseCategory() {
    printf(" 1 for ONES\n 2 for TWOS\n 3 for THREES\n 4 for FOURS\n 5 for FIVES\n 6 for SIXES\n 7 for THREE OF A KIND\n 8 for FOUR OF A KIND\n 9 for FULL HOUSE\n 10 for SMALL STRAIGHT\n 11 for LARGE STRAIGHT\n 12 for YAHTZEE\n 13 for CHANCE\n ");
    int input;
    
    int alreadyChosen = 0;

    do {
        alreadyChosen = 0;
        do{
            printf("Enter a number: ");
            scanf("%d", &input);
        }while(input < 0 || input > 14);

        // Check if input was already chosen
        for (int i = 0; i < humanChosenCount; i++) {
            if (humanChosen[i] == input) {
                alreadyChosen = 1;
                printf("This number is already chosen. Try again.\n");
            }
        }

        // If not already chosen, store it in the chosen array and break the loop
        if (!alreadyChosen) {
            humanChosen[humanChosenCount] = input;
            humanChosenCount++;
        }

    } while (alreadyChosen);
    return input;
}

int chooseWinner(int humanPoints, int computerPoints){
    if (humanPoints > computerPoints) {
        printf("\nHuman wins with a score of %d vs %d!\n", humanPoints, computerPoints);
    } else if (humanPoints < computerPoints) {
        printf("\nComputer wins with a score of %d vs %d!\n", computerPoints, humanPoints);
    } else {
        printf("\nIt's a tie! Both players scored %d!\n", humanPoints);
    }

}

int calculateScore(int category) {
    int score = 0;
    
    getCardCount();

    switch (category) {
        case ONES:
        case TWOS:
        case THREES:
        case FOURS:
        case FIVES:
        case SIXES:
            for (int i = 0; i < DICE; i++) {
                if (dice[i] == category) {
                    score += dice[i];
                }
            }
            break;
        case THREE_OF_A_KIND:
            score += getScoreAKind(category);
            break;
        case FOUR_OF_A_KIND: 
            score += getScoreAKind(category);
            break;
        case FULL_HOUSE:
            if (isFullHouse())
                score += 25;
            else    
                printf("Combo is not valid\n");
            break;
        case SMALL_STRAIGHT:
            if (isSmallStraight())
                score += 30;
            else    
                printf("Combo is not valid\n");
            break;
        case LARGE_STRAIGHT:
            if (isLargeStraight())
                score += 40;
            else    
                printf("Combo is not valid\n");
            break;

        case YAHTZEE:
            if (isYAHTZEE())
                score += 50;
            else
                printf("Combo is not valid\n");
            break;

        case CHANCE:
            for (int i = 0; i < DICE; i++) {
                score += dice[i];
            }
            break;
            
        default:
            printf("Choose a valid category\n");
        

    }
    return score;
}

int* getCardCount(){
    
    for (int i = 0; i < 6; i++) 
        countArray[i] = 0;

    for (int i = 0; i < DICE; i++) {
        switch (dice[i]){
        case 1:
            countArray[0] += 1;
            break;
        case 2:
            countArray[1] += 1;
            break;
        case 3:
            countArray[2] += 1;
            break;
        case 4:
            countArray[3] += 1;
            break;
        case 5:
            countArray[4] += 1;
            break;
        case 6:
            countArray[5] += 1;
            break;
                
        default:
            break;
    }}
}

int getScoreAKind(int Category){
    int score;
    int isValid;
    for (int i = 0; i < DICE; i++){
        if (countArray[i] >= Category)
            isValid = 1;
        score += dice[i];
    }
    if (isValid)
        return score;
    return 0;
}

int isLargeStraight(){
    int count1 = 0;
    int count2 = 0;
    for (int i = 0 ; i < 5; i++){
        if (countArray[i] == 1)
            count1++;
        if (countArray[i+1] == 1)
            count2++;
    }
    if (count1 == 5 || count2 == 5)
        return 1;
    
    return 0;
}

int isYAHTZEE(){
    for (int i = 0; i < 6; i++)
        if (countArray[i] == 5)
            return 1;
    return 0;
}

int isSmallStraight(){
    int isValid = 0;

    for (int i = 0; i < 4; i++){
        if (countArray[i] == 0){
            isValid = 0;
            break;
        }
        else isValid = 1;
    }
    for (int i = 1; i < 5; i++){
        if (countArray[i] == 0){
            isValid = 0;
            break;
        }
        else isValid = 2;
    }
    for (int i = 2; i < 6; i++){
        if (countArray[i] == 0){
            isValid = 0;
            break;
        }
        else isValid = 3;
    }
    return isValid;
}

int isFullHouse(){
    int condionOne = 0;
    int condionTwo = 0;
    for (int i = 0; i < 6; i++){
        if (countArray[i] == 3)
            condionOne = 1;
        if (countArray[i] == 2)
            condionTwo = 1;
    }
    if (condionOne && condionTwo)
        return 1;
    return 0;
}

int computerTurn(){
    int ifReroll;
    int category;

    rollDice();

    for (int roll = 0; roll < 2; roll++){
        maxDice();
        checkReroll();

        printf("Rerolled dice: ");
        for (int i = 0; i < DICE; i++){ 
            if (dice[i] == 0) 
                dice[i] = (rand() % 6) + 1;  // Re-roll the selected dice
            printf("%d ", dice[i]);
        }
        printf("\n");

        maxDice();
    }
    category = optimalThinking();
    printf("Computer Category: %d\n\n\n", category);

    computerChosen[computerChosenCount] = category;
    computerChosenCount ++;
    
    return category;

}

int optimalThinking(){

    int sum = sumDice();
    
    // prioratize 12,11,9
    if (!isNumberInArray(computerChosen, computerChosenCount, 12))
        if (isYAHTZEE())
            return 12;
        
    if (!isNumberInArray(computerChosen, computerChosenCount, 11))
        if (isLargeStraight())
            return 11;

    if (!isNumberInArray(computerChosen, computerChosenCount, 9))
        if (isFullHouse()){
            return 9;
        }
    
    // select small straight
    if (!isNumberInArray(computerChosen, computerChosenCount, 10)){    
        if (isSmallStraight())
            return 10;

    // if sum is not enough and max is 1,2,3 choose 1,2,3
    
    }
    if (!isNumberInArray(computerChosen, computerChosenCount, 8))    
        if (max == 4 && sum > 15) // check if FourofKind
            return 8;
    if (!isNumberInArray(computerChosen, computerChosenCount, 7))    
        if (max == 3 && sum > 11) // check if ThreeofKind
            return 7;
    if  (!isNumberInArray(computerChosen, computerChosenCount, 13))    
        if (max == 2 && sum > 18) // chance
            return 13;

    // select 6,5,4 if it is maximum
    for (int i = 6; i > 0; i--)
        if (!isNumberInArray(computerChosen, computerChosenCount, i))    
            if (maxCategory1 == i || maxCategory2 == i)
                return i;
    // last option 
    for (int i = 1; i < 14; i++)
        if (!isNumberInArray(computerChosen, computerChosenCount, i))    
            if (maxCategory1 == i || maxCategory2 == i)
                return i;
    
    return 0;
}

int sumDice(){
    int sum = 0;
    for (int i=0; i < DICE; i++)
        sum += dice[i];
    return sum;
}

int maxDice(){          
    max = 0;
    maxCount = 0;
    maxCategory2 = 0;
    maxCategory1 = 0;
    getCardCount();

    for (int i=0; i < 6; i++){
        if(countArray[i] == max){
            maxCategory2 = i + 1;
            maxCount++;
        }       
        if (countArray[i] > max){       
            max = countArray[i];        
            maxCategory1 = i + 1;
            maxCount = 1;
        }   
    }
    
    printf("Executing maxDice\n");

    printf("Count Array: ");
    for (int i=0; i < 6; i++)
        printf("%d ", countArray[i]);
    printf("\n");

    printf("maxCount: %d\n", maxCount);
    printf("max: %d\n", max);
    printf("maxCat1: %d\n", maxCategory1);
    printf("maxCat2: %d\n", maxCategory2);
    
}

// Check if number is in the array
int isNumberInArray(int arr[], int size, int number) {
    for (int i = 0; i < size; i++) 
        if (arr[i] == number) 
            return 1; 

    return 0; 
}

int checkReroll(){
    int sum = sumDice();

    // Going for Yachzzt1
    if (!isNumberInArray(computerChosen,computerChosenCount,12))
        if (max > 2)
            for (int i = 0; i < DICE; i++)                              
                if (dice[i] != maxCategory1 && dice[i] != maxCategory2)
                    dice[i] = 0;

    // Going for a Full House
    else if (!isNumberInArray(computerChosen,computerChosenCount,9))
        if (maxCount == 2)
            for (int i = 0; i < DICE; i++)                              
                if (dice[i] != maxCategory1 && dice[i] != maxCategory2)
                    dice[i] = 0;
                     
    // Going for LargeStraight
    else if (!isNumberInArray(computerChosen,computerChosenCount,11))
        if (isLargeStraight())
            return 0;

    // Rerolling for Large straight
    else if (!isNumberInArray(computerChosen,computerChosenCount,10 && !isNumberInArray(computerChosen,computerChosenCount,11))){
        int valid = isSmallStraight();

        if (valid == 1)
            for (int i = 0; i < DICE; i++)                              
                if (dice[i] == 6 || countArray[dice[i] - 1] == 2)
                    dice[i] = 0;
                
        if (valid == 2)
            for (int i = 0; i < DICE; i++)                              
                if (countArray[dice[i] - 1] == 2)
                    dice[i] = 0;
                
        if (valid == 3)
            for (int i = 0; i < DICE; i++)                              
                if (dice[i] == 1 || countArray[dice[i] - 1] == 2)
                    dice[i] = 0;   
        return 0;
    }
    

    else if (maxCategory1 > maxCategory2)
        for (int i = 0; i < DICE; i++)                              
            if (dice[i] != maxCategory1)
                dice[i] = 0;
    
    else for (int i = 0; i < DICE; i++)                              
        if (dice[i] != maxCategory2)
            dice[i] = 0;
    
    return 0;
}


    // dice       = {1,4,4,6,6}
    // countArray = {1,0,0,2,0,2} 
    // max        = {2}
    // category   = {4} 
    // maxcount   = {2} 2 4s and 2 6s