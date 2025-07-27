#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *filename;
    filename = malloc(8 * sizeof(char));
    uint8_t buffer[512];
    if (argc != 2)
    {
        printf("./recover filename\n");
        return 1;
    }
    char *memory_file = argv[1];

    FILE *file = fopen(memory_file, "r");
    if (file == NULL)
    {
        printf("cannot open file\n");
        return 1;
    }

    FILE *recover_images = NULL;
    int count = 0;
    int value;
    while ((value = fread(buffer, 1, 512, file)) > 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // start of the new jpeg file
            if (recover_images != NULL)
            {
                fclose(recover_images);
            }

            sprintf(filename, "%03i.jpg", count++);
            recover_images = fopen(filename, "w");
        }
        
        if (recover_images != NULL)
        {
            fwrite(buffer, 1, 512, recover_images);
        }
    }
    fclose(recover_images);
    fclose(file);
    free(filename);
}
