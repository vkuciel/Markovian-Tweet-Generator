// Victor Kuciel
// CPEG - 476 - Secure Software 
// Project 1: Markovian Tweet Generator

#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// Make struct first
struct Mark{
    vector<string> succeeders;
    string word;
};

///////////////////// Functions
int dWord(vector<Mark> wordlist, string s, int length);

vector<Mark> dictionaryGenerate(string tweet[],int length);

string makeTweet(vector<Mark> wordlist, string firstWord);

void generateTweet(string tweet);
////////////////////

/////////////////// Main
int main(){
    ifstream file;
    file.open("tweet.txt");
    int i = 0;
    string word;
    vector<string> tweet;

    if(!file.is_open()){
        cout<< "Error: Couldn't open file" << endl;
        return 0;
    } else{
        while(file >> word){
            string genNewWords[10];
            string tmp = word;
            int k = 0;

            for(int j = 0; j<tmp.length(); j++){
                word.erase(remove(word.begin(), word.end(), '\"' ), word.end());
                if(word.find(".") != std::string::npos){
                    genNewWords[k] = word[word.find(".")];
                    word.erase(word.find("."), 1);
                    k++;
		}

		if(word.find(",") != std::string::npos){
		    genNewWords[k] = word[word.find(",")];
                    word.erase(word.find(","), 1);
                    k++;
		}

		if(word.find("?") != std::string::npos){
                    genNewWords[k] = word[word.find("?")];
                    word.erase(word.find("?"), 1);
                    k++;
                }

		if(word.find("!") != std::string::npos){
                    genNewWords[k] = word[word.find("!")];
                    word.erase(word.find("!"), 1);
                    k++;
                }

                if(word.find(";") != std::string::npos){
                    genNewWords[k] = word[word.find(";")];
                    word.erase(word.find(";"), 1);
                    k++;
		}
            }
            tweet.push_back(word);
	    i++;

            for(int j = 0; j<10; j++){
                if(genNewWords[j] != ""){
		    tweet.push_back(genNewWords[j]);
		    i++;
		}
            }
        }
    }
    string newArr[i];
    for(int q = 0; q<i; q++){
        newArr[q] = tweet[q];
    }
    vector<Mark> wordlist = dictionaryGenerate(newArr, i);
    string newTweet = makeTweet(wordlist,"The");
    generateTweet(newTweet);
    file.close();
    return 0;
}
//////////////////////
int dWord(vector<Mark> wordlist, string s, int length){  
  
    for(int i = 0; i<wordlist.size(); i++){
        string word1 = wordlist[i].word;
        string word2 = s;
        transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
        transform(word2.begin(), word2.end(), word2.begin(), ::tolower);  
	if(word1 == word2){
	    return i;
	}
    }
    return -1;
}

vector<Mark> dictionaryGenerate(string tweet[], int length){
    vector<Mark> wordlist;

    for (int i = 0; i<length-1; i++){
        int index = dWord(wordlist, tweet[i], length);
	if(index != -1){
            
	    wordlist[index].succeeders.push_back(tweet[i+1]);
            
	} else{
            Mark newList;
            newList.word = tweet[i];
            newList.succeeders.push_back(tweet[i+1]);
            wordlist.push_back(newList);
	}
    }
    return wordlist;
}


string makeTweet(vector<Mark> wordlist, string firstWord){
    int charNum = 0;
    string currentWord = firstWord;
    string newTweet = firstWord;
    srand(time(0));

    while(charNum < 280){
        int wordIndex = dWord(wordlist, currentWord, wordlist.size());
        int newWordSize = wordlist[wordIndex].succeeders.size();
        int randIndex = rand() % newWordSize;
        string nextWord = wordlist[wordIndex].succeeders[randIndex];
    
        if(nextWord != ";" && nextWord != "!" && nextWord != "?" && nextWord != "," && nextWord != "."){ // Checks for punctuation marks
            newTweet = newTweet + " " + nextWord;
            charNum = charNum + nextWord.length()+1;
        } else{
            newTweet = newTweet+nextWord;
            charNum = charNum + nextWord.length();
	}

        currentWord = "";
        currentWord = currentWord+nextWord;
    }
    return newTweet;
}

void generateTweet(string tweet){
    int spaceIndex = 0;
    cout << "Newly Generated Tweet:" << endl;

    for(int i = 70; i<80; i++){
        if(tweet[i] ==' '){
            spaceIndex = i;
        }
    }

    string l1 = tweet.substr(0, spaceIndex);
    cout << l1 << endl;
    int spaceIndex2 = 0;

    for(int i = spaceIndex+70; i<spaceIndex+80; i++){
        if(tweet[i] == ' '){
            spaceIndex2 = i;
        }
    }

    string l2 = tweet.substr(spaceIndex+1, spaceIndex2-(spaceIndex+1));
    cout<< l2 << endl;
    int spaceIndex3 = 0;

    for(int i = spaceIndex2+70; i<spaceIndex2+80; i++){
        if(tweet[i] == ' '){
            spaceIndex3 = i;
        }
    }

    string l3 = tweet.substr(spaceIndex2+1,spaceIndex3-(spaceIndex2+1));
    cout<< l3 << endl;
    string l4 = tweet.substr(spaceIndex3+1,tweet.length()-spaceIndex3);
    cout<< l4 << endl;
}

