#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QDialog>
#include <QList>
#include <QVariant>
#include <QSqlDatabase>

#include "dictxml.h"
#include "migrationprogress.h"

enum DataTypes {
    ftInteger,
    ftVarchar,
    ftDateTime,
    ftFloat,
    ftBoolean
};

enum IndexType {
    ftPrimary,
    ftKey,
    ftUnique
};

class Fields
{
public:
    explicit Fields(QString name, DataTypes type, int size, bool isNull,
        bool pk, QVariant def, bool autoIncKey);
    explicit Fields() {}
    inline ~Fields() {}

    QString toSQL(void);
    QString typeToSQL(DataTypes type);

    void setName(QString name);
    void setType(DataTypes type);
    void setSize(int size);
    void setIsNull(bool isNull);
    void setPrimaryKey(bool pk);
    void setDefaultValue(QVariant def);
    void setExtra(QString extra);
    void setAutoIncKey(bool autoInc);

    QString name(void);
    DataTypes type(void);
    int size(void);
    bool isNull(void);
    bool isPrimaryKey(void);
    QVariant defaultValue(void);
    QString extra(void);
    bool isAutoIncKey(void);
private:
    QString f_name;
    DataTypes f_type;
    int f_size;
    bool f_null;
    bool f_primaryKey;
    QVariant f_defaultValue;
    QString f_extra;
};

class Index
{
public:
    explicit Index(QString name, IndexType type);
    inline Index() {}
    inline ~Index() {}

    void setName(QString name);
    void setType(IndexType type);

    QString name(void);
    IndexType type(void);
private:
    QString i_name;
    IndexType i_type;
};

class Table
{
public:
    Table() {}
    ~Table() {}

    void setName(QString);

    QString name(void);

    QList<Fields> fields;
    QList<Index> indexes;
private:
    QString t_name;
};

class Dictionary
{
public:
    explicit Dictionary();
    ~Dictionary();

    void Migrate(const QString);
    void compareTables(void);

    QString generateSQL(Table &);

    void addTablesChanged(void);
    void addVerifiedTables(void);
    void addCreatedTables(void);

    void setProgressVisible(bool visible);
    void setTablesChanged(int count);
    void setVerifiedTables(int count);
    void setCreatedTables(int count);

    bool progressVisible(void);
    int tablesChanged(void);
    int verifiedTables(void);
    int createTables(void);
private:
    void loadTablesFromFile(const QString &);
    void compareFields(Table &);

    QString generateAddColumnSQL(QString tableName, Fields field);
    //QString generateAddColumnSQL(QString &tableName, Fields &field, QList<Fields>);

    bool columnExists(QString tableName, QString columnName);

    MigrationProgress *dlg;
    QList<Table> Tables;
    bool m_progressVisible;
    int m_tablesChanged;
    int m_verifiedTables;
    int m_createdTables;
};

#endif // DICTIONARY_H
