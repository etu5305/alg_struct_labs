#include "rb.h"

RB::RB()
{
  count = 0;
  root = 0;
}

bool RB::bs_find(Node* &search, int key)
{
    Node* search_node = this->root;

    while(1)
    {
        if(search_node == 0)
            return 0;
        else
        {
            if(search_node->key == key)
            {
                search = search_node;
                return 1;
            }
            else
            {
                search = search_node;
                search_node = (key > search_node->key) ? search_node->right : search_node->left;
            }
        }
    }
}

bool RB::insert(int key)
{
    Node* search_node;

    if( this->root == 0 ) // Если дерево пустое
    {
        this->root = new Node(key);
        if( this->root != 0 )
        {
            count = 1;
            return 1;
        }
        return 0;
    }
    else if( bs_find(search_node, key) == 0 ) // Дерево не пустое | search_node = последний не пустой узел
    {
        if( key > search_node->key ) // Ключ больше родителя
        {
            search_node->right = new Node(key, search_node);
            if( search_node->right == 0 )
                return 0;
            count++;
            return 1;
        }
        else // Ключ меньше родительского
        {
            search_node->left = new Node(key, search_node);
            if( search_node->left == 0 )
                return 0;
            count++;
            return 1;
        }
    }
    return 1; // Узел с таким ключем уже существует
}

bool RB::remove(int key)
{
    Node* search_node;
    Node *tmp_node;
    if( this->bs_find(search_node, key) == 1) // узел с ключем key существует | search_node = узел с ключем key
    {
        /* Случаи:
        0) удаляем корень
        1) нету дочерних узлов
        2) один дочерний узел
        3) два дочерних узла
         1. левый узел правого поддерева отсутствует
         2. левый узел правого поддерева присутствует
        */

        if( search_node->parent == 0 ) // (0)
        {
            tmp_node = ( search_node->right != 0 ) ? search_node->right : search_node->left;

            if( tmp_node == 0 ) // корень - последний узел
            {
                this->count = 0;
                delete search_node;
                return 1;
            }

            search_node->key = tmp_node->key;
            search_node->left = tmp_node->left;
            search_node->right = tmp_node->right;

            delete tmp_node;
        }
        if( search_node->left == 0 && search_node->right == 0 ) // (1)
        {
            if( search_node->key > search_node->parent->key )
                search_node->parent->right = 0;
            else
                search_node->parent->left = 0;

            delete search_node;
        }
        else if( search_node->left != 0 && search_node->right != 0 ) // (3)
        {
            if( search_node->right->left == 0 ) // левый узел правого поддерева отсутствует
            {
                tmp_node = search_node->right;

                search_node->key = tmp_node->key;
                search_node->right = tmp_node->right;
            }
            else
            {
                tmp_node = search_node->right->left;

                // ищем самый левый узел правого поддерева
                while( tmp_node->left != 0 )
                    tmp_node = tmp_node->left;

                tmp_node->parent->left = 0;

                search_node->key = tmp_node->key;
            }

            delete tmp_node;
        }
        else // (2)
        {
            if( search_node->right != 0 )
                tmp_node = search_node->right;
            else
                tmp_node = search_node->left;

            search_node->key = tmp_node->key;
            search_node->left = tmp_node->left;
            search_node->right = tmp_node->right;

            delete tmp_node;
        }

        count--;
        return 1;
    }

    return 0;
}

bool RB::find(int key)
{
    static Node* node; // static чтобы в стеке места не занимала при каждом вызове
    return bs_find(node, key);
}

void RB::printnode(int key, int h)
{
    for (int i = 0; i < h; i++)
        std::cout << "\t";
    std::cout << key << std::endl;
}

void RB::show(Node* node, int h)
{
    if (node == 0) return;
    show(node->right, h+1);
    printnode(node->key, h);
    show(node->left, h+1);
}

void RB::print()
{
    show(this->root, 0);
}

void RB::build(int *A, int a, int b)
{

}

