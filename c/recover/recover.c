#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    BYTE buffer[512];

    int jpeg_count = 0;
    int current_jpeg = 0;

    char filename[8] = malloc(sizeof(char[8]));
    sprintf(filename, "%03i.jpg", current_jpeg);
    FILE *file_jpeg = fopen(filename, "w");

    while(fread(buffer, sizeof(BYTE), 512, card) == 512){
        if(buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && ((buffer[3] & 0xF0) == 0xE0)){
            if(jpeg_count == 0){
                fwrite(buffer, sizeof(BYTE), 512, file_jpeg);
            }else{
                fclose(file_jpeg);
                sprintf(filename, "%03i.jpg", ++current_jpeg);
                file_jpeg = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, file_jpeg);
            }
            jpeg_count++;
        }else{
            if(jpeg_count != 0){
                fwrite(buffer, sizeof(BYTE), 512, file_jpeg);
            }
        }
    }

    fclose(file_jpeg);
    fclose(card);

    return 0;
}
