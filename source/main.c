// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

// Main program entrypoint
int main(int argc, char* argv[])
{
    // This example uses a text console, as a simple way to output text to the screen.
    // If you want to write a software-rendered graphics application,
    //   take a look at the graphics/simplegfx example, which uses the libnx Framebuffer API instead.
    // If on the other hand you want to write an OpenGL based application,
    //   take a look at the graphics/opengl set of examples, which uses EGL instead.
    consoleInit(NULL);

    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    PadState pad;
    padInitializeDefault(&pad);


    // Other initialization goes here. As a demonstration, we print hello world.

    bool stickState = false;

    // Main loop
    while (appletMainLoop())
    {
        // Scan the gamepad. This should be done once for each frame
        padUpdate(&pad);

        // padGetButtonsDown returns the set of buttons that have been
        // newly pressed in this frame compared to the previous one
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus){
            break;
        }


        if (kDown & HidNpadButton_StickR){
            stickState = !stickState;
        }

        if (stickState){
            printf("\e[1;1H\e[2J");
            printf("BeanNX Stick Checker -- By TransKat\n\n\nPress the right stick to alternate between sticks\n\n\n");
            printf("RIGHT: x: %d -- y: %d\r", pad.sticks[1].x, pad.sticks[1].y);
        } else {
            printf("\e[1;1H\e[2J");
            printf("BeanNX Stick Checker -- By TransKat\n\n\nPress the right stick to alternate between sticks\n\n\n");
            printf("LEFT: x: %d -- y: %d\r", pad.sticks[0].x, pad.sticks[0].y);
        }

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}
