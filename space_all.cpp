#include "space.h"

void store(space * sp,FILE * f)
{
    if(sp == NULL)
    {
        return;
    }
    fwrite(sp,sizeof(space),1,f);

    star ** p_star = (star**)sp->sublvl;
    int count_star = sp->sublvl_count;

    if(p_star == NULL || count_star == 0)
    {
        fclose(f);
        return;
    }
    for(int i_star = 0;i_star < count_star;i_star++)
    {
        star * st = p_star[i_star];
        fwrite(st,sizeof(star),1,f);

        planet ** p_planet = (planet**)st->sublvl;
        int count_planet = st->sublvl_count;

        if(p_planet == NULL || count_planet == 0)
        {
            continue;
        }

        for(int i_plan = 0;i_plan < count_planet;i_plan++)
        {
            planet * pt = p_planet[i_plan];
            fwrite(pt,sizeof(planet),1,f);

            satellite ** p_sat = (satellite**)pt->sublvl;
            int count_sat = pt->sublvl_count;

            if(p_sat == NULL || count_sat == 0)
            {
                continue;
            }

            for(int i_sat = 0;i_sat < count_sat;i_sat++)
            {
                satellite * ps = p_sat[i_sat];
                fwrite(ps,sizeof(satellite),1,f);
            }
        }
    }fclose(f);
}

space * restore(FILE *f)
{
    space * root = new space;
    fread(root,sizeof(space),1,f);
    root->sublvl = NULL;
    int count_star = root->sublvl_count;

    for(int i_star = 0;i_star < count_star;i_star++)
    {
        star * p_star = new star;
        fread(p_star,sizeof(star),1,f);
        p_star->sublvl = NULL;
        add_star_sort(root,p_star);
        int count_planet = p_star->sublvl_count;

        for(int i_pl = 0;i_pl < count_planet;i_pl++)
        {
            planet * p_planet = new planet;
            fread(p_planet,sizeof(planet),1,f);
            p_planet->sublvl = NULL;
            add_planet_sort(p_star,p_planet);
            int count_sat = p_planet->sublvl_count;

            for(int i_sat = 0;i_sat < count_sat;i_sat++)
            {
                satellite * p_sat = new satellite;
                fread(p_sat,sizeof(satellite),1,f);
                add_satellite_sort(p_planet,p_sat);
            }
        }
    }
    fclose(f);
    return root;
}
