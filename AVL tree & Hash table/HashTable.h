//
#include "ListCity_Country.h"
//____________________________________Implementation of Hash Table_________________________

typedef struct hash // Hash Table Contain the city and two boolean to remark the sells
{
    city node ;
    boolean del ; // remark the cell deleted
    boolean vis ; // remark the cell visited

} hash_table;
int get_prime(int x);
int get_size(hash_table *h, int size );
hash_table* insert_hash(city c, int n, hash_table *h)  ;
hash_table* create_table(int size) // create new hash table
{
    int x = get_prime(size*2+1) , i=0; // get the print after 2*n
    hash_table *table = (hash_table*)malloc(sizeof(struct hash)*x) ; // create the table
    for(i=0; i<x ; i++ )
    {
        table[i].node = NULL ;
        table[i].vis = 0 ;
        table[i].del = 0 ;
    }
    return table ;
}
int get_prime(int x) // get the prime number after x
{
    int i = 3, temp = 1 ;
    for( ; x<1e9 ; x+=2 )
    {
        for(i=3 ; i*i<=x ; i+=2)
        {
            if(x%i == 0) // if is not prime
            {
                temp =0 ;
                break ;
            }
        }
        if(temp)
            return x ;
        temp =1 ;
    }
    return x ;
}
int get_key( char *c, int size ) // hash function
{
    ll hv = 1, i =0;
    for(i=0 ; i<strlen(c) ; i++){
        hv = ( ( (hv<<2) + ( (ll)c[i]-60) ) ) ; // equation of hash
        }

    return ((hv%size)+size)%size ; // resize the val
}
hash_table* rehash_table(hash_table *table, int n ) // rehash
{
    hash_table *new_table = create_table(n) ;
    int i =0 ;
    for(i = 0 ; i<n ; i++)
    {
        if(table[i].vis && !table[i].del && table[i].node != NULL)
        {
            insert_hash(table[i].node, n, new_table) ;

        }
    }
    return new_table ;
}
hash_table* insert_hash(city c, int n, hash_table *h)        // n capcity of table
{

    int size = get_prime(2*n+1) ; // get the prime
    int key = get_key( c->nameCun, size ) , ind = key ; // get the key of hash
    if(get_size(h, size) < n  ) // check if hash or rehash
    {
        int i = 0 ;
        while( h[ind].vis  ) // quadratic hash
        {
            i++;
           ind = (key+i*i)%size;
        }
        h[ind].node = c;
        h[ind].vis = 1 ; // remark the vis
        h[ind].del = 0 ;
    }
    else
    {
        h = rehash_table(h, size) ; // rehash table size
        n = size ;
        size = get_prime(size*2+1 ) ; // get prime
        h = insert_hash( c, n, h); // insert the element to hash table
    }
    return h;
}
hash_table* delete_value(hash_table* t, int size, char* c , char *cc) // delete city
{
    int key = get_key( c , size ) ; // find the key
    int i = 0 , ind = key ;
    while( (strcmp(t[ind].node->name,cc) != 0 && t[ind].vis)  || (t[ind].del == 1) )
    {
        i++ ;
        ind = (key+i*i)%size ; // quadratic hash
    }
    t[ind].del = 1 ; // remark it deleted
    return t ;
}
int search_value(hash_table *t, int size ,char* c, int flag) // search about the city
{
    int st =1 ;
    int key = get_key(c, size ) ;
    int i =0 ,ind = key ;

    while( t[ind].vis ) // if vis
    {
        if( t[(ind)%size].del == 0 && strcmp(t[ind].node->nameCun,c) == 0 ) // if not the city
        {
            if(flag)
                return 1;
            st = 0 ;
            printf("\tThe index is %d :: name : %s :: number Of  tourist is : %lf :: Rank is : %d\n", ind ,t[ind].node->name,t[ind].node->vis,t[ind].node->num );
        }
        i++ ;
        ind = (key + i*i)%size; // quadratic hash
    }
    if(st)
        return 0 ;
    else
        return 1 ;
}
int get_size(hash_table *h, int size ) // get size of table
{
    int i =0, n =0 ;
    for(i =0 ; i<size ; i++)
    {
        if(h[i].vis == 1) // if visited count them
            n++;
    }
    return n ;
}
void print_table(hash_table *h,int size) // print the table
{
    int i =0 ;
    for(i =0 ; i < size ; i++)
    {
        if(h[i].vis) // if the cell contain values
            printf("\t%s  :: %s :: del %d \n",h[i].node->name, h[i].node->nameCun, h[i].del  );
        else
        {
            printf("\t(empty)  :: vis ->%d :: del->%d   \n", h[i].vis, h[i].del );
        }
    }
}
void print_hash_file(hash_table *t, int size ) // print the hash in the file
{
    FILE *out ;
    char name[MAX_D] ;
    gets(name);
    out = fopen(name, "w") ; // open the file
    int i =0 ;
    for(i =0; i <size ; i++)
    {
        if(t[i].vis == 1 && t[i].del == 0) // if contain value
        {
            fprintf(out,"\tCity is : %s :: The Country is %s :: The Rank is %d :: Total tourist %lf\n",t[i].node->name, t[i].node->nameCun, t[i].node->num,t[i].node->vis  );
        }
        fclose(out); // close he file
    }
}
void print_hash(hash_table *t, int size ) // print the hash function
{
    int i =0 ;
    printf("\n\tHashValue = (HashValue<<2 + (long long)(str[i]-60)) \n") ;
    printf("\n\treturn ((HasValue%Size)+size)%size \n\n") ;

    for(i=0 ; i <size ; i++)
    {
        if(t[i].vis == 1 && t[i].del == 0)
        {
            printf("\t%s :: %s :: hash Function is : %d\n",t[i].node->nameCun,t[i].node->name, get_key( t[i].node->nameCun,size ) );
        }
    }
}
hash_table* add_to_table(T root, hash_table* h, int size  ) // add city to the table from the tree
{
    if(root == NULL)
        return h ;
    else
    {
        add_to_table(root->left, h,size ) ;
        city temp = root->node->head->next ;
        while(temp != NULL)
        {
            h = insert_hash(temp, size, h) ;
            temp = temp->next ;
        }
        add_to_table(root->rigth, h,size) ;
        return h ;
    }
}
hash_table* implement_table(T root) // create table
{
    int size = find_size(root);
    hash_table *h = create_table(size);
    h = add_to_table(root, h, size ) ;

    return h ;
}

