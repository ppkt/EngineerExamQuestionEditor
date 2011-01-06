#ifndef QUESTIONEDITOR_H
#define QUESTIONEDITOR_H

#include <QtGui/QMainWindow>
#include <QtCore>

namespace Ui {
    class QuestionEditor;
}

class QuestionEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuestionEditor(QWidget *parent = 0);
    ~QuestionEditor();

private slots:
    void on_actionWyjd_triggered();
    void on_actionZapisz_triggered();
    void on_actionNowy_triggered();
    void on_newQuestion_clicked();
    void on_nextQuestion_clicked();
    void on_prevQuestion_clicked();

    void on_actionOtw_rz_triggered();

private:
    void updateOrder();

    QPointer<QFile> file;
    bool changed;
    Ui::QuestionEditor *ui;
};

#endif // QUESTIONEDITOR_H
