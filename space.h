#ifndef SPACE
#define SPACE

#include <QString>
#include <QErrorMessage>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPalette>

#define NAME_SZIE 20
#define START_AR_SIZE 1

struct satellite{
    char name[NAME_SZIE];
    float distance_to_planet;
    bool human_made;
};

struct planet{
    char name[NAME_SZIE];
    float distance_to_star;
    float mass;
    int lenght;
    int sublvl_count;
    void** sublvl;
};

struct star{
    char name[NAME_SZIE];
    char star_class[NAME_SZIE];
    float mass;
    int lenght;
    int sublvl_count;
    void** sublvl;
};

struct space{
    char name[NAME_SZIE];
    int lenght;
    int sublvl_count;
    void** sublvl;
};
void *getRoot();
void setRoot(void *r);
space * create_space();
void update_space(QString name);
void remove_space();

satellite * create_satellite();
void update_satellite(satellite * sat, QString name, float distance, bool hmade);
void add_satellite_sort(planet * p, void *s);
void remove_satellite(planet * p,int index_sat);

planet * create_planet();
void update_planet(planet * p,QString name,float distance,float mas);
void add_planet_sort(star * s,planet * p);
void remove_planet(star * s,int index_p);

star * create_star();
void update_star(star * s,QString name,QString clas,float mas);
void add_star_sort(space * sp,star * st);
void remove_star(int index_st);

void store(space * sp,FILE * f);
space * restore(FILE *f);
#endif // SPACE

