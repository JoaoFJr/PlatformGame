#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "gamelib/camera.h"
#include "gamelib/screen.h"

#include <allegro5/allegro.h>
#include <allegro5/timer.h>
#include <vector>

enum Keys {KEY_W , KEY_S , KEY_A , KEY_D , KEY_SPACE , KEY_E ,
          KEY_UP , KEY_DOWN , KEY_LEFT , KEY_RIGHT , KEY_ENTER , KEY_BACKSPACE , DOG_DIG};


class GameApp
{
public:

    static const int FPS = 60;
    static const int kNumberOfKeys = 13;
    static const int kBGBlockSize = 32;

    enum GameScreen {MENU , LEVEL1};

    GameApp(int d_width , int d_height);
    ~GameApp();
    void exec();
    ALLEGRO_DISPLAY * getMainDisplay();



private:
    void gameLoop(ALLEGRO_EVENT &ev);
    void createScreens();
    void populateScreenVector();
    void releaseScreens();
    void populateScreen(int scr_id);

    ALLEGRO_EVENT_QUEUE *event_queue_;
    ALLEGRO_DISPLAY *main_display_;
    ALLEGRO_TIMER *fps_timer_;

//    InputHandler *input_handler_;
//    ScreenManager *screen_manager_;


    Camera cam;
    std::vector<Screen> screens_;
    std::vector<bool> keys_;
    bool done_ , update_screen_;
    int display_width_ , display_height_ , current_screen_;

};

#endif // GAMEAPP_H
