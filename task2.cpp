#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Програма написана для такої умови:
// 1800 символів = 1 сторінка

struct Word{
    string value;
    int* pages;
    int countR;
    int pagesCount;
};

int main(){
    int countStopWords = 7;
    string stopWords[] = {
        "-"
    };

    ifstream inputFile("text.txt");
    int resultArraySize = 0;
    Word* resultArray = new Word[resultArraySize];
    string readedWord;
    int symbolsCount = 0,
        k=0,
        i=0;

    readNewWord:{
        if(!(inputFile>>readedWord)){
            goto endOfReadingFile;
        }
        if(symbolsCount!=0) symbolsCount++;
        i=0;
        isStopWord:
            if(i>=countStopWords){
                goto endIsStopWord;
            }
            if(stopWords[i]==readedWord){
                symbolsCount++;
                goto readNewWord;
            }
            i++;
            goto isStopWord;
        endIsStopWord:

        string cleanedWord = "";
        i = 0;
        toLowerCase:
            if(!readedWord[i]){
                goto endToLowerCase;
            }

            if(readedWord[i]>=97 && readedWord[i]<=122){
                cleanedWord+=readedWord[i];
            }

            if(readedWord[i] >= 65 && readedWord[i] <= 90){
                readedWord[i]+=32;
                cleanedWord+=readedWord[i];
            }
            symbolsCount++;
            i++;
        goto toLowerCase;
        endToLowerCase:
        readedWord = cleanedWord;
        i=0;
        isAddedToResultArray:{
            if(i<=resultArraySize){
                if(readedWord==resultArray[i].value){
                    resultArray[i].countR++;
                    int page1 = symbolsCount / 1800;
                    if(symbolsCount % 1800>0){
                        page1++;
                    }
                    if(resultArray[i].pages[resultArray[i].pagesCount-1]<page1){
                        resultArray[i].pagesCount++;
                        k = 0;
                        int *pagesCopy = new int[resultArray[i].pagesCount];
                        copyPages:
                            if(k<resultArray[i].pagesCount-1){
                                pagesCopy[k] = resultArray[i].pages[k];
                            } else {
                                goto endCopyPages;
                            }
                            k++;
                        goto copyPages;
                        endCopyPages:
                            resultArray[i].pages=pagesCopy;
                            resultArray[i].pages[resultArray[i].pagesCount-1] = page1;
                    }
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
            int* page = new int[1];
            page[0] = symbolsCount / 1800;
            if(symbolsCount%1800>0){
                page[0]++;
            }
            copyResultArray[resultArraySize-1] = {readedWord,page,1,1};
            resultArray=copyResultArray;
        }
        endAddToResultArray:
            i=0;
            goto readNewWord;
    }
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
            if(resultArray[i].value<resultArray[j].value){
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

    j=0;
    i=0;

    iCycle1:
        if(i>=resultArraySize){
            goto endICycle1;
        }
        if(resultArray[i].countR>100){
            i++;
            goto iCycle1;
        }
        cout<< resultArray[i].value<< " - ";
        j=0;
        jCycle1:
            if(j>=resultArray[i].pagesCount){
                goto endJCycle1;
            }
          cout<<resultArray[i].pages[j]<<" ";
            j++;
            goto jCycle1;
        endJCycle1:
        cout<<endl;
        i++;
        goto iCycle1;
    endICycle1:

    return 0;
}
