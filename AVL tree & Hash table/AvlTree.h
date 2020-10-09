//
#include "ListCity_Country.h"
typedef long long ll ;
typedef int boolean ;
#define MAX_D 250
////_____________________________________AVL Implementation______________________________

typedef struct tree
{
    country node ;
    struct tree *left, *rigth ;
    int hight ;
} *T ;
T new_node(country node) // create new node
{
    T t = (T)malloc(sizeof(struct tree)) ;
    t->hight = 0 ;
    t->node = node;
    t->left = t->rigth = NULL ;
    return t ;
}

void inorder(T root ) // print the tree in inorder(sorted)
{
    if(root == NULL )
        return ;
    else
    {
        inorder(root->left) ; // left
        city c = root->node->head->next;
        printf("\n\t\t name Of Country : %s | number of city = %d  | total = %0.2lf\n",root->node->name, root->node->numOf_city, root->node->total) ;
        while(c != NULL)
        {
            printf("\t\t ->> %s  ,Rank = %d ,vis = %0.2lf \n",c->name, c->num, c->vis ) ;
            c=c->next ;
        }
        inorder(root->rigth) ; // right
    }
}
int B_F(T root) // Balance factor
{
    int c =0, c1 =0 ;
    if(root->left != NULL)
        c = root->left->hight+1 ;
    if(root->rigth != NULL )
        c1 = root->rigth->hight+1 ;
    return c - c1 ;
}
int update_higth(T root ) // update the hight of tree
{
    int c =-1, c1 =-1 ;
    if(root->left != NULL)
        c = root->left->hight ;
    if(root->rigth != NULL )
        c1 = root->rigth->hight ;
    return c >= c1 ? c+1 : c1+1 ;
}
T LL(T root ) // lift lift rotate
{
    T temp ;
    temp = root->left ;
    root->left = temp->rigth ;
    temp->rigth = root ;
    root->hight = update_higth(root) ;
    temp->hight = update_higth(temp ) ;

    return temp ;
}
T RR(T root ) // right right rotate
{
    T temp = root->rigth;
    root->rigth = temp->left ;
    temp->left = root ;
    root->hight = update_higth(root);
    temp->hight = update_higth(temp);
    return temp ;
}
T  balance(T root ) // balancing the tree
{
    if(root == NULL )
        return NULL ;
    else
    {
        if(B_F(root) == 2)
        {
            if(B_F(root->left) == -1) // Left Right case
                root->left = RR(root->left);
            root = LL(root) ;
        }
        else if(B_F(root ) == -2 )
        {
            if(B_F(root->rigth) == 1 ) // Right Left case
                root->rigth = LL(root->rigth);
            root = RR(root) ;
        }
        root->hight = update_higth(root) ; // update the hight
        return root ;
    }
}
T insert_node(T root, country node ) // insert node to the tree
{
    if(root == NULL )
    {
        T temp = new_node(node) ;
        return temp ;
    }
    else
    {
        if( strcmp( root->node->name, node->name ) > 0 ) // compare the name
        {
            root->left =  insert_node( root->left, node ) ;
        }
        else if( strcmp(root->node->name, node->name ) < 0)
        {
            root->rigth =  insert_node( root->rigth, node ) ;
        }
        // AVL TREE higth && balance
        root->hight = update_higth(root) ;
        root = balance(root) ;
        return root ;
    }
}
T max_node(T root ) // get the max element
{
    if(root == NULL )
        return NULL ;
    if(root->rigth == NULL)
        return root ;
    else
    {
        return max_node(root->rigth) ;

    }
}
T delete_node(T root, country c ) // delete node
{
    if(root == NULL )
        return NULL ;
    else
    {
        if( strcmp(root->node->name, c->name) > 0 )
        {
            root->left = delete_node(root->left, c);
        }
        else if( strcmp(root->node->name, c->name ) < 0 )
        {
            root->rigth = delete_node(root->rigth, c ) ;
        }
        else
        {
            if(root->left != NULL && root->rigth != NULL) // if two child exist
            {
                T temp = max_node(root->left);
                root->node = temp->node ;
                root->left = delete_node(root->left, temp->node);
                return root ;
            }
            else // if one child
            {
                T temp = NULL ;
                if(root ->left != NULL)
                    temp = root->left ;
                if(root->rigth != NULL)
                    temp = root->rigth ;
                free(root) ;
                return temp ;
            }

        }
        root = balance(root) ; // balancing
        root->hight = update_higth(root) ; // update hight

        return root ;
    }
}
T find_node(T root,country  c) // find the country
{
    {
        if(root == NULL )
        {
            return NULL ;
        }
        else
        {
            if( strcmp(root->node->name, c->name) > 0 )
            {
                return find_node(root->left, c ) ;
            }
            else if(strcmp(root->node->name, c->name) < 0)
            {
              return find_node(root->rigth, c ) ;
            }
            else
            {
                return root ;

            }


        }
    }
}
int find_cun(T root, country c ) // find the country node
{
    if(root == NULL )
    {
        return 0 ;
    }
    else
    {
        if( strcmp(root->node->name, c->name) > 0 )
        {
            return find_cun(root->left, c ) ;
        }
        else if(strcmp(root->node->name, c->name) < 0)
        {
            return find_cun(root->rigth, c ) ;
        }
        else
        {
            return 1 ;

        }


    }
}
int find_size(T root ) // calculate the size of the city
{
    if(root == NULL)
        return 0 ;
    else
    {
        return  find_size(root->left) + find_size(root->rigth) + root->node->numOf_city ;
    }
}
void print_level_Tree(T root, int len,int r ) // print level by level
{
    if(root == NULL)
        return ;
    if(len == 0 && r ==0 )
    {
        printf("\t\t[%s],H<%d>,root",root->node->name, root->hight);
    }
    if(len == 0 && r ==1 )
    {
        printf("\t[%s],H<%d>,R",root->node->name, root->hight );
    }
    if(len == 0 && r ==2 )
    {
        printf("\t[%s],H<%d>,L",root->node->name, root->hight );
    }
    print_level_Tree(root->left, len-1, 2  ) ;
    print_level_Tree(root->rigth, len-1, 1  ) ;

}
