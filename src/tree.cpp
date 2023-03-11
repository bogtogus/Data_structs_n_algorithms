#include <tree.h>
#include <functionality.h>
using namespace std;

int add_element(flight*& root, const flight& data) {
    flight* new_joint = new flight{};
    strcpy_s(new_joint->number, data.number);
    new_joint->company = data.company;
    new_joint->departure = data.departure;
    new_joint->arriving = data.arriving;
    new_joint->dep_time = data.dep_time;
    new_joint->arv_time = data.arv_time;
    new_joint->places = data.places;
    new_joint->free = data.free;

    flight* current_joint = root;
    flight* prev_joint = nullptr;
    
    if (root == nullptr) {
        root = new_joint;
    }
    else {
        while (current_joint != nullptr) { // перемещение до решающего узла
            prev_joint = current_joint;
            if (strcmp(new_joint->number, current_joint->number) < 0) {
                current_joint = current_joint->left;
            }
            else if (strcmp(new_joint->number, current_joint->number) > 0) {
                current_joint = current_joint->right;
            }
            else if (strcmp((current_joint->left)->number, new_joint->number) == 0) {
                return 1; // уже существует
            }
            else {
                break;
            }
        }
        if (current_joint == nullptr) { //решающий узел
            current_joint = prev_joint;
        }
        new_joint->prev = current_joint;
        if (strcmp(new_joint->number, current_joint->number) < 0) {
            current_joint->left = new_joint;
        }
        else if (strcmp(new_joint->number, current_joint->number) > 0) {
            current_joint->right = new_joint;
        }
        /* если новые данные такие же, как у решающего узла, 
        то к новому узлу привязывается всё левое поддерево решающего узла, если оно есть */
        else { 
            new_joint->left = current_joint->left;
            new_joint->prev = current_joint;
            if (current_joint->left != nullptr) {
                (current_joint->left)->prev = new_joint;
            }
            current_joint->left = new_joint;
            new_joint->height = current_joint->height;
            current_joint->height++;
        }

        current_joint = new_joint;
        int u = current_joint->height;
        while (current_joint != nullptr) { //подсчёт высоты обратным проходом
            if (u > current_joint->height) {
                current_joint->height = u;
            }
            u++;
            current_joint = current_joint->prev;

        }
    }
    while(!is_balanced(root)) {
        FullBalance(root);
        height_recalculation(root);
    }
    return 0;
}

int delete_element(flight*& root, const char* number) {
    if (root == nullptr) {
        return 1;
    }
    flight* current_joint = root;
    flight* prev_joint = nullptr;
    flight* maxleft = nullptr;
    while (current_joint != nullptr) { // дойти до узла(или пустоты) после искомого узла
        prev_joint = current_joint;
        if (strcmp(number, current_joint->number) < 0) {
            current_joint = current_joint->left;
        }
        else if (strcmp(number, current_joint->number) > 0) {
            current_joint = current_joint->right;
        }
        else if (current_joint->left != nullptr && strcmp(((current_joint->left)->number), number) == 0) {
            return 1; // уже существует
        }
        else {
            break;
        }
    }
    current_joint = prev_joint; //рассмотреть нужный удаляемый узел
    if (strcmp(number, current_joint->number) != 0) {
        return 2; // не найдено
    }
    else {
        maxleft = find_maxleft(current_joint); //максимум левого поддерева
        if (maxleft == nullptr) { //если левой ветви нет
            if (current_joint->prev != nullptr) { //если удаляемый не корень
                prev_joint = current_joint->prev;
                if (strcmp(number, prev_joint->number) < 0) {
                    prev_joint->left = current_joint->right;
                }
                else if (strcmp(number, prev_joint->number) > 0) {
                    prev_joint->right = current_joint->right;
                }
                if (current_joint->right != nullptr) {
                    (current_joint->right)->prev = prev_joint;
                }
                delete current_joint;
                current_joint = nullptr;
            }
            else {// если одинокий корень
                delete current_joint;
                root = nullptr;
            }
        }
        else { // если левая ветвь есть
            if (maxleft->left != nullptr) { // если у левого максимума есть левая ветвь
                if (maxleft->prev != nullptr && maxleft->prev != current_joint) { // если у заменяющего есть предок
                    (maxleft->prev)->right = maxleft->left;
                    (maxleft->left)->prev = maxleft->prev;
                    maxleft->left = nullptr;
                }
            }
            
            maxleft->right = current_joint->right;
            if (current_joint->right != nullptr) {
                (current_joint->right)->prev = maxleft;
            }
            prev_joint = current_joint->prev; // родительский узел удаляемого узла
            if (prev_joint != nullptr) { //если удаляемый не корень
                if (strcmp(number, prev_joint->number) < 0) {
                    prev_joint->left = maxleft;
                }
                else if (strcmp(number, prev_joint->number) > 0) {
                    prev_joint->right = maxleft;
                }
            }
            if (maxleft->prev != current_joint) {
                maxleft->left = current_joint->left;
                (maxleft->prev)->right = nullptr;
            }
            maxleft->prev = current_joint->prev;
            if(maxleft->left != nullptr) {
                (maxleft->left)->prev = maxleft;
            }
            if(maxleft->right != nullptr) {
                (maxleft->right)->prev = maxleft;
            }
            if (maxleft->prev == nullptr) {
                root = maxleft;
            }
            delete current_joint;
            current_joint = nullptr;
        }
    }
    height_recalculation(root);
    while(!is_balanced(root)) {
        FullBalance(root);
        height_recalculation(root);
    }
    return 0;
}

