#ifndef ALBUM_H
#define ALBUM_H
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
using namespace std;

struct Date
{
    int day, month, year;
    Date() {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    std::string toString() const
    {
        std::ostringstream oss;
        oss << (day < 10 ? "0" : "") << day << "/"
            << (month < 10 ? "0" : "") << month << "/"
            << year;
        return oss.str();
    }
    bool operator==(const Date &other) const
    {
        return day == other.day && month == other.month && year == other.year;
    }
};

struct Photo
{
    string name;
    Date date;
    string description;
    Photo *next;

    Photo(string n, Date d, string desc)
        : name(n), date(d), description(desc), next(nullptr) {}
};

class Album
{
private:
    Photo *head;

public:
    Album();
    ~Album();

    void addPhoto(string name, Date date, string description, int position);
    void deletePhoto(string name, bool saveToTrash);
    Photo *searchPhoto(string name);
    void searchByDate(const Date &targetDate);
    void searchByDescriptionKeyword(const string &keyword);
    void updatePhoto(string name, Date newDate, string newDesc);
    void displayAlbum();
    void removeDuplicates(bool useMap = false);
    void showAllDuplicates();
    void clearAlbum();
    Photo *getHead() const { return head; }
};

#endif
