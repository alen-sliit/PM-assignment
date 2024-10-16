#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROUNDS 13
#define DICE 5
#define CATEGORIES 8

void rollDice();
void humanTurn();
int chooseCategory();
int calculateScore(int category);
int getScoreAKind(int Category);
void getCardCount();
int isLargeStraight();
int isFullHouse();
int isSmallStraight();
int isYAHTZEE();
int computerTurn();
int optimalThinking();
int checkReroll();
int maxDice();
int isNumberInArray(int arr[], int size, int number);
void printScorecard(int humanScores[13],int computerScores[13], char* player1, char* player2);
int chooseWinner();

int humanChosen[ROUNDS];
int computerChosen[ROUNDS];
int humanChosenCount = 0; int computerChosenCount = 0;
int max, maxCategory1, maxCategory2, maxCount, sum;
int countArray[6];
int dice[DICE];
int humanScoreList[13] = {0};
int computerScoreList[13] = {0};
int humanScoreTotal = 0; int computerScoreTotal = 0;
char *categories[] = {
        "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", 
        "Three of a kind", "Four of a kind", "Full House", 
        "Small straight", "Large straight", "YAHTZEE", "Chance", "Total"
    };

int main() {
    
    int category, tempScore;
    // srand(time(NULL));
    printf("Welcome to Two-Player Yahtzee (Human vs Computer)\n");

    //Rounds 13
    for(int rounds; rounds < ROUNDS; rounds++){
        printf("-----------------Round %d-----------------\n", rounds + 1);
        printf("Human's turn:\n");
        humanTurn();
        category = chooseCategory();
        tempScore = calculateScore(category);
        humanScoreList[category - 1] =  tempScore;
        humanScoreTotal += tempScore;
        
        system("clear");

        printf("\nComputer's turn:\n");
        category = computerTurn();
        tempScore = calculateScore(category);
        computerScoreList[category - 1] =  tempScore;
        computerScoreTotal += tempScore;
        printScorecard(humanScoreList,computerScoreList, "alen", "Computer");
    }
    chooseWinner();
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
        
        for (int i = 0; i < DICE; i++) 
            do{
                printf("Keep die %d? (0: Re-roll, 1: Keep): ", dice[i]);
                scanf("%d", &reroll[i]);
            }while (reroll[i] != 0 && reroll[i] != 1 );
        
        printf("Rolled dice: ");
        for (int i = 0; i < DICE; i++) {
            if (reroll[i] == 0) 
                dice[i] = (rand() % 6) + 1;  // Re-roll the selected dice
            printf("%d ", dice[i]);
        }
        printf("\n");
    }
}

// Choose scoring category for human player
int chooseCategory() {
    int input;
    int alreadyChosen = 0;

    for (int i = 0; i < 13; i++)
        printf(" %d for %s\n", i + 1, categories[i]);

    do {
        alreadyChosen = 0;
        do{
            printf("Enter a number: ");
            scanf("%d", &input);
        }while(input < 0 || input > 14);

        // Check if input was already chosen
        for (int i = 0; i < humanChosenCount; i++) 
            if (humanChosen[i] == input) {
                alreadyChosen = 1;
                printf("This number is already chosen. Try again.\n");
            }
        // If not already chosen, store it in the chosen array and break the loop
        if (!alreadyChosen) {
            humanChosen[humanChosenCount] = input;
            humanChosenCount++;
        }
    } while (alreadyChosen);
    return input;
}

int chooseWinner(){
    if (humanScoreTotal > computerScoreTotal) 
        printf("\nHuman wins with a score of %d vs %d!\n", humanScoreTotal, computerScoreTotal);
    else if (humanScoreTotal < computerScoreTotal) 
        printf("\nComputer wins with a score of %d vs %d!\n", computerScoreTotal, humanScoreTotal);
    else 
        printf("\nIt's a tie! Both players scored %d!\n", humanScoreTotal);
}

