// #include <iostream>
// #include <sstream>
// #include "file_io.h"
// using namespace std;

// struct Date {
//     int day, month, year;
//     Date() {}
//     Date(int d, int m, int y) : day(d), month(m), year(y) {}

//     string toString() {
//         stringstream ss;
//         ss << day << "/" << month << "/" << year;
//         return ss.str();
//     }
// };

// struct Photo {
//     string name;
//     Date date;
//     string description;
//     Photo* next;

//     Photo(string n, Date d, string desc)
//         : name(n), date(d), description(desc), next(nullptr) {}
// };

// class Album {
// private:
//     Photo* head;
// public:
//     Album() : head(nullptr) {}
//     ~Album() {
//         clearAlbum();
//     }

//     void AddPhoto(string name, Date date, string description) {
//         Photo* newPhoto = new Photo(name, date, description);
//         newPhoto->next = head;
//         head = newPhoto;
//         cout << "Đã thêm ảnh: " << name << endl;
//     }

//     Photo* searchPhoto(string name) {
//         Photo* temp = head;
//         while (temp) {
//             if (temp->name == name) return temp;
//             temp = temp->next;
//         }
//         return nullptr;
//     }

//     void deletePhoto(string name) {
//         if (!head) return;
//         if (head->name == name) {
//             Photo* temp = head;
//             head = head->next;
//             delete temp;
//             cout << "Ảnh '" << name << "' đã bị xóa!\n";
//             return;
//         }
//         Photo* temp = head;
//         while (temp->next && temp->next->name != name) {
//             temp = temp->next;
//         }
//         if (temp->next) {
//             Photo* toDelete = temp->next;
//             temp->next = temp->next->next;
//             delete toDelete;
//             cout << "Ảnh '" << name << "' đã bị xóa!\n";
//         } else {
//             cout << "Không tìm thấy ảnh '" << name << "'\n";
//         }
//     }

//     void updatePhoto(string name, Date newDate, string newDesc) {
//         Photo* photo = searchPhoto(name);
//         if (photo) {
//             photo->date = newDate;
//             photo->description = newDesc;
//             cout << "Đã cập nhật ảnh: " << name << endl;
//         } else {
//             cout << "Không tìm thấy ảnh '" << name << "'\n";
//         }
//     }
//     void displayAlbum() {
//         Photo* temp = head;
//         if (!temp) {
//             cout << "Album trống!\n";
//             return;
//         }
//         cout << "Danh sách ảnh:\n";
//         while (temp) {
//             cout << "- " << temp->name << " | " << temp->date.toString() << " | " << temp->description << endl;
//             temp = temp->next;
//         }
//     }
//     void removeDuplicates() {
//         if (!head || !head->next) return;

//         Photo* node1 = head;

//         while (node1) {
//             Photo* node2 = node1;
//             while (node2->next) {
//                 if (node1->name == node2->next->name) {

//                     Photo* duplicate = node2->next;
//                     node2->next = node2->next->next;
//                     delete duplicate;
//                 } else {
//                     node2 = node2->next;
//                 }
//             }
//             node1 = node1->next;
//         }

//         cout << "Đã xóa các ảnh trùng lặp.\n";
//         displayAlbum();
//     }
//     void clearAlbum() {
//         while (head) {
//             Photo* temp = head;
//             head = head->next;
//             delete temp;
//         }
//     }
// };

// void displayMenu() {
//     Album album;
//     int choice;
//     while (choice != 7) {
//         cout << "\n=== QUẢN LÝ ALBUM ẢNH ===\n";
//         cout << "1. Thêm ảnh mới\n";
//         cout << "2. Xóa ảnh\n";
//         cout << "3. Cập nhật thông tin ảnh\n";
//         cout << "4. Hiển thị toàn bộ album\n";
//         cout << "5. Xóa các ảnh trùng lặp\n";
//         cout << "6. Tìm kiếm ảnh\n";
//         cout << "7. Thoát\n";
//         cout << "Chọn chức năng: ";
//         cin >> choice;
//         cin.ignore();

//         switch(choice) {
//             case 1: {
//                 string name, desc;
//                 int d, m, y;
//                 cout << "Nhập tên ảnh: ";
//                 getline(cin, name);
//                 cout << "Nhập ngày (dd mm yyyy): ";
//                 cin >> d >> m >> y;
//                 cin.ignore();
//                 cout << "Nhập mô tả: ";
//                 getline(cin, desc);
//                 album.AddPhoto(name, Date(d, m, y), desc);
//                 break;
//             }
//             case 2: {
//                 album.displayAlbum();
//                 string name;
//                 cout << "Nhập tên ảnh cần xóa: ";
//                 getline(cin, name);
//                 album.deletePhoto(name);
//                 break;
//             }
//             case 3: {
//                 string name, desc;
//                 int d, m, y;
//                 cout << "Nhập tên ảnh cần cập nhật: ";
//                 getline(cin, name);
//                 cout << "Nhập ngày mới (dd mm yyyy): ";
//                 cin >> d >> m >> y;
//                 cin.ignore();
//                 cout << "Nhập mô tả mới: ";
//                 getline(cin, desc);
//                 album.updatePhoto(name, Date(d, m, y), desc);
//                 break;
//             }
//             case 4:
//                 album.displayAlbum();
//                 break;
//             case 5:
//                 album.removeDuplicates();
//                 break;
//             case 6: {
//                 string name;
//                 cout << "Nhập tên ảnh cần tìm: ";
//                 getline(cin, name);
//                 Photo* result = album.searchPhoto(name);
//                 if (result) {
//                     cout << "Tìm thấy ảnh:\n";
//                     cout << "- " << result->name << " | "
//                          << result->date.toString() << " | "
//                          << result->description << endl;
//                 } else {
//                     cout << "Không tìm thấy ảnh '" << name << "'\n";
//                 }
//                 break;
//             }
//             case 7:
//                 cout << "Thoát chương trình!\n";
//                 break;
//             default:
//                 cout << "Lựa chọn không hợp lệ! Vui lòng nhập lại\n";
//         }
//     }
// }

// int main() {
//     displayMenu();
//     return 0;
// }
