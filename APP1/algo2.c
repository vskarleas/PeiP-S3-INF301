#include<stdio.h>

char* encode(char* str) {
   int j = 0;

   while (str[j] != '\0') {
      str[j] = str[j] - 30;  // Subtract 30 From Charcter
      j++;
   }
   return (str);
}

void main() {

   char *str;

   printf("\nEnter the String to be Encode : ");
   gets(str);

   str = encode(str);
   printf("\nEncoded String : %s", str);

   getch();
}