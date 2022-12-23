#include "funcs.hpp"

using std::cout;

List *create_listnode(int x, int y, int id, int is_alive, int existance, int satiety, int movement){
    List *p;

    p = (List*)malloc(sizeof(List));
    if(p != NULL){
        p->x = x;
        p->y = y;
        p->id = id;
        p->is_alive = is_alive;
        p->existance = existance;
        p->satiety = satiety;
        p->movement = movement;
        p->next = NULL;
    }
    return p;
}

List *add_front(List *list, int x, int y, int id, int is_alive, int existance, int satiety, int movement){
    List* node;

    node = create_listnode(x, y, id, is_alive, existance, satiety, movement);
    if(node != NULL){
        node->next = list;
        return node;
    }
    return list;
}

List *listnode_lookup(List *list, int x, int y, int id){
    for(; list != NULL; list = list->next){
        if(x == list->x && y == list->y && id == list->id){
            return list;
        }
    }
    return NULL;
}

List *listnode_lookup_by_coord(List *list, int x, int y){
        for(; list != NULL; list = list->next){
        if(x == list->x && y == list->y){
            return list;
        }
    }
    return NULL;
}

List *listnode_delete(List *list, int x, int y){
    List *p, *prev = NULL;

    for(p = list; p != NULL; p = p->next){
        if(x == p->x && y == p->y){
            if(prev == NULL){
                list = p->next;
            }
            else{
                prev->next = p->next;
            }
            free(p);
            return list;
        }
        prev = p;
    }
    return NULL;
}

void listnode_print(List *list){
    for(; list != NULL; list = list->next){
        cout << list->x << " " << list->y << "id:" << list->id << "\n";
    }
}

void Creature::set_is_alive(int num){
    is_alive = num;
}

int Creature::get_is_alive(){
    return is_alive;
}

void Creature::set_x(int num){
    x = num;
}

void Creature::set_y(int num){
    y = num;
}

int Creature::get_x(){
    return x;
}

int Creature::get_y(){
    return y;
}

List *Creature::set_data(List *list, int x, int y, int id, int is_alive, int existance, int satiety, int movement){
    list = add_front(list, x, y, id, is_alive, existance, satiety, movement);
    return list;
}

List *Creature::delete_data(List *list, int x, int y){
    List *node;
    node = listnode_delete(list, x, y);
    if(node != NULL){
        list = node;
    }
    return list;
}

// void Creature::delete_all_data(List *list){
//     for(int i = 0; i < HEIGHT; i++){
//         for(int j = 0; j < WIDTH; j++){
//             list = listnode_delete(list, i, j);
//         }
//     }
// }

int Wolf::get_satiety(){
    return satiety;
}

void Wolf::set_satiety(int num){
    satiety = num;
}

int Wolf::check_amount(List *list){
    int cnt = 0;

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            List *node;
            node = listnode_lookup_by_coord(list, i, j);
            if(node != NULL && node->id == 3){
                cnt++;
            }
        }
    }
    return cnt;
}

int Hare::check_amount(List *list){
    int cnt = 0;

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            List *node;
            node = listnode_lookup_by_coord(list, i, j);
            if(node != NULL && node->id == 2){
                cnt++;
            }
        }
    }
    return cnt;
}

