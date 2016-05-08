#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()   //destr
{
    delete ui;
}

void MainWindow::setButtonState(bool store, bool update)    //set visible for buttons
{
    ui->pushButton_1->setVisible(update);
    ui->pushButton_3->setVisible(store);
}

void MainWindow::show_space(){

    ui->stackedWidget->setCurrentWidget(ui->page_space);    //expose space in tree widget
    space * s = (space*)getRoot();
    if(s != NULL)
    {
        ui->lineEdit_space->setText(s->name);               //set text in edit line
    }else{
        ui->lineEdit_space->setText("");
    }
}

void MainWindow::show_star(star *st)                    //expose star in tree widget
{
    ui->stackedWidget->setCurrentWidget(ui->page_star);
    ui->lineEdit_star_name->setText(st->name);
    ui->lineEdit_star_class->setText(st->star_class);
    ui->lineEdit_star_mass->setText(QString::number(st->mass)); //set number in line edit
}

void MainWindow::show_planet(planet *p)                 //...
{
    ui->stackedWidget->setCurrentWidget(ui->page_planet);
    ui->lineEdit_planet_name->setText(p->name);
    ui->lineEdit_planet_mass->setText(QString::number(p->mass));
    ui->lineEdit_dist_to_star->setText(QString::number(p->distance_to_star));
}

void MainWindow::show_satellite(satellite *sat)             //...
{
    ui->stackedWidget->setCurrentWidget(ui->page_satellite);
    ui->lineEdit_sat_name->setText(sat->name);
    ui->lineEdit_sat_dist->setText(QString::number(sat->distance_to_planet));
    ui->checkBox->setChecked(sat->human_made);
}

void MainWindow::show_tree(){           //expose all tree

    delete ui->treeWidget->takeTopLevelItem(0);
    show_space();
    if(getRoot() == NULL)   //if tree doesn`t exist
    {
        return;
    }
    QTreeWidgetItem * root_item = new QTreeWidgetItem(ui->treeWidget); //create item for expose tree

    space * wp = (space*)getRoot();
    root_item->setText(0,wp->name);
    star** star_array = (star**)wp->sublvl;

    int star_count = wp->sublvl_count;

    if(star_count == 0 || star_array == NULL)
    {
        return;
    }

    for(int i_star = 0;i_star < star_count;i_star++)
    {
        star * p_star = star_array[i_star];
        //expose star
        QTreeWidgetItem *s_item = new QTreeWidgetItem(root_item);
        s_item->setText(0,p_star->name);

        planet ** planet_array = (planet**)p_star->sublvl;
        int planet_count =  p_star->sublvl_count;

        if(planet_array == NULL || planet_count == 0)
        {
            continue;
        }

        for(int i_planet = 0;i_planet < planet_count;i_planet++)
        {
            planet * p_planet = planet_array[i_planet];
            //expose planet
            QTreeWidgetItem * p_item = new QTreeWidgetItem(s_item);
            p_item->setText(0,p_planet->name);

            satellite ** satellite_array = (satellite**)p_planet->sublvl;
            int satellite_count = p_planet->sublvl_count;

            if(satellite_array == NULL || satellite_count == 0)
            {
                continue;
            }
            for(int i_sat = 0; i_sat < satellite_count;i_sat++)
            {
                satellite * p_sat = satellite_array[i_sat];
                //expose satellite
                QTreeWidgetItem *sat_item = new QTreeWidgetItem(p_item);
                sat_item->setText(0,p_sat->name);
            }
        }
    }ui->treeWidget->expandAll();
}

int MainWindow::selected_lvl()      //select tree widget lvl
{
    if(ui->treeWidget->selectedItems().count() == 0)        //if elements doesn`t exist
    {
        QErrorMessage error_mes;
        error_mes.showMessage("Node was not selected");
        error_mes.exec();
        return -1;
    }
    QTreeWidgetItem *item = ui->treeWidget->selectedItems().at(0);
    int lvl = 0;
    while((item = item->parent()) != NULL)
    {
        lvl++;
    }
    return lvl;
}

