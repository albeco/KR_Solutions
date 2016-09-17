#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101
#define MAXWORD 100

// kr_6-5 undef: remove name and definion from nlist table


struct nlist { // table entry
  struct nlist *next; // next entry in chain
  char *name; // defined name
  char *defn; // repacement text
};
static struct nlist *hashtab[HASHSIZE]; // pointer table

int getword(char *, int);
struct nlist *lookup(char *);
struct nlist *install(char *name, char *defn);
int undef(char *);
int cleanNlist(void);
char *mystrdup(const char *);

int main(void)
{
  char word[MAXWORD];
  char *worddef;
  char keywords[][20] = {"char", "int", "float", "double"};
  int i;
  struct nlist *np;
  
  for (i=0; i < 4; i++) {
    printf("intalling word \'%s\'\n", keywords[i]);
    worddef = mystrdup(keywords[i]);
    strcat(worddef,"_def");
    np = install(keywords[i], worddef);
    if (np == NULL)
      printf("cannot install keyword \'%s\'\n", keywords[i]);
  }
  np = install("cat", "animal");

  i = undef("float");
  if (i == 0)
    printf("error during undef\n");
 

  while (getword(word, MAXWORD) != EOF)
    if ((np = lookup(word)) != NULL)
      printf("found %s:%s\n", word, np->defn);
    else printf("not found %s\n", word);

  free(worddef);
  cleanNlist();
  return 0;
}

// hash: formhash value for string s
unsigned int hash(char *s)
{
  unsigned int hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

// install: put (name, defn) in hashtab
struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned int hashval;

  if ((np = lookup(name)) == NULL) { // not found
    np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL || (np->name = mystrdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  }
  else // already there
    free((void *) np->defn); // free previous defn
  if ((np->defn = mystrdup(defn)) == NULL)
    return NULL;
  return np;
}


// lookup: look for s in hashtab
struct nlist *lookup(char *s)
{
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np; // found
  return NULL; // not found
}

// undef: remove nodew with name and definition from hastab
int undef(char *name)
{
  struct nlist *a;
  struct nlist *b;
  int c;

  a = hashtab[hash(name)];
  b = NULL;
  
  if (a == NULL) {
    printf("undef: nothing for hashtab of \'%s\'\n", name);
    return 0;
  } else if (strcmp(a->name, name) == 0) {
    b = a;
    hashtab[hash(name)] = a->next;
  } else {
    for (b = a->next ; b != NULL; a = b) {
      if (strcmp(b->name, name) == 0) {
	a->next = b->next;
	break;
      }
    }
  }
  if (b == NULL) {
    printf("undef: no definition of \'%s\'\n", name);
    return 0;
  } else {
    free(b->name);
    free(b->defn);
    b->name = NULL;
    b->defn = NULL;
    free(b);
    b = NULL;
  }
}

// cleanNlist: free the memory occupied by nlist
int cleanNnode(struct nlist *node);
int cleanNlist(void)
{
  int i;
  
  for (i = 0; i < HASHSIZE; i++) {
    if (hashtab[i] != NULL) {
      cleanNnode(hashtab[i]);
      hashtab[i] = NULL;
    }
  }
  return i;
}

int cleanNnode(struct nlist *node)
{
  if (node != NULL) {
    if (node->next != NULL) {
      cleanNnode(node->next);
      node->next = NULL;
    }
    free(node->name);
    node->name =NULL;
    free(node->defn);
    node->defn = NULL;
    free(node);
    node = NULL;
    return 1;
  }
  else
    return 0;
}


// getword: get next word or character from input
int getword(char *word, int lim)
{
  int c, mygetch(void);
  void myungetch(int);

  char *w = word;

  while (isspace(c = mygetch()))
    ;
  
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

char *mystrdup(const char *s) // make a duplicate of s
{
  char *p;

  p = (char *) malloc(strlen(s) + 1); // +1 for the '\0'
  if (p != NULL)
    strcpy(p, s);
  return p;
}
