#include "game_object.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <qdebug.h>
#include <iostream>

GameObject::GameObject(Sprite *spr)
{
    id_ = object_counter_;
    object_counter_++;
    x_ = 0;
    y_ = 0;
    vel_x_ = 0;
    vel_y_ = 0;
    default_vel_x_ = 0;
    default_vel_y_ = 0;
    bound_y_offset_ = 0;
    bound_x_ = spr->frame_width_/2;
    bound_y_ = spr->frame_height_/2;
    alive_ = false;
    current_sprite_ = 0;
    show_collision_bound_ = false;
    collision_type_ = COLLIDABLE;
    controlling_ = false;
    sprite_vector_.push_back(spr);

}

GameObject::GameObject()
{
    id_ = object_counter_;
    object_counter_++;
    x_ = 0;
    y_ = 0;
    vel_x_ = 0;
    vel_y_ = 0;
    default_vel_x_ = 0;
    default_vel_y_ = 0;
    bound_y_offset_ = 0;
    bound_x_ = 0;
    bound_y_ = 0;
    alive_ = false;
    current_sprite_ = 0;
    show_collision_bound_ = false;
    collision_type_ = COLLIDABLE;
    controlling_ = false;
}

GameObject::~GameObject()
{
    sprite_vector_.clear();
}

// Add Sprite to the object
void GameObject::addSprite(Sprite *spr){
    sprite_vector_.push_back(spr);
}

// Return the object id
int GameObject::getId()
{
    return id_;
}

void GameObject::setCurrentSprite(int cur_sprite)
{
    if(cur_sprite < sprite_vector_.size())
    {
        current_sprite_ = cur_sprite;
    }
}

// Draw object
void GameObject::draw(void)
{

    if(alive_)
    {
        ALLEGRO_BITMAP *current_frame;
        Sprite *spr = sprite_vector_[current_sprite_];
        if(spr != NULL)
        {
            int fx = (spr->cur_frame_ % spr->num_colums_) * spr->frame_width_;
            int fy = (spr->cur_frame_ / spr->num_colums_) * spr->frame_height_;

            if(vel_x_==0 && vel_y_ == 0)
            {
                fx = 0;
                fy = 0;
            }

            int flip  =  0;
            if(spr->invert_horizontal_)
            {
                flip |= ALLEGRO_FLIP_HORIZONTAL;
            }
            if(spr->invert_vertical_)
            {
                flip |= ALLEGRO_FLIP_VERTICAL;
            }
            current_frame = al_create_sub_bitmap(spr->image_ , fx , fy , 60 , 80);
            if(show_collision_bound_)
            {
                al_draw_filled_rectangle(x_ - bound_x_ , y_ - bound_y_ , x_ + bound_x_ , y_ + bound_y_ , al_map_rgba_f(0.5f , 0.1f , 0.5f , 0.2f));
            }

            al_draw_scaled_bitmap(current_frame , 0 , 0 , spr->frame_width_ , spr->frame_height_ ,
                                  x_ - (spr->frame_width_/2)*spr->hor_scale_ , y_ - (spr->frame_height_/2)*spr->ver_scale_ ,
                                  spr->frame_width_ * spr->hor_scale_ , spr->frame_height_ * spr->ver_scale_ , flip);
        }
    }
}

void GameObject::setCollisionType(Collision col_type)
{
    collision_type_ = col_type;
}

GameObject::Collision GameObject::getCollisionType()
{
    return collision_type_;
}

