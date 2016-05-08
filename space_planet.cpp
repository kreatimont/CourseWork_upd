#include "space.h"

planet * create_planet(){
    planet * p = new planet;
    p->sublvl = NULL;
    p->sublvl_count = 0;
    return p;
}

void update_planet(planet * p,QString name,float distance,float mas)
{
    strncpy(p->name,qPrintable(name),NAME_SZIE-1);
    p->distance_to_star = distance;
    p->mass = mas;
}

void add_planet_sort(star * s,planet * p){
    if(s->sublvl == NULL)//if doesn`t exist
    {
        s->sublvl = new void*[START_AR_SIZE];
        s->lenght = START_AR_SIZE;
        s->sublvl_count = 0;
    }
    if(s->sublvl_count == s->lenght)//if full -> expend array
    {
        s->lenght += START_AR_SIZE;
        int new_size = sizeof(planet**)*s->lenght;
        s->sublvl = (void**)realloc(s->sublvl,new_size);
    }
    //int i = s->sublvl_count;
    planet ** wp_pl = (planet**)s->sublvl;
    for(int i = s->sublvl_count;i > 0;i--)
    {
        if(p->distance_to_star > wp_pl[i-1]->distance_to_star)
        {
            wp_pl[i] = p;
            s->sublvl_count++;
            return;
        }
        wp_pl[i] = wp_pl[i-1];
    }
    wp_pl[0] = p;
    s->sublvl_count++;
}


void remove_planet(star * s,int index_p)
{
        planet * p_planet = (planet*)s->sublvl[index_p];

        for(int j = 0; j < p_planet->sublvl_count;j++)
        {
            delete (planet*)(p_planet->sublvl[j]);
        }
        delete[] (p_planet->sublvl);
        delete p_planet;
        for(int i = index_p; i < s->sublvl_count;i++)
        {
            s->sublvl[i] = s->sublvl[i+1];
        }
        s->sublvl[s->sublvl_count] = NULL;
        s->sublvl_count--;

}

