#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qtextbrowser.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolButton>
#include <QSqlQuery>
#include <QtWidgets/QTreeWidgetItem>
#include <QBuffer>
#include <QMenu>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QTcpServer>
#include <QSystemTrayIcon>

#include "helpdialog.h"
#include "dropform.h"
#include "opds_server.h"
#include "common.h"

namespace Ui {
class MainWindow;
}

struct Stag
{
    QPixmap pm;
    int id;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool IsErrorQuit();
    
private:
    Ui::MainWindow *ui;
    opds_server opds_;
    QSystemTrayIcon *trayIcon_;
    DropForm *pDropForm_;
    HelpDialog *pHelpDlg_;
    QToolButton* tbClear_;
    QString lastSearchSymbol_;
    QMenu TagMenu_;
    QObject* currentListForTag_;
    QList<Stag> tagsPicList_;
    QToolButton *FirstButton_;
    QToolButton *langBtnHash_;

    int idCurrentLanguage_;
    uint idCurrentAuthor_;
    uint idCurrentGenre_;
    uint idCurrentSerial_;
    uint idCurrentBookForAuthor_;
    uint idCurrentBookForGenre_;
    uint idCurrentBookForSeria_;
    bool bUseTag_;
    bool bShowDeleted_;
    QString noSeries_;
    bool errorQuit_;

private:
    QPixmap GetTagFromTagsPicList(int id) const;
    // ���������� ���� ������� ����� ������ ������������
    void UpdateTagsMenu();
    // ���������� ��������� ������ ����� ����� ������ ������������ ��� ������ ���� � ������� ������ ����
    void UpdateBookLanguageControls();
    // ���������� ��������� ���� �������� ���� �� ������ ������������
    void UpdateExportMenu();
    
    // ���������� �������� ������ ������� �� ���� ��� ��������� ����������
    void FillAuthors();
    // ���������� �������� ������ ����� �� ���� ��� ��������� ����������
    void FillSerials();
    // ���������� �������� ������ ������ �� ���� ��� ��������� ����������
    void FillGenres();
    // ����� (���������) ������, �����, �����, � ����������� �� ��������� ������� ������� �������, ����� ��� ������
    void FillListBooks();
    // ���������� �������� ������ ���� �� ������� � ������ �� ���� ��� ��������� ����������
    void FillListBooks(QList<uint> listBook, uint idCurrentAuthor);
    // ����������� �� �������, ����� ����� ��������� � ������ (���������� ����� � �����, ����������� ��������� ����)
    bool IsBookInList(const SBook &book) const;
    // ���������� ������ ���� � ������� �������, �����, ����
    void UpdateListPix(qlonglong id, int list, int tag_id);
    void UncheckBooks(QList<qlonglong> list);
    // ���������� �������� ����������
    void SaveLibPosition();
    void DeleteDropForm();

    // ����� ���� �� �������� ���������
    QList<uint> StartBooksSearch(
        const QString& sName, const QString& sAuthor, const QString& sSeria, uint idGenre,
        int idLanguage, int idCurrentTag, uint idCurrentRating, const QDate& dateFrom, const QDate& dateTo, int nMaxCount
    );
    // ��������� 1-�� �������� ������ ������� ��� �����
    void SelectFirstItemList();
    // ������ �� ���� '�������' ��� ������� ���������� � id = g_idCurrentLib
    int LoadLibraryPosition();
    // ���������� ����� ���������� ���� ������� ���������� � id = g_idCurrentLib
    void SaveCurrentBookLanguageFilter(const QString& lang);
    // ���������� ���������� �������� �� ������� �����
    void FiilRatingList();
    // ������� ������ ������� '���������'
    void MarkReadedBook(QTreeWidgetItem* bookItem, bool idReaded);
protected:
    APP_MODE mode;

protected:
    void showEvent(QShowEvent *ev);
    void changeEvent(QEvent* event);
    void resizeEvent(QResizeEvent * e);
    void closeEvent(QCloseEvent* event);
    void leaveEvent(QEvent *e);
    void dropEvent(QDropEvent* ev);
    void dragEnterEvent(QDragEnterEvent* ev);
    void dragLeaveEvent(QDragLeaveEvent*);
    void dragMoveEvent(QDragMoveEvent* ev);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

    // �����������/������������� ������ �������� � �������� ����� �� ������ ������������
    void ExportBookListBtnEnabled(bool Enable);

    void CheckParent(QTreeWidgetItem* parent);
    void CheckChild(QTreeWidgetItem* parent);
    void SendToDevice();
    void SendMail();

