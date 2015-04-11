#ifndef SPRITE_H
#define SPRITE_H


#include<allegro5/allegro.h>

class Sprite
{
public:
    enum LoopType {SIMPLE , PING_PONG};
    enum AnimationFlow {FORWARD_ANIM=1 , REVERSE_ANIM=-1};
    static const short int kStandardFrameDelay = 5;
    static const float kStandardScale;

    Sprite(short int max_f , short int num_col , int f_width , int f_height , ALLEGRO_BITMAP *im);

    Sprite(short int max_f , short int num_col , int f_width , int f_height,
           ALLEGRO_BITMAP *im , short int ping_f , short int pong_f);
    ~Sprite();

    int frame_width_ , frame_height_;
    short int max_frames_ , cur_frame_ , frame_counter_ , frame_delay_,
    ping_frame_ , pong_frame_ , num_colums_ , animation_flow_;
    float hor_scale_ , ver_scale_;
    bool invert_horizontal_ , invert_vertical_;
    LoopType loop_type_;
    ALLEGRO_BITMAP *image_;

};

#endif // SPRITE_H
