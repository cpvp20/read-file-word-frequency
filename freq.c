//reads passage amd counts the number of times each word apppears
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define maxWords 50//amount of different words
#define maxLength 10
#define MAXWBUFFER maxLength+1//el +1 es por el caracter nulo en los strings

int main(){
	int getWord (FILE*, char[]);
	int bSearch (int, int, char[], int max, char [][max]);
	void addToList (char[], int max, char [][max], int[], int, int);
	void printResults (FILE*, int max, char[][max], int[], int);
	char wordList[maxWords][MAXWBUFFER], word[MAXWBUFFER];
	int freq[maxWords], numWords=0;

	FILE* in = fopen ("passage.txt", "r");//open text file
	if (in==NULL){
		printf("cannot find file\n");
		exit(1);
	}

	FILE * out = fopen ("output.txt","w");
	if (out==NULL){
		printf("cannot create output file\n");
		exit(2);
	}

	for (int i=0; i <maxWords; i++) freq[i]=0;//creates empty table of frequencies

	while (getWord(in,word) !=0){//no se ha acabdo el texto, se sigue leyendo la sig palabra
		int loc = bSearch (0, numWords-1, word, MAXWBUFFER, wordList);//find location for word
		if (strcmp(word, wordList[loc]) == 0) ++freq[loc];//already found word found
		else//new word found
			if (numWords<maxWords){//if table not full
				addToList(word, MAXWBUFFER, wordList, freq, loc, numWords-1);
				++numWords;
			}//if
			else fprintf (out, "'%s' not added to table\n", word);//fyi this word no longer was recorded
	}
	printResults(out, MAXWBUFFER, wordList,freq, numWords);
	return 0;
}//main



//funciones

int getWord (FILE* in, char str[]){//stores word in str and retunrs 1 if a word is found
char ch;
int n=0;
while(!isalpha(ch=getc(in)) && ch!= EOF);
if (ch== EOF) return 0;
str[n++]=tolower(ch);
while(isalpha(ch=getc(in)) && ch!= EOF)
	if (n< maxLength) str[n++] = tolower(ch);
str[n]= '\0';
return 1;
}

int bSearch (int lo, int hi, char key[], int max, char list[][max]){
	while(lo<=hi){
		int mid= (lo+hi)/2;
		int cmp = strcmp (key, list[mid]);
		if (cmp==0) return mid; //key found
		if (cmp<0) hi=mid -1;
		else lo = mid +1;
	}
return lo;// key not found so return location where it should be inserted
}

void addToList(char item[], int max, char list[][max], int freq[], int p, int n){//adds item to list[p] and sets freq[p] to 1
	for (int i=n; i >=p; i --){
		strcpy (list[i+1], list [i]);
		freq[i+1]= freq[i];
	}
	strcpy(list[p], item);
	freq[p]=1;
}

void printResults( FILE *out, int max, char list[][max], int freq[], int n){
fprintf(out, "\nWords     Frequency\n\n");
for(int i =0; i<n;i++)
	fprintf(out,"%-15s %2d\n", list[i], freq[i]);
}