// Draw object with offset
void GameObject::draw(float x_offset , float y_offset)
{
    if(alive_)
    {
        ALLEGRO_BITMAP *current_frame;
        Sprite *spr = sprite_vector_[current_sprite_];

        int fx = (spr->cur_frame_ % spr->num_colums_) * spr->frame_width_;
        int fy = (spr->cur_frame_ / spr->num_colums_) * spr->frame_height_;

        int flip  =  0;
        if(spr->invert_horizontal_)
        {
            flip |= ALLEGRO_FLIP_HORIZONTAL;
        }
        if(spr->invert_vertical_)
        {
            flip |= ALLEGRO_FLIP_VERTICAL;
        }

        current_frame = al_create_sub_bitmap(spr->image_ , fx , fy , spr->frame_width_ , spr->frame_height_);

        al_draw_scaled_bitmap(current_frame , 0 , 0 , spr->frame_width_ , spr->frame_height_ ,
                              x_ - (spr->frame_width_/2)*spr->hor_scale_ , y_ - (spr->frame_height_/2)*spr->ver_scale_ ,
                              spr->frame_width_ * spr->hor_scale_ , spr->frame_height_ * spr->ver_scale_ , flip);

        if(show_collision_bound_ )
        {
            al_draw_filled_rectangle(x_ - x_offset - bound_x_ , y_  - y_offset - bound_y_ , x_ + bound_x_ , y_ + bound_y_ , al_map_rgba_f(0.5f , 0.1f , 0.5f , 0.2f));
        }
    }

}


// Set object position
void GameObject::setPosition(float pos_x , float pos_y)
{
    x_ = pos_x;
    y_ = pos_y;
}

// Set object velocity
void GameObject::setVel(float vel_x , float vel_y)
{
    vel_x_ = vel_x;
    vel_y_ = vel_y;
}

// Set object x velocity
void GameObject::setVelx(float vel_x )
{
    vel_x_ = vel_x;
}

// Set object y velocity
void GameObject::setVely(float vel_y)
{

    vel_y_ = vel_y;
}

// Get object velocity on x axis
float GameObject::getVelx(){
    return vel_x_;
}

// Get object velocity on y axis
float GameObject::getVely()
{
    return vel_y_;
}

// Get object default velocity on x axis
float GameObject::getDefVelx()
{
    return default_vel_x_;
}

// Get object default velocity on y axis
float GameObject::getDefVely()
{
    return default_vel_y_;
}

// Get object default velocity
void GameObject::setDefaultVel(float dv_x, float dv_y)
{
    default_vel_x_ = dv_x;
    default_vel_y_ = dv_y;
}

// Set default velocity on x axis
void GameObject::setDefaultVelX(float dv_x)
{
    default_vel_x_ = dv_x;
}

// Set default velocity on y axis
void GameObject::setDefaultVelY(float dv_y)
{
    default_vel_y_ = dv_y;
}

bool GameObject::isAlive()
{
    return alive_;
}

// Set object liveness
void GameObject::setAlive(bool is_alive)
{
    alive_ = is_alive;
}

// Set object sprite
void GameObject::setSprite(int index)
{
    current_sprite_ = index;
}

// Get a pointer to its object sprite at index
Sprite * GameObject::getSprite(int index)
{
    return sprite_vector_[index];
}

// Set object boundaries and its y offset
void GameObject::setBoundaries(float bound_x, float bound_y , float bound_y_off)
{
    bound_x_ = bound_x;
    bound_y_ = bound_y;
}

void GameObject::inputResponse(std::vector<bool> *keys)
{

}

// update object
void GameObject::update(void)
{
    Sprite *spr = sprite_vector_[current_sprite_];

    // Update Sprite frame
    if(alive_ && (spr != NULL))
    {
        x_ += vel_x_;
        y_ += vel_y_;

        if((++spr->frame_counter_) >= (spr->frame_delay_))
        {
            spr->cur_frame_+=spr->animation_flow_;
            switch(spr->loop_type_)
            {
                case Sprite::PING_PONG:
                    if(spr->cur_frame_ >= spr->pong_frame_)
                        spr->animation_flow_ = Sprite::REVERSE_ANIM;
                    else if((spr->cur_frame_ <= spr->ping_frame_) && (spr->animation_flow_ == Sprite::REVERSE_ANIM))
                        spr->animation_flow_ = Sprite::FORWARD_ANIM;
                    spr->frame_counter_ = 0;
                    break;
                default:
                    //std::cout << "Default" << std::endl;
                    if(spr->cur_frame_ >= spr->max_frames_)
                        spr->cur_frame_ = 0;
                    else if(spr->cur_frame_ <= 0)
                        spr->cur_frame_ = spr->max_frames_ -1;
                    spr->frame_counter_ = 0;
                    break;
            }
        }
    }
}