bool is_exists(const flight* subroot, const string& number) {
    if (subroot != nullptr) {
        string nb = number;
        if (number.find('-') != string::npos) {
            nb.erase(3, 1);
        }
        if (is_exists(subroot->left, nb)) {
            return true;
        }
        if (strcmp(subroot->number, nb.c_str()) == 0) {
            return true;
        }
        if (is_exists(subroot->right, nb)) {
            return true;
        }
    }
    return false;
}

flight* find_element(flight* root, const char* number) {
    flight* prev_joint = nullptr;
    flight* current_joint = root;
    if (root == nullptr) {
        return nullptr;
    }
    else {
        while (current_joint != nullptr) { // перемещение до нужного узла
            prev_joint = current_joint;
            if (strcmp(number, current_joint->number) < 0) {
                current_joint = current_joint->left;
            }
            else if (strcmp(number, current_joint->number) > 0) {
                current_joint = current_joint->right;
            }
            else if (current_joint->left != nullptr && strcmp((current_joint->left)->number, number) == 0) {
                current_joint = current_joint->left;
            }
            else { // найден самый левый нужный узел
                break;
            }
        }
        if (current_joint == nullptr) { //если нужный узел - лист, то перемещаемся из пустоты в него
            current_joint = prev_joint;
        }
        if (strcmp(current_joint->number, number) != 0) {
            return nullptr;
        }
    }
    return current_joint;
}

bool find_elements_bytext(flight* subroot, found_flights*& ffl, const string text) { //обратный
    if (subroot != nullptr) {
        bool ret = find_elements_bytext(subroot->left, ffl, text);
        ret = find_elements_bytext(subroot->right, ffl, text);
        if (compare_fragments(subroot->arriving, text)) {
            push_back(ffl, subroot);
            return true;
        }
        else if (ret) {
            return ret;
        }
    }
    return false;
}

flight* find_maxleft(flight* subroot) {
    if (subroot == nullptr) {
        return nullptr;
    }
    flight* current_joint = subroot;
    current_joint = current_joint->left;
    if (current_joint == nullptr) {
        return nullptr;
    }
    while (current_joint->right != nullptr) {
        current_joint = current_joint->right;
    }
    return current_joint;
}

flight* find_minright(flight* subroot) {
    if (subroot == nullptr) {
        return nullptr;
    }
    flight* current_joint = subroot;
    current_joint = current_joint->right;
    if (current_joint == nullptr) {
        return nullptr;
    }
    while (current_joint->left != nullptr) {
        current_joint = current_joint->left;
    }
    if (current_joint->left == nullptr) {
        return nullptr;
    }
    return current_joint;
}

