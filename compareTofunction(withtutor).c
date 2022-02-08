#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Create a struct of your own and a compareTo function for that struct that takes in two pointers
// to the struct and returns a negative integer if the first struct "comes before" the second, returns a
// positive integer if the first struct "comes after" the second, and 0 if the two structs are equal. Then,
// write a recursive binary search which determines if a desired struct is in a sorted array of the structs

typedef struct node
{
  int data;
  struct node *front, *back;
} node;

int compareToNode(node *s1, node *s2)
{
  // Check if they're equal: Return 0
  if (s1->data == s2->data)
    return 0;

  // Check if s1 comes before s2: Return 1
  else if (s1->data < s2->data)
    return 1;

  // Check if s1 comes after s2: Return -`
  else
    return -1;
}

typedef struct Person
{
  char *firstName;
  char *lastName;
  int id;
} Person;

int compareTo(Person *p1, Person *p2)
{
  int res;

  res = strcmp(p1->firstName, p2->firstName);
  // res = 1, -1, 0

  // firstName
  if (res != 0)
    return res;

  res = strcmp(p1->lastName, p2->lastName);
  // lastName

  if (res != 0)
    return res;


  // id: 11111111   11111111 return 0
  //     11111111   11111113 return -2
  //     11111111   11111109 return 2
  return p1->id - p2->id;
}

int binarySearch4Real(array, n, key, 0, n-1);

//                  array of People  how many     who we're looking for
int binarySearch(int **array, int n, Person *key)
{
  // mid = (lo + hi) / 2;
  return binarySearch4Real(array, key, 0, n-1);
}

int binarySearch4Real(Person **array, Person *key, int lo, int hi)
{
  // Base Case
  if (lo > hi)
    return 0;

  int mid = (lo + hi) / 2;

  // if key is less than our mid
  if (compareTo(key, array[mid]) < 0)
    return binarySearch4Real(array, key, lo, mid - 1);
  // if key is greater than our mid
  else if (compareTo(key, array[mid]) > 0)
    return binarySearch4Real(array, key, mid + 1, hi);
  // else return 1
  else
    return 1;
}

int main(void) {

  Person *p1 = malloc(sizeof(Person));
  p1->firstName = malloc(sizeof(char) * 5);
  strcpy(p1->firstName, "Will");

  p1->lastName = malloc(sizeof(char) * 6);
  strcpy(p1->lastName, "Smith");

  p1->id = 11111111;

  Person *p2 = malloc(sizeof(Person));
  p2->firstName = malloc(sizeof(char) * 5);
  strcpy(p2->firstName, "Woll");

  p2->lastName = malloc(sizeof(char) * 6);
  strcpy(p2->lastName, "Smith");

  p2->id = 1011;

  printf("%d\n", compareTo(p1, p2)); // 0

  strcpy(p2->firstName, "Will");
  strcpy(p2->lastName, "Smith");

    printf("%d\n", compareTo(p1, p2)); // -

  return 0;
}
