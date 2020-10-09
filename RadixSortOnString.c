#include <stdio.h>
#include <stdlib.h> //hi.txt

#define MAX 100               // maximum number of Name
#define M 99000001
#define MAX_d 51        // maximum length of string
typedef char string[MAX_d];   // string from char array contain maximum digit for the list
typedef int boolean;      // boolean true = 1 ; false = 0 ;
typedef int ptr;           // ptr cursor elements

struct curser     // implementation of cursor string & next
{
    string str;
    ptr next;

};

typedef ptr pos;  // for node of cursor
typedef ptr head;  // for head of node
typedef struct curser LIST; //cursor name LIST

//*******************************   Function   ******************************************
int readFromFile(string [], FILE*);
boolean add_name(string [], int, string);
void print_befor_sort(string [], int);
void copy_string(string, string);
boolean equal(string, string);
void print_char(string [], int, char) ;
void print_sort_lsit(string [], int,FILE) ;
void clear_screan();
void end_screan() ;
int str_len(string);
void trim_str(string) ;
void add_last(LIST [], head, string ) ;
pos curser_alloc(LIST []);
void creat_curser(LIST [], int) ;
int long_str(string list []);
void free_node(LIST [], pos ) ;
void is_empty(LIST [], head );
void radixSort(string []) ;
//**************************************************************************************
//_________________________________Main Function________________________________________
int main()
{
    system("COLOR F0");
    int  state = 1 ;     // state to save the place
    char ag ;
    char  x[50] ;         // to read the input
    int max_size;         // store number of name
    string  name, del, path, g, path_out;
    string *list_name = (string*)malloc(sizeof(string)*M); // create the array to store the names
    FILE *file, *output;  // file to read && write
    boolean s, s1;
    char ch ;
    printf("\n\n\t\t______________________ Welcome to make List project ___________________________\n\n");
    printf("\n\t\tIn this project you can make the list of name & operation on it.\n\t\t,to continue follow the instruction.\n");
    do
    {
        printf("\n\t\t_______________________________________________________________________________\n\n");
        printf("\n\t\tPlease write the path of the file contain the names :");
        do
        {
            gets(path) ;       // read path of file
        }
        while(equal(path, "")) ;
        file = fopen(path, "r");
        if (file == NULL)        // check if file exists
        {
            ag = error_file() ;   // menu if theres error in file
            if(ag == '2')
            {
                printf("\n\t\t Exit.\n\n");
                exit(0);
            }
        }
        else
        {
            clear_screan() ;                             // clear screen
            max_size = readFromFile(list_name, file);    // read the name from the file and return number of elements
            printf("\n\t\t The name is read it & Done Successfully.\n");
            fclose(file);
            ag='3';
        }
    }
    while( ag != '3' ) ;


    do // main menu
    {
        printf("\n\t\t____________________________________________\n");
        printf("\n\t\t Please chose from the list :              \n\n");
        printf("\t\t\t| 1) - Read the list from the file again.   \n");
        printf("\t\t\t| 2) - Print name.           \n");
        printf("\t\t\t| 3) - ADD element from the list.           \n");
        printf("\t\t\t| 4) - Delete element from the list.        \n");
        printf("\t\t\t| 5) - Sort the List.                       \n");
        printf("\t\t\t| 6) - Search the Character after sorting.  \n");
        printf("\t\t\t| 7) - Print the List after sorting.\n");
        printf("\t\t\t| 8) - Print the list in File after sorting.\n");
        printf("\t\t\t| 9) - Exits.                               \n");
        printf("\n\t\t____________________________________________\n");
        printf("\t\t\t => ");
        scanf(" %s",x);
        if (x[0]<='9' && x[0] >='0' && str_len(x) == 1)
        {
            switch (x[0])
            {
            case '1':

                clear_screan();
                state =1 ;
                file = fopen(path, "r");   // open the file
                if (file == NULL)            // check if exist
                {
                    printf("EROOOR the file dose not exist");
                }
                else
                {
                    max_size = readFromFile(list_name, file);    // read from file and return the number of name
                    printf("\n\t\t Read Successfully.\n");
                    fclose(file);                                     // close file
                }
                break;

            case '2':
                clear_screan();
                print_befor_sort(list_name, max_size);  // print the name before sorting
                end_screan();
                break;



            case '3':                // add new name
                state =1 ;
                clear_screan();
                char name[100];
                printf("\n\t\t Write the name : ");
                do
                {
                    gets(name);  // read the name
                }
                while (equal(name, ""));
                if( is_valid(name) && str_len(name)< MAX_d-1 )  //check if valid
                {
                    trim_str(name);                              // trim the string
                    s = add_name(list_name, max_size, name);      //function to add name to the list
                    if (s)
                    {
                        max_size++;                              // increment the size of name
                        printf("\n\t\t Add Successfully.\n");
                    }
                    else
                    {
                        printf("\n\t\tFull list name Can't add to the list.\n");
                    }
                }
                else               // if the name invalid
                {
                    printf("\n\t\tString not valid dose not added.\n");
                }
                break;

            case '4':       // delete name from the list
                state =1 ;
                clear_screan();
                printf("\n\t\t Write the name you want to delete it : ");
                do
                {
                    gets(del);  // read the name
                }
                while (equal(del, ""));
                s1 = del_name(list_name, max_size, del); // function to delete name
                if (s1)
                {
                    max_size--;         // decrement the size name
                    printf("\n\t\t Delete Successfully.\n");

                }
                else
                {
                    printf("\n\t\t Name Not Found it. \n");
                }
                break;

            case '5':                 // radix sort
                state = 2 ;
                clear_screan();
                radixSort(list_name); // function to sort elements
                printf("\n\t\t List was Sorted.\n");
                break;

            case '6':                 // search about list of specific characters
                clear_screan();
                if(state == 1 )
                {
                    printf("\n\t\tYou should Sort the list before.\n");
                }
                else
                {
                    printf("\n\t\t Write the char :");
                    scanf(" %c", &ch);                       // read the char
                    print_char(list_name, max_size, ch);     // function to print list of this name
                    end_screan();
                }

                break;

            case '7':                        // print name after sorting in list
                clear_screan();
                if(state == 1 )
                {
                    printf("\n\t\tYou should Sort the list before.\n");
                }
                else
                {
                    output = NULL ;
                    print_sort_list(list_name, max_size,output);  // method for print list name
                    end_screan();
                }

                break;


            case '8' :               // print the list in the name

                clear_screan();
                if(state == 1 )
                {
                    printf("\n\t\tYou should Sort the list before.\n");
                }
                else
                {
                    printf("\n\t\tPlease Enter the path of file : ");
                    do
                    {
                        gets(path_out);        // read the path of file
                    }
                    while (equal(path_out, ""));

                    output = fopen(path_out, "a");
                    if (output == NULL)
                    {
                        printf("EROOOR the file dose not exist");
                    }
                    else
                    {
                        print_sort_list(list_name, max_size, output);  // function to print in file
                        printf("\n\t\t write Successfully.\n");
                        fclose(file);  // close the file
                    }
                }
                break;
            }
        }
        else
        {
            clear_screan();
            printf("\n\t\t The number in not from the List please try again. \n");
        }
    }
    while (x[0] != '9');

    return 0;

}
//********************** Implemantation the function *********************

