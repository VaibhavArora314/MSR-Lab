#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

struct ClassInfo {
    string name;
    vector<double> classValues;
    double methodSum = 0;
    int methodCount = 0;
};

int main() {
    string inputFileName = "ckjm.txt",outputFileName = "test.txt";
    // cin>>inputFileName>>outputFileName;

    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    vector<ClassInfo> classes;
    ClassInfo currentClass;

    string line;
    while (getline(inputFile, line)) {
        if (line.empty()) {
            classes.push_back(currentClass);
            currentClass = ClassInfo();
        } else {
            istringstream iss(line);
            string token;
            if (!(iss >> token)) {
                cerr << "Error: Unexpected format in input file." << endl;
                return 1;
            }
            if (token == "~") {
                string value;

                while (iss >> value) {
                };

                currentClass.methodSum += stoi(value);
                currentClass.methodCount++;
            } else {
                currentClass.name = token;
                double value;
                while (iss >> value) {
                    currentClass.classValues.push_back(value);
                }
            }
        }
    }

    if (!currentClass.name.empty()) {
        classes.push_back(currentClass);
    }

    inputFile.close();

    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    for (const auto& classInfo : classes) {
        // outputFile << classInfo.name << " ";
        for (int value: classInfo.classValues)
            outputFile << fixed << setprecision(4) << value << " ";
        
        if (classInfo.methodCount > 0) {
            outputFile << fixed << setprecision(4) << classInfo.methodSum/classInfo.methodCount << " ";
        }

        outputFile<<endl;
    }

    outputFile.close();

    cout << "Output has been written" << endl;

    return 0;
}
