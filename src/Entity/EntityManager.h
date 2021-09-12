#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

#include <vector>

#include "Core/entityx.h"
class EntityManager : public QObject{
    Q_OBJECT
public:

    static CFEntity createEntity(QString entityId, QString name, CFEntity* parent = nullptr);

    static void deleteEntity(QString entityId);

    static CFEntity& getRoot();

public:
    static CFEntity root_;
};

#endif // ENTITY_H
