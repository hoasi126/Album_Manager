#include <iostream>
#include "album.h"
#include "file_io.h"

using namespace std;

void displayMenu(Album& album, const string& filePath) {
    int choice = 0;
    while (choice != 7) {
        cout << "\n=== QUẢN LÝ ALBUM ẢNH ===\n";
        cout << "1. Thêm ảnh mới\n";
        cout << "2. Xóa ảnh\n";
        cout << "3. Cập nhật thông tin ảnh\n";
        cout << "4. Hiển thị toàn bộ album\n";
        cout << "5. Xóa các ảnh trùng lặp\n";
        cout << "6. Tìm kiếm ảnh\n";
        cout << "7. Thoát\n";
        cout << "Chọn chức năng: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                string name, desc;
                int d, m, y;
                cout << "Nhập tên ảnh: ";
                getline(cin, name);
                cout << "Nhập ngày (dd mm yyyy): ";
                cin >> d >> m >> y;
                cin.ignore();
                cout << "Nhập mô tả: ";
                getline(cin, desc);
                album.AddPhoto(name, Date(d, m, y), desc);
                saveAlbumToFile(filePath, album);
                break;
            }
            case 2: {
                string name;
                cout << "Nhập tên ảnh cần xóa: ";
                getline(cin, name);
                album.deletePhoto(name);
                saveAlbumToFile(filePath, album);
                break;
            }
            case 3: {
                string name, desc;
                int d, m, y;
                cout << "Nhập tên ảnh cần cập nhật: ";
                getline(cin, name);
                cout << "Nhập ngày mới (dd mm yyyy): ";
                cin >> d >> m >> y;
                cin.ignore();
                cout << "Nhập mô tả mới: ";
                getline(cin, desc);
                album.updatePhoto(name, Date(d, m, y), desc);
                saveAlbumToFile(filePath, album);
                break;
            }
            case 4:
                album.displayAlbum();
                break;
            case 5:
                album.removeDuplicates();
                saveAlbumToFile(filePath, album);
                break;
            case 6: {
                string name;
                cout << "Nhập tên ảnh cần tìm: ";
                getline(cin, name);
                Photo* result = album.searchPhoto(name);
                if (result) {
                    cout << "Tìm thấy ảnh:\n";
                    cout << "- " << result->name << " | "
                         << result->date.toString() << " | "
                         << result->description << endl;
                } else {
                    cout << "Không tìm thấy ảnh '" << name << "'\n";
                }
                break;
            }
            case 7:
                cout << "Thoát chương trình!\n";
                break;
            default:
                cout << "Lựa chọn không hợp lệ! Vui lòng nhập lại\n";
        }
    }
}

int main() {
    Album album;
    string filePath = "album.txt";
    loadAlbumFromFile(filePath, album);
    displayMenu(album, filePath);
    return 0;
}
