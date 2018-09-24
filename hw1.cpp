/*
 * Laney Martin
 * lbm0015
 * hw1.cpp
 *
 * How to compile:
 * 1. Navigate to file
 * 2. Type g++ -std=c++11 hw1.cpp
 * 3. Type ./a.out
 */

#include <iostream>
using namespace std;

int main() {

    const double dietSoda = .002;
    double amtKillMouse;
    double mouseWeight;
    double dieterWeight;
    double amtSoda;
    double killer;

    cout << "What is the amount of artificial sweetener needed to kill a mouse: ";
    cin >> amtKillMouse;

    cout << "What is the weight of the mouse: ";
    cin >> mouseWeight;

    cout << "What is the weight the dieter will stop dieting: ";
    cin >> dieterWeight;

    killer = amtKillMouse/mouseWeight;
    amtSoda = dieterWeight * (dietSoda/killer);

    cout << "You can drink " << amtSoda << " diet soda without dying as a result.";

}
