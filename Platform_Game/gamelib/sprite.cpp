
#include "sprite.h"

#include <iostream>
const float Sprite::kStandardScale = 1.0f;

Sprite::Sprite(short int max_f , short int num_col , int f_width , int f_height , ALLEGRO_BITMAP *im)
{
    max_frames_ = max_f;
    cur_frame_ = 0;
    frame_counter_ = 0;
    frame_delay_ = kStandardFrameDelay;
    frame_width_ = f_width;
    frame_height_ = f_height;
    num_colums_ = num_col;
    animation_flow_ = FORWARD_ANIM;
    hor_scale_ = kStandardScale;
    ver_scale_ = kStandardScale;
    invert_horizontal_ = false;
    invert_vertical_ = false;
    loop_type_ = SIMPLE;
    ping_frame_ = 0;
    pong_frame_ = max_f - 1;
    image_ = im;
}

Sprite::Sprite(short int max_f , short int num_col , int f_width , int f_height,
       ALLEGRO_BITMAP *im , short int ping_f , short int pong_f)
{
    max_frames_ = max_f;
    cur_frame_ = 0;
    frame_counter_ = 0;
    frame_delay_ = kStandardFrameDelay;
    frame_width_ = f_width;
    frame_height_ = f_height;
    num_colums_ = num_col;
    animation_flow_ = FORWARD_ANIM;
    hor_scale_ = kStandardScale;
    ver_scale_ = kStandardScale;
    invert_horizontal_ = false;
    invert_vertical_ = false;
    loop_type_ = PING_PONG;
    ping_frame_ = ping_f;
    pong_frame_ = pong_f;
    image_ = im;

}

Sprite::~Sprite()
{
    al_destroy_bitmap(image_);
    std::cout << "deleted image from sprite" << std::endl;
}


