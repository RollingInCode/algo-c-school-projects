#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int hourPay, hourPerWeek, numOfWeeks, videoGameCost = 30;
    int leftOverMoney, leftOverGames;

    printf("How much do you get paid per hour?\n");
    scanf("%d", &hourPay);
    printf("How many hours did you work per week?\n");
    scanf("%d", &hourPerWeek);
    printf("How many weeks are you working this summer?\n");
    scanf("%d", &numOfWeeks);
    leftOverMoney = ((hourPay*hourPerWeek*numOfWeeks)%(videoGameCost));
    leftOverGames = ((hourPay*hourPerWeek*numOfWeeks)/(videoGameCost));
    printf("Look here buddy, this is how much money you have left over during the summer: %d \n", leftOverMoney);
    printf("Here's all the games you could buy with that money: %d", leftOverGames);
    //printf()

    //printf("%d", videoGameCost);

    return 0;
}

// lesson to be learned, you have to use arithmetic operations in this program
//this problem is also right!
