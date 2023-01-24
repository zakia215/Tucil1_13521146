#include <bits/stdc++.h>
#include <chrono>

using namespace std;

const string validCard[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
const char operatorList[] = {'*', '/', '+', '-'};

int cardValue(string card) {
    if (card == "A") {
        return 1;
    } else if (card == "2") {
        return 2;
    } else if (card == "3") {
        return 3;
    } else if (card == "4") {
        return 4;
    } else if (card == "5") {
        return 5;
    } else if (card == "6") {
        return 6;
    } else if (card == "7") {
        return 7;
    } else if (card == "8") {
        return 8;
    } else if (card == "9") {
        return 9;
    } else if (card == "10") {
        return 10;
    } else if (card == "J") {
        return 11;
    } else if (card == "Q") {
        return 12;
    } else if (card == "K") {
        return 13;
    } else {
        return 0;
    }
}

string cardName(int cardValue) {
    switch (cardValue) {
        case 1:
            return "1";
            break;
        case 2:
            return "2";
            break;
        case 3:
            return "3";
            break;
        case 4:
            return "4";
            break;
        case 5:
            return "5";
            break;
        case 6:
            return "6";
            break;
        case 7:
            return "7";
            break;
        case 8:
            return "8";
            break;
        case 9:
            return "9";
            break;
        case 10:
            return "10";
            break;
        case 11:
            return "11";
            break;
        case 12:
            return "12";
            break;
        case 13:
            return "13";
            break;
        default:
            break;
    }
    return "None";
}

string cardType(int cardValue) {
    switch (cardValue) {
        case 1:
            return "A";
            break;
        case 2:
            return "2";
            break;
        case 3:
            return "3";
            break;
        case 4:
            return "4";
            break;
        case 5:
            return "5";
            break;
        case 6:
            return "6";
            break;
        case 7:
            return "7";
            break;
        case 8:
            return "8";
            break;
        case 9:
            return "9";
            break;
        case 10:
            return "10";
            break;
        case 11:
            return "J";
            break;
        case 12:
            return "Q";
            break;
        case 13:
            return "K";
            break;
        default:
            break;
    }
    return "None";
}

double getResult(double first, double second, char op) {
    if (first == 99999 || second == 99999) {
        return 99999;
    } else {
        if (op == '*' || op == 'X') {
            return first * second;
        } else if (op == '+') {
            return first + second;
        } else if (op == '-') {
            return first - second;
        } else if (op == '/' && second != 0) {
            return first / second;
        } else if (op == '/' && second == 0) {
            return 99999;
        } return -1;
    }
}

bool exist(vector<string> stringList, string element) {
    for (size_t i = 0; i < stringList.size(); i++) {
        if (stringList[i] == element) {
            return true;
        }
    }
    return false;
} 

bool commutativeExist(vector<string> validSolutions, vector<string> allPossibilities) {
    for (size_t i = 0; i < allPossibilities.size(); i++) {
        if (exist(validSolutions, allPossibilities[i])) {
            return true;
        }
    }
    return false;
}

bool addSolution(int numList[4], char opList[3], int format, vector<string> validSolution) {
    vector<vector<string>> numStringList;
    vector<char> localOp;
    vector<int> localOrder;
    vector<string> numString;
    for (int i = 0; i < 4; i++) {
        numString.push_back(cardName(numList[i]));
    }
    numStringList.push_back(numString);
    for (int i = 0; i < 3; i++) {
        localOp.push_back(opList[i]);
    }
    if (format == 1) {
        localOrder = {1, 2, 3};
    } else if (format == 2) {
        localOrder = {2, 1, 3};
    } else if (format == 3) {
        localOrder = {2, 3, 1};
    } else if (format == 4) {
        localOrder = {3, 2, 1};
    } else {
        localOrder = {1, 3, 2};
    }
    for (int i = 0; i < 3; i++) {
        int curOrd = localOrder[i];
        if (curOrd == 2) {
            for (int j = i + 1; j < 3; j++) {
                if (localOrder[j] == 3) {
                    localOrder[j]--;
                }
            }
        } else if (curOrd == 1) {
            for (int j = i + 1; j < 3; j++) {
                localOrder[j]--;
            }
        }
        size_t listSize = numStringList.size();
        for (size_t j = 0; j < listSize; j++) {
            string nonComm = numStringList[j][curOrd - 1] + " " + localOp[curOrd - 1] + " " + numStringList[j][curOrd], comm = numStringList[j][curOrd] + " " + localOp[curOrd - 1] + " " + numStringList[j][curOrd - 1];
            if (i != 2) {
                nonComm = "(" + nonComm + ")";
                comm = "(" + comm + ")";
            }
            if (localOp[curOrd  - 1] == '*' || localOp[curOrd  - 1] == '+') {
                vector<string> commString = numStringList[j];
                commString.erase(commString.begin() + curOrd);
                commString.erase(commString.begin() + (curOrd - 1));
                commString.insert(commString.begin() + (curOrd - 1), comm);
                numStringList.push_back(commString);
            }
            numStringList[j].erase(numStringList[j].begin() + curOrd);
            numStringList[j].erase(numStringList[j].begin() + (curOrd - 1));
            numStringList[j].insert(numStringList[j].begin() + (curOrd - 1), nonComm);
        }
        localOp.erase(localOp.begin() + (curOrd - 1));
    }
    vector<string> finalStringList;
    for (size_t i = 0; i < numStringList.size(); i++) {
        finalStringList.push_back(numStringList[i][0]);
    }
    return !(commutativeExist(validSolution, finalStringList));
}

string getLineString(int numArray[4], char opArray[3], int format) {
    string result;
    if (format == 1) {
        result = "((" + cardName(numArray[0]) + " " + opArray[0] + " " + cardName(numArray[1]) + ")" + " " + opArray[1] + " " + cardName(numArray[2])+ ")" + " " + opArray[2] + " " + cardName(numArray[3]);
    } else if (format == 2) {
        result = "(" + cardName(numArray[0]) + " " + opArray[0] + " (" + cardName(numArray[1]) + " " + opArray[1] + " " + cardName(numArray[2])+ ")) " + opArray[2] + " " + cardName(numArray[3]);
    } else if (format == 3) {
        result = cardName(numArray[0]) + " " + opArray[0] + " ((" + cardName(numArray[1]) + " " + opArray[1] + " " + cardName(numArray[2])+ ")" + " " + opArray[2] + " " + cardName(numArray[3]) + ")";
    } else if (format == 4) {
        result = cardName(numArray[0]) + " " + opArray[0] + " (" + cardName(numArray[1]) + " " + opArray[1] + " (" + cardName(numArray[2]) + " " + opArray[2] + " " + cardName(numArray[3]) + "))";
    } else {
        result = "(" + cardName(numArray[0]) + " " + opArray[0] + " " + cardName(numArray[1]) + ") " + opArray[1] + " (" + cardName(numArray[2]) + " " + opArray[2] + " " + cardName(numArray[3]) + ")";
    }
    return result;
}

string getOneContinuousString(vector<string> solutionList) {
    size_t solutionsFound = solutionList.size();
    if (solutionsFound == 0) {
        return "Tidak ada solusi\n";
    }
    string result = to_string(solutionsFound) + " solution(s) found\n";
    for (size_t i = 0; i < solutionList.size(); i++) {
        result += solutionList[i] + "\n";
    }
    return result;
}

string solve(int numArray[4]) {
    auto start = chrono::high_resolution_clock::now();
    int count = 0;
    vector<string> solutions;
    for (size_t l = 0; l < 4; l++) {
        for (size_t m = 0; m < 4; m++) {
            if (m != l) {
                for (size_t n = 0; n < 4; n++) {
                    if (n != m && n != l) {
                        for (size_t o = 0; o < 4; o++) {
                            if (o != m && o != n && o != l) {
                                int permutatedNum[4] = {numArray[l], numArray[m], numArray[n], numArray[o]};
                                char tempOp[3];
                                for (int i = 0; i < 4; i++) {
                                    tempOp[0] = operatorList[i];
                                    for (int j = 0; j < 4; j++) {
                                        tempOp[1] = operatorList[j];
                                        for (int k = 0; k < 4; k++) {
                                            tempOp[2] = operatorList[k];
                                            double leftLeft, leftRight, rightLeft, rightRight, splitMiddle;
                                            leftLeft = getResult(getResult(getResult(permutatedNum[0], permutatedNum[1], tempOp[0]), permutatedNum[2], tempOp[1]), permutatedNum[3], tempOp[2]);
                                            leftRight = getResult(getResult(permutatedNum[0], getResult(permutatedNum[1], permutatedNum[2], tempOp[1]), tempOp[0]), permutatedNum[3], tempOp[2]);
                                            rightLeft = getResult(permutatedNum[0], getResult(getResult(permutatedNum[1], permutatedNum[2], tempOp[1]), permutatedNum[3], tempOp[2]), tempOp[0]);
                                            rightRight = getResult(permutatedNum[0], getResult(permutatedNum[1], getResult(permutatedNum[2], permutatedNum[3], tempOp[2]), tempOp[1]), tempOp[0]);
                                            splitMiddle = getResult(getResult(permutatedNum[0], permutatedNum[1], tempOp[0]), getResult(permutatedNum[2], permutatedNum[3], tempOp[2]), tempOp[1]);
                                            if (leftLeft == 24 && !exist(solutions, getLineString(permutatedNum, tempOp, 1))) {
                                                count++;
                                                solutions.push_back(getLineString(permutatedNum, tempOp, 1));
                                            }
                                            if (leftRight == 24 && !exist(solutions, getLineString(permutatedNum, tempOp, 2))) {
                                                count++;
                                                solutions.push_back(getLineString(permutatedNum, tempOp, 2));
                                            }
                                            if (rightLeft == 24 && !exist(solutions, getLineString(permutatedNum, tempOp, 3))) {
                                                count++;
                                                solutions.push_back(getLineString(permutatedNum, tempOp, 3));
                                            }
                                            if (rightRight == 24 && !exist(solutions, getLineString(permutatedNum, tempOp, 4))) {
                                                count++;
                                                solutions.push_back(getLineString(permutatedNum, tempOp, 4));
                                            }
                                            if (splitMiddle == 24 && !exist(solutions, getLineString(permutatedNum, tempOp, 5))) {
                                                count++;
                                                solutions.push_back(getLineString(permutatedNum, tempOp, 5));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    string result = getOneContinuousString(solutions);
    result += "Process finished in " + to_string(duration.count()) + " microseconds\n";
    return result;
}

bool isFileExist(string name) {
    string testFilePath = "../test/" + name + ".txt";
    ifstream f(testFilePath.c_str());
    return f.good();
}

string removeTrailingAndLeadingSpace(string stringInput) {
    int trailingSpaceCount = 0;
    for (size_t i = stringInput.size() - 1; i >= 0; i--) {
        if (stringInput[i] == ' ') {
            trailingSpaceCount++;
        } else {
            break;
        }
    }
    int leadingSpaceCount = 0;
    for (size_t i = 0; i < stringInput.size(); i++) {
        if (stringInput[i] == ' ') {
            leadingSpaceCount++;
        } else {
            break;
        }
    }
    return stringInput.substr(leadingSpaceCount, stringInput.size() - trailingSpaceCount - leadingSpaceCount);
}

bool isElementOf(string card, const string cardList[13]) {
    for (int i = 0; i < 13; i++) {
        if (cardList[i] == card) {
            return true;
        }
    }
    return false;
}

bool isValidCardInput(string cardInput) {
    vector<string> cardList;
    string word = "";
    for (size_t i = 0; i < cardInput.size(); i++) {
        if (cardInput[i] == ' ') {
            cardList.push_back(word);
            word = "";
        } else {
            word += cardInput[i];
        }
    }
    cardList.push_back(word);
    if (cardList.size() != 4) {
        return false;
    }
    for (int i = 0; i < 4; i++) {
        if (!isElementOf(cardList[i], validCard)) {
            return false;
        }
    }
    return true;
}

void parseCards(string cards, int* cardValues[]) {
    string currentCard = "";
    *cardValues = new int[4];
    int j = 0;
    for (size_t i = 0; i < cards.size(); i++) {
        if (cards[i] == ' ') {
            (*cardValues)[j] = cardValue(currentCard);
            currentCard = "";
            j++;
        } else {
            currentCard += cards[i];
        }
    }
    (*cardValues)[j] = cardValue(currentCard);
}

int main() {

    // int ps1[4] = {1, 12, 9, 8};
    // int ps2[4] = {1, 1, 1, 24};

    // auto start = chrono::high_resolution_clock::now();
    // string solution = solve(ps1);
    // auto end = chrono::high_resolution_clock::now();
    // auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    // cout << duration.count() << endl;
    // cout << solution << endl;
    // cout << solve(ps2) << endl;

    while (true) {
        int *numValues;
        int pickOrRandom;
        string trash;
        cout << "Would you like to randomize the card or pick your own?\n1. Randomize\n2. Pick\n-> ";
        cin >> pickOrRandom;
        getline(cin, trash);
        while (pickOrRandom != 1 && pickOrRandom != 2) {
            cout << "Invalid input\n1. Randomize\n2. Pick\n-> ";
            cin >> pickOrRandom;
            getline(cin, trash);
        }
        if (pickOrRandom == 2) {
            string cardInput;
            cout << "Please input 4 valid cards seperated by white spaces\n-> ";
            getline(cin, cardInput);
            while (!isValidCardInput(removeTrailingAndLeadingSpace(cardInput))) {
                cout << "Invalid input. Please input 4 valid cards seperated by white spaces\n-> ";
                getline(cin, cardInput);
            }
            parseCards(removeTrailingAndLeadingSpace(cardInput), &numValues);
        } else {
            numValues = new int[4];
            srand(time(0));
            cout << "Cards:\n";
            for (int i = 0; i < 4; i++) {
                numValues[i] = rand() % 13 + 1;
                cout << cardType(numValues[i]) << " ";
            }
            cout << endl;
        }
        string result = solve(numValues);
        cout << result;
        cout << "Do you want to store the result in a txt file? (Y/N): ";
        char store;
        cin >> store;
        while (store != 'y' && store != 'Y' && store != 'N' && store != 'n') {
            cout << "Sorry, that input was invalid.\n(Y/N): ";
            cin >> store;
        }
        if (store == 'Y' || store == 'y') {
            cout << "Please enter the designated file name: ";
            string fileName;
            cin >> fileName;
            while (isFileExist(fileName)) {
                cout << "Sorry, that file name is already taken.\nPlease enter another file name: ";
                cin >> fileName;
            }
            string filePath = "../test/" + fileName + ".txt";
            ofstream tempFile(filePath);
            tempFile << result;
            tempFile.close();
        }
        cout << "Would you like to use this program again? (Y/N): ";
        char choice;
        cin >> choice;
        while (choice != 'y' && choice != 'Y' && choice != 'N' && choice != 'n') {
            cout << "Sorry, that input was invalid.\n(Y/N): ";
            cin >> choice;
        }
        if (choice == 'N' || choice == 'n') {
            cout << "Thank you" << endl;
            break;
        }
    }

    return 0;
}