#include "space.h"

space * create_space(){
    space * s = new space;
    s->sublvl = NULL;
    s->sublvl_count = 0;
    return s;
}

void update_space(QString name){
    space * wp = (space*)getRoot();
    strncpy(wp->name,qPrintable(name),NAME_SZIE-1);

}

void remove_space(){
    space * wp = (space*)getRoot();
    for(int n = 0;n < wp->sublvl_count;n++)
    {
        star * p_star = (star*)wp->sublvl[n];

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
    }
    delete[] (wp->sublvl);
    delete (space*)getRoot();
    setRoot(NULL);
}

