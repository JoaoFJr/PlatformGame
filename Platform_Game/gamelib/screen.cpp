#include "gamelib/screen.h"
#include "gamelib/mappy_A5.h"

#include <iostream>
#include <QDebug>


Screen::Screen(std::string name)
{
    this->name_ = name;
    this->id_ = screen_counter;
    screen_counter++;
    game_state_ = RUN;
    has_map_ = false;
}

Screen::Screen(std::string name ,  char *map_file_dir)
{
    this->name_ = name;
    this->id_ = screen_counter;
    screen_counter++;
    game_state_ = RUN;
    has_map_ = false;
    changeMap(map_file_dir);
}

Screen::~Screen()
{
    std::vector<GameObject*>::iterator it = objects_.begin();
    for(; it != objects_.end() ; ++it)
    {
        delete (*it);
        std::cout << "deleted object from Screen" << std::endl;
    }
    objects_.clear();
    MapFreeMem();

}

int Screen::getId(){
    return id_;
}

std::string Screen::getName(){
    return name_;
}

void Screen::draw()
{
    if(has_map_)
    {
   //     MapDrawBG(0 , 0 , 0 , 0 , 1024 , 640);
    }
    for(int i=0 ; i < objects_.size() ; i++)
    {
        //std::cout << "Draw screen size: " << objects_.size() << std::endl;
        objects_[i]->draw();
        //std::cout << "Desenhou " << std::endl;
    }
}

void Screen::update()
{
    std::vector<GameObject*>::iterator it = objects_.begin();
    for(; it != objects_.end() ; ++it)
    {
        (*it)->update(this->keyInput(););
    }
}

int Screen::getObjectsCount()
{
    return objects_.size();
}

GameObject * Screen::getObject(int id)
{
    for(int i = 0 ; i < objects_.size() ; i++)
    {
        if(objects_[i]->getId() == id)
            return objects_[i];
    }
    return NULL;
}

void Screen::addObject(GameObject *obj)
{
    objects_.push_back(obj);
}

void Screen::keyInput(std::vector<bool> keys)
{
    std::vector<GameObject*>::iterator it = objects_.begin();
    switch (game_state_) {

    case RUN:
        for(; it != objects_.end() ; ++it)
        {
            (*it)->inputResponse(&keys);
        }
        break;
    case PAUSED:
        break;
    case DEAD:
        break;
    default:
        break;
    }
}

void Screen::keyResponse(int obj_id, std::vector<bool> keys)
{

}

//void Screen::changeMap(char *map_file_dir)
//{
//    MapFreeMem();
//    has_map_ = false;
//    if(MapLoad(map_file_dir, 1)){
//        qDebug() << "Error loading map file" ;
//    }
//    else{
//        has_map_ = true;
//    }
//}

