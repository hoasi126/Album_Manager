#include "album.h"
#include<iostream>
using namespace std;
Album::Album() : head(nullptr) {}
Album::~Album() {
    clearAlbum();
}


void Album::AddPhoto(string name, Date date, string description){
    Photo* newPhoto = new Photo(name, date, description);
    newPhoto->next = head;
    head = newPhoto;
    cout << "Đã thêm ảnh: " << name << endl;
}
Photo* Album::searchPhoto(string name){
    Photo* temp = head;
    while(temp){
        if (temp->name == name) return temp;
        temp = temp->next;
    }
    return nullptr;
}
void Album::deletePhoto(string name){
    if(!head) return;
    if(head->name == name){
        Photo* temp = head;
        head = head->next;
        delete temp;
        cout << "Ảnh '" << name << "' đã bị xóa!\n";
        return;
    }
    Photo* temp = head;
    while(temp->next && temp->next-> name != name){
        temp = temp->next;
    } 
    if(temp->next){
        Photo* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Ảnh '" << name << "' đã bị xóa!\n";
    }
    else {
        cout << "Không tìm thấy ảnh '" << name << "'\n";
    }
}
void Album::updatePhoto(string name, Date newDate, string newDesc){
    Photo* temp = searchPhoto(name);
    if(temp){
        temp->date = newDate;
        temp->description = newDesc;
        cout << "Đã cập nhật ảnh: " << name << endl;
    }
    else {
        cout << "Không tìm thấy ảnh '" << name << "'\n";
    }
}
void Album::displayAlbum(){
    Photo* temp = head;
    if(!temp){
        cout << "Album trống!\n";
        return;
    }
    cout << "Danh sách ảnh trong album:\n";
    while(temp){
        cout << "- " << temp->name << " | "
             << temp->date.toString() << " | "
             << temp->description << endl;
        temp = temp->next;
    }
}
void Album::removeDuplicates(){
    if(!head || !head->next) return;
    Photo* node1 = head;
    while(node1){
        Photo* node2 = node1;
        while(node2->next){
            if(node1->name == node2->next->name){
                Photo* duplicate = node2->next;
                node2->next = node2->next->next;
                delete duplicate;
            } else {
                node2 = node2->next;
            }
        }
        node1 = node1->next;
    }
    cout << "Đã xóa các ảnh trùng lặp.\n";
    displayAlbum();
}
void Album::clearAlbum(){
    while(head){
        Photo* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "Album đã được xóa sạch.\n";
}

