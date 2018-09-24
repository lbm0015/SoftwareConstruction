/*
 * Laney Martin
 * lbm0015
 * hw3.cpp
 *
 * HOW TO COMPILE AND EXECUTE:
 * 1. Navigate to file
 * 2. Type "g++ -std=c++11 hw3.cpp"
 * 3. Type "./a.out"
 */

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
using namespace std;

/** CONSTANTS */
const int PROB_A = 33;
const int PROB_B = 50;
const int  DUELS = 10000;
const string DIVISION = "/10000";

/** VARIABLES */
string target;
bool a_alive;
bool b_alive;
bool c_alive;
bool True = true;
bool False = false;
int aaronWin = 0;
int bobWin = 0;
int charlieWin = 0;
int aaronWin2 = 0;
int bobWin2 = 0;
int charlieWin2 = 0;

/** Prototypes */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
/** Input: A_alive indicates whether Aaron is alive.
		  B_alive indicates whether Bob is alive.
 		  C_alive indicates whether Charlie is alive.
    Return: true if at least two are alive
 		   otherwise return false */

void Aaron_shoots1(bool& B_alive, bool& C_alive);
/** Strategy 1: Use call by reference
    Input: B_alive indicates whether Bob alive or dead
     	  C_alive indicates whether Charlie is alive or dead.
    Return: Change B_alive into false if Bob is killed.
  		   Change C_alive into false if Charlie is killed. */

void Bob_shoots(bool& A_alive, bool& C_alive);
/** Call by reference
    Input: A_alive indicates if Aaron is alive or dead
 		   C_alive indicates whether Charlie is alive or dead
    Return: Change A_alive into false if Aaron is killed.
 			Change C_alive into false if Charlie is killed. */

void Charlie_shoots(bool& A_alive, bool& B_alive);
/** Call by reference
  Input: A_alive indicates if Aaron is alive or dead
  		  B_alive indicates if Bob is alive or dead
  Return: Change A_alive into false if Aaron is killed
 		   Change B_alive into false if Bob is killed */

void Aaron_shoots2(bool& B_alive, bool& C_alive);
/** Strategy 2: Use call by reference
    Input: B_alive indicates whether Bob is alive or dead
 		  C_alive indicates whether Charlie is alive or dead
    Return: Change B_alive into false if Bob is killed
 		   Change C_alive into false if Charlie is killed */

int mygetch(void);
void press_any_key(void);

