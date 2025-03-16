#include "iconeditorrealisation.h"
#include "ui_iconeditorrealisation.h"
#include "iconeditor.h"

IconEditorRealisation::IconEditorRealisation()
    :   QMainWindow(),
        ui(new Ui::IconEditorRealisation)
{
    ui->setupUi(this);

    QWidget* mainWidget = new QWidget{this};
    setCentralWidget(mainWidget);

    QVBoxLayout* vl = new QVBoxLayout;
    mainWidget->setLayout(vl);

    iconEditor = new IconEditor{this};
    vl->addWidget(iconEditor);
    vl->setAlignment(Qt::AlignCenter);
    setWindowState(Qt::WindowMaximized);
    setFixedSize(1920, 1080);

    QMenu* fileMenu = menuBar()->addMenu("File");

    QAction* openFile = new QAction{"Open file..."};
    fileMenu->addAction(openFile);
    connect(openFile, &QAction::triggered, this, &IconEditorRealisation::open);

    QAction* saveFile = new QAction{"Save file..."};
    fileMenu->addAction(saveFile);
}

IconEditorRealisation::~IconEditorRealisation()
{
    delete ui;
}

void IconEditorRealisation::open()
{
    QUrl fileUrl = QFileDialog::getOpenFileUrl
    (
        this,
        "open file..."
    );

    QString path = fileUrl.path().mid(1);

    iconEditor->setIconImage(QImage{path});
}
