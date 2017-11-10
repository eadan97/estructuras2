#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <time.h>
#include <thread>
#include <QPainter>
#include <QBitmap>
#include <QtPrintSupport/qprinter.h>
#include "SmtpClient/src/SmtpMime";


QStringList nombres;
QStringList apellidos;
QStringList paises;
QHash<QString, QString> paisCorreo;
QHash<QString, QString> paisContinente;
QHash<QString, int> paisPecados;
QHash<QString, int> contPecados;
QStringList creencias;
QStringList profesiones;
Mundo* mundo;//EL mundo

void enviarCorreo(QString text, QString recipientMail, QString recipientName, QString subject){
    QString email="sistemaprogra2@gmail.com";
    QString password="darules123";

    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);
    smtp.setUser(email);
    smtp.setPassword(password);
    MimeMessage message;
    message.setSender(new EmailAddress(email, "Sistema - Progra 2"));
    message.addRecipient(new EmailAddress(recipientMail, recipientName));
    message.setSubject(subject);
    MimeHtml html;
    html.setHtml(text);

    message.addPart(&html);
    // Now we can send the mail
    if (!smtp.connectToHost()) {
        qDebug() << "Failed to connect to host!" << endl;
        return;
    }
    if (!smtp.login()) {
        qDebug() << "Failed to login!" << endl;
        return;
    }
    if (!smtp.sendMail(message)) {
        qDebug() << "Failed to send mail!" << endl;
        return;
    }
    smtp.quit();
}

QStringList pecadosPersonaToQStringList(Persona*persona){
    QStringList res;

    res<<QString::number(persona->id);
    res<<persona->nombre;
    res[1]+=" ";
    res[1]+=persona->apellido;
    res<<QString::number(persona->pecados[0]);
    res<<QString::number(persona->pecados[1]);
    res<<QString::number(persona->pecados[2]);
    res<<QString::number(persona->pecados[3]);
    res<<QString::number(persona->pecados[4]);
    res<<QString::number(persona->pecados[5]);
    res<<QString::number(persona->pecados[6]);

    return res;
}

QStringList personaToQStringList(Persona*persona){
    QStringList res;
    res<<QString::number(persona->id);
    res<<persona->nombre;
    res<<persona->apellido;
    res<<persona->pais;
    res<<persona->creencia;
    res<<persona->profesion;
    res<<persona->correo;
    res<<persona->nacimiento.toString();
    res<<QString::number(persona->sumatoriaDePecados());
    res<<QString::number(persona->hijos.count());
    return res;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Persona*p=new Persona(1,"a","a","a","a","a","a");
    //PersonaLista*pl=new PersonaLista(p);

    ui->setupUi(this);

    ui->tblPecadosFamilia->setColumnWidth(0, 40);
    ui->tblPecadosFamilia->setColumnWidth(1, 70);
    ui->tblPecadosFamilia->setColumnWidth(2, 70);
    ui->tblPecadosFamilia->setColumnWidth(3, 50);
    ui->tblPecadosFamilia->setColumnWidth(4, 70);
    ui->tblPecadosFamilia->setColumnWidth(5, 70);
    ui->tblPecadosFamilia->setColumnWidth(6, 40);
    ui->tblPecadosFamilia->setColumnWidth(7, 70);
    ui->tblPecadosFamilia->setColumnWidth(8, 70);


    startDialog=new StartDialog(this);
    mundo=new Mundo();

}

QList<Persona *> personasPorContinente(QString continente)
{
    QList<Persona *> personas;
    NodoListaPersona * temporal = mundo->listaPersonas->primeraPersona;
    while (temporal != NULL)
    {
        if (paisContinente[temporal->dato->pais].compare(continente) == 0)
            personas.append(temporal->dato);

        temporal = temporal->siguiente;
    }
    return personas;
}

void MainWindow::procesarArchivo(QStringList &list, QString fileDir){
    QFile file(fileDir);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        list+=line;
    }

}

void MainWindow::arreglarPaises(){
    for(int i=0; i<paises.size(); ++i){
        QStringList pais=paises.at(i).split(',');
        paisContinente[pais.at(0)]=pais.at(1);
        paisCorreo[pais.at(0)]=pais.at(2);
        paises[i]=pais[0];
    }

}

