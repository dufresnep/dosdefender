#include <allegro.h>
#include <stdio.h> // Include stdio.h for printf

int main() {
    printf("Starting test.exe\n");
    allegro_init();
    printf("allegro_init() successful\n");
    
    set_color_depth(8);
    printf("set_color_depth(8) successful\n");

    int ret = set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0);
    printf("set_gfx_mode() returned: %d\n", ret);
    if (ret != 0) {
        printf("Error setting graphics mode: %s\n", allegro_error);
        allegro_exit();
        return 1; // Exit with an error code
    }
    printf("set_gfx_mode() successful\n");
    
    clear_to_color(screen, makecol(255, 0, 0)); // Red screen
    printf("clear_to_color() successful\n");
    
    readkey(); // Wait for a key press
    printf("readkey() successful\n");
    
    allegro_exit();
    printf("allegro_exit() successful\n");
    printf("Exiting test.exe\n");
    return 0;
}
END_OF_MAIN()
