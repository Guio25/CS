
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct node {
  int data1;
  int data2;
  struct node *next;
};


struct nodeDangerous {

  int value;
  struct nodeDangerous *next;

};



struct nodeSecuritycameras {

  int value;
  struct nodeSecuritycameras *next;

};


void insertSecurityCameras(struct nodeSecuritycameras **head, int value) {


  struct nodeSecuritycameras *newNode = (struct nodeSecuritycameras*) malloc (sizeof(struct nodeSecuritycameras));

  newNode->value = value;
  newNode->next = NULL;


  if (*head == NULL)
  {
    *head = newNode;
    return;
  }

  struct nodeSecuritycameras *temp = *head;

  while (temp->next != NULL) {

    if (temp->value == value) {

      return;

    }

    temp = temp->next;
  }

  if (temp->value != value) {
    temp->next = newNode;
  }

}


void insertDangerous(struct nodeDangerous **head, int value) {


  struct nodeDangerous *newNode = (struct nodeDangerous*) malloc (sizeof(struct nodeDangerous));

  newNode->value = value;
  newNode->next = NULL;


  if (*head == NULL)
  {
    *head = newNode;
    return;
  }

  struct nodeDangerous *temp = *head;

  while (temp->next != NULL) {

    if (temp->value == value) {

      return;

    }

    temp = temp->next;
  }

  if (temp->value != value) {
    temp->next = newNode;
  }

}





void insertSame_table(struct node *head, int r1, int r2, int n, int matrixGroup[n][n]) {


  struct node *temp = (struct node*) malloc (sizeof(struct node));

  temp->data1 = r1;
  temp->data2 = r2;
  temp->next = NULL;


  struct node *ptr;
  ptr = head;


  while (ptr->next != NULL) {

    if ( (ptr->data1 == r1 && ptr->data2 == r2 ) || (ptr->data1 == r2 && ptr->data2 == r1 ) ) {

      return;

    }


    ptr = ptr->next;

  }

  // Cerca una riga contenente uno dei due numeri
  int found = 0;

  int index = -1;

  for (int i = 0; i < n && !found; i++) {

    for (int j = 0; j < n; j++) {

      if (matrixGroup[i][j] == r1 || matrixGroup[i][j] == r2) {

        found = 1;

        index = i;

        break;

      }

    }

  }


  // Se nessuno dei due numeri è stato trovato, cerca una riga vuota
  if (index == -1) {

    int break1 = 0;

    for (int i = 0; i < n && !break1; i++) {

      if (matrixGroup[i][0] == 0) {

        matrixGroup[i][0] = r1;

        matrixGroup[i][1] = r2;

        break1 = 1;

      }

    }

    // Altrimenti, controlla la riga in cui è stato trovato uno dei numeri
  } else {



    for (int x = 0; x < n; x++) {

      for (int y = 0; y < n; y++) {

        if (x != index && (matrixGroup[x][y] == r1 || matrixGroup[x][y] == r2)  ) {

          return;

        }



      }


    }


    int count = 0;

    for (int j = 0; j < n; j++) {

      if (matrixGroup[index][j] != r1 && matrixGroup[index][j] != r2 && matrixGroup[index][j] > 0) {

        count++;

      }


    }

    if (count + 2 > 4 ) {

      return;

    }



    int foundr1 = 0;

    int foundr2 = 0;

    for (int j = 0; j < n; j++) {

      if (matrixGroup[index][j] == r1) {

        foundr1 = 1;
      }


      if (matrixGroup[index][j] == r2) {

        foundr2 = 1;
      }


    }

    if (foundr1 && foundr2) {

      return;

    }




    if (!foundr1 && foundr2) {

      int breaks = 0;

      for (int j = 0; j < n && !breaks; j++) {

        if (matrixGroup[index][j] == 0) {

          matrixGroup[index][j] = r1;

          breaks = 1;

        }

      }


    } else if (foundr1 && !foundr2) {

      int breaks = 0;

      for (int j = 0; j < n && !breaks; j++) {

        if (matrixGroup[index][j] == 0) {

          matrixGroup[index][j] = r2;

          breaks = 1;

        }

      }

    }

  }


  if ( !(ptr->data1 == r1 && ptr->data2 == r2 ) && !(ptr->data1 == r2 && ptr->data2 == r1 ) ) {


    ptr->next = temp;

  }

//DEBUG

  for (int i = 0; i < n; i++) {

    for (int j = 0; j < n; j++) {

      printf("%d  ", matrixGroup[i][j]);

    }

    printf("\n");

  }

  printf("%d,%d \n", r1, r2);

  printf("%d,%d \n", ptr->next->data1, ptr->next->data2);

  printf("--------------------------\n" );

}


