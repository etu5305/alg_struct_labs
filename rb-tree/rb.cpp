#include "rb.h"

RB::RB()
{
  count = 0;
  root = 0;
  current = 0;
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
    Node* node;

    if( this->root == 0 ) // Если дерево пустое
    {
        this->root = new Node(key);
        if( this->root != 0 )
        {
            count = 1;
            this->root->color = 1; // узел - черный (свойство 2)
            return 1;
        }
        return 0;
    }
    else if( bs_find(node, key) == 0 ) // Дерево не пустое | node = последний не пустой узел
    {
        if( key > node->key ) // Ключ больше родителя
        {
            node->right = new Node(key, node);
            if( node->right == 0 )
                return 0;
            count++;
            node->right->color = 0;
            fix(node->right); // балансировка после вставки
            return 1;
        }
        else // Ключ меньше родительского
        {
            node->left = new Node(key, node);
            if( node->left == 0 )
                return 0;
            count++;
            node->left->color = 0;
            fix(node->left); // балансировка после вставки
            return 1;
        }
    }
    return 1; // Узел с таким ключем уже существует
}

void RB::fix(Node* N) // балансировка дерева после вставки
{
    while( N->parent != 0 && N->parent->color == 0 )
    {
        Node* P = N->parent;
        Node* G = RB::grandparent(N);
        Node* U = RB::uncle(N);

        if( P == G->left )
        {
            if( U->color == 0 )
            {
                P->color = 1;
                U->color = 1;
                G->color = 0;
                N = G;
            }
            else
            {
                if( N == P->right )
                {
                    N = P;
                    this->rotate_left(N);
                }
                P->color = 1;
                G->color = 0;
                this->rotate_right(G);
            }
        }
        else
        {
            if( U->color == 0 )
            {
                P->color = 1;
                U->color = 1;
                G->color = 0;
                N = G;
            }
            else
            {
                if( N == P->left )
                {
                    N = P;
                    this->rotate_right(N);
                }
                P->color = 1;
                G->color = 0;
                this->rotate_left(G);
            }
        }
    }
    this->root->color = 1;
}

bool RB::remove_fix(Node* N) // балансировка дерева после удаления
{
    while (N->parent != 0 && N->color == 1)
    {
        if( N == N->parent->left )
        {
            // D == 1
            Node *w = N->parent->right;		//right
            if (w->color == 0) {
               w->color = 1;
               N->parent->color = 0;
               this->rotate_left(N->parent);	//left
               w = N->parent->right;		//right
            }
            if (w->left->color == 1 && w->right->color == 1) {
               w->color = 0;
               N = N->parent;
            }
            else {
               if (w->right->color == 1) {	//right
                 w->left->color = 1;	//left
                 w->color = 0;
                 this->rotate_right(w);
                 w = N->parent->right;		//right
               }
               w->color = N->parent->color;
               N->parent->color = 1;
               w->right->color = 1;		//right
               this->rotate_left(N->parent);
               N = root;
            }
        }
        else
        {
            // D == 0
            Node *w = N->parent->left;		//left
            if (w->color == 0) {
               w->color = 1;
               N->parent->color = 0;
               this->rotate_right(N->parent);
               w = N->parent->left;		//left
            }
            if (w->left->color == 1 && w->right->color == 1) {
               w->color = 0;
               N = N->parent;
            }
            else {
               if (w->left->color == 1) {	//left
                 w->right->color = 1;	//right
                 w->color = 0;
                 this->rotate_left(w);
                 w = N->parent->left;		//left
               }
               w->color = N->parent->color;
               N->parent->color = 1;
               w->left->color = 1;		//left
               this->rotate_right(N->parent);
               N = root;
            }
        }
   }
   N->color = 1;
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


            if( tmp_node->color == 1 )
                remove_fix(search_node);

            delete tmp_node;
            // remove-fixup
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
            // remove-fixup
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
            // remove-fixup
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

RB::Node* RB::uncle(Node* node)
{
    if( node->parent != 0 )
    {
        if( node->parent->parent != 0 )
        {
            if( node->parent->parent->left == node->parent )
            {
                return node->parent->parent->right;
            }
            else
            {
                return node->parent->parent->left;
            }
        }
    }

    return 0;
}

RB::Node* RB::grandparent(Node* node)
{
    if( node->parent != 0 )
    {
        if( node->parent->parent != 0 )
        {
            return node->parent->parent;
        }
    }

   return 0;
}

RB::Node* RB::sibling(Node* node)
{
    if( node->parent != 0 )
    {
        if( node == node->parent->right )
        {
            return node->parent->left;
        }
        else
        {
            return node->parent->right;
        }
    }

   return 0;
}

void RB::rotate_left(Node* n)
{
    Node* pivot = n->right;

    pivot->parent = n->parent;
    if (n->parent != 0) {
        if (n->parent->left==n)
            n->parent->left = pivot;
        else
            n->parent->right = pivot;
    }

    n->right = pivot->left;
    if (pivot->left != 0)
        pivot->left->parent = n;

    n->parent = pivot;
    pivot->left = n;
}

void RB::rotate_right(Node* n)
{
    Node* pivot = n->left;

    pivot->parent = n->parent;
    if (n->parent != 0) {
        if (n->parent->left==n)
            n->parent->left = pivot;
        else
            n->parent->right = pivot;
    }

    n->left = pivot->right;
    if (pivot->right != 0)
        pivot->right->parent = n;

    n->parent = pivot;
    pivot->right = n;
}

int RB::get_current_value (){
  if (current != 0)
    return current->key;
}

bool RB::pop (){
  if (root == 0) // дерево пусто
    return false;
  if (current == 0){
    // ищём самый левый и нижний узел (лист)
    // идём в цикле от корня, выбирая каждый раз левого потомка, как только его не окажется - мы нашли самый левый и нижний узел (лист)
    current = root;
    
    while (current->left != 0){
      current = current->left;
    }
    return true;
  }else{
    // если есть правый потомок - спускаемся в него и ищём там самый левый узел (лист)
    if (current->right != 0){
      current = current->right;
      while (current->left != 0){
	current = current->left;
      }
      return true;
    }else if(current->parent !=0){ // иначе, если есть родитель, поднимаемся вверх, пока не встретим родителя с key > key текущего
      int key = current->key;
      Node* current_cpy = current;
      current = current->parent;
      while (current->key < key){
	current = current->parent;
	if (current == 0){
	  current = current_cpy; // не теряем последний элемент
	  return false; // цэ был последний элемент в дереве
	}
      }
      return true;
    }else{
      return false; // мы находимся в корне, правого поддерева нет
    }
    }
}
