#include <main.h>

#include <tree.h>

int add_element(flight*& root, const flight& data) {
    flight* new_joint = new flight{};
    strcpy(new_joint->number, data.number);
    new_joint->company = data.company;
    new_joint->departure = data.departure;
    new_joint->arriving = data.arriving;
    new_joint->dep_time = data.dep_time;
    new_joint->arv_time = data.arv_time;
    new_joint->places = data.places;
    new_joint->free = data.free;

    flight* current_joint = root;
    flight* prev_joint = nullptr;
    int cur_number = 0;
    int new_number = std::stoi(data.number);
    
    if (root == nullptr) {
        root = new_joint;
    }
    else {
        while (current_joint != nullptr) { // перемещение до решающего узла
            prev_joint = current_joint;
            cur_number = std::stoi(current_joint->number);
            if (new_number < cur_number) {
                current_joint = current_joint->left;
            }
            else if (new_number > cur_number) {
                current_joint = current_joint->right;
            }
            else if (current_joint->left != nullptr && std::stoi((current_joint->left)->number) == new_number) {
                return 1; // уже существует
            }
            else {
                break;
            }
        }
        if (current_joint == nullptr) { //решающий узел
            current_joint = prev_joint;
        }
        cur_number = std::stoi(current_joint->number);
        new_joint->prev = current_joint;
        if (new_number < cur_number) {
            current_joint->left = new_joint;
        }
        else if (new_number > cur_number) {
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

int delete_element(flight*& root, const int number) {
    if (root == nullptr) {
        return 1;
    }
    flight* current_joint = root;
    flight* prev_joint = nullptr;
    flight* maxleft = nullptr;
    int cur_number = 0;
    while (current_joint != nullptr) { // дойти до узла(или пустоты) после искомого узла
        prev_joint = current_joint;
        cur_number = std::stoi(current_joint->number);
        if (number < cur_number) {
            current_joint = current_joint->left;
        }
        else if (number > cur_number) {
            current_joint = current_joint->right;
        }
        else if (current_joint->left != nullptr && std::stoi((current_joint->left)->number) == number) {
            current_joint = current_joint->left;
        }
        else {
            break;
        }
    }
    current_joint = prev_joint; //рассмотреть нужный удаляемый узел
    if (number != std::stoi(current_joint->number)) {
        return 2; // не найдено
    }
    else {
        maxleft = find_maxleft(current_joint); //левый максимум поддерева
        if (maxleft == nullptr) { //если правой ветви в левом поддереве нет
            if (current_joint->prev != nullptr) { //если удаляемый не корень
                prev_joint = current_joint->prev;
                if (number < std::stoi(prev_joint->number)) {
                    prev_joint->left = current_joint->left;
                    if (current_joint->left != nullptr) {
                        (current_joint->left)->prev = prev_joint;
                        (current_joint->left)->right = current_joint->right;
                        if (current_joint->right != nullptr) {
                            (current_joint->right)->prev = current_joint->left;
                        }
                    }
                }
                else if (number > std::stoi(prev_joint->number)) {
                    prev_joint->right = current_joint->left;
                    if (current_joint->left != nullptr) {
                        (current_joint->left)->prev = prev_joint;
                        (current_joint->left)->right = current_joint->right;
                        if (current_joint->right != nullptr) {
                            (current_joint->right)->prev = current_joint->left;
                        }
                    }
                }
                else { // data==prev
                    prev_joint->left = current_joint->left;
                    if (current_joint->left != nullptr) {
                        (current_joint->left)->prev = prev_joint;
                        (current_joint->left)->right = current_joint->right;
                        if (current_joint->right != nullptr) {
                            (current_joint->right)->prev = current_joint->left;
                        }
                    }
                    
                }
                delete current_joint;
                current_joint = nullptr;
            }
            else {// если одинокий корень
                delete current_joint;
                root = nullptr;
            }
        }
        else { // если правая ветвь в левом поддереве есть
            prev_joint = maxleft->prev; // родительский узел максимума
            
            if (maxleft->left != nullptr) { // если у левого максимума есть левая ветвь
                prev_joint->right = maxleft->left;
                (maxleft->left)->prev = prev_joint;
            }
            
            maxleft->right = current_joint->right;
            prev_joint = current_joint->prev; // родительский узел удаляемого узла
            if (prev_joint != nullptr) { //если удаляемый не корень
                if (number < std::stoi(prev_joint->number)) {
                    prev_joint->left = maxleft;
                }
                else if (number > std::stoi(prev_joint->number)) {
                    prev_joint->right = maxleft;
                }
                else {
                    prev_joint->left = maxleft;
                }
            }
            if (maxleft->prev != nullptr) { // если у заменяющего есть предок
                if (number < std::stoi(maxleft->prev->number)) {
                    (maxleft->prev)->left = maxleft->left;
                }
                else if (number > std::stoi(maxleft->prev->number)) {
                    (maxleft->prev)->right = maxleft->left;
                }
                else {
                    (maxleft->prev)->left = maxleft->left;
                }
            }
            maxleft->left = current_joint->left;
            maxleft->prev = current_joint->prev;
            delete current_joint;
            current_joint = nullptr;
            if(maxleft->left != nullptr) {
                (maxleft->left)->prev = maxleft;
            }
            if(maxleft->right != nullptr) {
                (maxleft->right)->prev = maxleft;
            }
            if (maxleft->prev == nullptr) {
                root = maxleft;
            }
        }
    }
    height_recalculation(root);
    while(!is_balanced(root)) {
        FullBalance(root);
        height_recalculation(root);
    }
    return 0;
}

bool is_exists(const flight* subroot, const std::string number) {
    if (subroot != nullptr) {
        if (is_exists(subroot->left, number)) {
            return true;
        }
        if (strcmp(subroot->number, number.c_str()) == 0) {
            return true;
        }
        if (is_exists(subroot->right, number)) {
            return true;
        }
    }
    return false;
}

flight* find_element(flight* root, const int number) {
    flight* prev_joint = nullptr;
    flight* current_joint = root;
    int cur_number = 0;
    if (root == nullptr) {
        return nullptr;
    }
    else {
        while (current_joint != nullptr) { // перемещение до нужного узла
            prev_joint = current_joint;
            cur_number = std::stoi(current_joint->number);
            if (number < cur_number) {
                current_joint = current_joint->left;
            }
            else if (number > cur_number) {
                current_joint = current_joint->right;
            }
            else if (current_joint->left != nullptr && std::stoi((current_joint->left)->number) == number) {
                current_joint = current_joint->left;
            }
            else { // найден самый левый нужный узел
                break;
            }
        }
        if (current_joint == nullptr) { //если нужный узел - лист, то перемещаемся из пустоты в него
            current_joint = prev_joint;
        }
        if (std::stoi(current_joint->number) != number) {
            return nullptr;
        }
    }
    return current_joint;
}

bool find_elements_bytext(flight* subroot, found_flights*& ffl, const std::string text) { //обратный
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
    int data = std::stoi(subroot->number);
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
    int data = std::stoi(subroot->number);
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

void output_flights(const flight* const subroot) {
    if (subroot != nullptr) {
        char* nmbr = new char[8]{};
        char* source = (char*)subroot->number;
        // углубление максимально вправо
        output_flights(subroot->left); 
        //вывод листа
        strncpy(nmbr, source, 3);
        nmbr[3] = '-'; nmbr[4] = source[3];
        nmbr[5] = source[4]; nmbr[6] = source[5]; nmbr[7] = '\0';
        std::cout << std::setw(20) << std::left << "Рейс №" << nmbr << std::endl;
        std::cout << std::setw(20) << std::left << "Компания: " << subroot->company << std::endl;
        std::cout << std::setw(20) << std::left << "Отправляется из: " << subroot->departure << std::endl;
        std::cout << std::setw(20) << std::left << "В: " << subroot->arriving << std::endl;
        std::cout << std::setw(20) << std::left << "Время отправления: " << subroot->dep_time << std::endl;
        std::cout << std::setw(20) << std::left << "Время прибытия: " << subroot->arv_time << std::endl;
        std::cout << std::setw(20) << std::left << "Всего " << subroot->places << " мест, из которых " << subroot->free << " свободно." << std::endl;
        // после углубления вправо просматриваем уже левые поддеревья
        output_flights(subroot->right); 
        delete[] nmbr;
    }
}

void output_flights_height(flight *subroot) {
    if (subroot != nullptr) {
        // углубление максимально вправо
        output_flights_height(subroot->left); 
        //вывод высоты подкорня
        std::cout << "Рейс №" << subroot->number << std::endl;
        std::cout << subroot->height << std::endl;
        // после углубления вправо просматриваем уже левые поддеревья
        output_flights_height(subroot->right); 
    }
}

void output_tree_height(flight *subroot, long int n, const int direction, bool changed) {
    if (subroot != nullptr) {
        const int num_middle = ((int)log10(subroot->height) + 7) / 2;
        const int branch_lengh = 5;
        // углубление максимально вправо
        output_tree_height(subroot->right, n + branch_lengh + num_middle, 2, (bool)(direction != 2)); 
        //вывод высоты подкорня
        
        for (long i = 0; i < n; i++) {
            if (i < n - branch_lengh) {
                if (i == n - branch_lengh*2 - num_middle && changed) {
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
        std::cout << "№" << subroot->number << ' ' << subroot->height << std::endl;
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
            else if (std::stoi((subroot->right)->number) < std::stoi(subroot->number)) {
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
            else if (std::stoi((subroot->left)->number) > std::stoi(subroot->number)) {
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
        if (std::stoi(root->number) < std::stoi((root->prev)->number)) {
            (root->prev)->left = rightTree;
        }
        else if (std::stoi(root->number) > std::stoi((root->prev)->number)) {
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
        if (std::stoi(root->number) < std::stoi(rootprev->number)) {
            rootprev->left = leftTree;
        }
        else if (std::stoi(root->number) > std::stoi(rootprev->number)) {
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
        //std::this_thread::sleep_for(100ms);
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

bool is_num_correct(const std::string number, const int num_size) {
    if (number.length() > num_size) {
        return false;
    }
    for (int i=0; i< num_size; i++) {
        if (!isdigit(number[i])) {
            if (number[i] == '-' && i == 3) {
                continue;
            }
            return false;
        }
    }
    return true;
}

bool compare_fragments(const std::string& line, const std::string& need) { // Боуэра Мура
    if (need.length() > line.length()) {
        return false;
    }
    int st = 0;
    int c2 = 0;
    int i = 0;
    int s1 = 0;
    int nlen = need.length();
    int* stopsymb = new int[nlen]{};
    // формирование таблицы смещений
    for (int c1 = nlen - 2; c1 >= 0; c1--) { // сравнение текущего с правой от него частью слова
        if (need[c1] == need[nlen - 1] && stopsymb[nlen - 1] == 0) { // если символ в конце слова есть и в другом его месте
            stopsymb[nlen - 1] = nlen - c1 - 1;
            stopsymb[c1] =       nlen - c1 - 1;
            continue;
        }
        for (c2 = c1 + 1; c2 < nlen; c2++) { // если символ уже был просчитан ранее
            if (need[c2] == need[c1]) {
                stopsymb[c1] = stopsymb[c2];
                break;
            }
        }
        if (c2 == nlen && stopsymb[c1] == 0) { // ...иначе запись расстояния до конца слова
            stopsymb[c1] = nlen - c1 - 1;
        }
    }
    //for (int y = 0; y < nlen; y++) {
    //    std::cout << stopsymb[y] << ' ';
    //} 
    //std::cout << std::endl << std::endl;
    while (st < line.length() - nlen) {
        i = 0;
        //std::cout << st << std::endl;
        for (i = nlen - 1; i >= 0; i--) { // сравнение с конца слова
            if (line[i + st] != need[i]) { // если не совпало
                for (s1 = 0; s1 < nlen; s1++) { // ищется несовпавший в предложении символ в таблице
                    if (line[i + st] == need[s1]) {
                        break;
                    }
                } 
                if (s1 < nlen) { // если такой символ есть в таблице
                    st += stopsymb[s1];
                }
                else {
                    st += nlen;
                }
                break;
            }
        }
        if (i == -1) {
            delete[] stopsymb;
            return true;
        }
    }
    delete[] stopsymb;
    return false;
}

void push_back(found_flights *& ffl, flight*& fl) {
    if (fl == nullptr) {
        return;
    }
    found_flights* new_ffl = new found_flights;
    found_flights* cur_ffl = ffl;
    copy_element(*fl, new_ffl->fl);
    if (ffl == nullptr) {
        ffl = new_ffl;
    }
    else {
        while (ffl->next != nullptr) {
            cur_ffl = ffl->next;
        }
        ffl->next = new_ffl;
    }
}

void copy_element(const flight& orig, flight*& cfl) {
    strcpy(cfl->number, orig.number);
    cfl->company = orig.company;
    cfl->departure = orig.departure;
    cfl->arriving = orig.arriving;
    cfl->dep_time = orig.dep_time;
    cfl->arv_time = orig.arv_time;
    cfl->places = orig.places;
    cfl->free = orig.free;
}

void output_flights(found_flights* a) {
    if (a == nullptr) {
        return;
    }
    found_flights* b = a;
    char* nmbr = new char[8]{};
    while(b != nullptr) {
        strncpy(nmbr, a->fl->number, 3);
        nmbr[3] = '-'; nmbr[4] = a->fl->number[3];
        nmbr[5] = a->fl->number[4]; nmbr[6] = a->fl->number[5];
        std::cout << std::setw(20) << std::left << "Рейс №" << nmbr << std::endl;
        std::cout << std::setw(20) << std::left << "Компания: " << a->fl->company << std::endl;
        std::cout << std::setw(20) << std::left << "Отправляется из: " << a->fl->departure << std::endl;
        std::cout << std::setw(20) << std::left << "В: " << a->fl->arriving << std::endl;
        std::cout << std::setw(20) << std::left << "Время отправления: " << a->fl->dep_time << std::endl;
        std::cout << std::setw(20) << std::left << "Время прибытия: " << a->fl->arv_time << std::endl;
        std::cout << std::setw(20) << std::left << "Всего " << a->fl->places << " мест, из которых " 
        << a->fl->free << " свободно." << std::endl << std::endl;
        b = b->next;
    }
    delete[] nmbr;
}
