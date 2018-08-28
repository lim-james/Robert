#include "KeyHelpers.h"

bool g_abKeyPressed[K_COUNT];

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_W] = isKeyPressed(0x57);
	g_abKeyPressed[K_A] = isKeyPressed(0x41);
	g_abKeyPressed[K_S] = isKeyPressed(0x53);
	g_abKeyPressed[K_D] = isKeyPressed(0x44);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_TAB] = isKeyPressed(VK_TAB);
	g_abKeyPressed[K_BACKSLASH] = isKeyPressed(VK_OEM_5);
	g_abKeyPressed[K_LSHIFT] = isKeyPressed(VK_LSHIFT);
	g_abKeyPressed[K_RSHIFT] = isKeyPressed(VK_RSHIFT);
}