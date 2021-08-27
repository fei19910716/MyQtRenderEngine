#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <QString>
#include <QObject>

class Component: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setID)
    Q_PROPERTY(int entityID READ entityID WRITE setEntityID)

public:
    QString m_id;

    int m_entityID;

    Component(QString&& _id, int entid);
    Component(const Component& com);

    static std::vector<Component> getComponents();

    QString id() const
    {
        return m_id;
    }
    int entityID() const
    {
        return m_entityID;
    }

public slots:
    void setID(QString id)
    {
        m_id = id;
    }
    void setEntityID(int entityID)
    {
        m_entityID = entityID;
    }
};

class TriangleComponent: public Component{
public:
    TriangleComponent();

};

#endif // COMPONENTS_H