int calculateScore(int category) {
    int score = 0;
    getCardCount();

    if (category > 0 && category < 7){
        for (int i = 0; i < DICE; i++) 
            if (dice[i] == category) 
                score += dice[i];
    } else 
        switch (category) {
            case 7: score += getScoreAKind(category);
                    break;
            case 8: score += getScoreAKind(category);
                    break;
            case 9: if (isFullHouse())     score += 25;
                    break;
            case 10:if (isSmallStraight()) score += 30;
                    break;
            case 11:if (isLargeStraight()) score += 40;
                    break;
            case 12:if (isYAHTZEE())       score += 50;
                    break;
            case 13:for (int i = 0; i < DICE; i++) 
                        score += dice[i];
            default:
                printf("Choose a valid category\n");
        }
    return score;
}

void getCardCount(){
    for (int i = 0; i < 6; i++) 
        countArray[i] = 0;

    for (int i = 0; i < DICE; i++) {
        countArray[dice[i] - 1]++;
        }
}

int getScoreAKind(int Category){
    int score;
    int isValid;
    for (int i = 0; i < DICE; i++){
        if (countArray[i] >= Category)
            isValid = 1;
        score += dice[i];
    }
    if (isValid) return score;
    return 0;
}

int isLargeStraight(){
    int count1 = 0; int count2 = 0;
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
    int valid = 0;
    for (int x = 0; x < 3; x++)
        for (int i = x; i < x + 4; i++){
            if (countArray[i] == 0){
                valid = 0;
                break;
            }
            else valid  = x + 1;
            if (i == x + 3) return (x + 1);
        }
        return valid;
}

int isFullHouse(){
    int condionOne = 0; int condionTwo = 0;
    for (int i = 0; i < 6; i++){
        if (countArray[i] == 3)
            condionOne = 1;
        if (countArray[i] == 2)
            condionTwo = 1;
    }
    if (condionOne && condionTwo) return 1;
    return 0;
}

int is3seq(){
    int valid = 0;
    for (int x = 0; x < 4; x++)
        for (int i = x; i < x + 3; i++){
            if (countArray[i] == 0){
                valid = 0;
                break;
            }
            else valid  = x + 1;
            if (i == x + 2) return (x + 1);
        }
        return valid;
}

