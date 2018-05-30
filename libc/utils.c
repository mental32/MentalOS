#include <stdint.h>
#include <stddef.h>
#include <stdint.h>

#include "include/terminal.h"

char* reverse_string(char *str, size_t len) {
    register char *start = str;
    register char *end = str + len - 1;
    register char tmp;

    for (size_t i = 0; i < len / 2 + 1; i++) {
        tmp = *start;
        *start++ = *end;
        *end-- = tmp;
    }

    return str;
}

char* strconcat(char* a, char* b){
    int i=strlen(a), j=0;

    while(b[j]!='\0'){
        a[i]=b[j];
        j++;
        i++;
    }
    a[i]='\0';
    return a;
}

char* itoa(int num, char* str, int base){
    int i = 0;
    int isNegative = 0;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (!num){
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
    reverse_string(str, i);
 
    return str;
}
