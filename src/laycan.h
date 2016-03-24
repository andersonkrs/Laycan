#ifndef Laycan_H
#define Laycan_H

#include <QObject>
#include <QTime>
#include <QDomDocument>
#include <QVariant>
#include <QApplication>
#include <QDebug>
#include <QTextStream>
#include <QLabel>
#include <QDialog>
#include <QtGlobal>
#include <QDomNode>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QMessageBox>
#include <QDateTime>
#include <QException>

#include "schemaversion.h"
#include "logger.h"
#include "migration.h"

class MigrateException : public QException
{
public:
    void raise() const { throw *this; }
    MigrateException *clone() const { return new MigrateException(*this); }
};

class SaveMigrationException : public QException
{
public:
    void raise() const { throw *this; }
    SaveMigrationException *clone() const { return new SaveMigrationException(*this); }
};

class Laycan : public QObject
{
    Q_OBJECT
public:
    explicit Laycan(QObject* parent = nullptr);
    virtual ~Laycan();

    void Migrate(const QString &xmlPath);
    bool createVersionTable(void);

    QString logFilePath(void);
    void setLogFilePath(const QString &filePath);

    int verifiedMigrationsCount(void) const;
    void setVerifiedMigrations(const int value);

    int executedMigrationsCount(void) const;

    LaycanLogger* Logger();
    void setLogger(LaycanLogger &logger);

    QDomDocument& getXml();
    void setXml(QDomDocument &xml);

signals:
    void logChanged(QString,LogLevel);

private:
    void loadMigrationsFromXML(void);
    void executeMigrations(void);
    void flushLog(QString msg);
    void addExecutedMigration(Migration&);
    void log(LogLevel level, const QString &msg);
    void logList(const QStringList &list);
    void log(const QString &msg);
    void execMigration(QSqlQuery *q);
    void saveMigration(Migration m);

    bool writeMigrationLog(Migration&);
    float getCurrentSchemaVersion(void);

    LaycanLogger *m_logger;
    QDomDocument m_xml;
    SchemaVersion m_schemaversion;

    QList<Migration> Migrations;
    QList<Migration> m_ExecutedMigrations;
    QList<Migration> m_PendingMigrations;

    int m_verifiedMigrations;
};

#endif // Laycan_H
