#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Franklyn Gonzalez, COP3502, Program P4, last edited 07/11/2020, 10:49

struct trie {
	int freq;
	int sumFreq;
	int maxNode;
    struct trie* next[26];
	struct trie* parent;
};

struct trie* init();
void insert(struct trie* tree, char word[], int k, int frequency);
char* search(struct trie* tree, char word[], int k);
void freeDictionary(struct trie* tree);
void runCommands();

int main(void)
{
	runCommands();
	return 0;
}

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

// Just frees all the memory pointed to by tree (directly and indirectly)
void freeDictionary(struct trie* tree)
{
    for (int i = 0; i < 26; i++)
        if (tree->next[i] != NULL) freeDictionary(tree->next[i]);

    free(tree);
}

void insert(struct trie* tree, char word[], int k, int frequency) {

	// If this frequency is larger than the previously entered frequency then change it.
	if (tree->freq < frequency) tree->freq = frequency;

	// If deeper than the top node and its frequency is larger than its parent's max node.
	if (k >= 1 && tree->freq > tree->parent->maxNode) tree->parent->maxNode = tree->freq;

	tree->sumFreq += frequency;

    // Down to the end, insert the word.
    if (!(*word)) return;

    // See if the next place to go exists, if not, create it.
    int nextIndex = *word - 'a';
    if (!tree->next[nextIndex]) tree->next[nextIndex] = init(tree);

    insert(tree->next[nextIndex], ++word, ++k, frequency);
}

char* search(struct trie* tree, char word[], int k)
{
	// Initialize alphabet and error strings.
	char* alpha = "abcdefghijklmnopqrstuvwxyz";
	char* error = "\nunknown word";

    // Down to the end, insert the word.
    if (k == strlen(word))
	{
		// Initialize characters to be displayed.
		char* chars = malloc(sizeof(char) * 26);
		int max = 1, i, j;

		for (i = 0, j = 0; i < 26; i++)
		{
			// Check if a node is initialized and checks its sum of frequencies.
			if (tree->next[i] != NULL && tree->next[i]->sumFreq >= max)
			{
				if (tree->next[i]->sumFreq != max)
				{
					j = 0;
					chars[j++] = '\n';
				}
				chars[j++] = alpha[i];
				max = tree->next[i]->sumFreq;
			}
		}

		// If 0 then no additional nodes have been found.
		if (j != 0)
		{
			chars[j] = '\0';
			return chars;
		}
		else return error;
	}

    // If the next place doesn't exist, word is not a word.
    int nextIndex = word[k] - 'a';

	// If NULL then there are no additional characters in the given word.
    if (!tree->next[nextIndex]) return error;
	else return search(tree->next[nextIndex], word, k+1);
}

void runCommands()
{
	// Obtains the number of commands to be executed.
	int numLines;
	scanf("%d", &numLines);

	struct trie* tree = init(NULL);

	// Initializes output string
	char* str = calloc(2000000, sizeof(char));
	int numChars = 0;

	for (int i = 0; i < numLines; i++)
	{
		// Obtains the command number.
		int cmd;
		scanf("%d", &cmd);

		// Grabs the word being used for the command; 45 is the length of the longest English word.
		char* word = malloc(45*sizeof(char));
		scanf("%s", word);

		if (cmd == 1)
		{
			// Obtains the amount of times the word will be entered into the trie.
			int frequency;
			scanf("%d", &frequency);
			insert(tree, word, 0, frequency);
		}
		else
		{
			char* result = search(tree, word, 0);
			numChars += strlen(result);
			strcat(str, result);
		}
	}

	str[numChars] = '\0';
	printf("%s", str);


	freeDictionary(tree);
	return;
}