//********************** Read & ADD & & print Delete from the list ****************
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
        printf("\t\t__________________________________________________________\n");
        printf("\n\t\t Enter (1) to try again.\n");
        printf("\n\t\t Enter (2) to Exit.\n\n\t\t ->");
        scanf(" %s",ag) ;
        if(str_len(ag)!= 1 || ag[0] >= '3' || ag[0] <='0'){
                continue;}
    }
    while( ag[0] >='3' || ag[0]<='0' ) ;
    return ag[0] ;
}
int readFromFile(string list_name [], FILE* file) // function to read the name
{
    string s;
    int c = 0, n=0;
    while (fgets(s, MAX_d, file) != NULL)        // read all the name in file
    {
        trim_str(s);                           // trim the string> remove first space
        if(!is_valid(s))                       // check if the string valid
        {
            n++;   // count the invalid string
        }
        else
        {
            copy_string(list_name[c], s);    // add the name to the list
            c++;
            if(c == MAX )     // check the list if full
            {
                printf("\t\t Note::The number of name is great then the max size we accept only number of max name.\n");
                break ;
            }
        }
    }
    if(n) // print number of invalid string
    {
        printf("\t\t Note::that there is %d string not valid and dose not added.\n", n);

    }
    return c; // return the number of name
}

void print_befor_sort(string arr[], int size)  // print the name before sorting
{
    int i = 0;
    for (; i < size; i++)
        printf("\t\t %d - %s\n", i + 1, arr[i]);

}