int MainWindow::selected_index(int offset)      //select index(space - star - planet - satellite)
{
    QTreeWidgetItem * item = ui->treeWidget->selectedItems().at(0);
    for(int i = 0;i < offset; i++)
    {
        item = item->parent();
    }
    return item->parent()->indexOfChild(item);
}

void MainWindow::on_pushButton_2_clicked()      //Exit programm
{
    exit(0);
}

void MainWindow::on_actionCreate_root_triggered()   //Create root
{
    if(getRoot() != NULL)           //if tree already craete
    {
        QErrorMessage error_mes;
        error_mes.showMessage("Root already exist");
        error_mes.exec();
        return;
    }
    space * s = create_space();
    setRoot(s);

    QTreeWidgetItem * root_item = new QTreeWidgetItem(ui->treeWidget);
    root_item->setSelected(true);
    ui->treeWidget->setCurrentItem(root_item);

    ui->stackedWidget->setCurrentWidget(ui->page_space);

    setButtonState(false,true);
}

void MainWindow::on_pushButton_1_clicked()          //button "Update" - used for update info in tree
{
    setButtonState(false,false);
    int lvl = selected_lvl();
    space * wp = (space*)getRoot();
    if(lvl == 0)
    {
        update_space(ui->lineEdit_space->text());

    }else if(lvl == 1){
        int index_sx = selected_index(0);
        star * p_star = (star*)wp->sublvl[index_sx];
        update_star(p_star,ui->lineEdit_star_name->text(),
                    ui->lineEdit_star_class->text(),
                    ui->lineEdit_star_mass->text().toInt());

    }else if(lvl == 2){
        int index_sx = selected_index(1);
        star * p_star = (star*)wp->sublvl[index_sx];

        int index_px = selected_index(0);
        planet * p_planet = (planet*)p_star->sublvl[index_px];

        update_planet(p_planet,ui->lineEdit_planet_name->text(),
                      ui->lineEdit_dist_to_star->text().toFloat(),
                      ui->lineEdit_planet_mass->text().toFloat());

    }else if(lvl == 3){
        int index_sx = selected_index(2);
        star * p_star = (star*)wp->sublvl[index_sx];

        int index_px = selected_index(1);
        planet * p_planet = (planet*)p_star->sublvl[index_px];

        int index_satx = selected_index(0);
        satellite * p_sat = (satellite*)p_planet->sublvl[index_satx];

        update_satellite(p_sat,ui->lineEdit_sat_name->text(),
                         ui->lineEdit_sat_dist->text().toFloat(),
                         ui->checkBox->isChecked());

    }else{
        setButtonState(true,true);
        return;
    }
    show_tree();
}

void MainWindow::on_actionEdit_triggered()  //for edit elements
{
    if(ui->treeWidget->selectedItems().count() == 0)
    {
        QErrorMessage error_mes;
        error_mes.showMessage("Node was not selected");
        error_mes.exec();
        return;
    }
    setButtonState(false,true);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 1){
        return;
    }
    return;
}

