#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define MAXPAGES 100
#define DEFAULT_NOFIRSTLETT 12

int isnoise(char *word);

int nofirstlett = DEFAULT_NOFIRSTLETT;
struct tnode {
  char *word;
  int count;
  int *pagelist;
  int ipage;
  int nopages;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *addtree (struct tnode *, char *s, int n);
struct tnode *addleaf2tree(struct tnode *tree, struct tnode *leaf);
void treeprint(struct tnode *);
void sortedtreeprint(struct tnode *);
struct tnode *sorttree(struct tnode *st, struct tnode *tree);
int getword(char *, int);
void cleantree(struct tnode *);

// word frequency count
int main(int argc, char *argv[])
{
  struct tnode *root;
  struct tnode *sortedtree; // sorted by word frequency
  char word[MAXWORD];
  int pageno = 1;
    
  if (argc > 1 && *argv[1]++) {
    nofirstlett = atoi(argv[1]);
  }
  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]) && !isnoise(word))
      root = addtree(root, word, pageno);
    else if (word[0] == '\n')
      pageno++;
  //treeprint(root);
  sortedtree = sorttree(sortedtree, root);
  sortedtreeprint(sortedtree);
  cleantree(root);
  cleantree(sortedtree);
  return 0;
}

struct tnode *talloc(void);
char *strdup(const char *s);

// addtree: add a node with w, at or below p
struct tnode *addtree(struct tnode *p, char *w, int pageno)
{
  int cond;
    
  if (p == NULL) { // a new word has arrived
    p = talloc();  // make a new node
    p->word = strdup(w);
    p->count = 1;
    p->pagelist = calloc(MAXPAGES, sizeof(int));
    (p->pagelist)[0] = pageno;
    p->ipage = 1;
    p->nopages = MAXPAGES;
    p->left = p->right = NULL;
  } else if ((cond = strncmp(w, p->word, nofirstlett)) == 0) {
    p->count++; // repeated word
    if (pageno != p->pagelist[p->ipage - 1])
      p->pagelist[p->ipage++] = pageno;
    //printf("added (%s) at %d\n", w, pageno);
  }
  else if (cond < 0) //less than into left subtree
    p->left = addtree(p->left, w, pageno);
  else
    p->right = addtree(p->right, w, pageno);
  return p;
}

struct tnode *addleaf2tree(struct tnode *p, struct tnode *leaf)
{
  int cond;
    
  if (p == NULL) { // a new word has arrived
    p = talloc();  // make a new node
    p->word = strdup(leaf->word);
    p->count = leaf->count;
    p->pagelist = NULL;
    p->ipage = 0;
    p->nopages = MAXPAGES;
    p->left = p->right = NULL;
  } else if (leaf->count > p->count) //less than into left subtree
    p->left = addleaf2tree(p->left, leaf);
  else
    p->right = addleaf2tree(p->right, leaf);
  return p;
}


// treeprint: in-order print of tree p
void treeprint(struct tnode *p)
{
  int i;
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s: ", p->count, p->word);
    for (i = 0; i < p->ipage - 1; i++)
      printf("%d, ", p->pagelist[i]);
      printf("%d.", p->pagelist[i]);
    putchar('\n');
    treeprint(p->right);
  }
}

void sortedtreeprint(struct tnode *p)
{
  int i;
  if (p != NULL) {
    sortedtreeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    sortedtreeprint(p->right);
  }
}

// sorttree: sort tree using word frequency
struct tnode *sorttree(struct tnode *st, struct tnode *tree)
{
  if (tree != NULL) {
    st = addleaf2tree(st, tree);
    if (tree->left != NULL)
      st = sorttree(st, tree->left);
    if (tree->right != NULL)
      st = sorttree(st, tree->right); 
  }
  return st;
}


// getword: get next word or character from input
int getword(char *word, int lim)
{
  int c, mygetch(void);
  void myungetch(int);
  int insidecomment = 0;
  char *w = word;
    
  while (isblank(c = mygetch()))
    ;

  if (c == '\"') {           // string litteral
    while ((c = mygetch()) != '\"' && c != EOF)
      ;
    if (c != EOF)
      while (isblank(c = mygetch()))
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
	while (isblank(c = mygetch()))
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

char noisewords[][10] = {"a", "an", "in", "out", "for", "from",
			 "to", "and", "or","is", "be", "are", "too"};
#define MIN_WORD_SIZE 4
#define NO_NOISE_WORDS (sizeof noisewords / sizeof noisewords[0])
int isnoise(char *word)
{
  int i;

  if (strlen(word) < MIN_WORD_SIZE)
    return 1;
  for (i = 0; i < NO_NOISE_WORDS; i++)
    if (strcmp(word, noisewords[i]) == 0)
      return 1;
  return 0;
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
    free(p->pagelist);
    p->pagelist = NULL;
    free(p->word);
    p->word = NULL;
    free(p);
    p = NULL;
  }
}
