#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractMessageHandler>

#include "aboutwindow.h"
#include "types.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;
    AboutWindow about;
    QString filename;

    void updateTitle();
    bool validXML();
    void moveCursor(int line, int column);

private slots:
    void changedParameter();
    void changedXML();
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};


class MessageHandler : public QAbstractMessageHandler
{
public:
    MessageHandler()
        : QAbstractMessageHandler(0)
    {
    }

    QString statusMessage() const
    {
        return m_description;
    }

    int line() const
    {
        return m_sourceLocation.line();
    }

    int column() const
    {
        return m_sourceLocation.column();
    }

protected:
    virtual void handleMessage(QtMsgType type, const QString &description,
                               const QUrl &identifier, const QSourceLocation &sourceLocation)
    {
        Q_UNUSED(type);
        Q_UNUSED(identifier);

        m_messageType = type;
        m_description = description;
        m_sourceLocation = sourceLocation;
    }

private:
    QtMsgType m_messageType;
    QString m_description;
    QSourceLocation m_sourceLocation;
};

#endif // MAINWINDOW_H
