#ifndef _LISTH_
#define _LISTH_
typedef long long ll ;
typedef int boolean ;
#define MAX_D 250

//___________________________________City___________________________________________
typedef struct city
{
    char name[MAX_D] ; // name of city
    char nameCun[MAX_D] ; // name of country
    double vis ; // number of tourist
    int num ; // rank
    struct city *next ; // list of city
}*city, *list_city, *head_city;

city new_city(char* s,char* s1,double vis,int ind ) // create new city
{
    city c = (city ) malloc(sizeof(struct city)) ;
    strcpy(c->name, s) ;
    strcpy(c->nameCun, s1) ;
    c->vis = vis ;
    c->num = ind ;
    c->next = NULL ;
    return c ;
}
city add_city(head_city head, char*s,char *s1, double vis,int ind) // add city(add first)
{
    city c = new_city(s, s1,vis, ind ) ;
    c->next = head->next ;
    head->next = c ;
    return head ;
}

//____________________________________ Country Node__________________________________
typedef struct country_node
{
    char name[MAX_D] ; // name of country
    head_city head ; // header of city
    double total   ; // total tourist of the all city
    int numOf_city ; // number of city
}*country ;
country new_country( char *s ) // create new country
{
    country c = (country) malloc(sizeof(struct country_node)) ;
    strcpy(c->name, s ) ;
    c->head = new_city("", s, -1, -1) ;
    c->total =0 ;
    c->numOf_city=0 ;
    return c ;
}
country add_city_country(country head, city c ) // add city to the country
{
    head->head = add_city( head->head, c->name,head->name,c->vis, c->num ) ;
    head->total+= c->vis ;
    head->numOf_city++ ;
    return head ;
}
//


country delete_city( char*s,country c) // delete city from the country
{
    city cc = c->head->next ; // next step
    city pre = c->head ; // privous step
    while(cc != NULL && pre != NULL )
    {
        if(strcmp(cc->name,s) == 0) // if find it
        {
            pre->next = cc->next ;
            c->total -= cc->vis ;
            free(cc) ; // delete it
            break ;
        }
        cc = cc->next ;
        pre = pre->next ;
    }
    c->numOf_city-- ;
    return c ;
}
#endif
