#include <stdio.h>
#include <ctype.h>

int main(void){
    char t[2];
    char s[] = {'a', 'b'};

    t[0] = s[0];

    t[0] = toupper(t[0]);

    printf("%c\n", t[0]);
    printf("%c\n", s[0]);
}
