/*
for compiling
g++ -std=c++11 filename.cpp -o filename

for output
./filename

*/

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

int op, cnt = 0;

class node {
public:
    node *left;
    char word[50], mean[50];
    node *right;
};

class BT {
public:
    node *root;
    BT() {
        root = NULL;
    }

    void create();
    node *insert(node *, node *);
    void inorder(node *);
    void preorder(node *);
    void postorder(node *);
    void search(node *, char[]);
    void modify(node *, char[]);
    node* dit(node*, char[]);  // Corrected declaration
    node* findmin(node*);      // Corrected declaration
};

void BT::create() {
    int op;
    node *temp;
    do {
        temp = new node;
        cout << "Enter A Word: ";
        cin >> temp->word;
        cout << "Enter A Meaning: ";
        cin >> temp->mean;
        temp->left = temp->right = NULL;
        if (root == NULL) {
            root = temp;
        } else {
            root = insert(root, temp);
        }
        cout << "Want to insert again (enter 1 to continue and 0 to exit):";
        cin >> op;
    } while (op == 1);
}

node *BT::insert(node *root, node *temp) {
    if (strcmp(temp->word, root->word) < 0) {
        if (root->left == NULL) {
            root->left = temp;
        } else {
            insert(root->left, temp);
        }
    } else {
        if (root->right == NULL) {
            root->right = temp;
        } else {
            insert(root->right, temp);
        }
    }
    return root;
}

void BT::inorder(node *temp) {
    if (temp != NULL) {
        inorder(temp->left);
        cout << temp->word << "->" << temp->mean << ",";
        inorder(temp->right);
    }
}

void BT::preorder(node *temp) {
    if (temp != NULL) {
        cout << temp->word << "->" << temp->mean << ",";
        preorder(temp->left);
        preorder(temp->right);
    }
}

void BT::postorder(node *temp) {
    if (temp != NULL) {
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->word << "->" << temp->mean << ",";
    }
}

void BT::search(node *temp, char src[]) {
    if (temp != NULL) {
        if ((strcmp(temp->word, src)) == 0) {
            cout << "\nWord Found";
            cout << "\nWord: " << temp->word;
            cout << "\nMeaning: " << temp->mean;
            cnt++;
        } else {
            if ((strcmp(src, temp->word)) > 0) {
                search(temp->right, src);
                cnt++;
            } else {
                search(temp->left, src);
                cnt++;
            }
        }
    } else {
        cout << "\nWord Not Found";
    }
    cout << "\nTotal no of comparisons to search an element is: " << cnt;
}

void BT::modify(node *temp, char src[]) {
    if (temp != NULL) {
        if ((strcmp(temp->word, src)) == 0) {
            cout << "\nWord Found!";
            cout << "\nEnter New Meaning of word: " << temp->word;
            cin >> temp->mean;
        } else {
            if ((strcmp(temp->word, src)) < 0) {
                modify(temp->right, src);
            } else if ((strcmp(temp->word, src)) > 0) {
                modify(temp->left, src);
            }
        }
    } else {
        cout << "\n Word Not Found";
    }
}

node* BT::dit(node *root, char src[]) {
    if (root != NULL) {
        if ((strcmp(root->word, src)) > 0) {
            root->left = dit(root->left, src);
        } else {
            if (root->left == NULL && root->right == NULL) {
                delete root;
                root = NULL;
            } else {
                if (root->left == NULL && root->right != NULL) {
                    node *temp = root;
                    root = root->right;
                    strcpy(root->word, temp->word);
                    strcpy(root->mean, temp->mean);
                    temp->right = NULL;
                    delete temp; // Move delete statement here
                } else if (root->right == NULL) {
                    node *temp = root;
                    root = root->left;
                    strcpy(root->word, temp->word);
                    strcpy(root->mean, temp->mean);
                    temp->left = NULL;
                    delete temp; // Move delete statement here
                } else {
                    node *temp = findmin(root->right);
                    strcpy(root->word, temp->word);
                    strcpy(root->mean, temp->mean);
                    root->right = dit(root->right, temp->word);
                }
            }
        }
    }
    return root;
}