/** Coninuous key */
int mygetch(void) {
    int ch;
    struct termios oldt, newt;
    tcgetattr ( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
void press_any_key(void) {
    char ch;
    cout << "Press any key to continue...\n";
    ch = mygetch();
    if (ch == 0 || ch == 127) mygetch();
}


/**
 * Return true if two are live, otherwise return false.
 */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
    if ((A_alive && B_alive) | (B_alive && C_alive) | (A_alive && C_alive)) {
        return true;
    } else
        return false;
}

/**
 * Aaron shoots implementation Strategy 1.
 * @param B_alive
 * @param C_alive
 */
void Aaron_shoots1(bool& B_alive, bool& C_alive) {
    b_alive = B_alive;
    c_alive = C_alive;
    int ranNum = rand()%100;

    if (c_alive) {
        cout << "\t\t\t\tAaron is shooting at Charlie";
        target = "Charlie";
    }
    else {
        cout << "\t\t\t\tAaron is shooting at Bob";
        target = "Bob";
    }

    if (ranNum <= PROB_A) {
        cout << "\n\t\t\t\t" << target << " is dead.\n";
        if (target == "Bob") {
            b_alive = false;
            return;
        }
        else {
            c_alive = false;
            return;
        }
    }
    else {
        cout << "\n\t\t\t\tAaron misses.\n";
    }
}

/**
 * Bob shoots implementation
 * @param A_alive
 * @param C_alive
 */
void Bob_shoots(bool& A_alive, bool& C_alive) {
    a_alive = A_alive;
    c_alive = C_alive;
    int ranNum = rand()%100;

    if (a_alive) {
        cout << "\t\t\t\tBob is shooting at Aaron";
        target = "Aaron";
    }
    else {
        cout << "\t\t\t\tBob is shooting at Charlie";
        target = "Bob";
    }

    if (ranNum <= PROB_B) {
        cout << "\n\t\t\t\t" << target << " is dead.\n";
        if (target == "Aaron") {
            a_alive = false;
            return;
        }
        else {
            c_alive = false;
            return;
        }
    }
    else {
        cout << "\n\t\t\t\tBob misses.\n";
    }
}

/**
 * Charlie shoots implementation
 * @param A_alive
 * @param B_alive
 */
void Charlie_shoots(bool& A_alive, bool& B_alive) {
    a_alive = A_alive;
    b_alive = B_alive;
    int ranNum = rand()%100;

    if (a_alive) {
        cout << "\t\t\t\tCharlie is shooting at Aaron";
        a_alive = false;
        target = "Aaron";
    }
    else {
        cout << "\t\t\t\tCharlie is shooting at Bob";
        b_alive = false;
        target = "Bob";
    }

    cout << "\n\t\t\t\t" << target << " is dead.\n";
}

/**
 * Aaron shoots implementation Strategy 2, where Aaron misses his first shot.
 * @param B_alive
 * @param C_alive
 */
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
    b_alive = B_alive;
    c_alive = C_alive;
    int ranNum = rand() % 100;

    if ((b_alive == true) && (c_alive == true)) {
        cout << "\t\t\t\tAaron intentionally misses his first shot\n";
        cout << "\t\t\t\tBoth Bob and Charlie are alive.\n";
    }
    if (c_alive) {
        cout << "\t\t\t\tAaron is shooting at Charlie";
        target = "Charlie";
    } else {
        cout << "\t\t\t\tAaron is shooting at Bob";
        target = "Bob";
    }

    if (ranNum <= PROB_A) {
        cout << "\n\t\t\t\t" << target << " is dead.\n";
        if (target == "Bob") {
            b_alive = false;
            return;
        } else {
            c_alive = false;
            return;
        }
    } else {
        cout << "\n\t\t\t\tAaron misses.\n";
    }
}

/** Strategy 1 driver. Everyone plays fair. */
void strategy1() {
    cout << "Ready to test strategy 1 (run " << DUELS << " times) :" << endl;
    press_any_key();

    for (int i = 0; i < DUELS; i++) {
        a_alive = b_alive = c_alive = true;
        do {
            if (a_alive) {
                Aaron_shoots1(b_alive, c_alive);
            }
            if (b_alive) {
                Bob_shoots(a_alive, c_alive);
            }
            if (c_alive){
                Charlie_shoots(a_alive, b_alive);
            }
        }
        while (at_least_two_alive(a_alive, b_alive, c_alive));

        if (a_alive) {
            aaronWin++;
        }
        if (b_alive) {
            bobWin++;
        }
        if (c_alive) {
            charlieWin++;
        }

        cout << "\n" << endl;
    }

    double aaronPercent = aaronWin * 0.01;
    double bobPercent = bobWin * 0.01;
    double charliePercent = charlieWin * 0.01;
    cout << "Aaron won " << aaronWin << DIVISION << " duels or " << aaronPercent << "%" << endl;
    cout << "Bob won " << bobWin << DIVISION << " duels or " << bobPercent << "%" << endl;
    cout << "Charlie won " << charlieWin << DIVISION << "duels or " << charliePercent << "%\n";

}

