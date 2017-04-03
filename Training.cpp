#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <termios.h> // for keypress
using namespace std;

ifstream infile("typingInput_t1_01.txt");
const int MAX_RATE=5;
const float FIXED_RATE[MAX_RATE]={0.02f, 0.07f, 0.1f, 0.15f, 0.19f};

/* reads from keypress, doesn't echo */
int myGetch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

float Typing(string _line, int* cntWrongTyping) {
    time_t _timer, _now;
    int wrongChar = 0;
    char tmp;
    time(&_now);
    for(int i = 0; i < _line.length(); i++) {
        tmp = myGetch();
        if(tmp!=_line[i]) {
            cout << '\7' << "\033[1;41m" << tmp << "\033[39;49m";
            wrongChar++;
            cntWrongTyping++; 
        } else {
            cout << tmp;
        }
    } // </for>
    cout << endl;
    time(&_timer);
    cout << "total: \033[1;32m" << _line.length() << "\033[39;49m, wrong: \033[1;31m" 
    << wrongChar << " : " << (float)wrongChar / _line.length() * 100 << "%\033[39;49m" 
    << " ~ \033[1;32m" << _line.length()/(difftime(_timer, _now)/60) << " wpm\033[39;49m\n";
    /* color: https://en.wikipedia.org/wiki/ANSI_escape_code
       working with clang++ -stdlib=libstdc++ abc.cpp -o acb.o */
       
    return (float)wrongChar / _line.length();
}

string convertSecondToTime(int sec) {
    stringstream ss;
    ss << sec/3600 << ":";
    sec-=(sec/3600)*3600;
    ss << sec/60 << ":";
    sec-=(sec/60)*60;
    ss << sec;
    
//    tmp+=to_string((int)(sec/3600));
//    tmp+=to_string(sec/60);
//    tmp+=to_string(sec);
    
    return ss.str();
}

int main() {
    string _line;
    int cntTotalWrong, cntTotal; 
    cntTotal=cntTotalWrong=0;
    time_t firstTime, finalTime;
    time(&firstTime);
    while( getline(infile, _line, '\n')) {
        int cnt = -1;
        do {
            cnt < MAX_RATE-1 ? cnt++ : cnt=MAX_RATE-1;
            cout<<_line<<endl;
            cntTotal += _line.length();
        }
        while (Typing(_line, &cntTotalWrong) >= FIXED_RATE[cnt]);  
    }
    time(&finalTime);
    cout << "\033[1;32mtotal time: " << convertSecondToTime((int)difftime(finalTime, firstTime)) << ", with acc: " 
    << (float)(cntTotal-cntTotalWrong)/cntTotal*100 << "%\033[39;49m\n";
    
return 0;
}


/* 
// What is equivalent to getch() & getche() in Linux?

#include <termios.h>
#include <stdio.h>

static struct termios old, new;

// Initialize new terminal i/o settings 
void initTermios(int echo) 
{
  tcgetattr(0, &old); // grab old terminal i/o settings 
  new = old; // make new settings same as old settings 
  new.c_lflag &= ~ICANON; // disable buffered i/o 
  new.c_lflag &= echo ? ECHO : ~ECHO; // set echo mode 
  tcsetattr(0, TCSANOW, &new); // use these new terminal i/o settings now 
}

// Restore old terminal i/o settings 
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

// Read 1 character - echo defines echo mode 
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

// Read 1 character without echo 
char getch(void) 
{
  return getch_(0);
}
*/