List *Wolf::move(List *list, int **arr){
    List *temp_list;
    List *temp_list2;

    // cout << "*" << "\n";
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            int temp_i, temp_j;
            temp_i = rand() % 3 + (-1);
            temp_j = rand() % 3 + (-1);
            temp_list = listnode_lookup(list, i, j, 3);
            if(temp_list != NULL){
                if((temp_i != 0 || temp_j != 0) && (i + temp_i <= HEIGHT - 1 && i + temp_i >= 0) && (j + temp_j >= 0 && j + temp_j <= WIDTH - 1) && (arr[i + temp_i][j + temp_j] == 1)){
                    temp_list2 = listnode_lookup_by_coord(list, i + temp_i, j + temp_j);
                    if(temp_list2 != NULL && temp_list2->id == 2){
                        list = delete_data(list, i + temp_i, j + temp_j);
                        list = add_front(list, i + temp_i, j + temp_j, 3, 1, 1, 10, 0);
                        list = delete_data(list, i, j);
                    }
                    else if(temp_list2 != NULL && temp_list2->id == 1){
                        list = delete_data(list, i, j);
                        list = add_front(list, i, j, 3, 1, 1, (temp_list->satiety - 2), 0);
                        continue;
                    }
                    else if(temp_list2 != NULL && temp_list2->id == 3){
                        list = delete_data(list, i, j);
                        list = add_front(list, i, j, 3, 1, 1, (temp_list->satiety - 2), 0);
                        continue;
                    }
                    else{
                        list = add_front(list, i + temp_i, j + temp_j, 3, 1, 1, (temp_list->satiety - 2), 0);
                        list = delete_data(list, i, j);
                    }
                }
                else{
                    continue;
                }
            }

            // if(temp_list != NULL){
            //     if(j + 1 <= WIDTH - 1  && arr[i][j + 1] == 1 && temp_list->movement != 0){
            //         temp_list2 = listnode_lookup_by_coord(list, i, j + 1);
            //         if(temp_list2 != NULL && temp_list2->id == 2){
            //             list = delete_data(list, i, j + 1);
            //             list = add_front(list, i, j + 1, 3, 1, 1, 1.0, 0);
            //             list = delete_data(list, i, j);
            //         }
            //         else if(temp_list2 != NULL && temp_list2->id == 1){
            //             continue;
            //         }
            //         else if(temp_list2 != NULL && temp_list2->id == 3){
            //             // cout << "*" << "\n";
            //         }
            //         else{ //if empty cell
            //             list = add_front(list, i, j + 1, 3, 1, 1, 1.0, 0);
            //             list = delete_data(list, i, j);
            //         }
            //     }
            //     else if(i + 1 <= HEIGHT - 1 && arr[i + 1][j] == 1 && temp_list->movement != 0){
            //         temp_list2 = listnode_lookup_by_coord(list, i + 1, j);
            //         if(temp_list2 != NULL && temp_list2->id == 2){
            //             list = delete_data(list, i + 1, j);
            //             list = add_front(list, i + 1, j, 3, 1, 1, 1.0, 0);
            //             list = delete_data(list, i, j);
            //         }
            //         else if(temp_list2 != NULL && temp_list2->id == 1){
            //             continue;
            //         }
            //         else if(temp_list2 != NULL && temp_list2->id == 3){

            //         }
            //         else{ //if empty cell
            //             list = add_front(list, i + 1, j, 3, 1, 1, 1.0, 0);
            //             list = delete_data(list, i, j);
            //         }
            //     }
            // }
        }
    }

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            temp_list = listnode_lookup(list, i, j, 3);
            if(temp_list != NULL){
                list = delete_data(list, i, j);
                list = add_front(list, i, j, 3, 1, 1, temp_list->satiety, 1);
            }
        }
    }

    return list;
}

List *Wolf::kill(List *list){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            List *node;
            node = listnode_lookup_by_coord(list, i, j);
            if(node != NULL && node->id == 3 && node->satiety < 0){
                list = delete_data(list, i, j);
            }
        }
    }
    return list;
}

char *Wolf::color(){
    char *alph = "g";
    return alph;
}

char *Carrot::color(){
    char *alph = "o";
    return alph;
}

