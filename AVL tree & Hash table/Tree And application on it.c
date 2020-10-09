#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val ;
    struct node* l ;
    struct node* r ;
};
typedef struct node* T ;

T make_tree(int val )
{
    T t = (T)malloc(sizeof(struct node)) ;
    t->val = val ;
    t->l = t->r = NULL ;
    return t ;
}
typedef struct node1
{
    T tree ;
    struct node1 *next ;
}*queu;

queu new_queu(T r)
{
    queu q = (queu)malloc(sizeof(struct node)) ;
    q->tree = r ;
    q->next = NULL ;
    return q ;
}
void add_queu(queu q, T r )
{
    queu d =  new_queu(r);
    queu p = q ;
    while(p->next != NULL)
    {
        p = p->next ;
    }
    p->next = d ;
}
T get_front(queu q )
{
    if(q->next != NULL)
        return q->next->tree ;
    return NULL ;
}
void pop(queu q )
{
    if(q->next != NULL)
    {
        queu temp = q->next ;
        q->next = temp->next ;
        free(temp) ;
    }
}
T delete_node( T root, int x ) ;
T max_tree( T root ) ;
T insert_tree(T root, int x ) ;
int main()
{
    queu head = (queu)malloc(sizeof(struct node)) ;
    head->next = NULL ;
    int path[100]= {} ;

    T t1,t2 ;
    t1 = make_tree(4) ;
    t2 = make_tree(2);
    t2->l = make_tree(1);
    t2->r = make_tree(3);
    t1->l = t2 ;
    t1->r = make_tree(19);
//insert_tree(t1 , 50);
//insert_tree(t1 , 55);
//insert_tree(t1 , 23);
//t1 = delete_node(t1 , 1 ) ;
    print_path(t1, path, 0 );
    printf("PreOrder : ") ;
    prints(t1) ;
    puts(" ");
    printf("is BST : %d",is_bst(t1));
    puts(" ");
    printf("Higth -> %d",higth(t1));
    puts(" ");
    printf("num of leave -> %d",num_leav(t1));
    puts(" ");
    printf("num of node -> %d",num_node(t1));
    T temp = t1 ;
    printf("\nlevel by level .\n") ;
    while(temp != NULL)
    {
        printf("%d,", temp->val);
        if(temp->l != NULL)
        {
            add_queu(head, temp->l);
        }
        if(temp->r != NULL)
        {
            add_queu(head, temp->r);
        }
        temp = get_front(head);
        pop(head) ;
    }
    puts(" " ) ;
    printf("is balanced : >> %d ", is_balance(t1) ) ;
    return 0;
}
void prints(T root )
{
    if( root != NULL )
    {

        printf("%d,",root->val) ;
        prints(root->l);
        prints(root->r) ;
    }
}
int is_bst(T root )
{
    if(root == NULL)
        return 1 ;
    else
    {
        if( root->l != NULL &&  root->val < root->l->val)
        {
            return 0 ;
        }
        if(root->r != NULL && root->val > root->r->val)
        {
            return 0;
        }
        if( is_bst(root->l ) && is_bst(root->r) )
            return 1 ;
        return 0 ;
    }
}

int higth(T root )
{
    if(root == NULL)
    {
        return 0 ;
    }
    else
    {
        int p1, p2 ;
        p1 = higth(root->l) +1 ;
        p2 = higth(root->r) +1 ;
        return p1>p2? p1 : p2 ;
    }
}
int num_leav(T root )
{
    if(root == NULL)
        return NULL ;
    if(root->l == NULL && root->r == NULL)
    {
        return 1 ;
    }
    else
    {
        int c = num_leav(root->l) + num_leav(root->r) ;
        return c ;
    }
}
T insert_tree(T root, int x )
{
    if(root == NULL)
    {
        T t = make_tree(x) ;
        return t ;
    }
    else
    {
        if( x > root->val )
        {
            root->r = insert_tree(root->r, x );
        }
        else
        {
            root->l = insert_tree(root->l, x ) ;

        }
        return root ;
    }
}
T delete_node( T root, int x )
{
    if(root == NULL)
    {
        return NULL ;
    }
    else
    {
        if(x < root->val)
        {
            root->l =  delete_node(root->l, x) ;
        }
        else if(x > root->val)
        {
            root->r =  delete_node(root->r, x) ;
        }
        else
        {
            if(root->l != NULL && root->r != NULL)
            {
                T r = max_tree(root->l) ;
                root->val = r->val ;
                root->l = delete_node(root->l, r->val) ;
            }
            else
            {
                T r =NULL  ;
                if(root->l == NULL)
                {
                    r = root->r ;
                }
                if(root->r == NULL)
                {
                    r = root->l ;
                }
                free(root) ;
                return r;
            }
        }
    }
}
T max_tree( T root )
{
    if(root->l == NULL && root->r == NULL)
    {
        return root ;
    }
    else
    {
        return max_tree(root->r) ;
    }
}
int num_node(T root)
{
    if(root == NULL)
    {
        return 0 ;
    }
    else
    {
        int c = 0 ;
        c = 1 + num_node(root->l) + num_node(root->r) ;
        return c ;
    }

}
void print_path(T root, int path [], int i)
{
    if(root == NULL)
    {
        return ;
    }
    if( root->l == NULL && root->r == NULL )
    {
        path[ i ++] = root->val ;
        int t =0 ;
        for(t= 0 ; t < i ; t++)
        {
            printf("%d ", path[ t ]);
        }
        puts(" ");
    }
    else
    {
        path[i++] = root->val ;
        print_path(root->l, path, i ) ;
        print_path(root->r, path, i ) ;
    }
}
int is_balance(T root )
{
    if(root == NULL)
        return 1 ;
    else
    {
        if(root->l != NULL && root->r == NULL)
            return 0 ;
        if(root->r != NULL && root->l == NULL )
            return 0 ;
        if(is_balance(root->l ) && is_balance(root->r))
            return 1 ;
        return 0 ;
    }
}
