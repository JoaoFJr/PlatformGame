#ifndef SCREEN_H
#define SCREEN_H

#include "game_object.h"

#include <string>
#include <vector>



static int screen_counter = 0;
class Screen
{
public:
    enum GameState{RUN , PAUSED , DEAD};

    Screen(std::string name_);
    Screen(std::string name_ , char* map_file_dir);
    ~Screen();
    int getId();
    std::string getName();
    void update();
    void addObject(GameObject *obj);
    GameObject * getObject(int id);
    int getObjectsCount();
    void draw();
    void keyInput(std::vector<bool> keys);
    bool hasMap();
    void changeMap(char* map_file_dir);

private:

    int id_;
    bool has_map_;
    std::string name_;
    std::vector<GameObject*> objects_;
    GameState game_state_;
    void keyResponse(int obj_id , std::vector<bool> &keys);



};

#endif // SCREEN_H
