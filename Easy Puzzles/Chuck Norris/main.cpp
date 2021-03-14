#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string MESSAGE;
    getline(cin, MESSAGE);

    vector<char> m(MESSAGE.begin(),MESSAGE.end());

    int count = 0;
    bool begin = false;
    int current = 0;
    string zero = "0";
    string one = "1";
    for (auto i = m.cbegin(); i != m.cend(); ++i){ 

        int val = int(*i);
        // Convert ASCII value to binary 
        vector<int> bin; 
        while (val > 0) 
        { 
            (val % 2)? bin.push_back(1) : 
                       bin.push_back(0); 
            val /= 2; 
        } 
        while(bin.size()!=7) bin.push_back(0);
        
        while(!bin.empty()){
            int read = bin.back();
            bin.pop_back();

            if(begin==true){
                if(read == current){
                    count = count + 1;
                }else{
                    //print function
                    if(current == 0){
                        cout<< "00 ";
                    }else{
                        cout<< "0 ";
                    }
                    while(count!=0){
                        cout<< "0" ;
                        count--;
                    }
                    cout<< " " ;
                    if(read == 0){
                        current = 0;
                    }else{
                        current = 1;
                    }
                    count = 1;
                }
            }else{
                cerr<<"begin"<<endl;
                begin = true;
                count = 1;
                if(read == 0){
                    current = 0;
                }else{
                    current = 1;
                }
            }
        }
    }
    while(count!=0){
        if(current == 0){
            cout<< "00 ";
        }else{
            cout<< "0 ";
        }
        while(count!=0){
            cout<< "0" ;
            count--;
        }
    }

    cout << endl;
}
