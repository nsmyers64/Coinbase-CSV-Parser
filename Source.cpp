// Coinbase CSV Parser.cpp 
//Input your file into the source files folder, named "fills.csv" in order to input your data

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//reading the data from the file and storing the information into a vector. 
vector<vector<string>> readData(string fileName) {

    fstream file;

    file.open(fileName);

    string currLine;
    string currWord;
    string columnName;
    vector<string> rowToInput;
    vector<vector<string>> data;  // vector of vectors in order to store each of the rows in a vector. 

    while (1 > 0) {
        rowToInput.clear();

        getline(file, currLine);

        stringstream s(currLine);

        while (getline(s, currWord, ',')) {
            rowToInput.push_back(currWord);
        }

        data.push_back(rowToInput);
        cout << "working " << endl;
        if (rowToInput.empty() == true) {
            break;
        }
    }

    data.erase(data.begin());
    return data;
}

//Prints the data out, outputting what each thing was purchased for. 
void printData(vector<vector<string>> data) {
    int i;

    for (i = 0; i < data.size() - 1; i++) {
        cout << data.at(i).at(6) << " was purchased for " << data.at(i).at(7) << endl;
    }
}

// Calculates the gain/loss totals for all of the sales and purchases. This is all gain an loss, not realized loss. If you want to get your value that you would submit for taxes, 
// You need to account for the value of the assets you are currently holding. 
//
// This function is for a single type of currency. 
float printGainLossTotalsSingle(vector<vector<string>> data, string icon) {
    int i;
    float gainLoss = 0;
    for (i = 0; i < data.size() - 1; i++) {
        if (data.at(i).at(6) == icon) {
            gainLoss = gainLoss + stof(data.at(i).at(9));
        }
    }
    cout << icon << " had a gain/loss of  " << gainLoss << endl;
    return gainLoss;
}

// Uses the gain loss single function in order to calculate the gain and loss for all of the currencies contained in the file.
void printGainLossTotalsAll(vector<vector<string>> data) {
    int i;
    float all = 0;
    vector<string> gainLosses;
    for (i = 0; i < data.size() - 1; i++) {
        if (count(gainLosses.begin(), gainLosses.end(), data.at(i).at(6)) == 0) {
            gainLosses.push_back(data.at(i).at(6));
        }
    }
    for (i = 0; i < gainLosses.size() - 1; i++) {
        all = all + printGainLossTotalsSingle(data, gainLosses.at(i));
    }
    cout << "Total Gain/Loss is : " << all << endl;
}

// Prints out all of the fees  for a single currency, eexcluding any gains or losses made. This is only the transfer fees taken by coinbase. 
float printFeeTotalsSingle(vector<vector<string>> data, string icon) {
    int i;
    float feeTotal = 0;
    for (i = 0; i < data.size() - 1; i++) {
        if (data.at(i).at(6) == icon) {
            feeTotal = feeTotal + stof(data.at(i).at(8));
        }
    }
    cout << icon << " had a fee total of  " << feeTotal << endl;
    return feeTotal;
}

//Uses the print fees single function in order to calculate all of the fees for every currency contained in the file. 
void printFeeTotalsAll(vector<vector<string>> data) {
    int i;
    float all = 0;
    vector<string> fees;
    for (i = 0; i < data.size() - 1; i++) {
        if (count(fees.begin(), fees.end(), data.at(i).at(6)) == 0) {
            fees.push_back(data.at(i).at(6));
        }
    }
    for (i = 0; i < fees.size() - 1; i++) {
        all = all + printFeeTotalsSingle(data, fees.at(i));
    }
    cout << "Total Fees are : " << all << endl;
}



int main()
{
    string input = "";

    //Make sure the data file is in the main directory and is named "fills.csv"
    vector<vector<string>> data = readData("fills.csv");


    //Simple menu system using the command prompt, with numbered choices
    cout << "Welcome to the Coinbase CSV Parser";
    while (input != "9") {

        cout << "Please chose from one of the following inputs:" << endl;
        cout << "1: Print all data" << endl;
        cout << "2: Print gains and losses for 1 currency" << endl;
        cout << "3: Print gains and losses for all currency" << endl;
        cout << "4: Print fees for 1 currency" << endl;
        cout << "5: Print fees for all currency" << endl;
        cout << "9: Exit this menu" << endl;

        cin >> input;


        if (input == "1") {
            printData(data);
        }

        else if (input == "2") {
            cout << "Please type the name of the currency to search for" << endl;
            cin >> input;

            printGainLossTotalsSingle(data, input);
        }

        else if (input == "3") {
            printGainLossTotalsAll(data);
        }

        else if (input == "4") {
            cout << "Please type the name of the currency to search for" << endl;
            cin >> input;

            printFeeTotalsSingle(data, input);
        }

        else if (input == "5") {
            printFeeTotalsAll(data);
        }

    }



}
