#include <conio.h>

char* screen = (char*)(1024);
unsigned char* color = (unsigned char*)(55296);

char* joystick = (char*)(56321);

#define block_char 224
#define empty_char 96
#define place_color 2
#define sand_color 7

int main() {
    int pixels[1000];
    int currentIndex = 0;
    short i;
    short index;
    unsigned short placement_index;
    unsigned short delay;
    *((unsigned char*)53281) = 0;
    clrscr();
    delay = 0;
    placement_index = 0;
    screen[placement_index] = block_char;
    color[placement_index] = place_color;
    for (;;) {
        screen[placement_index] = block_char;
        color[placement_index] = 2;
        if ((*joystick & 0x01) == 0 && placement_index >= 40) {
            screen[placement_index] = empty_char;
            color[placement_index] = 0;
            placement_index -= 40;
            screen[placement_index] = block_char;
            color[placement_index] = place_color;
        }
        if ((*joystick & 0x02) == 0 && placement_index <= 959) {
            screen[placement_index] = empty_char;
            color[placement_index] = 0;
            placement_index += 40;
            screen[placement_index] = block_char;
            color[placement_index] = place_color;
        }
        if ((*joystick & 0x04) == 0 && placement_index % 40 != 0) {
            screen[placement_index] = empty_char;
            color[placement_index] = 0;
            placement_index -= 1;
            screen[placement_index] = block_char;
            color[placement_index] = place_color;
        }
        if ((*joystick & 0x08) == 0 && placement_index % 40 != 39) {
            screen[placement_index] = empty_char;
            color[placement_index] = 0;
            placement_index += 1;
            screen[placement_index] = block_char;
            color[placement_index] = place_color;
        }
        if ((*joystick & 0x10) == 0) {
            screen[placement_index] = block_char;
            color[placement_index] = sand_color;
            pixels[currentIndex] = placement_index;
            currentIndex += 1;
        }

        for (index = currentIndex - 1; index >= 0; index--) {
            i = pixels[index];
            if ((color[i] & 0x0F) == sand_color && screen[i] == block_char) {
                short stopped = 1;
                if (screen[i + 40] != block_char && i + 40 <= 1000) {
                    screen[i + 40] = block_char;
                    color[i + 40] = sand_color;
                    screen[i] = empty_char;
                    color[i] = 0;
                    pixels[index] = i + 40;
                    stopped = 0;
                } else if (screen[i + 39] != block_char && i + 39 <= 1000) {
                    screen[i + 39] = block_char;
                    color[i + 39] = sand_color;
                    screen[i] = empty_char;
                    color[i] = 0;
                    pixels[index] = i + 39;
                    stopped = 0;
                } else if (screen[i + 41] != block_char && i + 41 <= 1000) {
                    screen[i + 41] = block_char;
                    color[i + 41] = sand_color;
                    screen[i] = empty_char;
                    color[i] = 0;
                    pixels[index] = i + 41;
                    stopped = 0;
                }
                if (stopped) {
                    pixels[index] = pixels[currentIndex - 1];
                    currentIndex = currentIndex - 1;
                }
            }
        }
    }

    return 0;
}
