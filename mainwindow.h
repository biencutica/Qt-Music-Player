
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>
#include <QMessageBox>
#include "song.h"

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void add_song();
    void delete_song();
    void send_song();
    void update_song();
    void filter();

private:
    void setupUI();

    QWidget* m_centralWidget;
    QHBoxLayout* main_HLayout;
    QVBoxLayout* m_centralVLayout;
    QVBoxLayout* m_rightVLayout;
    QVBoxLayout* m_rightHLayout;
    QVBoxLayout* m_leftVLayout;
    QFormLayout* m_leftFormLayout;
    QGridLayout* m_leftGridLayout;
    QHBoxLayout* m_buttons;

    // form layout
    QLabel* m_titleLable;
    QLineEdit* m_titleText;

    QLabel* m_artistLable;
    QLineEdit* m_artistText;

    QLabel* m_durationLable;
    QLineEdit* m_durationText;

    QLabel* m_linkLable;
    QLineEdit* m_linkText;

    QLabel* m_listSongsLabel;
    QListWidget* m_listSongs;

    QPushButton* add_button;
    QPushButton* delete_button;
    QPushButton* update_button;
    QPushButton* filter_button;


    QLabel* m_playlist;
    QListWidget* m_songs;

    std::list<Song> songs;
    std::list<Song> playlist;
};

#endif // MAINWINDOW_H
