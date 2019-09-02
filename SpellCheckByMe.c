

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct trie node;
struct trie
{
    bool isEOW;
    node *next[ALPHABET_SIZE];
};

node *root;
node* CreateNode()
{
	node *newNode = malloc(sizeof(node));
	int i;
	for(i=0;i<ALPHABET_SIZE;i++)
		newNode->next[i]=NULL;

	newNode->isEOW = false;
	return newNode;

}
void insertWord(node *root, char word[])
{
	node *temp=root;
	int i;
	int word_length=strlen(word);

	for(i=0;i<word_length;i++)
	{
		int index= word[i]-'a';

		if(temp->next[index]== NULL)
		temp->next[index]=CreateNode();

		temp=temp->next[index];
	}
	temp->isEOW=true;
}
bool hasWord(node* root, char word[])
{
	node *temp=root;
	int word_length=strlen(word);
	int i;
	for(i=0;i<word_length;i++)
	{
		int index=word[i]-'a';

		if(temp->next[index]==NULL)
			return false;

		temp=temp->next[index];
	}
	return temp->isEOW;
}
void replaceChar(node* root,char word[])
{

	int i,len;
	char ch;

	len=strlen(word);

	for(i=0;i<len;i++)
	{
		char in=word[i];
		for(ch='a';ch<='z';ch++)
		{
			if(word[i]!=ch)
			{
				word[i]=ch;

				if(hasWord(root,word))
							{
								printf("\nREPLACED:%s",word);
							}
			 }


		}
		word[i]=in;
	}
}
void insertChar(node* root, char word[])
{
	 printf("%s ","cccccccccccc");
     int i, len;
     len=strlen(word);
     char newWord[len+2];
     sprintf(newWord, "%c%s",'~', word);
     for(i=0;i<len+1;i++)
     {
    	 char ch;
    	 for(ch='a';ch<='z';ch++)
    	 {
    		 newWord[i]=ch;


				if(hasWord(root,newWord))
							{
								printf("\nINSERTED:%s",newWord);
							}
    	 }
    	 newWord[i]=newWord[i+1];
     }

}

void deleteChar(node* root, char word[])
{
	int i, len,j,k;
	len=strlen(word);
	char newWord[len-1];

	for(i=0;i<len;i++)
	{
		k=0;
		for(j=0;j<len;j++)
		{
			if(i==j)continue;
			newWord[k++]=word[j];
		}
		if(hasWord(root,newWord))
		{
			printf("\nDELETED: %s",newWord);
		}
	}


}

void swap(char word[], int i, int j)
{
    char ch = word[i];
    word[i] = word[j];
    word[j] = ch;
}

void swapAlternate(node*root,char word[])
{
    int i;
    int len = strlen(word);
    for(i=0; i<=len-2; i++)
    {
        swap(word, i, i+1);
        if(hasWord(root, word))
            printf("\nSWAP: %s", word);
        swap(word, i, i+1);
    }
}
int main()
{
	 FILE *fp = fopen("dictionary.txt", "r");

	    if(fp==NULL)
	    {
	        printf("File Not Found");
	        return 1;
	    }

	    node *root=CreateNode();
	    char word[200];
	        while(!feof(fp))
	        {
	            fscanf(fp, "%s", word);
	            insertWord(root, word);
	        }

	        fclose(fp);

	        char misspelt_word[200];
	        printf("\nEnter mis-spelt word: ");
	        scanf("%s", misspelt_word);

	        insertChar(root,misspelt_word);
	        replaceChar(root,misspelt_word);

	        deleteChar(root,misspelt_word);
	        swapAlternate(root,misspelt_word);

	        return 0;
}