int computerTurn(){
    int ifReroll; int category;
    rollDice();

    for (int roll = 0; roll < 2; roll++){
        maxDice();
        checkReroll();

        printf("0ed dice: ");
        for (int i = 0; i < DICE; i++)
            printf("%d ", dice[i]);
        printf("\n");

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
    maxDice();
    // prioratize 12,11,10,9
    if (!isNumberInArray(computerChosen, computerChosenCount, 12))
        if (isYAHTZEE())
            return 12;
    if (!isNumberInArray(computerChosen, computerChosenCount, 11))
        if (isLargeStraight())
            return 11;
    if (!isNumberInArray(computerChosen, computerChosenCount, 10))  
        if (isSmallStraight())
            return 10;
    if (!isNumberInArray(computerChosen, computerChosenCount, 9))
        if (isFullHouse())
            return 9;

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
            if (maxCategory1 == i && maxCategory2 == 0 )
                return i;
    // sacrificing 1,2,3
    for (int i = 1; i < 4; i++)
        if (!isNumberInArray(computerChosen, computerChosenCount, i))  
            return i;
    // last option  
    for (int i = 1; i < 14; i++)
        if (!isNumberInArray(computerChosen, computerChosenCount, i))    
            return i;
    return 0;
}

int maxDice(){    
    int mark;      
    max = 1; maxCount = 1; maxCategory2 = 0; maxCategory1 = 0; sum = 0;
    getCardCount();

    for (int i=0; i < 6; i++){  
        sum += dice[i];  
        if (countArray[i] > max){      
            max = countArray[i];        
            maxCategory1 = i + 1;
            mark = i;
        }
    }   
    for (int i=0; i < 6; i++)
        if(countArray[i] == max && i != mark){
            maxCategory2 = i + 1;
            maxCount++;
        }
    printf("Count Array: ");
    for (int i=0; i < 6; i++)
        printf("%d ", countArray[i]);
    printf("\n");

    printf("maxCount: %d ", maxCount);
    printf("max: %d ", max);
    printf("maxCat1: %d ", maxCategory1);
    printf("maxCat2: %d ", maxCategory2);
    printf("sum: %d\n", sum);

    printf("Computer Chosen cat: ");
    for (int i=0; i < 13; i++)
        printf("%d ", computerChosen[i]);
    printf("\n");    
    
}

// Check if number is in the array
int isNumberInArray(int arr[], int size, int number) {
    for (int i = 0; i < size; i++) 
        if (arr[i] == number) 
            return 1; 
    return 0; 
}

int checkReroll(){
    // Going for Yachzzt1
    if (!isNumberInArray(computerChosen,computerChosenCount,12))
        if (isYAHTZEE())
            return 0;

    // Going for a Full House
    if (!isNumberInArray(computerChosen,computerChosenCount,9)){
        if (maxCount == 2)
            for (int i = 0; i < DICE; i++)                              
                if (dice[i] != maxCategory1 && dice[i] != maxCategory2)
                    dice[i] = 0;
        return 0;
    }
    // Rerolling for Large straight
    if (!isNumberInArray(computerChosen,computerChosenCount,11) && max < 3){
        if (isLargeStraight()) return 0;
        int count = 0;
        int valid = isSmallStraight();

        if (valid) 
            for (int i = 0; i < DICE; i++){ 
                if (countArray[dice[i] - 1] == 2){
                    if (count)
                        dice[i] = 0;
                    count++;
                }
                if (valid == 1)
                    if (dice[i] == 6)
                        dice[i] = 0;
                if (valid == 3)
                    if (dice[i] == 1)
                        dice[i] = 0;
            }                     
    }

    // Rerolling for small straight
    if ((!isNumberInArray(computerChosen,computerChosenCount,10) || !isNumberInArray(computerChosen,computerChosenCount,11)) && (max < 3 || computerChosenCount > 7)){
        int count = 0;
        int valid = is3seq();

        if (valid)
            for (int i = 0; i < DICE; i++){
                if (countArray[dice[i] - 1] > 1){
                    if (count)
                        dice[i] = 0;
                    count++;
                }
                if (valid == 1)                
                    if (dice[i] == 6 || dice[i] == 5 )
                        dice[i] = 0;     
                if (valid == 2)                       
                    if (dice[i] == 6 )
                        dice[i] = 0;
                if (valid == 3)
                    if (dice[i] == 1)
                        dice[i] = 0;
                if (valid == 4)                           
                    if (dice[i] == 1 || dice[i] == 2)
                        dice[i] = 0; 
        }
        return 0;  
    }

    // Rerolling for maximaize the maximum nummber
    if (maxCategory1 > maxCategory2 && maxCategory1 > 2)
        if ((!isNumberInArray(computerChosen, computerChosenCount, maxCategory1) || computerChosenCount > 7)){
            for (int i = 0; i < DICE; i++)                              
                if (dice[i] != maxCategory1)
                    dice[i] = 0;
            return 0;
        }
    
    if (!isNumberInArray(computerChosen, computerChosenCount, maxCategory2) && maxCategory2 > 2){
            for (int i = 0; i < DICE; i++)                              
                if (dice[i] != maxCategory2)
                    dice[i] = 0;
            return 0;
        }  

    printf("Last option!!\n");  
    for (int i = 6; i > 0; i--)
        if (!isNumberInArray(computerChosen, computerChosenCount, i)){ 
            printf("going for %d\n",i);         
            for (int x = 0; x < DICE; x++)                              
                if (dice[x] != i)
                    dice[x] = 0;
            return 0;
        }
    return 0;   
}

void printScorecard(int humanScores[13],int computerScores[13], char* player1, char* player2) {
    printf("+------------------+----------+----------+\n");
    printf("|                  | %-8s | %-8s |\n", player1, player2);
    printf("+------------------+----------+----------+\n");

    for (int i = 0; i < 14; i++) {
        if (i == 13)
            printf("| %-16s | %8d | %8d |\n", categories[i], humanScoreTotal, computerScoreTotal);
        else
            printf("| %-16s | %8d | %8d |\n", categories[i], humanScores[i], computerScores[i]);
        printf("+------------------+----------+----------+\n");
    }
}

    // dice       = {1,4,4,6,6}
    // countArray = {1,0,0,2,0,2} 
    // max        = {2}
    // category   = {4} 
    // maxcount   = {2} 2 4s and 2 6s