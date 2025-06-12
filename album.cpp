#include "album.h"
#include <iostream>
#include <unordered_map>
#include <iomanip>
using namespace std;
Album::Album() : head(nullptr) {}
Album::~Album()
{
    clearAlbum();
}

void Album::addPhoto(string name, Date date, string description, int position)
{
    Photo *newPhoto = new Photo(name, date, description);

    if (position == 0 || !head)
    {
        newPhoto->next = head;
        head = newPhoto;
    }

    else if (position == -1)
    {
        if (!head)
        {
            head = newPhoto;
        }
        else
        {
            Photo *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newPhoto;
        }
    }

    else
    {
        Photo *temp = head;
        for (int i = 0; i < position - 1 && temp->next; i++)
        {
            temp = temp->next;
        }
        newPhoto->next = temp->next;
        temp->next = newPhoto;
    }
    cout << "Đã thêm ảnh: " << name << endl;
}

Photo *Album::searchPhoto(string name)
{
    Photo *temp = head;
    while (temp)
    {
        if (temp->name == name)
        {
            cout << "\n=== KẾT QUẢ TÌM KIẾM THEO TÊN \"" << name << "\" ===\n";
            cout << "┌────────────────────────────────────────────────────────┐\n";
            cout << "│    Tên ảnh    │    Ngày    │      Mô tả              │\n";
            cout << "├────────────────────────────────────────────────────────┤\n";
            cout << "│ " << setw(13) << temp->name << " │ "
                 << setw(10) << temp->date.toString() << " │ "
                 << setw(20) << temp->description << " │\n";
            cout << "└────────────────────────────────────────────────────────┘\n";
            return temp;
        }
        temp = temp->next;
    }
    cout << "\nKhông tìm thấy ảnh có tên \"" << name << "\".\n";
    return nullptr;
}

void Album::searchByDate(const Date &targetDate)
{
    Photo *current = head;
    bool found = false;
    int count = 0;

    cout << "\n=== KẾT QUẢ TÌM KIẾM THEO NGÀY " << targetDate.toString() << " ===\n";
    cout << "┌────────────────────────────────────────────────────────┐\n";
    cout << "│ STT │    Tên ảnh    │    Ngày    │      Mô tả         │\n";
    cout << "├────────────────────────────────────────────────────────┤\n";

    while (current)
    {
        if (current->date == targetDate)
        {
            count++;
            cout << "│ " << setw(3) << count << " │ "
                 << setw(13) << current->name << " │ "
                 << setw(10) << current->date.toString() << " │ "
                 << setw(20) << current->description << " │\n";
            found = true;
        }
        current = current->next;
    }

    cout << "└────────────────────────────────────────────────────────┘\n";
    if (!found)
    {
        cout << "Không tìm thấy ảnh nào vào ngày " << targetDate.toString() << ".\n";
    }
    else
    {
        cout << "Tìm thấy " << count << " ảnh.\n";
    }
}

void Album::searchByDescriptionKeyword(const string &keyword)
{
    Photo *current = head;
    bool found = false;
    int count = 0;

    cout << "\n=== KẾT QUẢ TÌM KIẾM THEO TỪ KHÓA \"" << keyword << "\" ===\n";
    cout << "┌────────────────────────────────────────────────────────┐\n";
    cout << "│ STT │    Tên ảnh    │    Ngày    │      Mô tả         │\n";
    cout << "├────────────────────────────────────────────────────────┤\n";

    while (current)
    {
        if (current->description.find(keyword) != string::npos)
        {
            count++;
            cout << "│ " << setw(3) << count << " │ "
                 << setw(13) << current->name << " │ "
                 << setw(10) << current->date.toString() << " │ "
                 << setw(20) << current->description << " │\n";
            found = true;
        }
        current = current->next;
    }

    cout << "└────────────────────────────────────────────────────────┘\n";
    if (!found)
    {
        cout << "Không tìm thấy ảnh nào chứa từ khóa \"" << keyword << "\" trong mô tả.\n";
    }
    else
    {
        cout << "Tìm thấy " << count << " ảnh.\n";
    }
}

