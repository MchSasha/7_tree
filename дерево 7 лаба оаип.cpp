#include <iostream>
#include <vector>
#include <ctime>
#include <map>
using namespace std;

struct arr {
    int num;
    string fio;
};
struct tree {
    int num;
    string fio;
    tree* left;
    tree* right;
} *t, * root, * anc;

tree* leaf(int num, string fio) {
    tree* t = new tree;
    t->num = num;
    t->fio = fio;
    t->left = t->right = NULL;
    return t;
}

void add_leaf(tree*& root, int key_n, string key_f, vector<arr>& list) {
    bool find = true;
    t = root;
    while (t && find) {
        anc = t;
        if (key_n == t->num) {
            find = false;
            cout << "Already exists!\n";
        }
        else
            if (key_n < t->num) t = t->left;
            else t = t->right;
    }
    if (find) {
        t = leaf(key_n, key_f);
        if (key_n < anc->num) anc->left = t;
        else anc->right = t;
    }

}
void crt_tree(tree*& root, vector <arr> list) {
    if (!list.size()) {
        cout << "Array isn't created yet!\n";
        return;
    }
    if (root) {
        cout << "Tree is already created...\n";
        return;
    }
    for (arr i : list) {
        if (!root)
            root = leaf(i.num, i.fio);
        else add_leaf(root, i.num, i.fio, list);
    }
}

void gen_pass(vector <arr>& list) {
    cout << "num of el\n"; int k; cin >> k;
    for (int i = 0; i < k; i++) {
        arr item;
        item.num = rand() % 150 + 100;
        item.fio = rand() % 25 + 65;
        for (int i = 0; i < 3; i++)
            item.fio += rand() % 25 + 97;
        list.push_back(item);
    }
    for (arr i : list)
        cout << i.fio << ' ' << i.num << endl;
}

void show(tree* root, int level) {
    string str;
    if (root) {
        show(root->right, level + 1); // Правое поддерево
        for (int i = 0; i < level; i++) str = str + " ";
        cout << str << level << "_ " << root->num << '(' << root->fio << ')' << '\n';
        show(root->left, level + 1); // Левое поддерево
    }
}

void balance(tree*& root, vector <arr>& list, int level) {

    int step = list.size() / 4;
    root = leaf(list[list.size() / 2].num, list[list.size() / 2].fio);
    list[list.size() / 2].num = 0;
    while (step >= 1) {
        for (int i = 0; i + step < list.size(); i += step) {
            if (list[i + step].num)
                add_leaf(root, list[i + step].num, list[i + step].fio, list);
            list[i + step].num = 0;
        }
        step /= 2;
    }
    add_leaf(root, list[0].num, list[0].fio, list);
}

int search(tree* root, int key) {
    t = root;
    int n = 0;
    while (t) {
        if (t->num == key) {
            cout << "The owner: " << t->fio << endl;
            n++;
            if (t->left == NULL && t->right == NULL)
                return 1;
            if (t->left == NULL || t->right == NULL)
                return 2;
            else return 3;
        }
        if (key < t->num)
            t = t->left;
        else t = t->right;
    }
    if (!n) {
        cout << "There is no such a passport\n";
        return -1;
    }
    return 0;
}

tree* max_left(tree* key, tree*& root) {
    tree* ancc = new tree;
    t = key; ///
    ancc = t;  /// 
    t = t->left; ////
    while (t->right) {
        ancc = t; /// 
        t = t->right;///
    }
    if (t->left && ancc != key)//
        ancc->right = t->left;
    if (!t->left && ancc != key) ancc->right = NULL;


    t->right = key->right;
    if (t == key->right)
        t->right = NULL;

    if (t != key->left)
        t->left = key->left;

    return t;
}

void rootlr(tree* root)
{
    if (!root)
        return;
    cout << root->num << " " << '(' << root->fio << ')' << '\n';
    rootlr(root->left);   //рекурсивный вызов левого поддерева
    rootlr(root->right);  //рекурсивный вызов правого поддерева
}

void lrootr(tree* root)
{
    if (!root)
        return;
    lrootr(root->left);   //рекурсивный вызов левого поддерева
    cout << root->num << " " << '(' << root->fio << ')' << '\n';
    lrootr(root->right);  //рекурсивный вызов правого поддерева
}
void to_rr(tree* root, vector <arr>& list) {
    if (!root)
        return;
    to_rr(root->left, list);   //рекурсивный вызов левого поддерева
    arr temp;
    temp.num = root->num;
    temp.fio = root->fio;
    list.push_back(temp);
    to_rr(root->right, list);
}
void lrroot(tree* root) {
    if (!root)
        return;
    lrroot(root->left);
    lrroot(root->right);
    cout << root->num << " " << '(' << root->fio << ')' << '\n';
}

void task(tree* root, map<int, int>& numb, int lvl)
{
    if (!root->left && !root->right) numb[lvl]++;
    else numb[lvl] = 0;
    if (root->left)  task(root->left, numb, lvl + 1);
    if (root->right) task(root->right, numb, lvl + 1);
}

int menu() {
    cout << "MENU" << endl;
    cout << "Choose actions from the list below.. " << endl;
    cout << "0. Exit" << '\n'
        << "1. Generate the array of passports" << '\n'
        << "2. Create the tree from the created array" << '\n'
        << "3. Add a new record in the tree" << '\n'
        << "4. Show the tree" << '\n'
        << "5. Balance the tree" << '\n'
        << "6. Find the information" << '\n'
        << "7. Delete " << '\n'
        << "8. Show the tree Root-Left-Right\n"
        << "9. Show the tree Left-Root-Right\n"
        << "10. Show the tree Left-Right-Root\n"
        << "11. Task" << '\n';
    int n;
    cin >> n;
    return n;
}


