// Arup Guha
// 6/20/2020
// Solution to COP 3502 Program #4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLETTERS 2000001

typedef struct trienode {
    int freq;
    int freqAtOrBelow;
    int curChildMax;
    struct trienode* next[26];
} trienode;

// Functions for inserting.
void insert(trienode* root, char* word, int wLen, int howMany);
void insertRec(trienode* root, char* word, int k, int wLen, int howMany);

// Returns a new empty trienode.
trienode* makeNewNode();

// Frees all the memory associated with the trie pointed to by root.
void freeTrie(trienode* root);

// Functions for queries.
char* query(trienode* root, char* word, int wLen);
char* queryRec(trienode* root, char* word, int k, int wLen);

int main(void) {

    // Make this from the start. Root node for our trie.
    trienode* root = makeNewNode();

    // Get the number of commands.
    int numCommands;
    scanf("%d", &numCommands);

    // Process each command.
    for (int i=0; i<numCommands; i++) {

        int command;
        char* str = malloc(sizeof(char)*MAXLETTERS);

        // Safe to read first two items.
        scanf("%d%s", &command, str);

        // Insert.
        if (command == 1) {
            int freq;
            scanf("%d", &freq);
            insert(root, str, strlen(str), freq);
        }

        // Query
        else {
            char* ans = query(root, str, strlen(str));

            // Check this first for safety.
            if (ans == NULL)
                printf("unknown word\n");

            // Otherwise, we print the result and free it.
            else {
                printf("%s\n", ans);
                free(ans);
            }
        }

        // Need to free this also.
        free(str);
    }

    // Free the trie.
    freeTrie(root);

    return 0;
}

// Just a wrapper function for our recursive insert.
void insert(trienode* root, char* word, int wLen, int howMany) {
    insertRec(root, word, 0, wLen, howMany);
}

// Inserts howMany copies of word starting at index k into the trie pointed to by root.
void insertRec(trienode* root, char* word, int k, int wLen, int howMany) {

    // We always do this.
    root->freqAtOrBelow += howMany;

    // Here is our base case. We got to the end, so add 1 to our node and stop.
    if (k == wLen) {
        root->freq += howMany;
        return;
    }

    // No node exists, so let's create it!
    if (root->next[word[k]-'a'] == NULL) {
        root->next[word[k]-'a'] = makeNewNode();
    }

    // Calculate the new size of the subtree this will go in.
    int newChildThisPath = root->next[word[k]-'a']->freqAtOrBelow + howMany;

    // If this changes my max subtree size, update.
    if (newChildThisPath > root->curChildMax)
        root->curChildMax = newChildThisPath;

    // Now, we insert, recursively.
    insertRec(root->next[word[k]-'a'], word, k+1, wLen, howMany);
}

// Returns a pointer to a newly allocated empty trienode.
trienode* makeNewNode() {

    // Create a new node, set everything to 0, null.
    trienode* tmp = malloc(sizeof(trienode));
    tmp->freq = 0;
    tmp->freqAtOrBelow = 0;
    tmp->curChildMax = 0;

    for (int i=0; i<26; i++)
        tmp->next[i] = NULL;

    // This is a pointer to our new node.
    return tmp;
}

// A wrapper function for the query.
char* query(trienode* root, char* word, int wLen) {
    return queryRec(root, word, 0, wLen);
}

// Recursively inserts word, starting at index k into the trie pointed to by root. The length
// of the word is wLen. We pass this in to avoid calling strlen multiple times.
char* queryRec(trienode* root, char* word, int k, int wLen) {

    // Got to the end.
    if (k == wLen) {

        // No kids below.
        if (root->curChildMax == 0) return NULL;

        // Here we count how many future nodes are maximums.
        int numMax = 0;
        for (int i=0; i<26; i++) {
            if (root->next[i] == NULL) continue;
            if (root->next[i]->freqAtOrBelow == root->curChildMax)
                numMax++;
        }

        // Allocate space now.
        char* res = malloc( (numMax+1)*sizeof(char) );
        res[numMax] = '\0';

        // This is index into res.
        int idx = 0;

        // Go through letters again.
        for (int i=0; i<26; i++) {

            if (root->next[i] == NULL) continue;        // forgot this traced bit by bit...

            // Is this a max next letter? If so, add it to the string.
            if (root->next[i]->freqAtOrBelow == root->curChildMax)
                res[idx++] = (char)('a'+i);
        }

        // What we want to return.
        return res;
    }

    // Check for null pointer error and return accordingly.
    if (root->next[word[k]-'a'] == NULL) return NULL;

    // If we get here, we just recurse.
    return queryRec(root->next[word[k]-'a'], word, k+1, wLen);
}

// Frees all the memory pointed to by root, directly and indirectly.
void freeTrie(trienode* root) {

    // Go to all children.
    for (int i=0; i<26; i++) {

        // Free this subtree, if it exists.
        if (root->next[i] != NULL)
            freeTrie(root->next[i]);
    }

    // Now free our node.
    free(root);
}