void MainWindow::afterLoad(){


    //startDialog->exec();
    QString qNombres="C:/Users/eadan/nombres.txt";
    QString qApellidos="C:/Users/eadan/apellidos.txt";
    QString qPaises="C:/Users/eadan/paises.txt";
    QString qCreencias="C:/Users/eadan/creencias.txt";
    QString qProfesiones="C:/Users/eadan/profesiones.txt";
    procesarArchivo(nombres,qNombres);
    procesarArchivo(apellidos,qApellidos);
    procesarArchivo(paises,qPaises);
    procesarArchivo(creencias,qCreencias);
    procesarArchivo(profesiones,qProfesiones);


    //TODO: hacer esto en hilos, speed is the key.

    //procesarArchivo(nombres,startDialog->fileNombres);
    //procesarArchivo(apellidos,startDialog->fileApellidos);
    //procesarArchivo(paises,startDialog->filePaises);
    arreglarPaises();
    //procesarArchivo(creencias,startDialog->fileCreencias);
    //procesarArchivo(profesiones,startDialog->fileProfesiones);

    mundo->generarPersonas(10000);


    for(int i=0; i<mundo->ids.size(); ++i){
        qDebug()<<mundo->encontrarPersona(mundo->ids[i])->dato->id << "-" << mundo->encontrarPersona(mundo->ids[i])->dato->hijos.size();
    }

    //ui->lblMapa->colorMap();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void Mundo::generarPersona(){
    //srand (time(NULL));
    int newId=rand() % 10000000;
    while (ids.indexOf(newId)!=-1) {
        //srand (time(NULL));
        newId=rand() % 10000000;
    }

    //srand (time(NULL));
    QString nombre=nombres[rand()% nombres.size()];

    //srand (time(NULL));
    QString apellido=apellidos[rand()%apellidos.size()];

    //srand (time(NULL));
    QString pais=paises[rand()%paises.size()];

    //srand (time(NULL));
    QString creencia=creencias[rand()%creencias.size()];

    //srand (time(NULL));
    QString profesion=profesiones[rand()%profesiones.size()];

    QString correo=paisCorreo[pais];

    Persona* nueva=new Persona(newId,nombre,apellido,pais,creencia,profesion,correo);



    mundo->agregarPersona(nueva);


    NodoListaPersona*auxPL=mundo->listaPersonas->primeraPersona;
    AVLtree<Persona*>*familia=new AVLtree<Persona*>;
    while (auxPL!=NULL) {
        Persona*auxDato=auxPL->dato;
        if(auxDato!=nueva&&auxDato->apellido==apellido&&auxDato->pais==pais)
            familia->insert(auxDato);
        auxPL=auxPL->siguiente;
    }
    //todo: creo que el arbol de la familia no deberia ser un puntero, y si no, hay que borrar los datos.
    //srand(time(NULL));
    int cantHijos=rand()%9;

    AVLnode<Persona*>*aux=familia->root;

    while (cantHijos>0&&familia->root!=0) {
        int seleccion=0;
        do{
            if (aux==0){
                aux=familia->root;}
            //srand(time(NULL));
            seleccion=rand()%3;
            if (seleccion==0){
               aux=(aux->left==NULL)?aux:aux->left;}
            else if(seleccion==2){
                aux=(aux->right==NULL)?aux:aux->right;}
        }while(seleccion!=1);

        if(!(aux->key->esDescendiente(nueva)||aux->key==nueva)){
            nueva->hijos.append(aux->key);
            cantHijos-=1;}
        familia->deleteKey(aux->key);
        aux=familia->root;
    }

}

void contarPecados(){
    NodoListaPersona*aux=mundo->listaPersonas->primeraPersona;
    paisPecados.clear();
    contPecados.clear();
    while(aux!=NULL){
        int pecados = aux->dato->pecados[0];
        pecados += aux->dato->pecados[1];
        pecados += aux->dato->pecados[2];
        pecados += aux->dato->pecados[3];
        pecados += aux->dato->pecados[4];
        pecados += aux->dato->pecados[5];
        pecados += aux->dato->pecados[6];

        paisPecados[aux->dato->pais]=paisPecados[aux->dato->pais]+pecados;
        contPecados[aux->dato->correo]=paisPecados[aux->dato->pais]+pecados;
        aux=aux->siguiente;
    }
}