int main()
{
    srand(time(NULL));
    vector <arr> list{};
    int n; string f; bool l = 0; bool r = 0; map<int, int> numb;

    while (true) {
        switch (menu()) {
        case 1:
            cout << "...GENERATING THE ARRAY...\n";
            gen_pass(list);
            cout << '\n'; break;
        case 2:
            cout << "...CREATING THE TREE FROM THE ARRAY...\n";
            crt_tree(root, list);
            cout << '\n'; break;
        case 3:
            cout << "...ADD A NEW RECORD IN THE TREE...\n";
            if (!root) {
                cout << "There is no tree!\n";
                break;
            }
            cout << "Enter the number of the passport...\n";
            cin >> n;
            cout << "Enter full name of the owner...\n";
            cin >> f;
            add_leaf(root, n, f, list); show(root, 0);
            cout << '\n'; break;
        case 4:
            cout << "...Show the tree...\n";
            if (!root) {
                cout << "There is no tree!\n";
                break;
            }
            show(root, 0);
            cout << '\n'; break;
        case 5:
            cout << "...Balance the tree...\n";
            if (!root) {
                cout << "There is no tree!\n";
                break;
            }
            list.clear(); to_rr(root, list);//rerecord(root, list);
            balance(root, list, 0); show(root, 0);
            cout << '\n'; break;
        case 6:
            cout << "...SEARCHING...\n";
            if (!root) {
                cout << "There is no tree!\n";
                break;
            }
            cout << "Enter the number of the passport...\n";
            int key;
            cin >> key;
            search(root, key);
            cout << '\n'; break;
        case 7:
            cout << "...DELETE...\n";
            if (!root) {
                cout << "There is no tree!\n";
                break;
            }
            cout << "Entere the number of the passport you want to delete...\n";
            cin >> key;
            n = search(root, key);
            ///del(key, root, n);

            t = root;
            while (t) {
                if (t->num == key) {
                    if (n == 1) {                               ///leaf
                        if (anc->left && anc->left->num == key)
                            anc->left = NULL;
                        else anc->right = NULL;
                        break;
                    }
                    if (n == 2) {  /// 1/2 leaf
                        /// 
                        if (key == root->num)
                        {
                            if (root->right)
                                root = root->right;
                            else root = root->left;
                            break;// return;
                        }
                        ///root-1/2 leaf

                        if (anc->left && t->left && anc->left->num == key)
                            anc->left = t->left;
                        if (anc->right && t->left && anc->right->num == key)
                            anc->right = t->left;
                        if (anc->left && t->right && anc->left->num == key)
                            anc->left = t->right;
                        if (anc->right && t->right && anc->right->num == key)
                            anc->right = t->right;
                        ///return;
                    }

                    if (n == 3) {
                        if (r)
                            anc->right = max_left(t, root);
                        if (l)
                            anc->left = max_left(t, root);
                        if (key == root->num)
                            root = max_left(t, root);
                        break;// return;

                    }
                }
                r = 0; l = 0;
                anc = t;
                if (key < t->num) {
                    t = t->left;
                    l++;
                }
                else {
                    t = t->right;
                    r++;
                }
            }
            show(root, 0);
            cout << "Deleted\n";  break;
        case 8:
            cout << "...ROOT-LEFT-RIGHT...\n";
            if (!root) {
                cout << "There is no tree!\n";
                break;
            }
            rootlr(root);
            cout << '\n'; break;
        case 9:
            cout << "...LEFT-ROOT-RIGHT...\n";
            if (!root) {
                cout << "There is no tree!\n";
                break;
            }
            lrootr(root);
            cout << '\n'; break;
        case 10:
            cout << "...LEFT-RIGHT-ROOT...\n";
            if (!root) {
                cout << "There is no tree!\n";
                break;
            }
            lrroot(root);
            cout << '\n'; break;
        case 11:
            cout << "...COUNTING THE NUMBER OF LEIVES...\n";
            if (!root) {
                cout << "There is no tree!\n";
                break;
            }
            task(root, numb, 0);
            for (auto i : numb)
            {
                cout << i.first << " : " << i.second << "\n";
            }
            numb.clear();
            cout << "\n"; break;

        case 0:
            cout << "...EXIT...\n";
            return 0;
        }
    }
}


//расческа

    /*double factor = 1.2473309;
    int step = list.size() - 1;
    while (step >= 1)
    {
        for (int i = 0; i + step < list.size(); i++)
        {
            if (list[i].num > list[i + step].num)
                swap(list[i], list[i + step]);
        }
        step /= factor;
    }*/

    /*void rerecord(tree* root, vector <arr>& list) {
        if (root == NULL)
            return;
        arr temp;
        temp.fio = root->fio;
        temp.num = root->num;
        list.push_back(temp);
        rerecord(root->left, list);
        rerecord(root->right, list);
    }*/


    //tree* max_left_r(tree* key, tree*& root) {
    //    tree* ancc = new tree;
    //    t = key; ///
    //    ancc = t;  /// 
    //    t = t->left; ////
    //    while (t->right) {
    //        ancc = t; /// 
    //        t = t->right;///
    //    }
    //    if (t->left && ancc != key)//
    //        ancc->right = t->left;
    //    if (!t->left && ancc != key) ancc->right = NULL;
    //
    //
    //    t->right = key->right;
    //    if (t == key->right)
    //        t->right = NULL;
    //
    //    if (t != key->left)
    //        t->left = key->left;
    //
    //    return t;
    //}