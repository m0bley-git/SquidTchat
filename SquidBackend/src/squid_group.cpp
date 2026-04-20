#include "squid_group.h"
#include "squidcien_session.h"

squid_group::squid_group(const QString &nom, Squidcien_session* admin, const QList<Squidcien_session*> &members, QObject *parent)
    : QObject{parent}
{
    m_nom = nom;
    m_admin = admin;
    m_member = members;
    b_words_list = {};

    qDebug() << " le group " << m_nom << " a comme admin " << m_admin->get_user_name() << " et a " << m_member.length() << " memebers";
}

QString squid_group::get_name()
{
    return m_nom;
}

Squidcien_session* squid_group::get_p_admin()
{
    return m_admin ;
}

QList<Squidcien_session *> squid_group::get_p_member()
{
    return m_member;
}

QStringList squid_group::get_b_words()
{
    return b_words_list;
}

void squid_group::add_b_words(QString b_word)
{
    b_words_list.append(b_word);
}

void squid_group::dell_b_words(QString b_word)
{
    b_words_list.removeOne(b_word);
}

void squid_group::dell_member(Squidcien_session * user)
{
    m_member.removeOne(user);
}

QString squid_group::get_grp_info() {

    QStringList memberNames;
    for (Squidcien_session* session : m_member) {
        if (session) {
            memberNames << session->get_user_name();
        }
    }

    QJsonObject payload;
    payload["group_name"] = m_nom;
    payload["members"]    = QJsonArray::fromStringList(memberNames);
    payload["admin"]      = m_admin->get_user_name();

    QJsonObject root;
    root["type"]      = "grp/info_rep";
    root["timestamp"] = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
    root["payload"]   = payload;

    QString jsonString = QJsonDocument(root).toJson(QJsonDocument::Compact);

    return jsonString;
}


QString squid_group::get_grp_admin_info() {

    QStringList memberNames;

    QJsonObject payload;
    payload["group_name"] = m_nom;
    payload["members"] = QJsonArray::fromStringList(memberNames);
    payload["admin"] = m_admin->get_user_name();

    payload["b_words"] = QJsonArray::fromStringList(b_words_list);

    payload["member_count"] = m_member.length();

    QJsonObject root;
    root["type"] = "grp/admin_info_rep";
    root["timestamp"] = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
    root["payload"] = payload;

    return QJsonDocument(root).toJson(QJsonDocument::Compact);
}
