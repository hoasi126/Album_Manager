#include "file_io.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

bool loadAlbumFromFile(const string& filePath, Album& album) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "[Lỗi] Không thể mở file để đọc: " << filePath << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, dateStr, description;

        if (!getline(ss, name, '|') ||
            !getline(ss, dateStr, '|') ||
            !getline(ss, description)) {
            cerr << "[Cảnh báo] Bỏ qua dòng không hợp lệ: " << line << endl;
            continue;
        }

        int d, m, y;
        if (sscanf(dateStr.c_str(), "%d/%d/%d", &d, &m, &y) != 3) {
            cerr << "[Cảnh báo] Ngày không hợp lệ: " << dateStr << endl;
            continue;
        }

        album.AddPhoto(name, Date(d, m, y), description);
    }

    file.close();
    return true;
}

bool saveAlbumToFile(const string& filePath, const Album& album) {
    ofstream file(filePath);
    if (!file.is_open()) {
        cerr << "[Lỗi] Không thể mở file để ghi: " << filePath << endl;
        return false;
    }

    Photo* temp = album.getHead();
    while (temp) {
        file << temp->name << "|"
             << temp->date.toString() << "|"
             << temp->description << "\n";
        temp = temp->next;
    }

    file.close();
    return true;
}