    // ���������� ���� ������ ���������
    void FillLibrariesMenu();
    //void FillBookList(QSqlQuery& query);
    void FillCheckedBookList(QList<book_info>& list, QTreeWidgetItem* item = nullptr, bool send_all = false, bool count_only = false, bool checked_only = false);
    void FillCheckedItemsBookList(QList<book_info>& list, QTreeWidgetItem* item, bool send_all, bool count_only);

    void ProcPath(QString path, QStringList* book_list);
    void ShowHeaderCoulmn(int nColumn, QString sSetting, bool bHide);

private slots:
    // ������ ������-����, ��������
    void ChangingLanguage(bool change_language = true);
    // ������ ������ �����/������ �� ������� ������ �� ������ ������ �������� �����
    void LangBtnSearch();
    // �������� � ����� ������������ ���� ��� ������� �������, ����� � ����
    void ContextMenu(QPoint point);
    // �������� � ����� ������������ ���� ���������� ������� ����
    void HeaderContextMenu(QPoint point);

    // ���������� ������ ����������� ������ �������
    void btnAuthor();
    // ���������� ������ ����������� ������ �����
    void btnSeries();
    // ���������� ������ ����������� ������ ������
    void btnGenres();
    // ���������� ������ ����������� ������ ������ ����
    void btnPageSearch();
    // ���������� ������ ����� �� ������� �����
    void StartSearch();
    // ���������� ��������� ������ � �������� ������ ������
    void searchChanged(QString str);
    void searchClear();

    // ������� ���������� ����
    void ExportAction();
    // ��������� �������� (������) �����
    void RatingAction();
    // ��������� �������� ���������/�� ��������� �����
    void ReadedAction();
    // ������ ���������� �����
    void EditBooks();
    // ���������� ������ "��������/����� ������� � ����" 
    void CheckBooks();
    // ���������� ������ "���������� ������������" 
    void ManageLibrary();
    // ���������� ������ "���������" 
    void Settings();

    // ��������� ����� �� �� �������� � �������� ����� � �������� � ���� ���������
    void MarkDeletedBooks();

    // ����� ���������� ��� �� ��������
    void SelectLibrary();
    // ����� (���������) ������ � ������ �������
    void SelectAuthor();
    // ����� (���������) ����� � ������ �����
    void SelectSeria();
    // ����� (���������) ����� � ������ ������
    void SelectGenre();
    // ����� (���������) ����� � ������ ����
    void SelectBook();

    // ���������� ����� ������ �� ������� � �������� �����
    void onAnchorClicked(const QUrl& link);
    // ������� � ���������� ������ � ������ ������� �� ����� �� ������-������ � �������� �����
    void MoveToAuthor(qlonglong id = -1, QString FirstLetter = "");
    // ������� � ��������� ����� � ������ ����� �� ����� �� �����-������ � �������� �����
    void MoveToSeria(qlonglong id = -1, QString FirstLetter = "");
    // ������� � ���������� ����� � ������ ������ �� ����� �� �����-������ � �������� �����
    void MoveToGenre(qlonglong id);

    // ���������� ��������� ������� �����
    void BookItemChanged(QTreeWidgetItem*,int);
    // ���������� �������� ����� �� ��������� �����
    void BookDblClick();
    
    // ���������� ������ �������� ���� � ���������� ������ ������� �����
    void TagSelect(int index);
    // ��������� ������ �������� ���� ��� ������/�����/�����
    void SetTag();

    void About();
    void HelpDlg();
    void ShowDropForm();
    void ChangingPort(int i);
    void ChangingTrayIcon(int index = -1, int color = -1);
    void TrayMenuAction(QSystemTrayIcon::ActivationReason reson);
    void dockClicked();
    void MinimizeWindow();

    // ���������� ������������ � ����� ���������� �� ����
    void on_actionSwitch_to_convert_mode_triggered();
    // ���������� ������������ � ����� ���������� �� ����
    void on_actionSwitch_to_library_mode_triggered();
    // ���������� ������������ � ����� ���������� �� ���������� �� ������� ������
    void on_btnSwitchToLib_clicked();
    // ���������� ������ ������� �������� �� ���������� �� ������� ������
    void on_btnPreference_clicked();
    // �������� ������� �������, �����, ������, ����, �������������� ���������� ����� � ���������� ������ ������ �� ������ ������������
    void on_comboBoxLanguageFilter_currentIndexChanged(const QString& arg1);

    //void on_splitter_splitterMoved(int pos, int index);

public slots:
    // ���������� ������ "�������� ���������� ����������"
    void newLibWizard(bool AddLibOnly=true);

signals:
    void window_loaded();
};

#endif // MAINWINDOW_H
