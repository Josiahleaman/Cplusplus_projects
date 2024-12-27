//L32856679
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

string GetTicker();
int buildArrayQuotes(string);
void performAnalysis(string ticker, int numberOfQuotes);

string date[10000];
float quote[10000];

int main()
{
    string ticker = GetTicker();
    int numberOfQuotes= buildArrayQuotes(ticker);
    performAnalysis(ticker, numberOfQuotes);
}

string GetTicker()
{
    cout << "********** Stock Analyzer **********\n";
    cout << "************************************\n";
    cout << "1- Facebook (META) \n";
    cout << "2- Amazon (AMZN) \n";
    cout << "3- Netflix (NFLX) \n";
    cout << "4- Google (GOOG) \n";
    cout << "~ - NVIDIA (NVDA) \n\n";
    cout << "Input a number (1-4): ";
    int option = 0;
    cin >> option;

    string ticker = "";
    switch (option)
    {
        case 1:
            ticker = "META";
            break;
        case 2:
            ticker = "AMZN";
            break;
        case 3:
            ticker = "NFLX";
            break;
        case 4:
            ticker = "GOOG";
            break;
        case 5:
            ticker = "NVDA";
            break;
        default:
            cout << "Invalid option. Defaulting to NVIDIA (NVDA).\n";
            ticker = "NVDA";
            break;
    }
    return ticker;
}

int buildArrayQuotes(string ticker)
{
    string lineOfText = "";
    ifstream file(ticker+".csv");
    getline(file, lineOfText);
    int counter = 0;
    while (getline(file, lineOfText))
    {
        cout << lineOfText << "\n";
        date[counter] = lineOfText.substr(0,10);
        cout << date[counter] << "\n";
        size_t firstComma = lineOfText.find_first_of(",");
        size_t secondComma = lineOfText.find(',', firstComma+1);
        quote[counter] = stof(lineOfText.substr(11, secondComma-firstComma));
        cout << quote[counter] << endl;
        counter++;
    }
    return counter-1;
}

void performAnalysis(string ticker, int numberOfQuotes)
{
    int up = 0;
    int down = 0;
    cout << "Day\t" << "Date\t" << "Quote\n";
    for (int i = 3; i< numberOfQuotes; i++)
    {
        cout << i << "\t" << date[i] << "\t" << quote[i];
        if (
            quote[i-3] < quote[i-2] &&
            quote[i-2] < quote[i-1] &&
            quote[i-1] < quote[i]
            )
        {
            cout << "+";
            up++;
        }
        if (
            quote[i-3] < quote[i-2] &&
            quote[i-2] < quote[i-1] &&
            quote[i-1] > quote[i]
            )
        {
            cout << "-";
            down++;
        }
        cout << "\n";
        
    }
    cout << "View Analysis\n";
    cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    cout << "********** Analysis: " << ticker << " **********\n";
    cout << "Trading Up: " << up << "\n";
    cout << "Trading Down: " << down << "\n";
    cout << "Percent of 3-Day Successive Gains: " << up *100 /(up+down) << "\n";
    cout << "************************************\n";
}
