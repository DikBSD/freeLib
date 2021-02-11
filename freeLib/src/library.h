#ifndef LIBRARY_H
#define LIBRARY_H

#include <QMultiMap>
#include <QList>
#include <QDateTime>
#include "common.h"

class SAuthor
{
public:
    QString getName() const;
    int nTag;
    QString sFirstName;
    QString sLastName;
    QString sMiddleName;
};

struct SBook
{
    QString sName;
    QString sAnnotation;
    QString sImg;
    QString sArchive;
    QString sIsbn;
    QDate date;
    QString sFormat;
    QList<uint> listIdGenres;
    QList<uint> listIdAuthors;
    QList<uint> listIdGroups;
    uint idInLib;
    QString sFile;
    uint idSerial;
    uint idFirstAuthor;
    uint numInSerial;
    uint nSize;
    uchar nStars;
    uchar idLanguage;
    uchar nTag;
    QString sKeywords;
    bool bDeleted;
    bool bReaded;
    SBook()
    {
        idInLib = 0;
        idSerial = 0;
        idFirstAuthor = 0;
        numInSerial = 0;
        nSize = 0;
        nStars = 0;
        idLanguage = 0;
        nTag = 0;
        bDeleted = false;
        bReaded = false;
    }
};

struct SSerial
{
    QString sName;
    uchar nTag;
    SSerial()
    {
        nTag = 0;
    }
};

struct SGenre
{
    QString sName;
    ushort idParrentGenre;
    ushort nSort;
    SGenre()
    {
        idParrentGenre = 0;
        nSort = 0;
    }
};

class Group
{
private:
    QString Name_;
    uint Id_;
    bool Blocked_;
public:
    Group() {
        Name_ = ""; Id_ = 0; Blocked_ = false;
    };
    Group(const QString& Name, uint id, bool blocked) : Name_(Name), Id_(id), Blocked_(blocked) { };

    void setName(QString Name) { Name_ = Name; };
    void setId(uint Id) { Id_ = Id; };
    void setBlocked(bool blocked) { Blocked_ = blocked; };
    QString getName() const { return Name_; };
    QString getId() const { return Id_; };
    bool getBlocked() const { return Blocked_; };
};

struct SLib
{
    QString name;
    QString path;
    QString sInpx;
    bool bFirstAuthor;
    bool bWoDeleted;
    bool bLoaded;
    int nCurrentTab;
    uint uIdCurrentAuthor;
    uint uIdCurrentSeria;
    uint uIdCurrentGenre;
    uint uIdCurrentGroup;
    uint uIdCurrentBookForAuthor;
    uint uIdCurrentBookForSeria;
    uint uIdCurrentBookForGenre;
    uint uIdCurrentBookForGroup;
    QString sCurrentSearchingFilter;
    uint uCurrentTag;
    QString sCurrentBookLanguage;
    QHash<uint,SAuthor> mAuthors;
    QMultiHash<uint,uint> mAuthorBooksLink;
    QHash<uint,SBook> mBooks;
    QHash<uint,SSerial> mSerials;
    QHash<uint, Group> mGroups;
    QVector<QString> vLaguages;
    SLib()
    {
        bFirstAuthor = false;
        bWoDeleted = false;
        bLoaded = false;
        nCurrentTab = 0;
        uIdCurrentAuthor = 0;
        uIdCurrentSeria = 0;
        uIdCurrentGenre = 0;
        uIdCurrentGroup = 0;
        uIdCurrentBookForAuthor = 0;
        uIdCurrentBookForSeria = 0;
        uIdCurrentBookForGenre = 0;
        uIdCurrentBookForGroup = 0;
        uCurrentTag = 0;
    }
};

void loadBooksDataFromSQLiteToLibraryStructure(uint idLibrary);
void loadGenresFromSQLiteToLibraryStructure();
void loadGroupsFromSQLiteToLibraryStructure(uint idLibrary);

extern bool db_is_open;

extern SLib currentLib;
extern QMap<int,SLib> mLibs;
extern QMap <uint,SGenre> mGenre;

#endif // LIBRARY_H