void MainWindow::on_actionAdd_item_triggered() //for add elements in tree
{
    if(ui->treeWidget->selectedItems().count() == 0)
    {
        QErrorMessage error_mes;
        error_mes.showMessage("Node was not selected");
        error_mes.exec();
        return;
    }
    setButtonState(true,false);
    int lvl = selected_lvl();
    if(lvl == 0){
        ui->stackedWidget->setCurrentWidget(ui->page_star);
    }else if(lvl == 1){
        ui->stackedWidget->setCurrentWidget(ui->page_planet);
    }else if(lvl == 2){
        ui->stackedWidget->setCurrentWidget(ui->page_satellite);
    }else{
        QErrorMessage error_mes;
        error_mes.showMessage("This lvl is last");
        error_mes.exec();
        return;
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(getRoot() == NULL) {
        QErrorMessage error_mes;
        error_mes.showMessage("Node was not create");
        error_mes.exec();
        return;
    }
    QString file_name = QFileDialog::getSaveFileName(NULL,
                                                     QString::fromUtf8("Chose file name for data"),
                                                     QDir::currentPath(),"(*.*)");

    char * f_name = (char*)qPrintable(file_name);
    FILE * f = fopen(f_name,"wb");
    if(f == NULL)
    {
        QErrorMessage err;
        err.showMessage(file_name + "File open error");
        err.exec();
        return;
    }
    store((space*)getRoot(),f);
}

void MainWindow::on_pushButton_3_clicked()
{
    setButtonState(false,false);
    int lvl = selected_lvl();
    space * wp = (space*)getRoot();
    if(lvl == 0)
    {
        star * p_star = create_star();
        update_star(p_star,ui->lineEdit_star_name->text(),
                    ui->lineEdit_star_class->text(),
                    ui->lineEdit_star_mass->text().toFloat());

        add_star_sort(wp,p_star);

    }else if(lvl == 1){
        int index_s = selected_index(0);
        star * p_star = (star*)wp->sublvl[index_s];
        planet * p_planet = create_planet();
        update_planet(p_planet,ui->lineEdit_planet_name->text(),
                      ui->lineEdit_dist_to_star->text().toFloat(),
                      ui->lineEdit_planet_mass->text().toFloat());

        add_planet_sort(p_star,p_planet);

    }else if(lvl == 2){
        int index_s = selected_index(1);
        star * p_star = (star*)wp->sublvl[index_s];
        int index_p = selected_index(0);
        planet * p_planet = (planet*)p_star->sublvl[index_p];
        satellite * p_sat = create_satellite();
        update_satellite(p_sat,ui->lineEdit_sat_name->text(),
                         ui->lineEdit_sat_dist->text().toFloat(),
                         ui->checkBox->isChecked());

        add_satellite_sort(p_planet,p_sat);
    }else{
        setButtonState(true,true);
    }
    show_tree();
}

void MainWindow::on_treeWidget_clicked(const QModelIndex &index)
{

    setButtonState(false,false);
    int lvl = selected_lvl();
    space * wp = (space*)getRoot();
    if(lvl == 0){
        show_space();

    }else if(lvl == 1){
        int index_s = selected_index(0);
        star * p_star = (star*)wp->sublvl[index_s];
        show_star(p_star);

    }else if(lvl == 2){
        int index_s = selected_index(1);
        star * p_star = (star*)wp->sublvl[index_s];

        int index_p = selected_index(0);
        planet * p_planet = (planet*)p_star->sublvl[index_p];
        show_planet(p_planet);

    }else if(lvl == 3){
        int index_s = selected_index(2);
        star * p_star = (star*)wp->sublvl[index_s];

        int index_p = selected_index(1);
        planet * p_planet = (planet*)p_star->sublvl[index_p];

        int index_sat = selected_index(0);
        satellite * p_sat = (satellite*)p_planet->sublvl[index_sat];
        show_satellite(p_sat);
    }
}

void MainWindow::on_actionRemove_triggered()
{
    if(ui->treeWidget->selectedItems().count() == 0)
    {
        QErrorMessage error_mes;
        error_mes.showMessage("Node was not selected");
        error_mes.exec();
        return;
    }
    int lvl = selected_lvl();
    space * wp = (space*)getRoot();
    if(lvl == 0){
        remove_space();

    }else if(lvl == 1){
        int index_star = selected_index(0);
        remove_star(index_star);

    }else if(lvl == 2){
        int index_star = selected_index(1);
        star * p_star = (star*)wp->sublvl[index_star];
        int index_planet = selected_index(0);
        remove_planet(p_star,index_planet);

    }else if(lvl == 3){
        int index_star = selected_index(2);
        star * p_star = (star*)wp->sublvl[index_star];
        int index_planet = selected_index(1);
        planet * p_planet = (planet*)p_star->sublvl[index_planet];
        int index_sat = selected_index(0);
        remove_satellite(p_planet,index_sat);
    }
    show_tree();
}

void MainWindow::on_actionLoad_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(NULL,
                                                     QString::fromUtf8("Chose file with data"),
                                                     QDir::currentPath(),"(*.*)");

    char * f_name = (char*)qPrintable(file_name);
    FILE * f = fopen(f_name,"rb");
    if(f == NULL)
    {
        QErrorMessage err;
        err.showMessage(file_name + "File open error");
        err.exec();
        return;
    }
    space * root = restore(f);
    setRoot(root);
    show_tree();
}

