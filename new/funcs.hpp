#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>
#define HEIGHT 11
#define WIDTH 11

typedef struct Listnode{
    int x, y, id, is_alive, existance, movement;
    int satiety;
    struct Listnode *next;
    
} List;

List *create_listnode(int x, int y, int id, int is_alive, int existance, int satiety, int movement);

List *add_front(List *list, int x, int y, int id, int is_alive, int existance, int satiety, int movement);

List *listnode_lookup(List *list, int x, int y, int id);

List *listnode_lookup_by_coord(List *list, int x, int y);

List *listnode_delete(List *list, int x, int y);

void listnode_print(List *list);

void delete_all_data(List *list);

class Creature{
    protected:
    int x, y;
    int is_alive;

    public:
    Creature(){
        x = -1;
        y = -1;
        is_alive = 0;
    }
    ~Creature() = default;
    void set_x(int num);
    void set_y(int num);
    void set_is_alive(int num);
    int get_x();
    int get_y();
    int get_is_alive();
    List *set_data(List *list, int x, int y, int id, int is_alive, int existance, int satiety, int movement);
    List *delete_data(List *list, int x, int y);
    void print(List *list);
    virtual char *color() = 0;
};

class Wolf:public Creature{
    protected:
    int satiety;

    public:
    Wolf():satiety{0}{
        // Creature();
        x = -1;
        y = -1;
        is_alive = 0;
        // satiety = 0;
    }
    ~Wolf(){

    }
    int get_satiety();
    void set_satiety(int num);
    List *move(List *list, int **arr);
    int check_amount(List *list);
    List *kill(List *list);
    char *color();
};

class Hare:public Wolf{
    public:
    Hare(){
        // Wolf();
        x = -1;
        y = -1;
        is_alive = 0;
        satiety = 0;
    }
    ~Hare(){

    }
    virtual List *move(List* list, int **arr);
    virtual int check_amount(List *list);
    virtual List *kill(List *list);
};

class Carrot:public Creature{
    protected:
    int existance;

    public:
    Carrot():existance{0}{
        // Creature();
        // existance = 0;
        x = -1;
        y = -1;
        is_alive = 0;
    }
    ~Carrot(){

    }
    int get_existance();
    void set_existance(int num);
    List *decrease_existance(List *list);
    List *seed_carr(List *list, int **arr);
    char *color();
};

List *next_cycle(List *list, int **arr, Wolf wf, Hare hr, Carrot cr);

void init_world(int **arr, Wolf wf, Hare hr, Carrot cr);

void game_over();