#include <stdio.h>
#include <stdlib.h>

int main() {
    int heartBeat = 0;
    int heartBPM = 0;
    printf("How many beats per 15 seconds?");
    scanf('%i', &heartBeat);
    heartBPM = (4 * ((60*heartBeat)/15));

    printf("Your heartbeat per minute is '%i'\n, heartBPM");
    return 0;

}