/** Strategy 2 driver. Aaron misses his first shot. */
void strategy2() {
    cout << "\nReady to test strategy 2 (run " << DUELS << " times):" << endl;
    press_any_key();

    for (int i = 0; i < DUELS; i++) {
        a_alive = b_alive = c_alive = true;
        do {
            if (a_alive) {
                Aaron_shoots2(b_alive, c_alive);
            }
            if (b_alive) {
                Bob_shoots(a_alive, c_alive);
            }
            if (c_alive) {
                Charlie_shoots(a_alive, b_alive);
            }

        } while (at_least_two_alive(a_alive, b_alive, c_alive));

        if (a_alive) {
            aaronWin2++;
        }
        if (b_alive) {
            bobWin2++;
        }
        if (c_alive) {
            charlieWin2++;
        }
        cout << "\n" << endl;
    }

    double aaronPercent = aaronWin2 * 0.01;
    double bobPercent = bobWin2 * 0.01;
    double charliePercent = charlieWin2 * 0.01;
    cout << "Aaron won " << aaronWin2 << DIVISION << " duels or " << aaronPercent << "%" << endl;
    cout << "Bob won " << bobWin2 << DIVISION << " duels or " << bobPercent << "%" << endl;
    cout << "Charlie won " << charlieWin2 << DIVISION << "duels or " << charliePercent << "%" << endl;

    if (aaronWin2 > aaronWin) {
        cout << "\nStrategy 2 is better that strategy 1." << endl;
    }
    if (aaronWin2 < aaronWin) {
        cout << "\nStrategy 1 is better than strategy 2." << endl;
    }
    if (aaronWin2 == aaronWin) {
        cout << "\nStrategy 1 is equal to strategy 2" << endl;
    }
}

/** TEST DRIVERS */
void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";

    cout << "\t\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\t\tCase passed ...\n";

    cout << "\t\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\t\tCase passed ...\n";

    cout << "\t\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\t\tCase passed ...\n";

    cout << "\t\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\t\tCase passed ...\n";

    cout << "\t\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\t\tCase passed ...\n";

    cout << "\t\tCase 6: Aaron dead, Bob Alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\t\tCase passed ...\n";

    cout << "\t\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\t\tCase passed ...\n";

    cout << "\t\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\t\tCase passed ...\n";

    press_any_key();
}

void test_aaron_shoots1(void) {
    cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive\n";

    cout << "\t\tCase 1: Bob alive, Charlie alive\n";
    Aaron_shoots1(True, True);

    cout << "\t\tCase 2: Bob dead, Charlie alive\n";
    Aaron_shoots1(False, True);

    cout << "\t\tCase 3: Bob alive, Charlie dead\n";
    Aaron_shoots1(True, False);

    press_any_key();
}

void test_bob_shoots(void) {
    cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";

    cout << "\t\tCase 1: Aaron alive, Charlie alive\n";
    Bob_shoots(True, True);

    cout << "\t\tCase 2: Aaron dead, Charlie alive\n";
    Bob_shoots(False, True);

    cout << "\t\tCase 3: Aaron alive, Charlie dead\n";
    Bob_shoots(True, False);

    press_any_key();
}

void test_charlie_shoots(void) {
    cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";

    cout << "\t\tCase 1: Aaron alive, Bob alive\n";
    Charlie_shoots(True, True);

    cout << "\t\tCase 2: Aaron dead, Bob alive\n";
    Charlie_shoots(False, True);

    cout << "\t\tCase 3: Aaron alive, Bob dead\n";
    Charlie_shoots(True, False);

    press_any_key();
}

void test_aaron_shoots2(void) {
    cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";

    cout << "\t\tCase 1: Bob alive, Charlie alive\n";
    Aaron_shoots2(True, True);

    cout << "\t\tCase 2: Bob dead, Charlie alive\n";
    Aaron_shoots2(False, True);

    cout << "\t\tCase 3: Bob alive, Charlie dead\n";
    Aaron_shoots2(True, False);

    press_any_key();
}

int main() {
    srand(time(0)); //set random seed
    cout << "*** Welcome to Brianne's Duel Simulator ***" << endl;
    test_at_least_two_alive();
    test_aaron_shoots1();
    test_bob_shoots();
    test_charlie_shoots();
    test_aaron_shoots2();
    strategy1();
    strategy2();
}
