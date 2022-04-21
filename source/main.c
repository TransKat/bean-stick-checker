// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

// Main program entrypoint
int main(int argc, char* argv[])
{

    consoleInit(NULL);

    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    PadState pad;
    padInitializeDefault(&pad);


    // Other initialization goes here. As a demonstration, we print hello world.

    // Main loop
    while (appletMainLoop())
    {
        // Scan the gamepad. This should be done once for each frame
        padUpdate(&pad);

        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus){
            break;
        }

        // padGetButtonsDown returns the set of buttons that have been
        // newly pressed in this frame compared to the previous one
        //u64 kDown = padGetButtonsDown(&pad);

        printf("\e[1;1H\e[2J");
        printf("BeanNX Stick Checker -- By TransKat\n\n\nhttps://github.com/TransKat/bean-stick-checker\n\n\nThis is Free Software licenced under the GNU GPLv3.\n\n\n");
        printf("RIGHT: x: %d -- y: %d\r", pad.sticks[1].x, pad.sticks[1].y);
        printf("\nLEFT: x: %d -- y: %d\r", pad.sticks[0].x, pad.sticks[0].y);

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}
