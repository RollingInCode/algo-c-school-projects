#include <stdio.h>
#include <stdlib.h>

int main(void) {
    double gasPerGallonPrice, extraGas;
    int numOfGas, milesPerGallon, lengthOfTrip;
    int gallonsOfGasCar;
    printf("What is the price of gasoline per gallon?\n");
    scanf("%lf", &gasPerGallonPrice);
    printf("How many gallons of gas is in your car?\n");
    scanf("%d", &gallonsOfGasCar);
    printf("How many miles does your car get per gallon?\n");
    scanf("%d", &milesPerGallon);

    printf("How far is this road trip?\n");
    scanf("%d", &lengthOfTrip);

    if (lengthOfTrip < (gallonsOfGasCar*milesPerGallon)) {
        extraGas = 0.00;
    }
    else {
    extraGas = (double) (((gallonsOfGasCar*milesPerGallon)%(lengthOfTrip))*(gasPerGallonPrice));
    }
    printf("This is how much more you have to spend on gas to complete the road trip: %.2f", extraGas);

    return 0;
}

//DONE!!!
