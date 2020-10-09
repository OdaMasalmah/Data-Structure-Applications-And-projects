#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AvlTree.h"
#include "HashTable.h"
#include "ListCity_Country.h"
/*
In this project you can insert, delete, search, In the two data structure
                         The AVL Tree & Hash Table.
*/
typedef long long ll ; // redefine
typedef int boolean ; // redefine boolean
#define MAX_D 250
//_________________________________________Function____________________________________________________
T read_node(FILE *in);
country get_node(char*line);
void end_screan(int b);
void clear_screan();
void menu_hash(hash_table *table, int size);
int error_file() ;
//___________________________________________Main Project#3____________________________________________
int main()
{
    // printf("Hello world!\n");
    system("color f1"); // color of cmd
    FILE *in ; // file input
    // Welcome menu
    printf("\t\t______________________________________________________________________________________\n");
    printf("\n\n\t\t\t\t\t\t Welcome to Project 3.\n\n") ;
    printf("\t\t\t In this project you can insert, delete, search, In the two data structure\n") ;
    printf("\t\t\t The AVL Tree & Hash Table.\n\n") ;
    printf("\t\t______________________________________________________________________________________\n\n");
    T root =  read_node(in) ; // create the tree
    char chose[50], name_cuntry[MAX_D], cname[MAX_D]   ;
    int ind = 0 ;
    double vi =0 ;
    do
    {
        // main tree menu
        clear_screan();
        printf("\n\n\t\t\t Choose one of the following.\n\n") ;
        printf("\t\t\t 1)- Print the node sorted.\n\n") ;
        printf("\t\t\t 2)- Search for a specific Country.\n\n") ;
        printf("\t\t\t 3)- Insert a new Country.\n\n") ;
        printf("\t\t\t 4)- Delete a specific Country.\n\n") ;
        printf("\t\t\t 5)- Calculate tree height.\n\n") ;
        printf("\t\t\t 6)- Implement the Hash Table.\n\n") ;
        printf("\t\t\t 7)- EXITS.\n\n\t\t\t ->") ;
        gets(chose) ;
        if(strlen(chose)>=2 && chose[1]>='7' && chose[0]<='0') // aligle input
            continue;
        switch(chose[0])
        {
        case '1' :
            clear_screan();
            inorder(root) ; // print the tree sorted
            end_screan(0);
            break ;
        case '2' :
            clear_screan() ;
            printf("\n\t\t Please write the name of country : ") ;
            gets(name_cuntry);
            country c =new_country(name_cuntry) ; // create new country
            T t = find_node(root, c );
            if(t == NULL)
            {
                printf("\n\t\tCountry name Not find it.");
            }
            else
            {
                c = t->node ;
                city x1 ;
                printf("\n\t\t The country is exist : %s , numberOfCity is %d , total vis %0.2lf\n",c->name,c->numOf_city,c->total);
                x1 = c->head->next ;
                while(x1 != NULL)
                {
                    printf("\n\t\t -> %d | %s | : | %s | : | vis : %0.2lf \n",x1->num,x1->name,x1->nameCun,x1->vis) ;
                    x1 = x1->next ;
                }
            }
            end_screan(0) ;

            break ;
        case '3' :
            clear_screan() ;
            printf("\n\t\t Write the name of Country : ");
            gets(name_cuntry) ;
            printf("\n\t\t Write the name of City  : ");
            gets(cname) ;
            printf("\n\t\t Write the Rank of City  : ");
            scanf("%d",&ind);
            printf("\n\t\t Write the tourist of City  : ");
            scanf("%lf",&vi);
            city c1 = new_city(cname, name_cuntry,vi, ind); // create new city
            country x = new_country(name_cuntry);
            x = add_city_country(x,c1) ; // add city to country
            if( !find_cun(root, x ) ) // find the node
            {
                root = insert_node(root, x ) ;
                printf("\n\t\t The country is added.");
            }
            else
            {
                T temp =  find_node(root, x);
                temp->node  = add_city_country( temp->node, x->head->next ); // add the city in the node
                printf("\n\t\t The country is exist and we add the city.");
            }
            end_screan(1) ; // two
            break ;
        case '4' :
            clear_screan() ;
            printf("\n\t\t Write The name of Country you want to delete it: ") ;

            gets(name_cuntry) ;
            country cc = new_country(name_cuntry) ; // create new country
            T tt = find_node(root, cc );
            if(tt == NULL)
            {
                printf("\n\t\tCountry name Not find it.");
            }
            else
            {
                cc = tt->node ;
                city x1 ;
                printf("\n\t\t The country Information : %s , numberOfCity is %d , total vis %0.2lf\n",cc->name,cc->numOf_city,cc->total);
                x1 = cc->head->next ;
                while(x1 != NULL)
                {
                    printf("\n\t\t -> %d | %s | : | %s | : | vis : %0.2lf ",x1->num,x1->name,x1->nameCun,x1->vis) ;
                    x1 = x1->next ;
                }
                char o[50], ccname[MAX_D] ;
                // menu to delete the country or city
                printf("\n\t\t_______________________________________________________________________________\n");
                printf("\t\t The country contain all of above are you sure to delete it?");
                printf("\n\t\t 1 - Yes, sure.");
                printf("\n\t\t 2 - delete city in this country.");
                printf("\n\t\t 3 - No. back To menu.\n\t\t ->") ;
                gets(o);
                if(strlen(o)>=2 && o[0]>= '4' && o[0]<='0')
                    continue;
                switch(o[0])
                {
                case '1' :
                    root = delete_node(root, cc); // delete the country
                    break ;
                case '2' :
                    printf("\n\t\t Write the city you want to delete it in %s -> ",cc->name);
                    gets(ccname) ;
                    cc = delete_city(ccname,cc) ; // delete the city

                    break ;
                }

            }

            break ;
        case '5' :
            clear_screan() ;    // print the hight and the level
            printf("\n\t\t The hight of Tree is : < %d >",root->hight) ;
            int lev = root->hight, i = 0  ;
            puts("\n");
            for( i =0  ; i<=lev ; i++)
            {
                printf("\t Level %d",i);
                print_level_Tree(root, i, 0 ) ; // print the level
                puts("\n") ;
            }
            end_screan(0) ;
            break ;
        case '6' :
            clear_screan();
            int size= find_size(root); // find the capacity
            hash_table *h = implement_table(root ) ; // create the table
            menu_hash(h, size ); // menu of hash
            break ;
        }
    }
    while(chose[0]!= '7') ;
    return 0;
}
//
void menu_hash(hash_table *table, int size) // menu of hash
{
    int numOfelement = size ; // capacity
    int n = get_prime(size*2+1) ; // get the prime after 2*n
    char ncity[MAX_D], ncountry[MAX_D] ; // to store the input city and country
    int rank = 0;
    double vis = 0 ;
    char line[MAX_D] ;
    do
    {
        clear_screan() ; // menu of the hash table
        printf("\n\n\t\t\t Choose one of the following.\n\n") ;
        printf("\t\t\t 1)- Print HashTable.\n\n") ;
        printf("\t\t\t 2)- Print Table Size.\n\n") ;
        printf("\t\t\t 3)- Insert a new record.\n\n") ;
        printf("\t\t\t 4)- Search for a specific record.\n\n") ;
        printf("\t\t\t 5)- Delete a specific record.\n\n") ;
        printf("\t\t\t 6)- Print Use HashFunction.\n\n") ;
        printf("\t\t\t 7)- Save Hash Table to file.\n\n") ;
        printf("\t\t\t 8)- Back to menu.\n\n") ;
        printf("\t\t\t 9)- EXITS.\n\n\t\t\t ->") ;
        gets(line) ;
        if(strlen(line)>=2 && line[0]>'9' && line[0]<='0')
            continue;

        switch(line[0])
        {
        case '1' :
            clear_screan() ;
            print_table(table, n); // print the table
            end_screan(0) ;
            break ;
        case '2' :
            clear_screan() ; // print the size of table
            printf("\tThe size Of Table : %d \n\tThe Number Of element : %d\n\tThe capacity : %d",n, numOfelement, size) ;
            printf("\n\tNumber of vis & deleted sell : %d", get_size(table, n)) ;
            end_screan(0) ;
            break ;
        case '3' :
            clear_screan() ; // insert new record

            printf("\tWrite the name of City : ");
            gets(ncity);
            printf("\n\tWrite the name of Country : ");
            gets(ncountry);
            printf("\n\tWrite The rank of city : ");
            scanf("%d",&rank) ;
            printf("\n\tWrite The number Of tourist : ");
            scanf("%lf",&vis) ;
            city cc = new_city(ncity, ncountry, vis, rank ) ; // create new city
            table = insert_hash(cc, size,table) ;
            if(numOfelement == size)
            {
                size = n ;
                n = get_prime(n*2+1);
            }
            numOfelement++ ;
            printf("\n\t\tADD Succfully. ");
            end_screan(0);
            break ;
        case '4' :
            clear_screan(); // serch about the city
            printf("\tWrite the name of Country : ");
            gets(ncity);
            if(!search_value(table, n, ncity, 0) )
            {
                printf("\n\tValue Not Found");
            }
            end_screan(0);
            break ;
        case '5' :
            clear_screan() ;
            printf("\tWrite the name of Country : ");
            gets(ncity);
            char nn[MAX_D] ;
            if( search_value(table, n, ncity,0)  ) // search about the city
            {
                printf("\n\n\tThe country contain all the above City.") ;
                printf("\n\tWrite the name of city to delete it.\n\t ->") ;
                gets(nn) ;
                int r = 0 ;
                int key = get_key( ncity, n ) ;
                city ct =  table[key].node ;
                while(ct != NULL)
                {
                    if(strcmp( nn, ct->name) == 0)
                    {
                        table = delete_value(table, n, ncity,nn );    // delete the city
                        numOfelement--;
                        r =1 ;
                        printf("\n\tDeleted.");
                        break ;
                    }
                    ct = ct->next ;
                }
                if(!r)
                    printf("\n\tCity not found.");

            }
            else
            {
                printf("\n\tCountry Not Found.");
            }
            end_screan(0);
            break ;
        case '6' :
            clear_screan() ;
            print_hash(table, n); // print hash function
            end_screan(0) ;
            break ;
        case '7' :
            puts("\n") ;
            print_hash_file(table, n); // print in  the file
            clear_screan() ;
            break ;
        case '8' : // back to the menu
            break ;
        case '9' :
            exit(1); // exit
            break ;
        }

    }
    while(line[0] != '8');

}
//



