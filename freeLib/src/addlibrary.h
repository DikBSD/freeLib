#ifndef ADDLIBRARY_H
#define ADDLIBRARY_H

#include <QDialog>
#include <QItemSelectionModel>

#include "importthread.h"
#include "common.h"
#include "library.h"

namespace Ui {
class AddLibrary;
}

class AddLibrary : public QDialog
{
    Q_OBJECT

public:
    explicit AddLibrary(QWidget *parent = 0);
    ~AddLibrary();
    //int exec();
    void AddNewLibrary(SLib &lib);
    void StartImport(SLib &Lib);
    void SelectLibrary(int idLib);
    bool IsLibraryChanged() const;
    
private:
    Ui::AddLibrary *ui;
    ImportThread *imp_tr_;
    QThread *thread_;
    int idCurrentLib_;
    bool bLibChanged_;
    QStringList LogList_;

    void UpdateLibList();
    void SaveLibrary(int idLib, SLib& Lib);
    // ������������ ������ ��������� � ������� ��� ������� ����������
    void MakeDirsList();
    // ��������� �����������/������������� ���������, � ����������� �� ����� ������ ������� ������ �����
    void SetEnabledOrDisabledControllsOfBooksDirs();
    // ��������� �����������/������������� ���������, � ����������� �� ������� ��������� ������ ������� ������ �����
    void SetEnabledOrDisabledControllsOfSelectedStateItemBooksDirs();
    // ��������� � ������� groups ��� ����������� ������
    void AddGroupToSQLite(qlonglong libID);

private slots:
    void LogMessage(QString msg);
    void InputINPX();
    void SelectBooksDir();
    void StartImport();
    void SelectLibrary();
    void DeleteLibrary();
    void Add_Library();
    void EndUpdate();
    void terminateImport();
    void reject();
    void ExistingLibsChanged();
    void ExportLib();
    void ButtonSaveLogClicked();
    // ���������� ������ �������� � ������� � ������ ��������� ����������
    void AddBooksDirToList();
    // �������� ���������� �������� � ������� �� ������ ��������� ����������
    void DeleteDirFromBookDirsList();
    // ���������� ������� ����� � ������ ����� ���� ����������
    void InsertItemToBookDirsList();
    // ���������� �������� ����� �� ������ ����� ���� ����������
    void RemoveItemFromBookDirsList();
    // ���������� ������� ���������/������ ��������� ����� ������ ���� ����������
    void SelectionChangedBookDirsList(const QItemSelection& /*selected*/, const QItemSelection& /*deselected*/);

signals:
    void break_import();
};

#endif // ADDLIBRARY_H
