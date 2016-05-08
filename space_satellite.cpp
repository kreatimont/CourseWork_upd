#include "space.h"

satellite * create_satellite(){
    satellite * sat = new satellite;
    return sat;
}

void update_satellite(satellite * sat, QString name, float distance, bool hmade){
    strncpy(sat->name,qPrintable(name),NAME_SZIE-1);
    sat->distance_to_planet = distance;
    sat->human_made = hmade;
}

void add_satellite_sort(planet * p,void * s){
    if(p->sublvl == NULL)//if doesn`t exist
    {
        p->sublvl = new void*[START_AR_SIZE];
        p->lenght = START_AR_SIZE;
        p->sublvl_count = 0;
    }
    if(p->sublvl_count == p->lenght)
    {
        p->lenght += START_AR_SIZE;
        int new_size = sizeof(satellite**)*p->lenght;
        p->sublvl = (void**)realloc(p->sublvl,new_size);
    }
    if(p->sublvl_count == 0)
    {
        p->sublvl[0] = s;
    }else{
        p->sublvl[p->sublvl_count] = s;
    }
    p->sublvl_count++;
}

void remove_satellite(planet * p,int index_sat)
{
    satellite * p_sat = (satellite*)p->sublvl[index_sat];
    delete p_sat;

    p->sublvl_count--;
    for(int i = index_sat;i < p->sublvl_count;i++)
    {
        p->sublvl[i] = p->sublvl[i+1];
    }
    p->sublvl[p->sublvl_count] = NULL;
}
