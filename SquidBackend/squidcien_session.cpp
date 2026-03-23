#include "squidcien_session.h"
#include <QObject>
#include <QWebSocketServer>
#include <QMap>
#include <QString>
#include <QList>
#include <QPointer>
#include <QJsonDocument>   // Pour manipuler le document global
#include <QJsonObject>     // Pour les structures { "cle": "valeur" }
#include <QJsonArray>      // Si tu as des listes [ ... ]
#include <QJsonValue>      // Pour manipuler une donnée précise
#include <QJsonParseError> // TRES important pour savoir pourquoi ça crash

Squidcien_session::Squidcien_session(QWebSocket *pclient, QObject *parent){
    m_autentifier=false;
    m_pclient=pclient;
    m_User_name="";
    connect(m_pclient, &QWebSocket::textMessageReceived, this, &Squidcien_session::onMessageReceived);


}
void Squidcien_session::onMessageReceived(const QString &message)
{
    // message contient ici le texte envoyé par le client
    qDebug() << "Message reçu du Squid Client :" << message;
    // début trantement JSON
    QString reponc="";
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (doc.isNull() || !doc.isObject()) {
        reponc = "Erreur : Le JSON est corrompu ou mal formé ou vide.";
    }else{
        QJsonObject root = doc.object();

        QString type = root["type"].toString();

        // oute pseudo
        if (root.contains("payload") && root["payload"].isObject()) {
            QJsonObject payload = root["payload"].toObject();

            // 4. Extraction du pseudo final
            QString pseudo = payload["pseudo"].toString();


            if ( pseudo_autorise(pseudo)){
            qDebug() << "Nouvelle tentative d'inscription pour :" << pseudo;
            // C'est ici que tu appuies sur le bouton "Valider"
            m_User_name=pseudo;
            m_autentifier=true;
            emit signal_autentifier(m_User_name);
        }else {
            reponc="Erreur : Le nom d'utilsatuer n'est pas au norme de la platforme";


        }
        }}
    // a re fair propore dans une focntion sendError
    if (reponc.contains("Erreur")){
        QString now = QDateTime::currentDateTime().toString(Qt::ISODate);

        QString type = "auth/ack";
        QString message = sendError(type,reponc);

        sendMessage(message);

    }else{
    //fin trantement JSON
    sendMessage("salut tous vas bien");
    }
    //fonction de RAHAEL
}

void Squidcien_session::sendMessage(const QString &message)
{
    // On vérifie que le pointeur n'est pas nulptr == conextion fermer
    if (m_pclient && m_pclient->isValid()) {
        m_pclient->sendTextMessage(message);
    } else {
        qDebug() << "Erreur : Impossible d'envoyer le message, socket invalide ou déconnecté.";
    }
}


bool Squidcien_session::pseudo_autorise(const QString pseudo) {

    const std::vector<QString> interdits = {"admin", "root", "moderateur"}; // Création de la liste interdite

    for (const QString& mot : interdits) { // Comparaison : pseudo / liste interdite

        if (pseudo == mot) return false;

    } // Si la boucle se termine sans correspondance, le pseudo est accepté

    return true;

}

QString Squidcien_session::sendError(const QString &source_error,const QString &type ) {

    QJsonObject racine; // Création du bloc JSON "racine"
    racine["type"] = type; //création de la variable type dans racine
    racine["date"] = QDateTime::currentDateTime().toString(Qt::ISODate); //création de la variable date dans racine

    QJsonObject payload; // Création du bloc JSON "payload"
    payload["status"] = "error"; //création de la variable statut dans payload
    payload["source"] = source_error; //On attrbut le pseudo invalide taper comme pseudo de Erreur_pseudo()

    //Insertion du bloc payload dans le bloc racine
    racine["payload"] = payload; // à toujours faire après l'avoir remplie
    QJsonDocument doc(racine); //Création du conteneur du bloc racine
    return doc.toJson(QJsonDocument::Compact); //Formatage compact pour fluidifier le programme

}