void Album::deletePhoto(string name, bool saveToTrash)
{
    if (!head)
    {
        cout << "Album trống!\n";
        return;
    }

    ofstream trashFile;
    if (saveToTrash)
    {
        trashFile.open("trash.txt", ios::app);
        if (!trashFile.is_open())
        {
            cerr << "[Lỗi] Không thể mở file trash.txt để ghi!\n";
            return;
        }
    }

    if (head->name == name)
    {
        Photo *temp = head;
        head = head->next;
        if (saveToTrash)
        {
            trashFile << temp->name << "|"
                      << temp->date.toString() << "|"
                      << temp->description << "\n";
        }
        delete temp;
        cout << "Ảnh '" << name << "' đã bị xóa" << (saveToTrash ? " và ghi vào trash.txt" : "") << "!\n";
        if (saveToTrash)
            trashFile.close();
        return;
    }

    Photo *current = head;
    while (current->next && current->next->name != name)
    {
        current = current->next;
    }

    if (current->next)
    {
        Photo *toDelete = current->next;
        current->next = current->next->next;
        if (saveToTrash)
        {
            trashFile << toDelete->name << "|"
                      << toDelete->date.toString() << "|"
                      << toDelete->description << "\n";
        }
        delete toDelete;
        cout << "Ảnh '" << name << "' đã bị xóa" << (saveToTrash ? " và ghi vào trash.txt" : "") << "!\n";
    }
    else
    {
        cout << "Không tìm thấy ảnh '" << name << "'\n";
    }

    if (saveToTrash)
        trashFile.close();
}

void Album::updatePhoto(string name, Date newDate, string newDesc)
{
    Photo *temp = searchPhoto(name);
    if (temp)
    {
        temp->date = newDate;
        temp->description = newDesc;
        cout << "Đã cập nhật ảnh: " << name << endl;
    }
    else
    {
        cout << "Không tìm thấy ảnh '" << name << "'\n";
    }
}
void Album::displayAlbum()
{
    Photo *temp = head;
    if (!temp)
    {
        cout << "Album trống!\n";
        return;
    }
    cout << "Danh sách ảnh trong album:\n";
    while (temp)
    {
        cout << "- " << temp->name << " | "
             << temp->date.toString() << " | "
             << temp->description << endl;
        temp = temp->next;
    }
}
void Album::removeDuplicates(bool useMap)
{
    if (!head || !head->next)
    {
        cout << "Không có ảnh nào hoặc chỉ có một ảnh.\n";
        return;
    }

    cout << "Đang xóa ảnh trùng lặp " << (useMap ? "sử dụng Map" : "sử dụng vòng lặp") << "...\n";

    if (useMap)
    {
        unordered_map<string, bool> seen;
        Photo *current = head;
        Photo *prev = nullptr;
        int count = 0;

        while (current)
        {
            if (seen[current->name])
            {
                Photo *toDelete = current;
                if (prev)
                {
                    prev->next = current->next;
                }
                else
                {
                    head = current->next;
                }
                current = current->next;
                delete toDelete;
                count++;
            }
            else
            {
                seen[current->name] = true;
                prev = current;
                current = current->next;
            }
        }
        cout << "Đã xóa " << count << " ảnh trùng lặp.\n";
    }
    else
    {
        Photo *node1 = head;
        int count = 0;
        while (node1)
        {
            Photo *node2 = node1;
            while (node2->next)
            {
                if (node1->name == node2->next->name)
                {
                    Photo *duplicate = node2->next;
                    node2->next = node2->next->next;
                    delete duplicate;
                    count++;
                }
                else
                {
                    node2 = node2->next;
                }
            }
            node1 = node1->next;
        }
        cout << "Đã xóa " << count << " ảnh trùng lặp.\n";
    }

    cout << "Danh sách ảnh sau khi xóa trùng lặp:\n";
    displayAlbum();
}
void Album::showAllDuplicates()
{
    if (!head || !head->next)
    {
        cout << "Không có ảnh nào hoặc chỉ có một ảnh.\n";
        return;
    }

    unordered_map<string, int> nameCount;

    Photo *current = head;
    while (current)
    {
        nameCount[current->name]++;
        current = current->next;
    }

    bool found = false;
    current = head;
    cout << "Các ảnh trùng tên (kể cả lặp lại):\n";
    while (current)
    {
        if (nameCount[current->name] > 1)
        {
            found = true;
            cout << "- " << current->name << " | "
                 << current->date.toString() << " | "
                 << current->description << "\n";
        }
        current = current->next;
    }

    if (!found)
    {
        cout << "Không có ảnh trùng tên.\n";
    }
}

void Album::clearAlbum()
{
    while (head)
    {
        Photo *temp = head;
        head = head->next;
        delete temp;
    }
    cout << "Album đã được xóa sạch.\n";
}