void MainWindow::on_actionClear_tree_triggered()
{
    if(ui->treeWidget->selectedItems().count() == 0)
    {
        QErrorMessage error_mes;
        error_mes.showMessage("Tree doesn`t exist");
        error_mes.exec();
        return;
    }
    remove_space();
    show_tree();
}

void MainWindow::on_actionQueue2_triggered()
{
    if(getRoot() == NULL)
    {
        QErrorMessage err;
        err.showMessage("Root does not exits");
        err.exec();
        return;
    }
    space * wp = (space*)getRoot();
    if(wp->sublvl == NULL)
    {
        QErrorMessage err;
        err.showMessage("Stars does not exits");
        err.exec();
        return;
    }
    star ** st = (star**)wp->sublvl;
    int count_star = wp->sublvl_count;
    star * max = st[0];
    QString result = "Biggest star:";
    for(int i = 1;i < count_star;i++)
    {
        if(st[i]->sublvl_count > max->sublvl_count)
        {
            max = st[i];
        }else if(st[i]->sublvl_count == max->sublvl_count){
            if(st[i]->mass > max->mass){
                max = st[i];
            }
        }
    }
    result += " " + QString::fromStdString(max->name);
    QMessageBox::about(this,"Found data",result);
}

void MainWindow::on_actionHuman_made_triggered()
{
    if(getRoot() == NULL)
    {
        QErrorMessage err;
        err.showMessage("Root does not exits");
        err.exec();
        return;
    }
    int count_hm = 0;
    space * wp = (space*)getRoot();
    star** star_array = (star**)wp->sublvl;
    int star_count = wp->sublvl_count;
    for(int i_star = 0;i_star < star_count;i_star++)
    {
        star * p_star = star_array[i_star];

        planet ** planet_array = (planet**)p_star->sublvl;
        int planet_count =  p_star->sublvl_count;
        for(int i_planet = 0;i_planet < planet_count;i_planet++)
        {
            planet * p_planet = planet_array[i_planet];

            satellite ** satellite_array = (satellite**)p_planet->sublvl;
            int satellite_count = p_planet->sublvl_count;
            for(int i_sat = 0; i_sat < satellite_count;i_sat++)
            {
                satellite * p_sat = satellite_array[i_sat];

                if(p_sat->human_made){
                    count_hm++;
                }
            }
        }
    }
    QString txt = QString("Human-made: %1").arg(count_hm);
    QMessageBox::about(this,"Satellites",txt);
}

void MainWindow::on_actionNatural_triggered()
{
    if(getRoot() == NULL)
    {
        QErrorMessage err;
        err.showMessage("Root does not exits");
        err.exec();
        return;
    }
    int count_n = 0;
    space * wp = (space*)getRoot();
    star** star_array = (star**)wp->sublvl;
    int star_count = wp->sublvl_count;
    for(int i_star = 0;i_star < star_count;i_star++)
    {
        star * p_star = star_array[i_star];
        //expose star
        planet ** planet_array = (planet**)p_star->sublvl;
        int planet_count =  p_star->sublvl_count;
        for(int i_planet = 0;i_planet < planet_count;i_planet++)
        {
            planet * p_planet = planet_array[i_planet];
            //expose planet
            satellite ** satellite_array = (satellite**)p_planet->sublvl;
            int satellite_count = p_planet->sublvl_count;
            for(int i_sat = 0; i_sat < satellite_count;i_sat++)
            {
                satellite * p_sat = satellite_array[i_sat];
                //expose satellite
                if(!p_sat->human_made){
                    count_n++;
                }
            }
        }
    }
    QString txt = QString("Natural: %1").arg(count_n);
    QMessageBox::about(this,"Satellites",txt);
}

void MainWindow::on_actionSave_2_triggered()
{
    if(getRoot() == NULL)
    {
        QErrorMessage error_mes;
        error_mes.showMessage("Node was not create");
        error_mes.exec();
        return;
    }
    FILE * f = fopen("STANDART.txt","wb");
    if(f == NULL)
    {
        QErrorMessage err;
        err.showMessage("File open error");
        err.exec();
        return;
    }
    store((space*)getRoot(),f);
}

void MainWindow::on_actionQuit_triggered()
{
   exit(0);
}

