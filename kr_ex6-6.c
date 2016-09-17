#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 500
#define MAXWORD 500
#define MAXLINE 2000

// kr_ex6-6 simple version of #define preprocessor
// skip comments, handles well string constant but does not
// support char constants
// kr_ex6-5 undef: remove name and definion from nlist table


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
  int copyspaces(void); // copy blanks from input to output
  int skipspaces(void); //skip spaces
  char line[MAXLINE];
  char *p;
  char word[MAXWORD];
  char name[MAXWORD];
  char worddef[MAXWORD];
  //char keywords[][20] = {"char", "int", "float", "double"};
  int i;
  struct nlist *np;
  
  while (copyspaces() != EOF && getword(word, MAXWORD) != EOF) {
    if (strcmp(word, "#define") == 0) {
      if (getword(name, MAXWORD) != EOF) {
      	if (getword(worddef, MAXWORD) != EOF) {
      	  install(name, worddef);
      	} else {
      	  printf("error: cannot read definition of word: \'%s\'\n", name);
      	  break;
      	}
      } else {
      	printf("error: cannot read definition word name\n");
      	break;
      }
    } else if (strcmp(word, "#undef") == 0) {
      if (getword(name, MAXWORD) != EOF)
  	undef(name);
      else {
  	printf("error: cannot undefine name\n");
  	break;
      }
    } /* else if (word[0] == '?') { */
    /*   if (getword(name, MAXWORD) != EOF && (np = lookup(name)) != NULL) { */
    /* 	printf("%s = %s\n", np->name, np->defn); */
    /*   } */
    /*   else */
    /* 	printf("error: cannot retrieve requested definition\n"); */
    /* } */
    else if (isalpha(word[0])) {
      np = lookup(word);
      printf("%s", np == NULL ? word : np->defn);
    }
    else
      printf("%s", word);
  }
  
  cleanNlist();
  return 0;
}

int copyspaces(void)
{
  int c, mygetch(void);
  void myungetch(int);
  
  c = EOF;
  while (isspace(c = mygetch()))
    putchar(c);
  myungetch(c);
  return c;
}

int skipspaces(void)
{
  int c, mygetch(void);
  void myungetch(int);
  
  c = EOF;
  while (isspace(c = mygetch()))
    ;
  myungetch(c);
  return c;
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
  return 1;
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
// this version reads also numbers
int getword(char *word, int lim)
{
  int c, mygetch(void);
  void myungetch(int);
  int insidecomment = 0;
  char *w = word;

  while (isspace(c = mygetch()))
    ;
  if (c == '/') {
    if ((c = mygetch()) != '*') { 
      myungetch(c);
      strcpy(word, "/");
      return '/';
    } else { // skipping a comment
      insidecomment = 1;
      while (insidecomment && (c = mygetch()) != EOF) {
	if (c == '*' && (((c = mygetch()) == EOF) || c == '/'))
	  insidecomment = 0;
      }
      if (c != EOF)
	while (isspace(c = mygetch()))
	  ; //skipping spaces
    }
  }
  
  if (c != EOF)
    *w++ = c;
  if (c == '\"') { // string litteral
    while ((c = mygetch()) != '\"' && c != EOF)
      *w++ = c;
    *w++ = '\"';
    *w = '\0';
    if (c == EOF)
      myungetch(c); // note that standard ungetch does not allow EOF pushback
    return word[0];
  } else if (c == '\'') { // escaped char sequence
    c = mygetch();
    if (c == EOF) {
      *w = '\0';
      myungetch(c);
      return word[0];
    }
    else if (c == '\'') {
      *w++ = c;
      *w = '\0';
      return word[0];
    }
    else if (c != '\\') {
      *w++ = c; // write the char
      c = mygetch(); //read the '
      *w++ = c;
      *w = '\0';
      if (c != '\'') printf("error (%c) instead of (\')\n", c);
      return word[0];
    }
    else // c == '\\'
      {
	*w++ = c; // write the /
	c = mygetch(); // read the char
	*w++ = c; // write the char
	c = mygetch(); //read the '
	if (c != '\'') printf("error (%c) instead of (\')\n", c);
	*w++ = c; // write the '
	*w = '\0';
	return word[0];
      }
  }
  else if (!isalnum(c) && c != '#') {
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
int buf[BUFSIZE]; // buffer for myunmygetch
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
