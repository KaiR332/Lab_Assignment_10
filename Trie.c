#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//data not stored inside trie node, no letter is stored inside the nodes.
//the letter is decided by the index which is being used, example: children[15] represents 'p' b/c p is 16th letter of alphabet.
struct Trie
{
    int count; //number of times the letter is used
    struct Trie* children[26]; //26 letters in alphabet
};

void insert(struct Trie *ppTrie, char *word);//pptrie is root, word is for letter insertion. get word, find length of word for number of nodes to create&insert. you can then use a for loop to create the empty nodes
//check if letter node is available, if not create a new node, if so then just point the node to the already existing letter node.
//use a temp node to navigate through each word.
int numberOfOccurances(struct Trie *pTrie, char *word);//ptrie is for data structure, word is for how many versions of a word present in trie structure
struct Trie *deallocateTree(struct Trie *pTrie);
struct Trie* createNode();

int main(void)
{
    //read the number of the words in the dictionary
    // parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    struct Trie* myDictionary = createNode();

    for(int i=0;i<5;i++)
    {
        insert( myDictionary, pWords[i]);
    }

    for(int i=0;i<5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances( myDictionary, pWords[i]));
    }

    myDictionary = deallocateTree( myDictionary);

    if (myDictionary != NULL)
       printf("There is an error in this program\n");
    return 0;
}

struct Trie* createNode() 
{
    // Create the struct, not a word.
    struct Trie* newNode = malloc(sizeof(struct Trie));
    newNode->count = 0;

    // Set each pointer to NULL.
    int i;
    for (i=0; i<26; i++)
        newNode->children[i] = NULL;

    // Return a pointer to the new root.
    return newNode;
}


void insert(struct Trie *ppTrie, char *word)
{
    struct Trie* temp = ppTrie;
    for(int i=0;i<strlen(word);i++)
    {
        int index = word[i] - 'a';
        if(temp->children[index] == NULL)
        {
            temp->children[index] = createNode();
        }
        temp = temp->children[index];
    }
    temp->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int result;
    struct Trie* temp = pTrie;

    for(int i=0;i<strlen(word);i++)
    {
        int index = word[i] - 'a';
        temp = temp->children[index]; 
    }

    result = temp->count;
    return result;
}

struct Trie *deallocateTree(struct Trie *pTrie)
{
    int i;
    for (i=0; i<26; i++)
        deallocateTree(pTrie->children[i]);

    free(pTrie);
}