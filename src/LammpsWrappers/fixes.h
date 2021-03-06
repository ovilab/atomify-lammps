#ifndef FIXES_H
#define FIXES_H

#include <QObject>
#include <QVariant>

class Fixes : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(CPFixIndent* activeFixIndent READ activeFixIndent WRITE setActiveFixIndent NOTIFY activeFixIndentChanged)
public:
    explicit Fixes(QObject *parent = 0);

    QVariant model() const;
    void reset();
    void synchronize(class LAMMPSController *lammpsController);
    int count() const;
    QVector<class SimulatorControl*> simulatorControls();

    void synchronizeQML(LAMMPSController *lammpsController);
    void updateThreadOnDataObjects(QThread *thread);
    class CPFixIndent* activeFixIndent() const;

signals:
    void modelChanged(QVariant model);
    void countChanged(int count);
    void activeFixIndentChanged(class CPFixIndent* activeFixIndent);

public slots:
    void setModel(QVariant model);
    void setCount(int count);
    void setActiveFixIndent(class CPFixIndent* activeFixIndent);

private:
    QVariant m_model;
    QList<QObject *> m_data;
    QMap<QString, QObject *> m_dataMap;
    class CPFixIndent* m_activeFixIndent = nullptr;
    int m_count = 0;

    void add(QString identifier, class LAMMPSController *lammpsController);
    void remove(QString identifier);
    bool addOrRemove(LAMMPSController *lammpsController);
};

#endif // FIXES_H