boolean add_name(string list_name [], int size, string s) // add name to the list
{
    if (size == MAX) // check if the list is full
    {
        return 0;
    }
    else
    {
        copy_string(list_name[size], s);
        return 1;
    }
}

boolean del_name(string list_name [], int size, string del) // delete name from the list
{
    int i = 0;
    boolean b = 0;              // to return if the name delete or not
    for (; i < size; i++)
    {
        if (equal(list_name[i], del))       // file the name
        {
            b = 1;
            int y = i;
            for (; y < size - 1; y++) // shift all elements to delete the name
            {
                copy_string(list_name[y], list_name[y + 1]);
            }
            break;
        }
    }
    if (b)
        return 1;
    else
        return 0;
}

void print_char(string arr [], int size, char ch) // print the list start with characters ch
{
    if (ch >= 97)  // if the char is small make him capital
    {
        ch -= 32;
    }
    boolean b = 1;
    printf("\n\t The List begin with %c is :", ch);
    int i = 0;
    for (; i < size; i++)
    {
        if (arr[i][0] == ch || arr[i][0] == ch + 32)  // check the string if begin with this char to prints
        {
            printf("\n\t  -  %s ", arr[i]);
            b = 0;
        }
    }
    if (b)
    {
        printf("\n\n\t\t NO Elements with this character, you can add too."); // if no name begin with this char
    }
}

void print_sort_list(string list [], int size,FILE *out) // print the list in screen and file
{

    int i, mod =0 , arr[26] = {0}; // arr to count the number of name in all litters
    if(out != NULL)  // to check were you want to print
    {
        mod = 1 ;
    }
    for (i = 0; i < size; i++) // freq array to calculate how name begin with the litters
    {
        if (list[i][0] >= 'a' && list[i][0] <= 'z')
        {
            arr[(int) list[i][0] - 'a']++;
        }
        else if (list[i][0] >= 'A' && list[i][0] <= 'Z')
        {
            arr[(int) list[i][0] - 'A']++;
        }
    }
    int k = 0, j = 0;
    boolean b = 0;
    char ch = 'A';
    for (; k < 26; k++)          // print in the screen the list and name contain
    {
        if (arr[k] > 0)
        {

            if(mod)
            {
                fprintf(out,"\n The list %c is :\n", (ch + k)) ;
            }
            else
            {
                printf("\n\t\t The list %c is :\n", (ch + k));
            }
        }
        while (arr[k] != 0) // print in file the list name
        {

            if(mod)
            {
                fprintf(out,"\n     - %s \n", list[j++]);
            }
            else
            {
                printf("\n\t\t     - %s \n", list[j++]);
            }
            arr[k]--;
            b = 1;
        }
        if (b)

            if(mod)
            {
                fprintf(out,"\n");
            }
            else
            {
                printf("\n");
            }

        b = 0;
    }
}

void clear_screan() // clear screen
{
    system("cls");
    printf("\n\t\t_______________________________________________________________________________\n\n");

}

void end_screan()  // wait for the user enter
{
    string g;
    printf("\n\n\n\t Enter to back menu ... ");
    gets(g);
    gets(g);
    system("cls");
    printf("\n\t\t_______________________________________________________________________________\n\n");

}

