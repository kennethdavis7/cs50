#include <stdio.h>
#include <cs50.h>

void hashtag(int n){
    int j;
    for(j=1; j <= n; j++){
        printf("#");
    }
}

void space(int height, int i){
    int v;
    for(v=1; v<= height - i; v++){
        printf(" ");
    }
}

int main(void){
    while(1){
        int height = get_int("Height: ");
        int i;
        if(height >= 1 && height <= 8){
            for(i = 1; i <= height; i++){
                space(height, i);
                hashtag(i);
                printf("  ");
                hashtag(i);
                printf("\n");
            }
            break;
        }
    }
}
