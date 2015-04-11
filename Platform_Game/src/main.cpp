#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <QDir>

#include "game_app.h"
//TODO: Keyresponse on Screen.cpp
// Main application file

int main(int argc, char *argv[])
{

    // Init Allegro library
    if(!al_init()){
        al_show_native_message_box(NULL , NULL , NULL , "Could not initialize allegro library" , NULL , NULL);
    }

    // Create game application and set Display size
    GameApp game(1024,640);

//     Verify if display was created successfully
    if(game.getMainDisplay() == 0){
        al_show_native_message_box(NULL , NULL , NULL , "Could not initialize allegro library" , NULL , NULL);
    }
    // Execute Game application
    game.exec();
}
