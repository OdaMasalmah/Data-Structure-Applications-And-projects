#include <stdio.h>
#include <stdlib.h>
// AVL Tree implementation
typedef struct tree
{
    int val ;
    int h ;
    struct tree *l, *r ;
}*T   ;

T new_node(int val )
{
    T t = (T)malloc(sizeof(struct tree) ) ;
    t->l = t->r = NULL ;
    t->h = 1;
    t->val = val ;
    return t ;

}

int higth(T root )
{
    return root->h ;
}

int B_F(T root )
{
    int c = 0, c1 = 0  ;
    if(root->l != NULL)
        c = root->l->h ;
    if(root->r != NULL)
        c1 = root->r->h ;
    return c - c1 ;
}
T Right_Ro(T root )
{
    T temp = root->l ;
    root->l =  temp->r ;
    temp->r = root ;
    root->h = update_h(root)  ;
    temp->h = update_h(temp) ;
    return temp ;
}
T Lift_Ro(T root )
{
    T temp = root->r ;
    root->r = temp->l ;
    temp->l = root ;
    root->h = update_h(root)  ;
    temp->h = update_h(temp) ;
    return temp ;
}
T balance(T root )
{
    if(B_F(root) == 2 )
    {
        if(B_F(root->l) == -1)
        {
            root->l = Lift_Ro(root->l);
            root->h = update_h(root) ;

        }
        root = Right_Ro(root) ;
    }
    else if(B_F(root) == -2 )
    {
        if(B_F(root->r) == 1 )
        {
            root->r =  Right_Ro(root->r);
            root->h = update_h(root) ;
        }
        root =  Lift_Ro(root) ;
    }
    root->h = update_h(root) ;
    return root ;
}
T insert_node( T root, int x )
{
    if(root == NULL )
    {
        T t = new_node(x) ;
        return t ;
    }
    else
    {
        if(root->val > x )
        {
            root->l = insert_node(root->l, x ) ;
        }
        else
        {
            root->r = insert_node(root->r, x ) ;
        }

        root->h = update_h( root ) ;
        root = balance(root) ;
        return root ;
    }

}

int update_h(T r )
{
    int c = 0, c1 = 0  ;
    if(r->l != NULL)
        c = r->l->h ;
    if(r->r != NULL)
        c1 = r->r->h ;
    return c >= c1 ? c+1 : c1+1 ;
}
T max_node( T root )
{
    if(root == NULL)
    {
        return root ;
    }
    if(root->r == NULL)
    {
        return root ;
    }
    else
    {
        max_node(root->r) ;
    }
}

T delet_node(T root, int x  )
{
    if(root == NULL)
        return root ;
    else
    {
        if(root->val > x )
            root->l = delet_node(root->l,x ) ;
        else if(root->val < x )
            root->r = delet_node(root->r,x) ;
        else
        {
            if(root->l != NULL && root->r != NULL)
            {
                T temp = max_node(root->l) ;
                root->val = temp->val ;
                root->l = delet_node(root->l, root->val ) ;
            }
            else
            {
                T temp = NULL ;
                if(root->l != NULL)
                    temp = root->l ;
                if(root->r != NULL)
                    temp = root->r ;
                free(root) ;
                return temp ;
            }
        }
        root->h = update_h(root) ;
        root = balance(root) ;
        return root ;

    }
}

int main()
{
    printf("Hello world!\n");
    T root = new_node(5) ;
    root = insert_node(root, 1) ;
    root = insert_node(root, 9 ) ;
    root = insert_node(root, 3 ) ;
    root = insert_node(root, 2) ;
    root = insert_node(root, 0 ) ;
    root = delet_node(root, 5) ;
    root = delet_node(root, 9) ;
    root = delet_node(root, 3) ;

    pre_order(root) ;
    //printf("%d\n", root->r->val ) ;
    //root = delet_node(root, 1) ;
    //printf("%d", root->r->val ) ;

    return 0;
}
void pre_order( T root ){
if(root == NULL)return ;
else{
    pre_order(root->l) ;
    pre_order(root->r) ;
    printf("%d " , root->val) ;
}

}
