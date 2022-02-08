#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Franklyn Gonzalez, COP3502, Program P4, last edited 07/11/2020, 10:49

struct trie* init();
void insert(struct trie* tree, char word[], int k, int frequency);
char* search(struct trie* tree, char word[], int k);
char** getLines();

struct trie
{
	int freq;
	int sumFreq;
	int maxNode;
    struct trie* next[26];
	struct trie* parent;
};

struct trie* init(struct trie* mypar)
{

    // Create the struct, not a word.
    struct trie* myTree = malloc(sizeof(struct trie));

	myTree->freq = 0;
	myTree->sumFreq = 0;
	myTree->maxNode = 0;

    // Set each pointer to NULL.
    int i;
    for (i=0; i<26; i++)
		myTree->next[i] = NULL;

	myTree->parent = mypar;

    // Return a pointer to the new root.
    return myTree;
}

void insert(struct trie* tree, char word[], int k, int frequency) {

    // Down to the end, insert the word.
    if (!(*word))
    {
		if (tree->freq < frequency) tree->freq = frequency;
		tree->sumFreq += frequency;

		if (k >= 1 && tree->freq > tree->parent->maxNode)
			tree->parent->maxNode = tree->freq;
        return;
    }

    // See if the next place to go exists, if not, create it.
    int nextIndex = *word - 'a';
    if (tree->next[nextIndex] == NULL)
        tree->next[nextIndex] = init(tree);

    if (tree->freq < frequency) tree->freq = frequency;
	tree->sumFreq += frequency;

	if (k >= 1 && tree->freq > tree->parent->maxNode)
		tree->parent->maxNode = tree->freq;

    insert(tree->next[nextIndex], ++word, ++k, frequency);
}

int c;
char* search(struct trie* tree, char word[], int k)
{
	char* alpha = "abcdefghijklmnopqrstuvwxyz";

    // Down to the end, insert the word.
    if (k == strlen(word))
	{
		char* s = malloc(sizeof(char) * k);
		int max = 1, i, j;

		for (i = 0, j = 0; i < 26; i++)
		{
			if (tree->next[i] != NULL && tree->next[i]->freq >= max)
			{
				if (tree->next[i]->freq != max)
				{
					j = 0;
					s[j++] = '\n';
				}
				s[j++] = alpha[i];
				max = tree->next[i]->freq;
			}
		}

		if (j != 0)
		{
			s[j] = '\0';
			c += strlen(s);
			return s;
		}
		else
		{
			c += 13;
			return "\nunknown word";
		}
	}

    // If the next place doesn't exist, word is not a word.
    int nextIndex = word[k] - 'a';

    if (tree->next[nextIndex] == NULL)
	{
		c += 13;
		return "\nunknown word";
	}
	else return search(tree->next[nextIndex], word, k+1);
}

// Just frees all the memory pointed to by tree (directly and indirectly)
void freeDictionary(struct trie* tree) {

    int i;
    for (i=0; i<26; i++)
        if (tree->next[i] != NULL)
            freeDictionary(tree->next[i]);

    free(tree);
}

int main(int argc, char** argv)
{
	int frequency;
	int size;

	scanf("%d", &size);

	//char** lines = getLines(size);
	struct trie* tree = init(NULL);

	char* str = calloc(10000, sizeof(char));
	c = 0;

	for (int i = 0; i < size; i++)
	{
		int cmd;
		scanf("%d", &cmd);

		char* word = malloc(sizeof(char) * 26);
		scanf("%s", word);

		if (cmd == 1)
		{
			scanf("%d", &frequency);
			insert(tree, word, 0, frequency);
		}
		else strcat(str, search(tree, word, 0));
	}

	str[c] = '\0';
	printf("%s\n\n", str);

	freeDictionary(tree);
	return 0;
}
