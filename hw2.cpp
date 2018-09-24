/*
 * Laney Martin
 * lbm0015
 * hw2.cpp
 *
 * HOW TO COMPILE AND EXECUTE:
 * 1. Navigate to file
 * 2. Type "g++ -std=c++11 hw2.cpp"
 * 3. Type "./a.out"
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double loanAmount;
    double interestRate;
    double monthlyPayments;
    double rate;
    const double months = 12.0;
    double interest;
    double principle;
    int count = 0;
    const double percentage = 100.0;
    double interestSum = 0.00;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Loan Amount: ";
    cin >> loanAmount;

    cout << "Interest Rate (% per year): ";
    cin >> interestRate;

    cout << "Monthly Payments: ";
    cin >> monthlyPayments;

    rate = interestRate / months;
    interest = loanAmount * (rate / percentage);
    if (monthlyPayments < interest) {
        cout << "ERROR: Interest is greater than monthly payments";
    }

    else {
        cout << "******************************************************" << endl;
        cout << "       Amortization Table " << endl;
        cout << "******************************************************" << endl;
        cout << left << setw(8) << "Month" << setw(8) << "Balance" << setw(8) << "Payment" << setw(8) << "Rate";
        cout << left << setw(9) << "Interest" << "Principle" << endl;
        cout << left << setw(8) << count << "$" << setw(8) << loanAmount << setw(7) << "N/A" << setw(8) << "N/A";
        cout << left << setw(9) << "N/A" << "N/A" << endl;


        while (loanAmount > 0) {
            rate = interestRate / months;
            interest = loanAmount * (rate / percentage);
            principle = monthlyPayments - interest;
            loanAmount = loanAmount - principle;
            interestSum = interestSum + interest;
            count++;


            if (loanAmount < monthlyPayments) {
                interest = loanAmount * (rate / percentage);
                monthlyPayments = loanAmount + interest;
                principle = loanAmount;
                interestSum = interestSum + interest;
                loanAmount = 0;
                count++;
            }

            cout << left << setw(8) << count << "$" << setw(8) << loanAmount << "$" << setw(6) << monthlyPayments
                << setw(9) << rate << "$" << setw(9) << interest << "$" << principle << endl;
        }

        cout << "******************************************************" << endl;
        cout << "It takes " << count << " months to pay off the loan." << endl;
        cout << "Total interest paid is: $" << interestSum << endl;
    }


}
