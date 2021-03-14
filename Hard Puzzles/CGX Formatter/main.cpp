#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void printBlock(int tabNum){
    string Block = "    ";
    for(int i = 0; i < tabNum; i++){
        cout << Block;
    }
}


int main()
{
    int tabNum = 0;
    
    int N;
    cin >> N; cin.ignore();
    
    char prevLast;
    string fullInput = "";
    for (int i = 0; i < N; i++) {
        string CGXLine;
        getline(cin, CGXLine);
        cerr << "---- " << CGXLine << endl;
        fullInput.append(CGXLine);
    }

    bool quoteMode = false;
    bool newLine = false;  // maybe don't need

    char prevPrint = '\0';  // should I initialize?
    string blockQuote = "";
    for(int i = 0; i < fullInput.size(); i++){
        char inChar = fullInput[i], nextChar;
        if( (i+1) < fullInput.size()) nextChar= fullInput[i+1];

        if(quoteMode){          // copy entirety one for one until hit the next '
            if(inChar == '\''){
                if(newLine) printBlock(tabNum);
                newLine = false;

                blockQuote.push_back(inChar);
                cout << blockQuote;  // maybe need to print out one ... at a time
                blockQuote = "";
                prevPrint = inChar;

                quoteMode = false;
            }else{
                blockQuote.push_back(inChar);
            }
        }else{
            switch(inChar){
                case ' ':   // ignore addit. spaces
                    break;
                case '\t':  // ignore tabs
                    break;
                case '\n':  // ignore newlines
                    break;
                case '=':
                    cout << inChar;
                    prevPrint = inChar;
                    break;
                case '\'':
                    quoteMode = true;
                    blockQuote.push_back(inChar);
                    break;
                case ';':
                    cout << inChar << endl;
                    prevPrint = inChar;
                    newLine = true;
                    break;
                case '(':
                    if(prevPrint == '='){
                        cout << endl;
                        newLine = true;
                    }
                    if(newLine) printBlock(tabNum);
                    tabNum++;              
                    cout << inChar << endl;
                    prevPrint = inChar;
                    newLine = true;
                    break;
                case ')':
                    if(prevPrint != '(') cout << endl;  // to dealt with empty blocks
                    tabNum--;
                    printBlock(tabNum);
                    cout << inChar;
                    prevPrint = inChar;
                    break;    
                default:
                    if(newLine) printBlock(tabNum);
                    newLine = false;
                    cout << inChar;
                    prevPrint = inChar;
                    break;              
            }
        }
    }
}
