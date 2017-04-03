#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int _level = 9;
const int _line = 25;
const int _maxChar = 500; /*25 multiple line*/
const char pracChar[_level] = {'a', 's', 'd', 'f', 'j', 'k', 'l', ';', ' '};
time_t t;
int tmp;

int main() {

    /* Initializes random number generator */
    srand((unsigned) time(&t));

    for(int i = 1; i <= _maxChar; i++) {
    
        do {
            tmp = rand() % _level;
        } while(((i % _line == 0) || ((i - 1) % _line == 0 )) && (tmp == (_level - 1)));
        
        if(i % _line == 0){
            printf("%c\n", pracChar[tmp]);
        } else {
            printf("%c", pracChar[tmp]);
        }
    }

return 0;
}