List *Hare::move(List* list, int **arr){
    List *temp_list;
    List *temp_list2;

    // cout << "*" << "\n";
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            int temp_i, temp_j;
            temp_i = rand() % 3 + (-1);
            temp_j = rand() % 3 + (-1);
            temp_list = listnode_lookup(list, i, j, 2);
            if(temp_list != NULL){
                if((temp_i != 0 || temp_j != 0) && (i + temp_i <= HEIGHT - 1 && i + temp_i >= 0) && (j + temp_j >= 0 && j + temp_j <= WIDTH - 1) && (arr[i + temp_i][j + temp_j] == 1)){
                    temp_list2 = listnode_lookup_by_coord(list, i + temp_i, j + temp_j);
                    if(temp_list2 != NULL && temp_list2->id == 1){
                        list = delete_data(list, i + temp_i, j + temp_j);
                        list = add_front(list, i + temp_i, j + temp_j, 2, 1, 1, 10, 0);
                        list = delete_data(list, i, j);
                    }
                    else if(temp_list2 != NULL && temp_list2->id == 2){
                        list = delete_data(list, i, j);
                        list = add_front(list, i, j, 2, 1, 1, (temp_list->satiety - 2), 0);
                        continue;
                    }
                    else if(temp_list2 != NULL && temp_list2->id == 3){
                        list = delete_data(list, i, j);
                        list = add_front(list, i, j, 2, 1, 1, (temp_list->satiety - 2), 0);
                        continue;
                    }
                    else{
                        list = add_front(list, i + temp_i, j + temp_j, 2, 1, 1, (temp_list->satiety - 2), 0);
                        list = delete_data(list, i, j);
                    }
                }
                else{
                    continue;
                }
            }

            // if(temp_list != NULL){
            //     if(j + 1 <= WIDTH - 1  && arr[i][j + 1] == 1 && temp_list->movement != 0){
            //         temp_list2 = listnode_lookup_by_coord(list, i, j + 1);
            //         if(temp_list2 != NULL && temp_list2->id == 2){
            //             list = delete_data(list, i, j + 1);
            //             list = add_front(list, i, j + 1, 3, 1, 1, 1.0, 0);
            //             list = delete_data(list, i, j);
            //         }
            //         else if(temp_list2 != NULL && temp_list2->id == 1){
            //             continue;
            //         }
            //         else if(temp_list2 != NULL && temp_list2->id == 3){
            //             // cout << "*" << "\n";
            //         }
            //         else{ //if empty cell
            //             list = add_front(list, i, j + 1, 3, 1, 1, 1.0, 0);
            //             list = delete_data(list, i, j);
            //         }
            //     }
            //     else if(i + 1 <= HEIGHT - 1 && arr[i + 1][j] == 1 && temp_list->movement != 0){
            //         temp_list2 = listnode_lookup_by_coord(list, i + 1, j);
            //         if(temp_list2 != NULL && temp_list2->id == 2){
            //             list = delete_data(list, i + 1, j);
            //             list = add_front(list, i + 1, j, 3, 1, 1, 1.0, 0);
            //             list = delete_data(list, i, j);
            //         }
            //         else if(temp_list2 != NULL && temp_list2->id == 1){
            //             continue;
            //         }
            //         else if(temp_list2 != NULL && temp_list2->id == 3){

            //         }
            //         else{ //if empty cell
            //             list = add_front(list, i + 1, j, 3, 1, 1, 1.0, 0);
            //             list = delete_data(list, i, j);
            //         }
            //     }
            // }
        }
    }
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            temp_list = listnode_lookup(list, i, j, 2);
            if(temp_list != NULL){
                list = delete_data(list, i, j);
                list = add_front(list, i, j, 2, 1, 1, temp_list->satiety, 1);
            }
        }
    }

    return list;
}

void Creature::print(List *list){
    List *node;

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){

            // if(i == 0 || i == HEIGHT - 1 || j == WIDTH - 1){
            //     cout << "*" << "";
            //     continue;
            // }

            node = listnode_lookup_by_coord(list, i, j);
            if(node != NULL){
                if(node->id == 1){
                    cout << "C";
                }
                else if(node->id == 2){
                    cout << "H";
                }
                else if(node->id == 3){
                    cout << "W";
                }
            }
            else{
               cout << "~"; 
            }
        }
        cout << "\n";
    }
}

int Carrot::get_existance(){
    return existance;
}

void Carrot::set_existance(int num){
    existance = num;
}

List *Hare::kill(List *list){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            List *node;
            node = listnode_lookup_by_coord(list, i, j);
            if(node != NULL && node->id == 2 && node->satiety < 0){
                list = delete_data(list, i, j);
            }
        }
    }
    return list;
}

List *Carrot::decrease_existance(List *list){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            List *node;
            node = listnode_lookup_by_coord(list, i, j);
            if(node != NULL && node->id == 1){
                if(node->existance <= 0){
                    list = delete_data(list, i, j);
                    continue;
                }
                list = delete_data(list, i, j);
                list = add_front(list, i, j, 1, 1, (node->existance - 1), 1, 0);
            } 
        }
    }
    return list;
}