void output_tree_height(flight* subroot, long int n, const int direction, bool changed) {
    if (subroot != nullptr) {
        const int num_middle = ((int)log10(subroot->height) + 1 + 7) / 2;
        const int branch_lengh = 8;
        // углубление максимально вправо
        output_tree_height(subroot->right, n + branch_lengh + num_middle, 2, (bool)(direction != 2));
        //вывод высоты подкорня

        for (long i = 0; i < n; i++) {
            if (i < n - branch_lengh) {
                if (i == n - branch_lengh * 2 - num_middle && changed) {
                    std::cout << '|';
                }
                else {
                    std::cout << ' ';
                }
            }
            else {
                if (direction == 1 && i == n - branch_lengh) {
                    std::cout << '\\';
                }
                else if (direction == 2 && i == n - branch_lengh) {
                    std::cout << '/';
                }
                else {
                    std::cout << '-';
                }
            }
        }
        std::cout << "№" << subroot->number << '*' << subroot->height << std::endl;
        // после углубления вправо просматриваем уже левые поддеревья
        output_tree_height(subroot->left, n + branch_lengh + num_middle, 1, (bool)(direction != 1));
    }
}

void clear_flights(flight*& subroot) {
    if (subroot != nullptr) {
        clear_flights(subroot->right); // углубление максимально вправо
        clear_flights(subroot->left); // после углубления вправо просматриваем уже левые поддеревья
        /* Когда обе функции завершают работу(то есть очищены все поддеревья, или функции пришли к листу),
        то удаляем корень поддерева */
        delete subroot;
        subroot = nullptr;
    }
}

bool tree_accuracy(flight* subroot) {
    bool accuracy = true;
    if (subroot != nullptr) {
        accuracy = tree_accuracy(subroot->right); // углубление максимально вправо
        if (!accuracy) {
            return false;
        }
        accuracy = tree_accuracy(subroot->left); // после углубления вправо просматриваем уже левые поддеревья
        if (!accuracy) {
            return false;
        }
        /* Когда обе функции завершают работу(то есть проверены все поддеревья),
        то проверяем корень поддерева */
        if (subroot->prev == subroot) {
            return false;
        }
        
        if (subroot->right != nullptr) {
            if ((subroot->right)->prev != subroot) {
                return false;
            }
            else if (subroot->right == subroot) {
                return false;
            }
            else if (strcmp((subroot->right)->number, subroot->number) < 0) {
                return false;
            }
        }
        if (subroot->left != nullptr) {
            if ((subroot->left)->prev != subroot) {
                return false;
            }
            else if (subroot->left == subroot) {
                return false;
            }
            else if (strcmp((subroot->left)->number, subroot->number) > 0) {
                return false;
            }
        }
    }
    return true;
}

void SmallLeftRotate(flight*& root) {
    if (root == nullptr) {
        return;
    }
    flight* rightTree = root->right;
    if (rightTree == nullptr) {
        return;
    }
    root->right = rightTree->left;
    if ((rightTree->left) != nullptr) {
        (rightTree->left)->prev = root;
    }
    rightTree->left = root;
    rightTree->prev = root->prev;
    root->prev = nullptr;
    if (root->prev != nullptr) {
        if (strcmp(root->number, (root->prev)->number) < 0) {
            (root->prev)->left = rightTree;
        }
        else if (strcmp(root->number, (root->prev)->number) > 0) {
            (root->prev)->right = rightTree;
        }
        else {
            (root->prev)->left = rightTree;
        }
    }
    root->prev = rightTree;
    root = rightTree;
}

void SmallRightRotate(flight*& root) {
    if (root == nullptr) {
        return;
    }
    flight* leftTree = root->left;
    if (leftTree == nullptr) {
        return;
    }
    root->left = leftTree->right;
    if ((leftTree->right) != nullptr) {
        (leftTree->right)->prev = root;
    }
    flight* rootprev = root->prev;
    leftTree->right = root;
    leftTree->prev = rootprev;
    root->prev = nullptr;
    root->prev = leftTree;
    if (rootprev != nullptr) {
        if (strcmp(root->number, rootprev->number) < 0) {
            rootprev->left = leftTree;
        }
        else if (strcmp(root->number, rootprev->number) > 0) {
            rootprev->right = leftTree;
        }
        else {
            rootprev->left = leftTree;
        }
    }
    root = leftTree;
}

