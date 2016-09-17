#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define DEFAULT_NOFIRSTLETT 6

int nofirstlett = DEFAULT_NOFIRSTLETT;
struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree (struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
void cleantree(struct tnode *);

// word frequency count
int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];
    
    if (argc > 1 && *argv[1]++) {
      nofirstlett = atoi(argv[1]);
    }
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root);
    cleantree(root);
    return 0;
}

struct tnode *talloc(void);
char *strdup(const char *s);

// addtree: add a node with w, at or below p
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    
    if (p == NULL) { // a new word has arrived
        p = talloc();  // make a new node
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strncmp(w, p->word, nofirstlett)) == 0)
        p->count++; // repeated word
    else if (cond < 0) //less than into left subtree
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

// treeprint: in-order print of tree p
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}


// getword: get next word or character from input
int getword(char *word, int lim)
{
    int c, mygetch(void);
    void myungetch(int);
    int insidecomment = 0;
    char *w = word;
    
    while (isspace(c = mygetch()))
        ;

    if (c == '\"') {           // string litteral
      while ((c = mygetch()) != '\"' && c != EOF)
	;
      if (c != EOF)
	while (isspace(c = mygetch()))
	  ;           //skipping spaces
    } else if (c == '/') {
      if ((c = mygetch()) != '*') { 
	myungetch(c);
	strcpy(word, "/");
	return '/';
      } else { // skipping a comment
	insidecomment = 1;
	while (insidecomment && (c = mygetch()) != EOF) {
	  if (c == '*' && ((c = mygetch()) == EOF || c == '/'))
	    insidecomment = 0;
	}
	if (c != EOF)
	  while (isspace(c = mygetch()))
	    ; //skipping spaces
      }
    }
    
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        //printf("-%d-\n",lim);
        if (!isalnum(*w = mygetch())) {
            myungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 100
char buf[BUFSIZE]; // buffer for myunmygetch
int bufp = 0; // nextt free position in buf

int mygetch(void) // get a (possibly pushed back) char
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void myungetch(int c) // push char back on input
{
    if (bufp >= BUFSIZE)
        printf("myunmygetch: too many characters\n");
    else
        buf[bufp++] = c;
}

#include <stdlib.h>
// talloc: make a tnode
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(const char *s) // make a duplicate of s
{
    char *p;
    
    p = (char *) malloc(strlen(s) + 1); // +1 for the '\0'
    if (p != NULL)
        strncpy(p, s, nofirstlett);
    return p;
}

// cleantree: free the memory allocated by tnode
void cleantree(struct tnode *p)
{
  if (p != NULL) {
    cleantree(p->left);
    p->left = NULL;
    cleantree(p->right);
    p->right = NULL;
    free(p->word);
    p->word = NULL;
    free(p);
    p = NULL;
  }
}