List *Carrot::seed_carr(List *list, int **arr){
    // cout << "*";
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            int temp_i, temp_j;
            temp_i = rand() % 3 + (-1);
            temp_j = rand() % 3 + (-1);
            int num = rand() % 3 + 0;
            List *temp_list;
            temp_list = listnode_lookup_by_coord(list, i, j);
            if(temp_list != NULL && temp_list->id == 1){
                // cout << "*";
                if((temp_i != 0 || temp_j != 0) && (i + temp_i <= HEIGHT - 1 && i + temp_i >= 0) && (j + temp_j >= 0 && j + temp_j <= WIDTH - 1) && (arr[i + temp_i][j + temp_j] == 1)){
                    List *temp_list2;
                    temp_list2 = listnode_lookup_by_coord(list, i + temp_i, j + temp_j);
                    if(temp_list2 == NULL && num % 2 == 0){
                        cout << "*";
                        list = add_front(list, temp_i + i, temp_j + j, 1, 1, 3, 1, 0);
                    }
                }
            }
        }
    }
    return list;
}

void game_over(){
    system("clear");
 std::cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
 std::cout << "███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n";
 std::cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n";
 std::cout << "██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n";
 std::cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n";
 std::cout << "███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n";
 std::cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
 std::cout << "███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n";
 std::cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
 std::cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n";
 std::cout << "██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
 std::cout << "███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n";
}

//funcs

List *next_cycle(List *list, int **arr, Wolf wf, Hare hr, Carrot cr){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            int num = rand() % 100 + 0;
            if(num % 1 == 0){
                arr[i][j] = 1;
            }
            else{
                arr[i][j] = 0;
            }
            // cout << arr[i][j];
        }
        // cout << "\n";
    }
    list = wf.move(list, arr);
    list = wf.kill(list);
    list = hr.move(list, arr);
    list = hr.kill(list);
    list = cr.seed_carr(list, arr);
    list = cr.decrease_existance(list);

    return list;
}

void init_world(int **arr, Wolf wf, Hare hr, Carrot cr){
    for(int i = 1; i < HEIGHT - 1; i++){
        for(int j = 1; j < WIDTH - 1; j++){
            int num = rand() % 100 + 0;
            if(num % 8 == 0){
                arr[i][j] = 1;
            }
            else{
                arr[i][j] = 0;
            }
        }
    }

    List *list = NULL;

    for(int i = 1; i < HEIGHT - 1; i++){
        for(int j = 1; j < WIDTH - 1; j++){
            int num = rand() % 200 + 0;
            if((arr[i][j] == 1) && (num > 0 && num < 70)){
                cr.set_x(i);
                cr.set_y(j);
                cr.set_is_alive(1);
                cr.set_existance(3);
                list = cr.set_data(list, cr.get_x(), cr.get_y(), 1, cr.get_is_alive(), cr.get_existance(), 1, 0);
                // cout << "C" << "[" << list->y << "]" << " ";
            }
            else if((arr[i][j] == 1) && (num > 70 && num < 150)){
                hr.set_x(i);
                hr.set_y(j);
                hr.set_is_alive(1);
                list = hr.set_data(list, hr.get_x(), hr.get_y(), 2, hr.get_is_alive(), 1, 1, 1);
                // cout << "H" << "[" << list->y << "]" << " ";
            }
            else if((arr[i][j] == 1) && (num > 150 && num < 200)){
                wf.set_x(i);
                wf.set_y(j);
                wf.set_is_alive(1);
                wf.set_satiety(10);
                list = wf.set_data(list, wf.get_x(), wf.get_y(), 3, wf.get_is_alive(), 1, wf.get_satiety(), 1);
                // cout << "W" << "[" << list->y << "]" << " ";
            }
            else{
                // cout << "-" << " ";
                continue;
            }
        }
        // cout << "\n";
    }
    // listnode_print(list);
    wf.print(list);
    sleep(2);

    while(1){
        if(wf.check_amount(list) < 5){
            list = add_front(list, 1, 1, 3, 1, 1, 10, 1);
        }
        if(wf.check_amount(list) < 1 || hr.check_amount(list) < 1){
            break;
        }
        list = next_cycle(list, arr, wf, hr, cr);
        // cout << "After new cycle:\n"; listnode_print(list);
        system("clear");
        cout << "------------------------------------------------------" << "\n";
        wf.print(list);
        // cout << "\n"; listnode_print(list);
        sleep(3);
    }
    game_over();
}