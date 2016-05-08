#include "space.h"


star * create_star(){
    star * s = new star;
    s->sublvl = NULL;
    s->sublvl_count = 0;
    return s;
}

void update_star(star * s,QString name,QString clas,float mas)
{
    strncpy(s->name,qPrintable(name),NAME_SZIE-1);
    strncpy(s->star_class,qPrintable(clas),NAME_SZIE-1);
    s->mass = mas;
}

void add_star_sort(space * sp,star * st){
    if(sp->sublvl == NULL)//if doesn`t exist
    {
        sp->sublvl = new void*[START_AR_SIZE];
        sp->lenght = START_AR_SIZE;
        sp->sublvl_count = 0;
    }
    if(sp->sublvl_count == sp->lenght)
    {
        sp->lenght += START_AR_SIZE;
        int new_size = sizeof(star**)*sp->lenght;
        sp->sublvl = (void**)realloc(sp->sublvl,new_size);
    }
    int i = sp->sublvl_count;
    star ** wp_star = (star**)sp->sublvl;
    for(;i > 0;i--)
    {
        if(st->mass > wp_star[i-1]->mass)
        {
            break;
        }
        wp_star[i] = wp_star[i-1];
    }
    wp_star[i] = st;
    sp->sublvl_count++;
}

void remove_star(int index_st)
{
    space * wp = (space*)getRoot();
    star * p_star = (star*)wp->sublvl[index_st];
    for(int i = 0;i < p_star->sublvl_count;i++)
    {
        planet * p_planet = (planet*)p_star->sublvl[i];

        for(int j = 0; j < p_planet->sublvl_count;j++)
        {
            delete (satellite*)(p_planet->sublvl[j]);
        }

        delete[] (p_planet->sublvl);
        delete p_planet;
    }
    p_star->sublvl = NULL;
    delete p_star;
    delete[] (p_star->sublvl);
    delete p_star;
    wp->sublvl_count--;
    for(int i = index_st;i < wp->sublvl_count;i++)
    {
        wp->sublvl[i] = wp->sublvl[i+1];
    }
}


