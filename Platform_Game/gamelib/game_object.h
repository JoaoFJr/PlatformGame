#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sprite.h"
#include <vector>


static int object_counter_ = 0;

class GameObject
{
public:

    enum Collision {COLLIDABLE , NOT_COLLIDABLE};
    // enum HorizontalOrientation {LEFT , RIGHT};  // Not every object has it
    // enum SpriteAnim {ANIM_FRONT , ANIM_BACK , ANIM_LEFT , ANIM_RIGHT , ANIM_STAND}; // Not every object has it

    GameObject(Sprite *spr);
    GameObject();
    ~GameObject();

    void addSprite(Sprite *spr);

    float x_ , y_ , bound_x_ , bound_y_ , bound_y_offset_;
    float vel_x_ , vel_y_ , default_vel_x_ , default_vel_y_;
    bool alive_ , show_collision_bound_ , controlling_;
    std::vector<Sprite*> sprite_vector_;

    int getId();
    void setCurrentSprite(int cur_sprite);
    int getCurrentSprite();
    void setCollisionType(Collision col_type);
    Collision getCollisionType();
    void draw(void);
    void draw(float x_offset , float y_offset);
    void setPosition(float pos_x , float pos_y);
    void setVel(float vel_x , float vel_y);
    void setVelx(float vel_x_);
    void setVely(float vel_y_);
    float getVelx();
    float getVely();
    float getDefVelx();
    float getDefVely();
    void setDefaultVel(float dv_x , float dv_y);
    void setDefaultVelX(float dv_x);
    void setDefaultVelY(float dv_y);
    bool isAlive();
    void setAlive(bool is_alive);
    void setSprite(int index);
    void setBoundaries(float bound_x , float bound_y , float bound_y_off);
    Sprite * getSprite(int index);
    void update(void);

    virtual void inputResponse(std::vector<bool> *keys);


private:
    int id_ , current_sprite_;
    Collision collision_type_;
};

#endif // GAMEOBJECT_H
