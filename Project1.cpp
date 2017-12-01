/*
 * Project1.cpp
 * 
 * Name: Thuy Nhung Pham (ttp484)
 * EE312 Summer 2017
 * SpellCheck
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

char articleWord[100];  //array to store a single word from article
char dictionaryWord[100]; //array to store a single word from dictionary
int dictionaryCount = 0;

int matchWord(char array[], int count, int dictCount) {
    int index=0;
    int length = count;
    if(count != dictCount) { //if the articleWord length and the dictionaryWord length is not the same--> break
        return 0;
    }
    else {
        for(index = 0; index < count; index++) {
            if((array[index] == dictionaryWord[index])) {
                length = length - 1;
            }
        }
        if(length == 0) {   //length = 0 means there is a match
            return 1;
        }
        else{
            return 0;       // length != 0 means there's no match
        }
    }
}

void ConvertToLower(char array[], int count) {  //Make all letters in the word lowercase
    int index=0;
    char character=0;
    for(index = 0; index < count; index++) {
        character = articleWord[index];
        if(((character >= 'A')&&(character <= 'Z'))) {
            array[index] = array[index] + 0x20;
        }
    }

}

void ConvertDictToLower(int dictionaryCount) { //Convert the dictionary words to lowercase
    int index=0;
    char character=0;
    for(index = 0; index < dictionaryCount; index++) {
        character = dictionaryWord[index];
        if(((character >= 'A')&&(character <= 'Z'))) {
            dictionaryWord[index] = 0x20 + dictionaryWord[index];
        }
    }
}

int DictWord(char dictionary[]) { //get the next word in the dictionary into dictionaryWord[]
    int count=0;
    int index;
    count = 0;

    for (index = 0; index < 100; index++) { //clear dictionaryWord for the next word in the dictionary
        dictionaryWord[index] = 0;
    }


    if(dictionaryCount != 0) {
        dictionaryCount++;      //the index of the dictionary, in other words, how far in the dictionary we've search through
    }
    while(dictionary[dictionaryCount] != '\n') { //put the word in the dictionary[] into dictionaryWord[]
        dictionaryWord[count] = dictionary[dictionaryCount];
        count++;
        dictionaryCount++; //index for dictionary[]
    }
    return count; //return the number of characters that were added into dictionaryWord[]
}

int detect(char array[], int count, char dictionary[]) {  //detect if there's only one letter or not, if not convert to lowercase then see if it's correct, and set the corresponding flag
    int flag = 0; //flag = 1 = there is a match,
    int dictcount = 0; //number of characters in the word from the dictionary
    if(count <= 1) { //if there's only one letter return 1 as a match
        return 1;
    }
    ConvertToLower(array, count); //convert articleWord[] into all lowercase
    while(1) {
        if ((dictionary[dictionaryCount + 1] == 0) || (dictionary[0] == 0)) { //break if it's at the end the copy of dictionary
            break;
        }

        dictcount = DictWord(dictionary); //get the number of characters that are in the currect word on the dictionary
        ConvertDictToLower(dictcount); //convert all the characters in the dictionaryWord [] to lowercase
        flag = matchWord(array, count, dictcount);
        if(flag == 1) { //if found is one that means there is match
            break;
        }
    }
    dictionaryCount = 0;
    return flag;
}


void spellCheck(char article[], char dictionary[]) {

    int index = 0;
    int index2 = 0;
    char character;
    int count = 0;
    int flag = -1; //flag = -1

    while(article[index] != 0) {

        character = article[index];
        flag = -1;
        if( ((character >= 'a')&&(character <= 'z'))||((character >= 'A')&&(character <= 'Z'))     ) { //if letter is lowercase or uppercase add it to the Word array
            articleWord[count] = character;
            count++;
        }
        else  {

            flag = detect(articleWord, count, dictionary); //if it's a space go detect if it's correct or not
        }

        if(flag == 0) { // if there isn't a match, print it out
            for(index2 = 0; index2 < count; index2++) {
                printf("%c", articleWord[index2]);
                articleWord[index2] = 0;
            }
            printf("\n"); //print new line
            count = 0;
        }
        if(flag == 1) {
            count = 0; // there's a match || there's only one letter, then reset count
        }
        index++;

    }
if(article[index]==0 && articleWord[count] !=0){ //for articles that do not have \n
    flag = detect(articleWord, count, dictionary);
    if(flag == 0) { // if there isn't a match, print it out
        for(index2 = 0; index2 < count; index2++) {
            printf("%c", articleWord[index2]);
            articleWord[index2] = 0;
        }
        printf("\n");
        count = 0;

    }
    if(flag == 1) {
        count = 0; //if it's only one letter, don't scan it thru dictionary
    }
}

}