//********************* Radix Sort By cursor Implementation ***************
int size_of_array( string arr[]){  // function return number of elements in array O(n)
int i = 0 ;
for(;!equal(arr[i],"\n") ; i++){
}
return i ;
}
void radixSort(string arr [])   // radix sort O(n)
{
    int size_arr = size_of_array(arr) ;      // size of array
    int size_of_list = size_arr + 29 + 1;       // size of cursor
    int max_digit =long_str(arr)   ;              // calculate the max_digits
    LIST *list = (LIST*)calloc(size_of_list , sizeof(LIST)); // alloc the cursor
    creat_curser(list, size_of_list);  // initialize the cursor
    head h1;                              // head of the name
    h1 = curser_alloc(list);            // node the head
    int i = 0;
    head pp1  = h1, pp2 ;
    for (i=0 ; i < size_arr ; i++)  // add the name from array to the cursor
    {
        pp2 = curser_alloc(list);
        copy_string(list[pp2].str, arr[i]);
        list[pp1].next = pp2 ;
        pp1 = list[pp1].next ;

    }
    list[pp1].next = 0 ;
    int t = 0, l, list_char[27], temp_arr[27], temp_h = h1, r =0  ; // buckets and temp of buckets
    pos p;
    for (l = 0; l < 27; l++)
    {
        list_char[l] = curser_alloc(list); // create node for the bucket
    }


    int index = 0 ;
    for (t = max_digit - 1; t >= 0; t--)   //sort the cursor
    {

        for(r= 0  ; r<27 ; r++) // pointer in all buckets to swap the names
        {
            temp_arr[r] = list_char[r];
        }
        temp_h = h1 ;
        p = list[h1].next;
        while (p != 0)               // distribution the name to the buckets
        {
            if (str_len(list[p].str) > t && list[p].str[t] >= 'a' && list[p].str[t] <= 'z')
            {

                index = (int) list[p].str[t] - 'a' + 1; // get the index
            }
            else if (str_len(list[p].str) > t && list[p].str[t] >= 'A' && list[p].str[t] <= 'Z')
            {
                index = (int) list[p].str[t] - 'A' + 1; // get the index

            }
            else
            {
                index = 0 ;      // if the length is small or the char is space
            }
            list[temp_arr[index]].next = p ;                // swap the node from head to bucket
            list[temp_h].next = list[p].next ;
            list[p].next =0 ;
            temp_arr[index] = list[temp_arr[index]].next ;
            p = list[temp_h].next ;
        }

        for(r = 0 ; r<27 ; r++)         // to return the pointers to the all buckets
        {
            temp_arr[r] = list_char[r];
        }
        pos temp, j, sw = h1 ;
        for (j = 0; j < 27; j++)   // from all bucket to the head again but with sort
        {
            temp = list[list_char[j]].next;
            while (temp != 0)
            {
                list[sw].next = temp ;     // swap from the buckets to head
                list[temp_arr[j] ].next = list[temp].next ;
                list[temp].next = 0 ;
                temp = list[temp_arr[j]].next ;
                sw = list[sw].next ;
            }
        }

    }
    pos p1, x = 0;
    p1 = list[h1].next;
    while (p1 != 0)          // copy the name from the cursor to the array
    {
        copy_string(arr[x++], list[p1].str);
        free_node(list,p1);                       // free all node
        p1 = list[p1].next;
    }
}
void free_node(LIST list[], pos p) // free the node
{
    list[0].next = list[p].next;
    list[0].next = p;
}

int long_str(string list []) // get the max length string
{
    int i = 0, max = size_of_array(list), temp;

    for (i = 0; i < max; i++)
    {
        temp = str_len(list[i]);
        if (temp > max)
        {
            max = temp;
        }
    }
    return max;
}

void creat_curser(LIST list[], int size) // initialize the cursor
{
    int i = 0;
    for (; i < size - 1; i++)
    {
        list[ i ].next = i + 1;
    }
    list[ size ].next = 0;
}

pos curser_alloc(LIST list []) // get node from the cursor
{
    pos p;
    p = list[0].next;
    list[0].next = list[p].next;
    list[p].next = 0;
    return p;
}
//********************* string Function **************************
int is_valid(string str)                 // check if the string are valid or not
{
    int i =0, n = str_len(str);
    boolean b = 0 ;
    if(str[0] == ' ' || str[0]== '\n' || equal(str, ""))  // if the first is space trim the string
    {
        return 0 ;
    }
    for(; i<n ; i++)
    {
        if((str[i]>'z' || str[i]<'A' || str[i]>'Z'&&str[i]<'a') && str[i]!= ' ' ) // if the name contain the unlike string
        {
            return 0 ;
        }
    }
    return 1 ;
}
void trim_str(string s) // to put '\0' to end of string
{
    int y = 0, j = 0;
    while(s[y]== ' ' && s[y]!='\0') // if begin with space
    {
        y++;
    }
    for( ; s[y]!='\0' ; y++, j++ )         // shift the space
    {
        s[j] = s[y];
    }
    s[j] = '\0';
    int i = str_len(s)-1;
    while (s[i] != '\n' && s[i] != '\0' &&i < MAX_d-1)
    {
        i++;
    }
    s[i] = '\0';
}

void copy_string(string s, string s2) // copy string
{
    int i;
    for (i = 0; s2[i] != '\0'; ++i)
        s[i] = s2[i];

    s[i] = '\0';

    return s;
}

int str_len(string s) // length of string
{
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

boolean equal(string s, string s2) // compare the two string
{
    int i = 0;
    while (i != str_len(s))
    {
        if (s[i] != s2[i])
            return 0;
        else
            i++;
    }
    return 1;
}