node* BT::findmin(node *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

int main() {
    BT b;
    char src[100];
    while (1) {
        cout << "\n\n1. Insert Binary Search Tree\n2. Display Inorder, Preorder, Postorder\n3. Search word";
        cout << "\n4. Modify the meaning of word\n5. Delete word from dictionary\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> op;

        switch (op) {
            case 1:
                b.create();
                break;

            case 2:
                cout << "\nInorder: ";
                b.inorder(b.root);
                cout << "\nPreorder: ";
                b.preorder(b.root);
                cout << "\n Postorder: ";
                b.postorder(b.root);
                break;

            case 3:
                cout << "Enter word want to search: ";
                cin >> src;
                b.search(b.root, src);
                break;

            case 4:
                cout << "\n Enter word to modify: ";
                cin >> src;
                b.modify(b.root, src);
                break;

            case 5:
                cout << "\n Enter word want to delete: ";
                cin >> src;
                b.dit(b.root, src);
                break;

            case 6:
                exit(0);
                break;

            default:
                cout << "\n Invalid Option";
                break;
        }
    }
    return 0;
}


//stl code
/*
#include <iostream>
#include <map>
#include <string>

class Dictionary {
public:
    std::map<std::string, std::string> wordMeaningMap;

    void insertWord(const std::string& word, const std::string& meaning) {
        wordMeaningMap[word] = meaning;
        std::cout << "Word inserted successfully!\n";
    }

    void displayDictionary() {
        std::cout << "Dictionary Contents:\n";
        for (const auto& pair : wordMeaningMap) {
            std::cout << pair.first << " -> " << pair.second << '\n';
        }
    }

    void searchWord(const std::string& word) {
        auto it = wordMeaningMap.find(word);
        if (it != wordMeaningMap.end()) {
            std::cout << "Word Found!\n";
            std::cout << "Word: " << it->first << "\nMeaning: " << it->second << '\n';
        } else {
            std::cout << "Word Not Found\n";
        }
    }

    void modifyMeaning(const std::string& word, const std::string& newMeaning) {
        auto it = wordMeaningMap.find(word);
        if (it != wordMeaningMap.end()) {
            std::cout << "Word Found!\n";
            it->second = newMeaning;
            std::cout << "Meaning modified successfully!\n";
        } else {
            std::cout << "Word Not Found\n";
        }
    }

    void deleteWord(const std::string& word) {
        auto it = wordMeaningMap.find(word);
        if (it != wordMeaningMap.end()) {
            wordMeaningMap.erase(it);
            std::cout << "Word deleted successfully!\n";
        } else {
            std::cout << "Word Not Found\n";
        }
    }
};

int main() {
    Dictionary dictionary;
    int op;
    std::string word, meaning;

    while (true) {
        std::cout << "\n1. Insert Word\n2. Display Dictionary\n3. Search Word\n4. Modify Meaning\n5. Delete Word\n6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> op;

        switch (op) {
            case 1:
                std::cout << "Enter a Word: ";
                std::cin >> word;
                std::cout << "Enter the Meaning: ";
                std::cin >> meaning;
                dictionary.insertWord(word, meaning);
                break;

            case 2:
                dictionary.displayDictionary();
                break;

            case 3:
                std::cout << "Enter the Word to Search: ";
                std::cin >> word;
                dictionary.searchWord(word);
                break;

            case 4:
                std::cout << "Enter the Word to Modify: ";
                std::cin >> word;
                std::cout << "Enter the New Meaning: ";
                std::cin >> meaning;
                dictionary.modifyMeaning(word, meaning);
                break;

            case 5:
                std::cout << "Enter the Word to Delete: ";
                std::cin >> word;
                dictionary.deleteWord(word);
                break;

            case 6:
                std::cout << "Exiting program...\n";
                return 0;

            default:
                std::cout << "Invalid Option\n";
                break;
        }
    }

    return 0;
}

*/
