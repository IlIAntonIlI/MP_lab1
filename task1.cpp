#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Word{
    string value;
    int countR;
};

int main(){
    int i;
    const int SHOWED_WORDS = 10;
    int countStopWords = 7;
    string stopWords[] = {
        "the","in","for","an","of","at","by"
    };

    int resultArraySize = 0;
    Word* resultArray = new Word[resultArraySize];
    string readedWord;
    ifstream inputFile("text.txt");
    readNewWord:
        if(!(inputFile>>readedWord)){
            goto endOfReadingFile;
        }
        i = 0;
        toLowerCase:
            if(!readedWord[i]){
                goto endToLowerCase;
            }
            if(readedWord[i] >= 65 && readedWord[i] <= 90){
                readedWord[i]+=32;
            }
            i++;
        goto toLowerCase;
        endToLowerCase:
        i=0;

        isStopWord:
            if(i>=countStopWords){
                goto endIsStopWord;
            }
            if(stopWords[i]==readedWord){
                goto readNewWord;
            }
            i++;
            goto isStopWord;
        endIsStopWord:
        i=0;
        isAddedToResultArray:{
            if(i<=resultArraySize){
                if(readedWord==resultArray[i].value){
                    resultArray[i].countR++;
                    goto endAddToResultArray;
                }
                i++;
                goto isAddedToResultArray;
            }

            resultArraySize+=1;
            i=0;
            Word* copyResultArray = new Word[resultArraySize];
            copyArray:
                if(i<resultArraySize-1){
                    copyResultArray[i]=resultArray[i];
                } else {
                    goto endCopyArray;
                }
            i++;
            goto copyArray;
            endCopyArray:
            copyResultArray[resultArraySize-1] = {readedWord,1};
            resultArray=copyResultArray;
        }
        endAddToResultArray:
            i=0;
            goto readNewWord;
    endOfReadingFile:
    inputFile.close();

    int j=0;
    i=0;

    iCycle:
        if(i>=resultArraySize){
            goto endICycle;
        }
        j=0;
        jCycle:
            if(j>=resultArraySize){
                goto endJCycle;
            }
            if(resultArray[i].countR>resultArray[j].countR){
                Word swaper = resultArray[i];
                resultArray[i] = resultArray[j];
                resultArray[j] = swaper;
            }
            j++;
            goto jCycle;
        endJCycle:
        i++;
        goto iCycle;
    endICycle:

    i=0;
    iCycle1:
        if((i>=SHOWED_WORDS)||(i>=resultArraySize)){
            goto endICycle1;
        }
        cout<< resultArray[i].value<< " - " << resultArray[i].countR<<endl;
        i++;
    goto iCycle1;
    endICycle1:
    return 0;
}
