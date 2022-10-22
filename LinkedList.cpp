//
//Name: Harshil Patel
//
//Create a Doubly Linked List template, create linked list for students
//Present User with command menu options
//Use ASCII art for display options

#include <iostream>
#include <string>
using namespace std;

//Student class
class Student{
private:
    string firstName;
    string lastName;
    string mNumber;
    float gpa;
    string birthday;
    int age;
    
public:
    //Constructor
    Student(string first, string last, string id, string birth, float grade = 0.0){
        firstName = first;
        lastName = last;
        mNumber = id;
        gpa = grade;
        birthday = birth;
        
        //Set the age of this student
        SetAge();
    }
    
    //GetName
    string GetName(){ return firstName + " " +lastName; }
    
    //Return mNumber integer
    int GetMNumber(){
        string number = mNumber;
        //If mNumber starts with M or m, remove it
        if ((number.at(0) == 'M') || (number.at(0) == 'm')){
            number.erase(0,1);
        }
        return stoi(number);
    }
    
    string GetMNumberString(){ return mNumber; }
    
    void SetAge(){
        cout<<"\nEnter Age: ";
        cin>>age;
    }
    
    //Return Age
    int GetAge(){ return age; }
    
    //Overload < operator
    friend bool operator<(Student& student1, Student& student2){
        if (student1.GetMNumber() < student2.GetMNumber()){
            return true;
        }
        return false;
    }
    
    //Overload > operator
    friend bool operator>(Student& student1, Student& student2){
        if (student1.GetMNumber() > student2.GetMNumber()){
            return true;
        }
        return false;
    }
    
    //Overload == operator
    friend bool operator==(Student& student1, Student& student2){
        if (student1.GetMNumber() == student2.GetMNumber()){
            return true;
        }
        return false;
    }
    
    void DisplayStudent(){
        cout<<"\nName: "<<GetName();
        cout<<"\nmNumber: "<<GetMNumberString();
        cout<<"\nAge: "<<GetAge()<<endl<<endl;
    }
};

//Node Class
class Node{
public:
    //Use Student type, this class can be changed into a template to use for any type.
    Student* data;
    Node* next;
    Node* prev;
    
    //Initialization Constructor
    Node(Student* input){
        data = input;
        next = NULL;
        prev = NULL;
    }
};

//Doubly Linked List Class Template
template <class T>
class LinkedList{
private:
    Node* head;
    Node* tail;
    
    int location = 1;
    
public:
    //Initialize Constructor to make head and tail both null
    LinkedList(){
        head = NULL;
        tail = NULL;
    }
    
