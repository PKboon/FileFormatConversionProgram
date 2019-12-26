// This program is written by Pikulkaew Boonpeng for C++ Programming class by Professor Morgam, P at BunkerHill Community College.
// Last modified 03/15/2019

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Constance variables
const int SIZE = 50;
const string PIPE = "|";
const string CM = ",";
const string DQ = "\"";

// Function prototypes
void printHelp();
void processData(ifstream &inFile, ostream &outFile, string delimiter);
int split(string inputRecord, string delimiter, string fieldArray[], int size);

// Main function
int main() {
    string command;     // For command input
    string inFileName;  // For input filename
    string outFileName; // For output filename
    ifstream inFile;
    ofstream outFile;
    
    // while loop begins
    while (true) {
        cout << "\nCommand: ";
        getline(cin >> ws, command);
        
        // Closing input file
        if (command == "CI" || command == "ci")
            inFile.close();
        
        // Closing output file
        else if (command == "CO" || command == "co")
            outFile.close();
        
        // Print command definition
        else if (command == "h")
            printHelp();
        
        // Ask for input filename
        else if (command == "i")
        {
            cout << "Enter name of input file: ";
            getline(cin, inFileName);
            inFile.open(inFileName);
            if (inFile.fail())
                cout << "Cannot open this file.";
        }
        
        // Ask for output filename
        else if (command == "o" || command == "O")
        {
            cout << "Enter name of output file: ";
            getline(cin, outFileName);
            outFile.open(outFileName);
            if (outFile.fail())
                cout << "Cannot open this file.";
        }
        
        // Pipe format to CSV format
        else if (command == "p")
            processData(inFile, outFile, PIPE);
        
        // Quit the program
        else if (command == "q" || command == "quit")
            exit(0);
        
        // When invalid commands are entered
        else
            cout << "Invalid command.";
    } // end while loop
    return 0;
} // end main function

// command h
void printHelp() {
    cout
    << "\nSupported commands:"
    << "\n\t CI \t Close input file."
    << "\n\t CO \t Close output file."
    << "\n\t h  \t print this help text."
    << "\n\t i  \t open file for input."
    << "\n\t o  \t open file for output."
    << "\n\t p  \t (lower case 'p') process data file."
    << "\n\t q  \t quit (end the program).";
}

// command p
void processData(ifstream &inFile, ostream &outFile, string delimiter)
{
    string inputRecord;         // For line input
    string fieldArray[SIZE];    // Stores fields
    int fieldCount; // Stores number of fields
    int startFieldPos = 0;      // Stores the beginning of the current field
    int commaPos;   // Stores comma position
    int openDQPos;  // Stores open double quotes position
    int closeDQPos; // Stores close double quotes position
    
    // while reading lines from the input file
    while (getline(inFile, inputRecord))
    {
        // Display the read line on the screen
        cout << "\nInput data = " << inputRecord;
        
        // Assign number of fields by calling split function
        fieldCount = split(inputRecord, delimiter, fieldArray, SIZE);
        
        for (int i = 0; i < fieldCount; i++)
        {
            string field = fieldArray[i];
            commaPos = field.find(CM, startFieldPos);
            openDQPos = field.find(DQ, startFieldPos);
            closeDQPos = field.find(DQ, openDQPos + 1);
            
            // When comma is found
            if (commaPos >= 0)
                outFile << DQ << field << DQ << CM;
            
            // When double quotes are found
            else if (openDQPos >= 0 && closeDQPos >= 0)
                outFile << DQ
                << field.insert(openDQPos + 1, DQ).insert(closeDQPos + 1, DQ)
                << DQ << CM;
            // When neither comma nor double quotes are found
            else
                outFile << field << CM;
        }
        // Start a new line after the current line was processed
        outFile << endl;
    }
    cout << "End of file encountered.\n";
}

// Split lines into fields
int split(string inputRecord, string delimiter, string fieldArray[], int size)
{
    int deliPos;            // Stores delimiter position
    int startFieldPos = 0;  // Stores the beginning of the current field
    int fieldCount = 0;     // Field-counter
    string fieldData;       // Stores Field-data
    bool endLine = false;   // Flag for the end of the current line
    
    // While it is NOT the end of the current line
    while (!endLine)
    {
        // Find the delimiter position in the current line
        deliPos = inputRecord.find(delimiter, startFieldPos);
        
        // If the delimiter is found
        if (deliPos >= 0)
        {
            fieldData = inputRecord.substr(startFieldPos, deliPos - startFieldPos);
            fieldCount++;
            startFieldPos = deliPos + 1;
        }
        
        // When reaching the end of line
        else
        {
            endLine = true;
            deliPos = inputRecord.length();
            if (deliPos > startFieldPos)
            {
                fieldData = inputRecord.substr(startFieldPos, deliPos - startFieldPos);
                fieldCount++;
            }
        }
        fieldArray[fieldCount - 1] = fieldData;
    }
    return fieldCount;
}

