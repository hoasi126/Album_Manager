#ifndef ALBUM_H
#define ALBUM_H
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
struct Date {
    int day, month, year;
    Date() {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << (day < 10 ? "0" : "") << day << "/"
            << (month < 10 ? "0" : "") << month << "/"
            << year;
        return oss.str();
    }

};


struct Photo {
    string name;
    Date date;
    string description;
    Photo* next;

    Photo(string n, Date d, string desc)
        : name(n), date(d), description(desc), next(nullptr) {}
};

class Album {
private:
    Photo* head;
public:
    Album();
    ~Album();
    void AddPhoto(string name, Date date, string description);
    void deletePhoto(string name);
    Photo* searchPhoto(string name);
    void updatePhoto(string name, Date newDate, string newDesc);
    void displayAlbum();
    void removeDuplicates();
    void clearAlbum();
    Photo* getHead() const { return head; }

};
#endif
