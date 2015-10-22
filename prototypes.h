struct node {
    int value;
    struct node *next;
};

//********************************************
void rest();                                    //this is a time delay and clear line
void clear_screen(struct node *);               //this clears the screen

int length (struct node *);
void print_colors(struct node *);               //color printing
void print_normal(struct node *);               //regular printing
void print(struct node *, char);

//Options for how to enter nodes
void entering_menu(struct node **, struct node **);

struct node * insert_middle(struct node *, int, int); //adds a node where you want

struct node * push(struct node *, int);         //add to front of list
struct node * append(struct node *, struct node *, int);       //add to rear of list

struct node * sort_ascending(struct node *);    //sorts by ascending 0 to MAX
struct node * sort_decending(struct node *);    //sorts by decending 0 to MAX

//checks to see if the list is arranged properly
bool is_decending(struct node *);
//checks to see if the list is arranged properly
bool is_ascending(struct node *);

void the_menu(struct node *, struct node*);
struct node * sort_menu(struct node *);         //options for sorting list

//adds items according to manual input
void not_random_add(struct node **, struct node **, int);
//adds items in a random order
void random_add(struct node **, struct node **, int);
struct node * removing_entries(struct node *);  //menu for removing list items
struct node * clear(struct node *);             //clears all the items in the list
struct node * remove_node(struct node *, int);  //the spcific function for removing an item
//********************************************