void Balance(flight*& root) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
        return;
    }
    int delta = delta_height(root->left, root->right);
    if (abs(delta) < 2) { // если балансировать не надо
        height_recalculation(root); // но до этого дерево могло в последний раз сбалансироваться
        return;
    }
    flight* q = nullptr;
    flight* s = nullptr;
    if (delta > 0) { // левое поддерево выше правого (левое определённо существует) БОЛЬШОЕПРАВОЕ
        q = root->left;
        s = q->right;
        if (s != nullptr) {
            if (q->left == nullptr || (q->left != nullptr && s->height > (q->left)->height)) { // s > D
                SmallRightRotate(q);
                //output_tree(root, 0, 0);
                SmallRightRotate(root);
            }
            else { // s < D
                SmallRightRotate(root);
            }
        }
        else {
            SmallRightRotate(root);
        }
    }
    else if (delta < 0) { // правое поддерево выше левого БОЛЬШОЕЛЕВОЕ
        q = root->right;
        s = q->left;
        if (s != nullptr) {
            if (q->right == nullptr || (s->height > (q->right)->height)) {
                SmallRightRotate(q);
                SmallLeftRotate(root);
            }
            else {
                SmallLeftRotate(root);
            }
        }
        else {
            SmallLeftRotate(root);
        }
    }
    height_recalculation(root);
    //flight* current_joint = root;
    //int u = current_joint->height;
    //while (current_joint != nullptr) { //подсчёт высоты обратным проходом
    //    if (u > current_joint->height) {
    //        current_joint->height = u;
    //    }
    //    u++;
    //    current_joint = current_joint->prev;
    //}
}

int delta_height(const flight* const Left, const flight* const Right) {
    if (Left == nullptr && Right == nullptr) {
        return 0;
    }
    else if (Left == nullptr) {
        return -Right->height;
    }
    else if (Right == nullptr) {
        return Left->height;
    }
    else {
        return Left->height - Right->height;
    }
}

int height_recalculation(flight*& subroot) {
    if (subroot != nullptr) {
        if (subroot->left == nullptr && subroot->right == nullptr) {
            subroot->height = 1;
            return 1;
        }
        int leftH = height_recalculation(subroot->left);
        int rightH = height_recalculation(subroot->right);
        subroot->height = ((leftH > rightH)? leftH : rightH) + 1;
        return subroot->height;
    }
    return 0;
}

void FullBalance(flight*& subroot) {
    if (subroot != nullptr) {
        FullBalance(subroot->right);
        FullBalance(subroot->left);
        Balance(subroot);
        //height_recalculation(subroot);
        //output_tree(to_root(subroot), 0, 0);
        //cout <<  endl;
        //this_thread::sleep_for(100ms);
        //cout << "1" << flush;
    }
}

bool is_tree_empty(const flight* const root) {
    if (root == nullptr) {
        return true;
    }
    return false;
}

bool is_balanced(const flight* subroot) {
    if (subroot != nullptr) {
        if (subroot->height < 2) {
            return true;
        }
        bool rightbalanced = is_balanced(subroot->right);
        bool leftbalanced = is_balanced(subroot->left);
        if (abs(delta_height(subroot->left, subroot->right)) > 1) {
            return false;
        }
        else if (!rightbalanced || !leftbalanced) {
            return false;
        }
    }
    return true;
}

flight* to_root(flight* subroot) {
    if (subroot != nullptr) { 
        flight* current = subroot;
        while (current->prev != nullptr) {
            current = current->prev;
        }
        return current;
    }
    else {
        return nullptr;
    }
}

