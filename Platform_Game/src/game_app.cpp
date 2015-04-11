#include "game_app.h"
#include "gamelib/game_object.h"
#include "gamelib/mappy_A5.h"


#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <QResource>
#include <QDir>
#include <QDebug>
#include <QTextStream>


#include <iostream>

GameApp::GameApp(int d_width , int d_height):
    done_(false),
    display_width_(d_width),
    display_height_(d_height),
    event_queue_(NULL),
    main_display_(NULL),
    fps_timer_(NULL)
{
    update_screen_ = false;
    main_display_ = al_create_display(display_width_ , display_height_);
    fps_timer_ = al_create_timer(1.0 / FPS);

    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();


    event_queue_ = al_create_event_queue();
    al_register_event_source(event_queue_ , al_get_display_event_source(main_display_));
    al_register_event_source(event_queue_ , al_get_timer_event_source(fps_timer_));
    al_register_event_source(event_queue_ , al_get_keyboard_event_source());

    al_start_timer(fps_timer_);
    createScreens();
    populateScreenVector();
    int i = 0;
    while(i<kNumberOfKeys)
    {
        keys_.push_back(false);
        i++;
    }
}

GameApp::~GameApp()
{

    al_destroy_display(main_display_);
    al_destroy_event_queue(event_queue_);
    al_destroy_timer(fps_timer_);
    screens_.clear();
}

ALLEGRO_DISPLAY * GameApp::getMainDisplay(){
    return main_display_;
}


// Game Loop
void GameApp::gameLoop(ALLEGRO_EVENT &ev)
{
    al_wait_for_event(event_queue_ , &ev);
    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        done_ = true;
    }
    if(ev.type == ALLEGRO_EVENT_TIMER)
    {
        update_screen_ = true;
    }
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_W:
            keys_[KEY_W] = true;
            break;
        case ALLEGRO_KEY_A:
            keys_[KEY_A] = true;
            break;
        case ALLEGRO_KEY_S:
            keys_[KEY_S] = true;
            break;
        case ALLEGRO_KEY_D:
            keys_[KEY_D] = true;
            break;
        case ALLEGRO_KEY_UP:
            keys_[KEY_UP] = true;
            break;
        case ALLEGRO_KEY_LEFT:
            keys_[KEY_LEFT] = true;
            break;
        case ALLEGRO_KEY_DOWN:
            keys_[KEY_DOWN] = true;
            break;
        case ALLEGRO_KEY_RIGHT:
            keys_[KEY_RIGHT] = true;
            break;
        default:
            break;
        }
        screens_[current_screen_].keyInput(keys_);
    }
    if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_W:
            keys_[KEY_W] = false;
            break;
        case ALLEGRO_KEY_A:
            keys_[KEY_A] = false;
            break;
        case ALLEGRO_KEY_S:
            keys_[KEY_S] = false;
            break;
        case ALLEGRO_KEY_D:
            keys_[KEY_D] = false;
            break;
        case ALLEGRO_KEY_UP:
            keys_[KEY_UP] = false;
            break;
        case ALLEGRO_KEY_LEFT:
            keys_[KEY_LEFT] = false;
            break;
        case ALLEGRO_KEY_DOWN:
            keys_[KEY_DOWN] = false;
            break;
        case ALLEGRO_KEY_RIGHT:
            keys_[KEY_RIGHT] = false;
            break;
        default:
            break;
        }
        screens_[current_screen_].keyInput(keys_);
    }

    if(al_event_queue_is_empty(event_queue_) && update_screen_)
    {
        update_screen_ = false;
        //updateGameObjects();
        //updateGameCamera();
        //drawGameObjects();
        screens_[current_screen_].update();
        screens_[current_screen_].draw();
        al_flip_display();
        al_clear_to_color(al_map_rgb(0 , 0 , 0));

    }
}


// Create the game screens and add to the screens vector
void GameApp::createScreens()
{
    Screen sc_menu = Screen("Menu");
    Screen sc_level_1 = Screen("Level 1" , "Level1.FMP");
    screens_.push_back(sc_menu);
    screens_.push_back(sc_level_1);
    current_screen_ = sc_level_1.getId();
}

// Create and populate every screen of the game.
void GameApp::populateScreenVector()
{
    int screen_id = 0;
    std::vector<Screen>::iterator it = screens_.begin();
    for(; it != screens_.end() ; ++it)
    {
        screen_id = (static_cast<Screen>(*it)).getId();
        populateScreen(screen_id);
    }

}

void GameApp::populateScreen(int scr_id)
{

    switch(scr_id)
    {
    case MENU:
        break;
    case LEVEL1:
        GameObject *hunter = new GameObject(new Sprite(2 , 2 , 60 , 80 , al_load_bitmap("./resources/images/HUNTER_F_.png")));
        screens_[scr_id].addObject(hunter);
        hunter->addSprite(new Sprite(2 , 2 , 60 , 80 , al_load_bitmap("./resources/images/HUNTER_B_.png")));
        hunter->addSprite(new Sprite(2 , 2 , 60 , 80 , al_load_bitmap("./resources/images/HUNTER_L_.png")));
        hunter->addSprite(new Sprite(2 , 2 , 60 , 80 , al_load_bitmap("./resources/images/HUNTER_R_.png")));
        hunter->setPosition(display_width_/2 , display_height_/2);
        hunter->setAlive(true);
        hunter->setDefaultVelX(0.7);
        hunter->setDefaultVelY(0.7);
        hunter->getSprite(0)->frame_delay_ = 8;
        hunter->getSprite(1)->frame_delay_ = 8;
        hunter->getSprite(2)->frame_delay_ = 8;
        hunter->getSprite(3)->frame_delay_ = 8;

        GameObject *dog = new GameObject(new Sprite(2 , 2 , 60 , 80 , al_load_bitmap("./resources/images/DOG_F_.png")));

        screens_[scr_id].addObject(dog);

        dog->addSprite(new Sprite(1 , 1 , 60 , 80 , al_load_bitmap("./resources/images/DOG_B.png")));
        dog->addSprite(new Sprite(1 , 1 , 60 , 80 , al_load_bitmap("./resources/images/DOG_L.png")));
        dog->addSprite(new Sprite(1 , 1 , 60 , 80 , al_load_bitmap("./resources/images/DOG_R.png")));
        dog->setPosition(display_width_/2 , display_height_/2);
        dog->setAlive(true);
        dog->setDefaultVelX(1.2);
        dog->setDefaultVelY(1.2);
        dog->getSprite(0)->frame_delay_ = 8;
        dog->getSprite(1)->frame_delay_ = 8;
        dog->getSprite(2)->frame_delay_ = 8;
        dog->getSprite(3)->frame_delay_ = 8;
        break;
    }
}

void GameApp::releaseScreens()
{
    screens_.clear();
}


// Game execution loop
void GameApp::exec()
{
    ALLEGRO_EVENT ev;
    while(!done_)
    {
        gameLoop(ev);
    }
    al_flush_event_queue(event_queue_);
}