void MainWindow::on_actionHelp_triggered()
{
    QString txt = "Created by \"Nadtoka A.A inc.\"LTD. 2016 - "
                  "Coursework 1st course -\"Structer and algorithm\"-";
    QMessageBox s;
    s.about(this,"About",txt);

}

void MainWindow::on_actionQueue3_triggered()  //Show Sky Map
{
    /*QDialog * dial = new QDialog;
    dial->setBaseSize(1300,800);
    dial->setWindowTitle("Sky map");
    //dial->setStyleSheet("background: url(:/new/prefix1/skymap_source.png)");*/

    QLabel *image = new QLabel();
    image->setPixmap( QPixmap( ":/new/prefix1/skymap_source.png" ) );

    image->setBackgroundRole(QPalette::Base);
    image->setBaseSize(1200,800);
    image->setScaledContents(true);

    QScrollArea * scrollArea = new QScrollArea;
    //scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setBaseSize(1200,800);
    scrollArea->setWidget(image);
    scrollArea->setWindowTitle("Sky map");
    scrollArea->show();
    //setCentralWidget(scrollArea);

    /*QVBoxLayout * mainLayout = new QVBoxLayout();

    dial->setLayout(mainLayout);

    dial->exec();*/

}



void MainWindow::on_actionFor_each_star_triggered()         //Found satellites amount for each star
{
    if(ui->treeWidget->selectedItems().count() == 0)
    {
        QErrorMessage error_mes;
        error_mes.showMessage("Node was not create");
        error_mes.exec();
        return;
    }
    if(selected_lvl() != 1)
    {
        QErrorMessage error_mes;
        error_mes.showMessage("Select star");
        error_mes.exec();
        return;
    }
    int index_sx = selected_index(0);
    space * wp = (space*)getRoot();
    star * p_star = (star*)wp->sublvl[index_sx];
    int count_n = 0;
    int count_h = 0;

    planet ** planet_array = (planet**)p_star->sublvl;
    int planet_count =  p_star->sublvl_count;
    for(int i_planet = 0;i_planet < planet_count;i_planet++)
    {
        planet * p_planet = planet_array[i_planet];
        satellite ** satellite_array = (satellite**)p_planet->sublvl;
        int satellite_count = p_planet->sublvl_count;
        for(int i_sat = 0; i_sat < satellite_count;i_sat++)
        {
            satellite * p_sat = satellite_array[i_sat];
            if(p_sat->human_made){
                count_h++;
            }else {
                count_n++;
            }
        }
    }
    QString txt = QString("Natural: %1").arg(count_n);
    txt += QString(" Human-made: %1").arg(count_h);
    QMessageBox::about(this,"Satellites",txt);
}

void MainWindow::on_actionDark_2_triggered()
{
    this->setStyleSheet("color: silver; "
                        "background-color: #302F2F; "
                        "selection-background-color:#3d8ec9;"
                        "selection-color: black;"
                        "background-clip: border;"
                        "border-image: none;"
                        "outline: 0;");
}


void MainWindow::on_actionDefault_2_triggered()
{
    this->setStyleSheet("background-color:");
}

void MainWindow::on_actionSolirized_triggered()
{
    this->setStyleSheet("background-color: #66969c; "
                        "color:#8a2048; "
                        "QMenu{border: 1px solid #3A3939;color: "
                        "silver;margin: 2px;} "
                        "QLineEdit{background-color: #201F1F;padding: 2px;"
                        "border-style: solid;border: 1px solid #3A3939;"
                        "border-radius: 2px;color: silver;}");
}

void MainWindow::on_actionCourier_New_triggered()
{
    QString txt = this->styleSheet();
    this->setStyleSheet(txt+"font: 12px Courier;");
}

void MainWindow::on_actionComic_San_triggered()
{
    QString txt = this->styleSheet();
    this->setStyleSheet(txt+"font: 12px Comic San,sans-serif;");
}

void MainWindow::on_treeWidget_doubleClicked(const QModelIndex &index)
{
    if(!index.parent().isValid()) {
        setButtonState(false,false);
        ui->treeWidget->collapseAll();
    }else {
        ui->treeWidget->collapse(index.child(1,1));
    }
}