void MainWindow::pintarMapa(){
    QPixmap px( ":/mapa2.png" );
    QColor asia(255,0,255);//Asia
    QColor euro(0,255,255);//Europa
    QColor ocea(0,0,255);//Oceania
    QColor afri(255,165,0);//Africa
    QColor nort(255,255,0);//NA
    QColor sura(0,128,0);//SA
    QColor anta(255,0,0);//Antartica

    QPixmap mAsia=px.createMaskFromColor( asia, Qt::MaskOutColor ) ;
    QPixmap mEuro=px.createMaskFromColor( euro, Qt::MaskOutColor ) ;
    QPixmap mOcea=px.createMaskFromColor( ocea, Qt::MaskOutColor ) ;
    QPixmap mAfri=px.createMaskFromColor( afri, Qt::MaskOutColor ) ;
    QPixmap mNort=px.createMaskFromColor( nort, Qt::MaskOutColor ) ;
    QPixmap mSou=px.createMaskFromColor( sura, Qt::MaskOutColor ) ;
    QPixmap mAnta=px.createMaskFromColor( anta, Qt::MaskOutColor ) ;

    int pecadosTotales=0;
    QList<int> vals = contPecados.values();

    foreach (int val, vals) {
        pecadosTotales+=val;
    }
    float aFloat;

    QPainter p(&px);
    aFloat=1/(pecadosTotales/(255*(float)contPecados["Asia"]));
    p.setPen(QColor(255, 255-((int)aFloat), 255-((int)aFloat)));
    p.drawPixmap(px.rect(), mAsia, mAsia.rect());
    //p.end();
    aFloat=1/(pecadosTotales/(255*(float)contPecados["Europe"]));

    p.setPen(QColor(255, 255-((int)aFloat), 255-((int)aFloat)));
    p.drawPixmap(px.rect(), mEuro, mEuro.rect());
    aFloat=1/(pecadosTotales/(255*(float)contPecados["Oceania"]));

    p.setPen(QColor(255, 255-((int)aFloat), 255-((int)aFloat)));
    p.drawPixmap(px.rect(), mOcea, mOcea.rect());
    aFloat=1/(pecadosTotales/(255*(float)contPecados["Africa"]));

    p.setPen(QColor(255, 255-((int)aFloat), 255-((int)aFloat)));
    p.drawPixmap(px.rect(), mAfri, mAfri.rect());
    aFloat=1/(pecadosTotales/(255*(float)contPecados["North America"]));

    p.setPen(QColor(255, 255-((int)aFloat), 255-((int)aFloat)));
    p.drawPixmap(px.rect(), mNort, mNort.rect());
    aFloat=1/(pecadosTotales/(255*(float)contPecados["South America"]));

    p.setPen(QColor(255, 255-((int)aFloat), 255-((int)aFloat)));
    p.drawPixmap(px.rect(), mSou, mSou.rect());

    p.setPen(QColor(0, 0, 0));
    p.drawPixmap(px.rect(), mAnta, mAnta.rect());


    p.end();

    ui->lblMapa->setPixmap(px);
}

void MainWindow::on_btnGenerarPersonas_clicked()
{
    int cantidad = ui->spnGenerarPersonas->value();
    ui->spnGenerarPersonas->setValue(0);
    mundo->generarPersonas(cantidad);

}

void MainWindow::on_btnAgregarPecados_clicked()
{
    mundo->sumarPecadosAMundo();
    contarPecados();
    refrescarTopsPecadores();
    pintarMapa();


}

void MainWindow::on_btnPecadosFamilia_clicked()
{
    QTableWidget *tbl=ui->tblPecadosFamilia;
    tbl->setRowCount(0);
    int id = ui->txtPecadosFamiliaID->text().toInt();

    NodoListaPersona * persona=mundo->encontrarPersona(id);
    if(persona!=NULL){
    agregarATable(tbl,pecadosPersonaToQStringList(persona->dato));

    for (int i =0; i<persona->dato->hijos.size(); ++i) {
        agregarATable(tbl,pecadosPersonaToQStringList(persona->dato->hijos[i]));
        for (int j=0; j<persona->dato->hijos[i]->hijos.size(); ++j) {
            agregarATable(tbl,pecadosPersonaToQStringList(persona->dato->hijos[i]->hijos[j]));
        }
    }
    }
    else{
        QMessageBox::critical(this, tr("Error"), tr("El ID digitado no pertenece a ninguna persona del mundo."));
    }

}
void MainWindow::agregarATable(QTableWidget*tbl, QStringList lista){
    //QTableWidget*tbl=ui->tblPecadosFamilia;
    int lastRow=tbl->rowCount();
    tbl->setRowCount(lastRow+1);
    for(int i=0; i<lista.size(); ++i){
        tbl->setItem(lastRow,i,new QTableWidgetItem(lista[i]));
    }


}