void insertHate(struct node *head1, struct node **head2  , int r1, int r2) {



  struct node *ptr;
  ptr = head1;


  while (ptr->next != NULL) {

    if ( (ptr->data1 == r1 && ptr->data2 == r2 ) || (ptr->data1 == r2 && ptr->data2 == r1 ) ) {

      return;

    }


    ptr = ptr->next;

  }


  struct node *newNode = (struct node*) malloc (sizeof(struct node));

  newNode->data1 = r1;
  newNode->data2 = r2;
  newNode->next = NULL;


  if (*head2 == NULL)
  {
    *head2 = newNode;
    return;
  }

  struct node *temp = *head2;

  while (temp->next != NULL) {

    if ( (ptr->data1 == r1 && ptr->data2 == r2 ) || (ptr->data1 == r2 && ptr->data2 == r1 ) ) {

      return;

    }


    temp = temp->next;
  }

  if ( !(ptr->data1 == r1 && ptr->data2 == r2 ) && !(ptr->data1 == r2 && ptr->data2 == r1 ) ) {


    temp->next = newNode;

  }

}




void printSame_table(struct node *head, FILE *fPtr) {

  struct node *ptr;

  ptr = head;

  while (ptr != NULL) {

    fprintf(fPtr, "same_table(%d,%d).\n", ptr->data1, ptr->data2);

    ptr = ptr->next;

  }


}


void printSame_tableMNZ(struct node *head, FILE *fPtr, int n) {

  struct node *ptr;

  ptr = head;

  int matrix[n][n];

  for (int i = 0; i < n; i++) {

    for (int j = 0; j < n; j++) {

      matrix[i][j] = 0;

    }


  }

  fprintf(fPtr, "array[1..n,1..n] of 0..1 : same_table =  ");

  while (ptr != NULL) {


    matrix[ptr->data1 - 1][ptr->data2 - 1] = 1;

    ptr = ptr->next;

  }

  fprintf(fPtr, "[");

  for (int i = 0; i < n; i++) {

    fprintf(fPtr, "| ");


    for (int j = 0; j < n; j++) {

      if (j == n - 1) {

        fprintf(fPtr, "%d\n", matrix[i][j] );


      } else {

        fprintf(fPtr, "%d, ", matrix[i][j] );

      }

    }


  }

  fprintf(fPtr, "|];\n");


}


void printHate(struct node *head, FILE *fPtr) {

  struct node *ptr;

  ptr = head;

  while (ptr != NULL) {

    fprintf(fPtr, "hate(%d,%d).\n", ptr->data1, ptr->data2);

    ptr = ptr->next;

  }


}



void printHateMNZ(struct node *head, FILE *fPtr, int n) {

  struct node *ptr;

  ptr = head;

  int matrix[n][n];

  for (int i = 0; i < n; i++) {

    for (int j = 0; j < n; j++) {

      matrix[i][j] = 0;

    }


  }

  fprintf(fPtr, "array[1..n,1..n] of 0..1 : hate =  ");

  while (ptr != NULL) {


    matrix[ptr->data1 - 1][ptr->data2 - 1] = 1;
    ptr = ptr->next;

  }

  fprintf(fPtr, "[");

  for (int i = 0; i < n; i++) {

    fprintf(fPtr, "| ");


    for (int j = 0; j < n; j++) {

      if (j == n - 1) {

        fprintf(fPtr, "%d\n", matrix[i][j] );


      } else {

        fprintf(fPtr, "%d, ", matrix[i][j] );

      }

    }


  }

  fprintf(fPtr, "|];\n");


}





