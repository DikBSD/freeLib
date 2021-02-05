#ifndef IMPORTTHREAD_H
#define IMPORTTHREAD_H

#include <QThread>
#include <QSqlQuery>
#include <QStringList>

//способы обновления
#define UT_FULL 10
#define UT_DEL_AND_NEW 11
#define UT_NEW 12



void ClearLib(QSqlDatabase dbase, qlonglong id_lib, bool delete_only);


class ImportThread : public QObject
{
    Q_OBJECT
public:
    explicit ImportThread(QObject *parent = 0);
    void start(QString fileName, QString name, QString path, long ID, int update_type, bool save_only=false, bool firstAuthor=false, bool bWoDeleted=false);
    //void SaveLibrary();
    bool _loop;
signals:
    void Message(QString str);
    void End();
public slots:
    void process();
    void break_import();
protected:
    void importBooks(QString path,int &count);
    void importBooksToLibrary(QString path);

    void readFB2(const QByteArray &ba, QString file_name, QString arh_name, qint32 file_size=0);
    void readEPUB(const QByteArray &ba,QString file_name, QString arh_name,qint32 file_size=0);
    void readFB2_test(const QByteArray& ba,QString file_name,QString arh_name);
private:
    QString _InpxFileName;
    QString _LibName;
    QString _LibPath;
    bool _SaveOnly;
    int _UpdateType;
    bool _FirstAuthorOnly;
    bool _bWoDeleted;
    long _ExistingLibID;
    QSqlQuery *query;
    qlonglong AddSeria(QString str,qlonglong libID,int tag);
    qlonglong AddAuthor(QString str,qlonglong libID,qlonglong id_book,bool first_author,QString language,int tag);
    qlonglong AddBook(
        qlonglong star, QString name, qlonglong id_seria, int num_in_seria, QString file,
        int size, int IDinLib, bool deleted, QString format, QDate date, QString language,
        QString keys, qlonglong id_lib, QString archive, int tag, bool readed
    );

    qlonglong AddGenre(qlonglong id_book,QString janre,qlonglong id_lib,QString language);

};

#endif // IMPORTTHREAD_H