void MainWindow::refrescarTopsPecadores(){
    ui->lstPaisesMenosPecadores->clear();
    ui->lstPaisesMasPecadores->clear();

    //Ordenar lista de PaisPecados
    QList<int> vals = paisPecados.values(); //Valores
    std::sort( vals.begin(), vals.end() ); //Ordenados

    foreach( int val, vals )
    {
        QList<QString> keys = paisPecados.keys( val );
        std::sort( keys.begin(), keys.end() );

        foreach( QString key, keys )
        {
            ui->lstPaisesMenosPecadores->addItem(QString("%1 - %2").arg(key).arg(val));
        }
        if(ui->lstPaisesMenosPecadores->count()==5)
            break;
    }

    for(int i=vals.count()-1;i>vals.count()-12;--i){
        int val = vals.at(i);
        QList<QString> keys = paisPecados.keys( val );
        std::sort( keys.begin(), keys.end() );

        foreach( QString key, keys )
        {
            ui->lstPaisesMasPecadores->addItem(QString("%1 - %2").arg(key).arg(val));
        }
        if(ui->lstPaisesMasPecadores->count()==10)
            break;
    }
}

void MainWindow::on_btnCondenarPais_clicked()
{
    mundo->agregarPecadoresAInfierno(ui->txtPaisACondenar->text());
    contarPecados();
    refrescarTopsPecadores();
    pintarMapa();
    refrescarPersonasEnIniferno();
}

void MainWindow::refrescarPersonasEnIniferno(){
    QTableWidget*tbl=ui->tblPersonasEnInfierno;
    tbl->setRowCount(0);
    NodoListaPersona*aux=mundo->infierno->listaPersonas->primeraPersona;
    while(aux!=NULL){
        agregarATable(tbl,personaToQStringList(aux->dato));
        aux=aux->siguiente;
    }
}


void Mundo::agregarPecadoresAInfierno(QString pais){
    QList<Persona * > listaParaHeap = personasDePais(pais);
    HeapPecados heap=HeapPecados();
    foreach (Persona*var, listaParaHeap) {
        heap.insert(var);
    }
    int cantidad25=heap.getSize()*0.25;
    if (cantidad25==0)
        return;
    QString html="<h1>Resumen de la condenacion</h1>";
    html+="<table>";
    html+="<tr>";
    html+="<th>ID</th>";
    html+="<th>Nombre</th>";
    html+="<th>Apellido</th>";
    html+="<th>Pais</th>";
    html+="<th>Creencia</th>";
    html+="<th>Profesion</th>";
    html+="<th>Nacimiento</th>";
    html+="<th>Cant. Pecados</th>";
    html+="<th>Cant. Hijos</th>";
    html+="</tr>";
    QString correo=listaParaHeap.at(0)->correo, nombre=pais;
    for (int i = 0 ; i < cantidad25+1 ; ++i)
    {

        Persona*aux=heap.remove();
        ids.removeAll(aux->id);
        infierno->listaPersonas->insertarPersona(aux);

        html+="<tr>";
        html+="<td>";html+=QString::number(aux->id);html+="</td>";
        html+="<td>";html+=aux->nombre;html+="</td>";
        html+="<td>";html+=aux->apellido;html+="</td>";
        html+="<td>";html+=aux->pais;html+="</td>";
        html+="<td>";html+=aux->creencia;html+="</td>";
        html+="<td>";html+=aux->profesion;html+="</td>";
        html+="<td>";html+=aux->nacimiento.toString();html+="</td>";
        html+="<td>";html+=QString::number(aux->sumatoriaDePecados());html+="</td>";
        html+="<td>";html+=QString::number(aux->hijos.count());html+="</td>";
        html+="</tr>";
        listaPersonas->borrarPersona(aux->id);
    }
    html+="</table>";

    enviarCorreo(html, correo, nombre, "Resumen de condenacion");
    infierno->crearArbol();
    crearArbol();
}


