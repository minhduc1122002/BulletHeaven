#include "EnemyArray.h"
using namespace std;
void EnemyArray_Type1(vector<Enemy*> &EnemyArray,SDL_Renderer* screen)
{
    for(int i=0;i<Num_of_ThreatArray1;i++)
    {
        Enemy* p_enemy1=new Enemy();
        p_enemy1->set_type_threat(1.1);
        p_enemy1->set_stats(screen);
        p_enemy1->set_x_pos_(SCREEN_WIDTH/2-(p_enemy1->get_width_frame())/2+100*(i-2));
        p_enemy1->set_y_limit(200);
        p_enemy1->set_y_pos_(-85*2-25*i);
        EnemyArray.push_back(p_enemy1);
    }
    for(int i=0;i<Num_of_ThreatArray1;i++)
    {
        Enemy* p_enemy2=new Enemy();
        p_enemy2->set_type_threat(1.1);
        p_enemy2->set_stats(screen);
        p_enemy2->set_x_pos_(SCREEN_WIDTH/2-(p_enemy2->get_width_frame())/2+100*(i-2));
        p_enemy2->set_y_limit(300);
        p_enemy2->set_y_pos_(-85-25*i);
        EnemyArray.push_back(p_enemy2);
    }
}
void EnemyArray_Type2(vector<Enemy*> &EnemyArray,SDL_Renderer* screen)
{
    for(int i=0;i<Num_of_ThreatArray2;i++)
    {
        Enemy* p_enemy1=new Enemy();
        p_enemy1->set_type_threat(4.1);
        p_enemy1->set_stats(screen);
        p_enemy1->set_x_pos_(-85);
        p_enemy1->set_y_pos_(SCREEN_WIDTH/3-(p_enemy1->get_height_frame())/2+100*(i-1.5));
        EnemyArray.push_back(p_enemy1);
    }
    for(int i=0;i<Num_of_ThreatArray2;i++)
    {
        Enemy* p_enemy2=new Enemy();
        p_enemy2->set_type_threat(4.2);
        p_enemy2->set_stats(screen);
        p_enemy2->set_x_pos_(SCREEN_WIDTH);
        p_enemy2->set_y_pos_(SCREEN_WIDTH/3-(p_enemy2->get_height_frame())/2+100*(i-1.5));
        EnemyArray.push_back(p_enemy2);
    }
}
void EnemyArray_Type3(vector<Enemy*> &EnemyArray,SDL_Renderer* screen)
{
    for(int i=0;i<Num_of_ThreatArray3;i++)
    {
        Enemy* p_enemy=new Enemy();
        p_enemy->set_type_threat(2.1);
        if(i==0)
        {
            p_enemy->set_angle_(0);
            p_enemy->set_angle_val(10);
        }
        else
        {
            p_enemy->set_angle_(180);
            p_enemy->set_angle_val(10);
        }
        p_enemy->set_stats(screen);
        p_enemy->set_x_pos_(SCREEN_WIDTH/2-(p_enemy->get_width_frame())/2+200*(i-0.5));
        p_enemy->set_y_limit(100);
        p_enemy->set_y_pos_(-85);
        EnemyArray.push_back(p_enemy);
    }
}
void EnemyArray_Type4(vector<Enemy*> &EnemyArray,SDL_Renderer* screen)
{
    for(int i=0;i<Num_of_ThreatArray4;i++)
    {
        Enemy* p_enemy=new Enemy();
        p_enemy->set_type_threat(3.1);
        p_enemy->set_stats(screen);
        p_enemy->set_x_pos_(rand()%(650-p_enemy->get_width_frame()-150+1)+150);
        p_enemy->set_y_limit(200);
        p_enemy->set_y_pos_(-85);
        EnemyArray.push_back(p_enemy);
    }
}
void EnemyArray_Type5(vector<Enemy*> &EnemyArray,SDL_Renderer* screen)
{
    for(double i=0;i<Num_of_ThreatArray5;i++)
    {
        for(double j=0;j<Num_of_ThreatArray5-i;j++)
        {
            Enemy* p_enemy=new Enemy();
            p_enemy->set_type_threat(5.1);
            p_enemy->set_stats(screen);
            p_enemy->set_x_pos_(SCREEN_WIDTH/2-(p_enemy->get_width_frame())/2+200*(j-(3-i)/2+0.5));
            p_enemy->set_y_limit(100+100*i);
            p_enemy->set_y_pos_(-85*3+85*i);
            EnemyArray.push_back(p_enemy);
        }
    }
}
void EnemyArray_Type6(vector<Enemy*> &EnemyArray,SDL_Renderer* screen)
{
    for(int i=0;i<4;i++)
    {
        Enemy* p_enemy=new Enemy();
        p_enemy->set_type_threat(7.1);
        p_enemy->set_stats(screen);
        if(i%2==0)
        {
            p_enemy->set_x_pos_(SCREEN_WIDTH/2-(p_enemy->get_width_frame())/2+100*(i-1));
            p_enemy->set_y_pos_(-p_enemy->get_height_frame());
            p_enemy->set_y_limit(200);
        }
        else
        {
            p_enemy->set_x_pos_(SCREEN_WIDTH/2-(p_enemy->get_width_frame())/2);
            p_enemy->set_y_pos_(-p_enemy->get_height_frame()+100*(i-2));
            p_enemy->set_y_limit(0+100*i);
        }
        EnemyArray.push_back(p_enemy);
    }
}
void EnemyArray_Type7(vector<Enemy*> &EnemyArray,SDL_Renderer* screen)
{
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<4;j++)
        {
            Enemy* p_enemy=new Enemy();
            p_enemy->set_type_threat(7.1);
            p_enemy->set_stats(screen);
            if(j%2==0)
            {
                p_enemy->set_x_pos_(SCREEN_WIDTH/2-(p_enemy->get_width_frame())/2+100*(j-1)+400*(i-0.5));
                p_enemy->set_y_pos_(-p_enemy->get_height_frame());
                p_enemy->set_y_limit(200);
            }
            else
            {
                p_enemy->set_x_pos_(SCREEN_WIDTH/2-(p_enemy->get_width_frame())/2+400*(i-0.5));
                p_enemy->set_y_pos_(-p_enemy->get_height_frame()+100*(j-2));
                p_enemy->set_y_limit(0+100*j);
            }
            EnemyArray.push_back(p_enemy);
        }
    }

}
void EnemyBoss(vector<Enemy*> &EnemyArray,SDL_Renderer* screen)
{
    Enemy* p_enemy=new Enemy();
    p_enemy->set_type_threat(6.1);
    p_enemy->set_stats(screen);
    p_enemy->set_angle_(0);
    p_enemy->set_angle_val(0.5);
    p_enemy->set_x_pos_(SCREEN_WIDTH/2-(p_enemy->get_width_frame())/2);
    p_enemy->set_y_limit(100);
    p_enemy->set_y_pos_(-p_enemy->get_height_frame());
    EnemyArray.push_back(p_enemy);
}
void GenerateEnemy(vector<Enemy*> &Enemy_List,SDL_Renderer* screen,int &wave)
{
    if(Enemy_List.size()<=0)
    {
        wave+=1;
        if(wave%10!=0)
        {
            int random=rand()%8+1;
            if(random==1)
            {
                EnemyArray_Type1(Enemy_List,screen);
            }
            else if(random==2)
            {
                EnemyArray_Type2(Enemy_List,screen);
            }
            else if(random==3)
            {
                EnemyArray_Type2(Enemy_List,screen);
                EnemyArray_Type3(Enemy_List,screen);
            }
            else if(random==4)
            {
                EnemyArray_Type2(Enemy_List,screen);
                EnemyArray_Type4(Enemy_List,screen);
            }
            else if(random==5)
            {
                EnemyArray_Type5(Enemy_List,screen);
            }
            else if(random==6)
            {
                EnemyArray_Type2(Enemy_List,screen);
                EnemyArray_Type5(Enemy_List,screen);
            }
            else if(random==7)
            {
                EnemyArray_Type6(Enemy_List,screen);
                EnemyArray_Type2(Enemy_List,screen);
            }
            else if(random==8)
            {
                EnemyArray_Type7(Enemy_List,screen);
            }
        }
        else
        {
            EnemyBoss(Enemy_List,screen);
        }

    }
}

