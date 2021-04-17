#ifndef THREATOBJECT_H_INCLUDED
#define THREATOBJECT_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#define Num_of_Frame_Enemy 1
using namespace std;
class ThreatObject:public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();

    void set_x_pos_(const float &xPos) {x_pos_=xPos;}
    int set_random_x_pos_();
    void set_y_pos_(const float &yPos) {y_pos_=yPos;}
    int set_random_y_pos_();

    void random_type_threat();
    int get_type_threat() const {return type;}


    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}

    int get_x_pos_() const {return x_pos_;}
    int get_y_pos_() const {return y_pos_;}
    int get_score() const {return score;}

    void set_x_val_(const float &xVal) {x_val_=xVal;}
    void set_y_val_(const float &yVal) {y_val_=yVal;}
    void set_stats(SDL_Renderer* screen);

    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void set_clip();
    void MoveThreat_Type1();
    void MoveThreat_Type2();

    int increase_die() {return die++;}

    int get_die() {return die;}
    vector< vector<BulletObject*> > get_bullet_list1() const {return p_bullet_list1_;}

    void ResetBullet(BulletObject *p_bullet);

    void RemoveBullet(const int &index1,const int &index2);

    void InitBullet(SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen,const int &x_border, const int &y_border);

    void resizebullet();

private:
    float x_pos_;
    float y_pos_;

    int die;
    int type;
    int score;

    double angle_move_;

    float x_val_;
    float y_val_;

    int width_frame_;
    int height_frame_;
    int n;


    SDL_Rect frame_clip_[Num_of_Frame_Enemy];
    int frame_;

    vector< vector< BulletObject* > > p_bullet_list1_;


    unsigned long long CurrentTime;
    unsigned long long LastTime;

};

#endif // THREATOBJECT_H_INCLUDED
