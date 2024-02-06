#include <iostream>

using namespace std;

struct node
{
    char name[20];
    int count;
    struct node *child[20];
} *root;

class trees
{
public:


    trees()
    {
        root = NULL;
    }


     void create()
{

    root = new node();
    cout << "Enter name of book: "<<endl;
    cin >> root->name;
    cout << "Enter no. of chapters in book: ";
    cin >> root->count;


    for (int i = 0;i < root->count; i++)
    {
        root->child[i] = new node;
        cout << "Enter Chapter name: "<<endl;
        cin >> root->child[i]->name;
        cout << "Enter no. of sections in Chapter " << root->child[i]->name << ": ";
        cin >> root->child[i]->count;

        for (int j = 0; j < root->child[i]->count; j++)
        {
            root->child[i]->child[j] = new node;
            cout << "Enter Section " << j + 1 << " name: ";
            cin >> root->child[i]->child[j]->name;
            cout<<"enter no of subsections:"<<endl;
            cin >> root->child[i]->child[j]->count;
            
            for(int k=0;k<root->child[i]->child[j]->count;k++){

            root->child[i]->child[j]->child[k]=new node();
            cout<<"enter name of subsection:"<<endl;
            cin>>root->child[i]->child[j]->child[k]->name;
            }
        }
    }
}

void display()
{


    
        cout << "\n-----Book Info---";
        cout << "\n Book title: " << root->name<<endl;
        

        for (int i = 0; i <root->count; i++)
        {
            cout << "\n Chapter " << i + 1<<endl;
            cout << " " << root->child[i]->name<<endl;


            for (int j = 0; j < root->child[i]->count; j++)
            {
                cout << "\n " << root->child[i]->child[j]->name<<endl;
                
                for(int k=0;k<root->child[i]->child[j]->count;k++){
               cout<<"  "<<root->child[i]->child[j]->child[k]->name<<endl;
              }
            }
        }
    }
};

int main()
{
   trees t;
   t.create();
   t.display();
   return 0;
}