void push_back(found_flights *& ffl, flight*& fl) {
    if (fl == nullptr) {
        return;
    }
    found_flights* new_ffl = new found_flights;
    new_ffl->fl = new flight;
    found_flights* cur_ffl = ffl;
    copy_element(*fl, new_ffl->fl);
    if (ffl == nullptr) {
        ffl = new_ffl;
    }
    else {
        while (cur_ffl->next != nullptr) {
            cur_ffl = cur_ffl->next;
        }
        cur_ffl->next = new_ffl;
    }
}

void copy_element(const flight& orig, flight*& cfl) {
    strcpy_s(cfl->number, orig.number);
    cfl->company = orig.company;
    cfl->departure = orig.departure;
    cfl->arriving = orig.arriving;
    cfl->dep_time = orig.dep_time;
    cfl->arv_time = orig.arv_time;
    cfl->places = orig.places;
    cfl->free = orig.free;
}

void output_flights(const flight* const subroot) {
    if (subroot != nullptr) {
        char* nmbr = new char[8] {};
        char* source = (char*)subroot->number;
        // углубление максимально вправо
        output_flights(subroot->left);
        //вывод листа
        strncpy_s(nmbr, 8, source, 3);
        nmbr[3] = '-'; nmbr[4] = source[3];
        nmbr[5] = source[4]; nmbr[6] = source[5]; nmbr[7] = '\0';
        cout << left << setw(2) << "+-" << setfill('-') << setw(43) << right << '+' << setfill(' ') << endl;
        cout << setw(22) << left << "| Рейс №" << setw(22) << nmbr << '|' << endl;
        cout << setw(22) << left << "| Компания " << setw(22) << subroot->company << '|' << endl;
        cout << setw(22) << left << "| Отправляется из: " << setw(22) << subroot->departure << '|' << endl;
        cout << setw(22) << left << "| В: " << setw(22) << subroot->arriving << '|' << endl;
        cout << setw(22) << left << "| Время отправления: " << setw(22) << subroot->dep_time << '|' << endl;
        cout << setw(22) << left << "| Время прибытия: " << setw(22) << subroot->arv_time << '|' << endl;
        cout << setw(22) << left << "| Всего " << setw(4) << subroot->places << setw(18) << " мест," << '|' << endl;
        cout << setw(22) << left << "| из которых " << setw(4) << subroot->free << setw(18) << " свободно." << '|' << endl;
        cout << left << setw(2) << "+-" << setfill('-') << setw(43) << right << '+' << setfill(' ') << endl;
        // после углубления вправо просматриваем уже левые поддеревья
        output_flights(subroot->right);
        delete[] nmbr;
    }
}

void output_flights(found_flights* a) {
    if (a == nullptr) {
        return;
    }
    found_flights* b = a;
    char* nmbr = new char[8]{};
    while(b != nullptr) {
        strncpy_s(nmbr, 8, b->fl->number, 3);
        nmbr[3] = '-'; nmbr[4] = b->fl->number[3];
        nmbr[5] = b->fl->number[4]; nmbr[6] = b->fl->number[5]; nmbr[7] = '\0';
        cout << left << setw(2)  << "+-" << setfill('-') << setw(43) << right << '+' << setfill(' ') << endl;
        cout << setw(22) << left << "| Рейс №" << setw(22) << nmbr << '|' << endl;
        cout << setw(22) << left << "| Компания " << setw(22) << b->fl->company << '|' << endl;
        cout << setw(22) << left << "| Отправляется из: " << setw(22) << b->fl->departure << '|' << endl;
        cout << setw(22) << left << "| В: " << setw(22) << b->fl->arriving << '|' << endl;
        cout << setw(22) << left << "| Время отправления: " << setw(22) << b->fl->dep_time << '|' << endl;
        cout << setw(22) << left << "| Время прибытия: " << setw(22) << b->fl->arv_time << '|' << endl;
        cout << setw(22) << left << "| Всего " << setw(4) << b->fl->places << setw(18) << " мест," << '|' << endl;
        cout << setw(22) << left << "| из которых " << setw(4) << b->fl->free << setw(18) << " свободно." << '|' << endl;
        cout << left << setw(2)  << "+-" << setfill('-') << setw(43) << right << '+' << setfill(' ') << endl;
        b = b->next;
    }
    delete[] nmbr;
}

