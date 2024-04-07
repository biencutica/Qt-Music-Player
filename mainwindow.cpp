#include "mainwindow.h"
#include "song.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setupUI();
}

MainWindow::~MainWindow()
{
    delete main_HLayout;
    delete m_centralWidget;
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget();
    main_HLayout = new QHBoxLayout();
    m_centralVLayout = new QVBoxLayout();
    m_rightVLayout = new QVBoxLayout();
    m_leftVLayout = new QVBoxLayout();
    m_leftGridLayout = new QGridLayout();
    m_buttons = new QHBoxLayout();

    m_listSongsLabel = new QLabel("All songs:");
    m_listSongs = new QListWidget();
    m_leftFormLayout = new QFormLayout();

    m_titleLable = new QLabel("Title:");
    m_titleText = new QLineEdit();

    m_artistLable = new QLabel("Artist:");
    m_artistText = new QLineEdit();

    m_durationLable = new QLabel("Duration:");
    m_durationText = new QLineEdit();

    m_linkLable = new QLabel("Link:");
    m_linkText = new QLineEdit();

    QPushButton* add_button = new QPushButton("Add");
    QPushButton* delete_button = new QPushButton("Delete");
    QPushButton* update_button = new QPushButton("Update");
    QPushButton* filter_button = new QPushButton("Filter");


    QPushButton* send_button = new QPushButton(">");


    QLabel* m_playlist = new QLabel("Playlist");
    QListWidget* m_songs = new QListWidget();


    QPushButton* play = new QPushButton("Play");
    QPushButton* next = new QPushButton("Next");


   //left form
    m_leftFormLayout->addRow(m_titleLable, m_titleText);
    m_leftFormLayout->addRow(m_artistLable, m_artistText);
    m_leftFormLayout->addRow(m_durationLable, m_durationText);
    m_leftFormLayout->addRow(m_linkLable, m_linkText);

    //bottom-left grid
    m_leftGridLayout->addWidget(add_button,0,0);
    m_leftGridLayout->addWidget(delete_button,0,1);
    m_leftGridLayout->addWidget(update_button,0,2);
    m_leftGridLayout->addWidget(filter_button,1,1);

    //left vertical layout
    m_leftVLayout->addWidget(m_listSongsLabel);
    m_leftVLayout->addWidget(m_listSongs);
    m_leftVLayout->addLayout(m_leftFormLayout);
    m_leftVLayout->addLayout(m_leftGridLayout);

    //central vertical layout
    m_centralVLayout->addWidget(send_button);


    //right vertical layout
    m_rightVLayout->addWidget(m_playlist);
    m_rightVLayout->addWidget(m_songs);
    m_buttons->addWidget(play);
    m_buttons->addWidget(next);
    m_rightVLayout->addLayout(m_buttons);


    //central
    main_HLayout->addLayout(m_leftVLayout);
    main_HLayout->addLayout(m_centralVLayout);
    main_HLayout->addLayout(m_rightVLayout);
    m_centralWidget->setLayout(main_HLayout);
    this->setCentralWidget(m_centralWidget);

    //lab 10
    connect(add_button, &QPushButton::clicked, this, &MainWindow::add_song);
    connect(delete_button, &QPushButton::clicked, this, &MainWindow::delete_song);
    connect(send_button, &QPushButton::clicked, this, &MainWindow::send_song);
    connect(update_button, &QPushButton::clicked, this, &MainWindow::update_song);
    connect(filter_button, &QPushButton::clicked, this, &MainWindow::filter);

}

void MainWindow::add_song(){
    QString title = m_titleText->text();
    QString artist = m_artistText->text();
    QString duration = m_durationText->text();
    QString link = m_linkText->text();

    if(title.isEmpty() || artist.isEmpty() || duration.isEmpty() || link.isEmpty()){
        QMessageBox::warning(this, "Error", "Please fill in all the fields.");
    }

    Song newSong(title.toStdString(), artist.toStdString(), duration.toStdString(), link.toStdString());
    songs.push_back(newSong);

    QString songinfo = title + " - " + artist + " (" + duration + ")";
    m_listSongs->addItem(songinfo); //add song as item

    m_titleText->clear();
    m_artistText->clear();
    m_durationText->clear();
    m_linkText->clear();
}

void MainWindow::delete_song(){
    QListWidgetItem* selected = m_listSongs->currentItem();
    if(selected){
        int row = m_listSongs->row(selected);
        m_listSongs->takeItem(row); //removes and returns the item from given row

        std::list<Song>::iterator it = std::next(songs.begin(), row);
        songs.erase(it);
    }
}

void MainWindow::send_song() {
    QListWidgetItem* selected = m_listSongs->currentItem();
    if (selected) {
        int row = m_listSongs->row(selected) - 1; // Subtract 1 to adjust for indexing
        if (row >= 0 && row < songs.size()) {
            std::list<Song>::iterator it = std::next(songs.begin(), row);
            Song selected_song = *it; //dereference iterator to get selected song
            playlist.push_back(selected_song);
            QString songinfo = QString::fromStdString(selected_song.get_title()) + " - " + QString::fromStdString(selected_song.get_artist()) + " (" + QString::fromStdString(selected_song.get_duration()) + ")";
            QListWidgetItem* new_item = new QListWidgetItem(songinfo);
            m_songs->addItem(new_item);
        }
    }
}




void MainWindow::update_song(){
    QListWidgetItem* selected = m_listSongs->currentItem();
    if(selected)
        QMessageBox::warning(this, "Message", "Not implemented yet.");
}

void MainWindow::filter(){
    QListWidgetItem* selected = m_listSongs->currentItem();
    if(selected)
        QMessageBox::warning(this, "Message", "Not implemented yet.");
}