int error_file()       // menu if there error in the file
{
    char ag[50] ;
    do
    {
        clear_screan() ;
        printf("\n\t\t Error the file dose not exist or the name is wrong.\n");
        printf("\n\t\t -> Please Check the file.");
        printf("\n\t\t -> Note that.\n\n\t\t (name.txt)-> if the file in project.");
        printf("\n\t\t (path//name.txt)-> if outside projects file.\n");
        printf("\t\t______________________________________________________________________________________\n\n");
        printf("\n\t\t Enter (1) to try again.\n");
        printf("\n\t\t Enter (2) to Exit.\n\n\t\t ->");
        scanf(" %s",ag) ;
        if(strlen(ag)!= 1 || ag[0] >= '3' || ag[0] <='0')
        {
            continue;
        }
    }
    while( ag[0] >='3' || ag[0]<='0' ) ;
    if(ag[0] == '2')
        exit(0) ;
    return ag[0] ;
}
//
T read_node(FILE *in) // create the tree and return it
{
    printf("\t\tWrite the path of file : ");
    char path[MAX_D], line[MAX_D] ;
    int i =0 ;
    gets(path);
    in = fopen( path, "r") ; // open the file
    T root ;
    if(in == NULL) // if error in file
    {
        char er ;
        do
        {
            er = error_file() ;
            printf("\t\t______________________________________________________________________________________\n\n");
            printf("\t\tWrite the path of file : ");
            gets(path);
            gets(path);
            in = fopen( path, "r") ;
        }
        while(in == NULL);
    }
    if(in!= NULL)
        while( fgets(line, MAX_D, in) != NULL )    //read the line in the file
        {

            country x = get_node(line) ; // create the country node
            if(i==0)
            {
                root = new_node(x) ; // add to root
            }
            else
            {

                if( !find_cun(root, x ) )
                {
                    root = insert_node(root, x ) ; // insert node
                }
                else
                {
                    T temp =  find_node(root, x);
                    temp->node  = add_city_country( temp->node, x->head->next ); // insert city in country
                }
            }
            ++i ;
        }
    return root ;

}
country get_node(char*line) //
{
    char *str ;
    char ar[MAX_D]="", ar1[MAX_D]="",ar2[MAX_D]="", ar3[MAX_D]="" ;
    int x =0;
    double y =0 ;
    str = strtok(line, "*") ;
    strcpy(ar, str ) ;               // index
    sscanf(ar, "%d", &x);
    str = strtok(NULL, "*") ;
    strcpy(ar1, str ) ;              // name city
    str = strtok(NULL, "*") ;
    strcpy(ar2, str ) ;              // name country
    str = strtok(NULL, "*") ;
    strcpy(ar3, str ) ;               // number of visit
    sscanf(ar3, "%lf", &y);
    city c1 = new_city(ar1, ar2,y, x );
    country c = new_country(ar2);
    c = add_city_country(c,c1) ;
    return c ;
}
//
void clear_screan() // clear screen
{
    system("cls");
    printf("\n\t\t_______________________________________________________________________________\n\n");

}
void end_screan(int b)  // wait the user
{
    char g[MAX_D];
    printf("\n\n\n\t Enter to back menu ... ");
    if(b)
        gets(g);
    gets(g);
    system("cls");
    printf("\n\t\t_______________________________________________________________________________\n\n");

}