void printDangerous(struct nodeDangerous *head, FILE *fPtr) {


  struct nodeDangerous *ptr;

  ptr = head;

  while (ptr != NULL) {

    fprintf(fPtr, "dangerous(%d).\n", ptr->value);

    ptr = ptr->next;

  }


}


void printDangerousMNZ(struct nodeDangerous *head, FILE *fPtr, int n) {

  struct nodeDangerous *ptr;

  ptr = head;

  int vector[n];

  for (int i = 0; i < n; i++) {

    vector[i] = 0;

  }

  fprintf(fPtr, "array[1..n] of 0..1 : dangerous = [ " );

  while (ptr != NULL) {


    vector[ptr->value - 1] = 1;

    ptr = ptr->next;

  }


  for (int i = 0; i < n; i++) {

    fprintf(fPtr, "%d, ", vector[i]);

  }




  fprintf(fPtr, "];\n");


}






void printSecurityCameras(struct nodeSecuritycameras *head, FILE *fPtr) {


  struct nodeSecuritycameras *ptr;

  ptr = head;

  while (ptr != NULL) {

    fprintf(fPtr, "security_cameras(%d).\n", ptr->value);


    ptr = ptr->next;

  }


}



void printSecurityCamerasMNZ(struct nodeSecuritycameras *head, FILE *fPtr, int k) {

  struct nodeSecuritycameras *ptr;

  ptr = head;

  int vector[k];

  for (int i = 0; i < k; i++) {

    vector[i] = 0;

  }

  fprintf(fPtr, "array[1..k] of 0..1 : security_cameras = [ " );

  while (ptr != NULL) {

    vector[ptr->value - 1] = 1;

    ptr = ptr->next;

  }


  for (int i = 0; i < k; i++) {

    fprintf(fPtr, "%d, ", vector[i]);

  }




  fprintf(fPtr, "];\n");


}





char* concat(const char *s1, const char *s2)
{
  char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
  // in real code you would check for errors in malloc here
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}