    //Adds item to linked list
    void AddItem(Node* newNode){
        //If it is the first element added to list, head and tail are same
        if (head == NULL){
            head = newNode;
            tail = newNode;
        }
        //Add item to the end of the list
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    //Finds search node in list, if found node is deleted
    Node* GetItem(Node* searchNode){
        //currNode will store the same value as searchNode for returning purposes
        Node* currNode = new Node(*searchNode);
        
        //Check if searchNode is in the list
        if (IsInList(searchNode)){
            Node* prevNode = searchNode->prev;
            Node* nextNode = searchNode->next;
            
            //The following lines will rearrange the list before deleting the searchNode
            
            //If the previous node is not null, make the node after it nextNode, which is the node after searchNode
            if (prevNode != NULL){
                prevNode->next = nextNode;
            }
            //If the next node is not null, make the node before it prevNode, which is the node before currentNode
            if (nextNode != NULL){
                nextNode->prev = prevNode;
            }
            //If searchNode is head, make the new head it's nextNode
            if (searchNode == head){
                head = nextNode;
            }
            //If searchNode is tail, mae the new tail it's prevNode
            if (searchNode == tail){
                tail = prevNode;
            }
            
            //delete the search node and return the currNode for GetItem
            delete searchNode;
            return currNode;
        }
        //If node does not exist in list, return null
        else{
            return NULL;
        }
    }
    
    //Check if searchNode is in list
    bool IsInList(Node* searchNode){
        Node* currNode = head;
        //Iterate through list until you find a node with the same data as searchNode
        while (currNode != NULL){
            if (currNode->data == searchNode->data){
                return true;
            }
            currNode = currNode->next;
        }
        return false;
    }
    
    //Check if list is empty
    bool IsEmpty(){
        if (head != NULL){
            return false;
        }
        return true;
    }
    
    //Return the Node with a certain mNumber
    Node* ReturnNode(string id){
        Node* currNode = head;
        //Iterate through list until you find a node with the same mNumber as id
        while (currNode != NULL){
            if (currNode->data->GetMNumberString() == id){
                return currNode;
            }
            currNode = currNode->next;
        }
        return NULL;
    }
    
    //return size of list
    int size(){
        int counter = 0;
        Node* currNode = head;
        //start at head and increment counter until we reach null data
        while (currNode != NULL){
            counter += 1;
            currNode = currNode->next;
        }
        return counter;
    }
    
    //See the next node after current location
    Node* SeeNext(){
        Node* currNode = head;
        //If list is empty, display error message and return null
        if (IsEmpty()){
            cout<<"ERROR: List is empty, cannot see next!\n\n";
            return NULL;
        }
        if (location >= size()){
            return NULL;
        }
        //Iterate through list until we reach current location
        for (int i = 0; i < location; i++){
            if ((currNode) && (currNode!= NULL)){
                currNode = currNode->next;
            }
        }
        //Incremenent location for next SeeNext() call
        location += 1;
        
        //display message if next location is null
        return currNode;
    }
    
    //go to the node at index, index starts at 1
    Node* SeeAt(int index){
        //If list is empty, display error message and return null
        if (IsEmpty()){
            cout<<"ERROR: List is empty, cannot see anything!\n\n";
            return NULL;
        }
        //If index is larger than size, display message
        if (index > size()){
            cout<<"We are past the end of the list.\n";
            return NULL;
        }
        //If index is 1, return head
        Node* currNode = head;
        if (index == 1){
            return currNode;
        }
        //Iterate through list until we reach index
        for (int i = 1; i < index; i++){
            if ((currNode) && (currNode!= NULL)){
                currNode = currNode->next;
            }
            //Change location to the node we are going to
            location += 1;
        }
        return currNode;
    }
    
    //Reset location back to 1
    void Reset(){
        location = 1;
    }
        
    //Overload < operator
    bool operator<(LinkedList const location){
        return false;
    }
    
    //Overload > operator
    bool operator>(LinkedList const location){
        return false;
    }
    
    //Overload == operator
    bool operator==(LinkedList const location){
        return false;
    }
    
    //ASCII art for arrow
    void ArrowArt(){
        cout<<"  ;;;;;"<<endl;
        cout<<"  ;;;;;"<<endl;
        cout<<"  ;;;;;"<<endl;
        cout<<"  ;;;;;"<<endl;
        cout<<"  ;;;;;"<<endl;
        cout<<"..;;;;;.."<<endl;
        cout<<" ':::::'"<<endl;
        cout<<"   ':`  "<<endl;
    }
    
    //Display the whole list
    void DisplayList(){
        //ASCII art for whole list
        cout<<" ,---.   ,--.             ,--.                 ,--.      ,--.   ,--.        ,--."<<endl;
        cout<<"'   .-',-'  '-.,--.,--. ,-|  | ,---. ,--,--, ,-'  '-.    |  |   `--' ,---.,-'  '-."<<endl;
        cout<<" `.  `-.'-.  .-|  ||  |' .-. || .-. :|      \'-.  .-'     |  |   ,--.(  .-''-.  .-'"<<endl;
        cout<<"  .-'    | |  |  '  ''  '\ `-' |\   --.|  ||  |  |  |      |  '--.|  |.-'  `) |  |"<<endl;
        cout<<"`-----'  `--'   `----'  `---'  `----'`--''--'  `--'      `-----'`--'`----'  `--'"<<endl;
        
        Node* currNode = head;
        //If list is empty, display error message
        if (IsEmpty()){
            cout<<"List is empty, cannot display anything!\n\n";
        }
        else{
            while (currNode != NULL){
                ArrowArt();
                currNode->data->DisplayStudent();
                currNode = currNode->next;
            }
        }
        
        cout<<",------.           ,--.            ,---.    ,--.   ,--.        ,--."<<endl;
        cout<<"|  .---',--,--,  ,-|  |     ,---. /  .-'    |  |   `--' ,---.,-'  '-."<<endl;
        cout<<"|  `--, |      \' .-. |    | .-. ||  `-,     |  |   ,--.(  .-''-.  .-'"<<endl;
        cout<<"|  `---.|  ||  |\ `-' |    ' '-' '|  .-'     |  '--.|  |.-'  `) |  |"<<endl;
        cout<<"`------'`--''--' `---'      `---'`--'       `-----'`--'`----'  `--'"<<endl;
        
        delete currNode;
    }
    
    //Destructor
    virtual ~LinkedList(){
        Node* currentNode = head;
        while(currentNode){
            Node* deleteNode = currentNode;
            currentNode = currentNode->next;
            delete deleteNode;
        }
        
        cout<<"\nStudent list has been destroyed!\n\n";
    }
};

//display the meny
void displayMenu(){
    cout<<"\n=======Student Linked List=======\n\n";
    cout<<"Enter the number corresponding to each command: \n\n";
    cout<<"1 - Add Item\n";
    cout<<"2 - Get and Delete Item\n";
    cout<<"3 - Is List Empty\n";
    cout<<"4 - Check if Item is in List\n";
    cout<<"5 - See Item At Location\n";
    cout<<"6 - See Item At Next Location\n";
    cout<<"7 - Get Size of List\n";
    cout<<"8 - Reset the Location\n";
    cout<<"9 - Display A Student\n";
    cout<<"10 - Display Student List\n";
    cout<<"11 - Terminate Program\n\n";
    cout<<"12 - Help\n";
    cout<<"\n=================================\n";
}



void StudentArt(){
    cout<<" ,---.   ,--.             ,--.                 ,--.    "<<endl;
    cout<<"'   .-',-'  '-.,--.,--. ,-|  | ,---. ,--,--, ,-'  '-.  "<<endl;
    cout<<" `.  `-.'-.  .-|  ||  |' .-. || .-. :|      \'-.  .-'  "<<endl;
    cout<<"  .-'    | |  |  '  ''  '\ `-' |\   --.|  ||  |  |  |  "<<endl;
    cout<<"`-----'  `--'   `----'  `---'  `----'`--''--'  `--'    "<<endl;
}

int main() {
    
    displayMenu();
    
    //Create Student Linked List
    LinkedList<Student> studentList;
    Student* student = NULL;
    Node* node = NULL;
    
    //Declare Student Information Variables
    string firstName;
    string lastName;
    string mNumber;
    float gpa;
    string birthday;
    string id;
    
    //First Input
    int input;
    cout<<"\nEnter command: ";
    cin>>input;
    
    //loop until program is terminated
    while (input != 11){
        switch (input){
            //Add Item
            case 1:{
                cout<<"\nEnter First Name: ";
                cin>>firstName;
                cout<<"\nEnter Last Name: ";
                cin>>lastName;
                cout<<"\nEnter mNumber: ";
                cin>>mNumber;
                cout<<"\nEnter Birthday: ";
                cin>>birthday;
                cout<<"\nEnter GPA (if you have no GPA, enter 0): ";
                cin>>gpa;
                
                student = new Student(firstName, lastName, mNumber, birthday, gpa);
                node = new Node(student);
                studentList.AddItem(node);
                
                break;
            }
            //GetItem
            case 2:{
                cout<<"\nEnter the mNumber of the student that you are trying to go to (include 'M' of 'm'): ";
                cin >> id;
                
                //Find the student based on inputted ID
                Node* searchNode = studentList.ReturnNode(id);
                while(searchNode == NULL){
                    cout<<"The mNumber entered was not found, try again: ";
                    cin>>id;
                    searchNode = studentList.ReturnNode(id);
                }
                
                //Remove the student from the list
                cout<<endl<<studentList.GetItem(searchNode)->data->GetName()<<" was found and removed.\n";
                
                break;
            }
            //IsListEmpty
            case 3:{
                if (studentList.IsEmpty()){
                    cout<<"\nStudent List is Empty.\n";
                }
                else{
                    cout<<"\nStudent List is Not Empty.\n";
                }
                break;
            }
            //IsInList
            case 4:{
                cout<<"\nEnter the mNumber of the student that you are trying to find: ";
                cin >> id;
                Node* searchNode = studentList.ReturnNode(id);
                
                if (searchNode == NULL){
                    cout<<"\nThe mNumber entered was not in list";
                }
                else if (studentList.IsInList(searchNode)){
                    cout<<endl<<searchNode->data->GetName()<<" is in list.\n";
                }
                
                break;
            }
            //SeeAt
            case 5:{
                int index;
                cout<<"\nEnter the location (in list) of the student you want to go to: ";
                cin>>index;
                cout<<"\nYou have moved to "<<studentList.SeeAt(index)->data->GetName()<<endl;
                break;
            }
            //SeeNext
            case 6:{
                Node *searchNode = studentList.SeeNext();
                if (searchNode == NULL){
                    cout<<"There is no one left in the list, you are at the end!"<<endl;
                }
                else{
                    cout<<"You have moved to the next student:"<<searchNode->data->GetName()<<endl;
                }
                
                break;
            }
            //size
            case 7:{
                cout<<"\nSize of List: "<<studentList.size()<<endl;
                break;
            }
            //Reset
            case 8:{
                //reset location back to 1
                studentList.Reset();
                break;
            }
            //Display Student
            case 9:{
                cout<<"\nEnter the mNumber of the student that you would like to display (include 'M'): ";
                cin >> id;
                Node* searchNode = studentList.ReturnNode(id);
                
                if (searchNode == NULL){
                    cout<<"\nThe mNumber entered was not in list";
                }
                else if (studentList.IsInList(searchNode)){
                    StudentArt();
                    searchNode->data->DisplayStudent();
                }
                break;
            }
            //Display Student List
            case 10:{
                studentList.DisplayList();
                break;
            }
            //Help
            case 12:{
                displayMenu();
                break;
            }
            
            //Default case for invalid inputs
            default:
                cout<<"This input is not valid, try again: ";
                cin>>input;
        }
        
        //Command for next iteration
        cout<<"\nEnter another command: ";
        cin>>input;
    }
    
    cout<<"\nProgram has ended!\n\n";
    
    return 0;
}
