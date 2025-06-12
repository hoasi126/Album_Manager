#include <iostream>
#include "album.h"
#include "file_io.h"

using namespace std;

void displayMenu(Album &album, const string &filePath)
{
    int choice = 0;
    while (choice != 10)
    {
        cout << "\n=== QUẢN LÝ ALBUM ẢNH ===\n";
        cout << "1. Thêm ảnh mới\n";
        cout << "2. Xóa ảnh\n";
        cout << "3. Cập nhật thông tin ảnh\n";
        cout << "4. Hiển thị toàn bộ album\n";
        cout << "5. Xóa các ảnh trùng lặp\n";
        cout << "6. Tìm kiếm ảnh theo tên\n";
        cout << "7. Tìm kiếm ảnh theo ngày\n";
        cout << "8. Tìm kiếm ảnh theo mô tả\n";
        cout << "9. Hiển thị các ảnh trùng\n";
        cout << "10. Thoát\n";
        cout << "Chọn chức năng: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string name, desc;
            int d, m, y, posChoice;
            cout << "Nhập tên ảnh: ";
            getline(cin, name);
            cout << "Nhập ngày (dd mm yyyy): ";
            cin >> d >> m >> y;
            cin.ignore();
            cout << "Nhập mô tả: ";
            getline(cin, desc);

            cout << "\nChọn vị trí thêm ảnh:\n";
            cout << "1. Thêm vào đầu danh sách\n";
            cout << "2. Thêm vào cuối danh sách\n";
            cout << "3. Thêm vào vị trí cụ thể\n";
            cout << "Lựa chọn của bạn: ";
            cin >> posChoice;
            cin.ignore();

            int position;
            switch (posChoice)
            {
            case 1:
                position = 0;
                break;
            case 2:
                position = -1;
                break;
            case 3:
            {
                // Hiển thị danh sách hiện tại để người dùng dễ chọn
                cout << "\nDanh sách ảnh hiện tại:\n";
                album.displayAlbum();
                cout << "\nNhập số thứ tự vị trí muốn thêm (1 là vị trí đầu tiên): ";
                cin >> position;
                cin.ignore();
                // Chuyển đổi từ số thứ tự (1-based) sang vị trí (0-based)
                position--;
                break;
            }
            default:
                cout << "Lựa chọn không hợp lệ, thêm vào cuối danh sách\n";
                position = -1;
            }

            album.addPhoto(name, Date(d, m, y), desc, position);
            saveAlbumToFile(filePath, album);
            break;
        }
        case 2:
        {
            string name;
            char saveToTrash;
            cout << "Nhập tên ảnh cần xóa: ";
            getline(cin, name);
            cout << "Lưu vào trash? (y/n): ";
            cin >> saveToTrash;
            cin.ignore();
            album.deletePhoto(name, saveToTrash == 'y' || saveToTrash == 'Y');
            saveAlbumToFile(filePath, album);
            break;
        }
        case 3:
        {
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
        {
            char useMap;
            cout << "Sử dụng Map để xóa trùng lặp? (y/n): ";
            cin >> useMap;
            cin.ignore();
            album.removeDuplicates(useMap == 'y' || useMap == 'Y');
            saveAlbumToFile(filePath, album);
            break;
        }
        case 6:
        {
            string name;
            cout << "Nhập tên ảnh cần tìm: ";
            getline(cin, name);
            Photo *result = album.searchPhoto(name);
            if (result)
            {
                cout << "Tìm thấy ảnh:\n";
                cout << "- " << result->name << " | "
                     << result->date.toString() << " | "
                     << result->description << endl;
            }
            else
            {
                cout << "Không tìm thấy ảnh '" << name << "'\n";
            }
            break;
        }
        case 7:
        {
            int d, m, y;
            cout << "Nhập ngày cần tìm (dd mm yyyy): ";
            cin >> d >> m >> y;
            cin.ignore();
            album.searchByDate(Date(d, m, y));
            break;
        }
        case 8:
        {
            string keyword;
            cout << "Nhập từ khóa cần tìm trong mô tả: ";
            getline(cin, keyword);
            album.searchByDescriptionKeyword(keyword);
            break;
        }
        case 9:
            album.showAllDuplicates();
            break;
        case 10:
            cout << "Thoát chương trình!\n";
            break;
        default:
            cout << "Lựa chọn không hợp lệ! Vui lòng nhập lại\n";
        }
    }
}

int main()
{
    Album album;
    string filePath = "album.txt";
    loadAlbumFromFile(filePath, album);
    displayMenu(album, filePath);
    return 0;
}