void generateInput(int n, int k, int N , char *name) {

  struct node *head = (struct node*) malloc (sizeof(struct node));

  int matrixGroup [n][n];

  for (int i = 0; i < n; i++) {

    for (int j = 0; j < n; j++) {

      matrixGroup[i][j] = 0;

    }


  }



  srand ( time(NULL) );

  int r1 = rand() % n + 1;

  int r2 = rand() % n + 1;

  if (r1 != r2) {

    head->data1 = r1;
    head->data2 = r2;
    head->next = NULL;

    matrixGroup[0][0] = r1;

    matrixGroup[0][1] = r2;

  }


  for (int i = 1; i <= N / 2 ; i++) {


    int r11 = rand() % n + 1;

    int r12 = rand() % n + 1;


    if (r11 != r12) {
      insertSame_table(head, r11, r12, n, matrixGroup);
    }

  }


  struct node *headBis = NULL;

  for (int i = 1; i <= N / 3; i++) {


    int r21 = rand() % n + 1;

    int r22 = rand() % n + 1;

    if (r21 != r22) {
      insertHate(head, &headBis, r21, r22);
    }


  }


  struct nodeDangerous *headBisBis = NULL;


  for (int i = 1; i <= N / 3; i++) {


    int r3 = rand() % n + 1;


    insertDangerous(&headBisBis, r3);



  }


  struct nodeSecuritycameras *headBisBisBis = NULL;

  for (int i = 1; i <= k / 2; i++) {


    int rbis = rand() % k + 1;


    insertSecurityCameras(&headBisBisBis, rbis);



  }

  FILE *fPtr;

  char *s = concat("ASP", name);

  fPtr = fopen(s, "w");

  /* fopen() return NULL if last operation was unsuccessful */
  if (fPtr == NULL)
  {
    /* File not created hence exit */
    printf("Unable to create file.\n");
    exit(EXIT_FAILURE);
  }

  fprintf(fPtr, "room(1..%d).\n", k);
  fprintf(fPtr, "table(1..%d).\n", 4 * k);
  fprintf(fPtr, "person(1..%d).\n", n);
  printSame_table(head, fPtr);
  printHate(headBis, fPtr);
  printDangerous(headBisBis, fPtr);
  printSecurityCameras(headBisBisBis, fPtr);

  fclose(fPtr);


  FILE *fPtrBis;


  char *s1 = concat("MZN", name);

  fPtrBis = fopen(s1, "w");

  /* fopen() return NULL if last operation was unsuccessful */
  if (fPtrBis == NULL)
  {
    /* File not created hence exit */
    printf("Unable to create file.\n");
    exit(EXIT_FAILURE);
  }


  fprintf(fPtrBis, "int : k = %d;\n", k);
  fprintf(fPtrBis, "int : t = %d;\n", 4 * k);
  fprintf(fPtrBis, "int : n = %d;\n", n);
  fprintf(fPtrBis, "\n");
  printSame_tableMNZ(head, fPtrBis, n);
  fprintf(fPtrBis, "\n");
  printHateMNZ(headBis, fPtrBis, n);
  fprintf(fPtrBis, "\n");
  printDangerousMNZ(headBisBis, fPtrBis, n);
  fprintf(fPtrBis, "\n");
  printSecurityCamerasMNZ(headBisBisBis, fPtrBis, k);

  fclose(fPtrBis);


}



int main() {


//  int c = 1;
//
//  char *str = "instance";
//
//  char *str1 = ".txt";
//
//  size_t len = strlen(str);
//
//  for (int n = 10; n <= 20; n = n + 2) {
//
//    char c1 = c + '0';
//
//    /* one for extra char, one for trailing zero */
//    char *str2 = (char *) malloc(sizeof(char) * (len + 1 + 1) );
//
//    strcpy(str2, str);
//    str2[len] = c1;
//    str2[len + 1] = '\0';
//
//    char *s = concat(str2, str1);
//
//    //generateInput(n, 4, 5, s);
//
//    free(s);
//
//    free(str2);
//
//    c++;
//
//  }


  generateInput(10, 4, 5  , "instance1.txt");
  generateInput(12, 4, 5  , "instance2.txt");
  generateInput(14, 4, 5  , "instance3.txt");
  generateInput(16, 4, 5 , "instance4.txt");
  generateInput(18, 4, 5 , "instance5.txt");
  generateInput(20, 4, 5 , "instance6.txt");
  //generateInput(25, 4, 5  , "instance7.txt");
  //generateInput(30, 4, 5  , "instance8.txt");
  //generateInput(20, 4, 10  , "instance9.txt");
  //generateInput(25, 4, 10 , "instance10.txt");
  //generateInput(30, 4, 10 , "instance11.txt");
  //generateInput(25, 4, 25 , "instance12.txt");
  //generateInput(28, 4, 25 , "instance13.txt");
  //generateInput(30, 4, 25 , "instance14.txt");
  //generateInput(35, 4, 10 , "instance15.txt");
  //generateInput(35, 4, 25 , "instance16.txt");
  //generateInput(35, 8, 25 , "instance17.txt");
  //generateInput(35, 12, 25 , "instance18.txt");
  //generateInput(33, 8, 25 , "instance19.txt");
  //generateInput(33, 8, 30 , "instance20.txt");
  //generateInput(50, 20, 25 , "instance21.txt");
  //generateInput(50, 40, 25 , "instance22.txt");
  //generateInput(35, 12, 10 , "instance23.txt");
  //generateInput(35, 20, 25 , "instance24.txt");


}

