#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

#include <vector>

#include "CFEntity.h"

class EntityManager : public QObject{
    Q_OBJECT
public:

    static CFEntity* createEntity(QString entityId, QString name, CFEntity* parent = nullptr);

    static void deleteEntity(CFEntity* entity);

    static CFEntity* root();

public:
    static CFEntity* root_;
};

#endif // ENTITY_H
