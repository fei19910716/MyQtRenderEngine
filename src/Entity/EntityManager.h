#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

#include <vector>

#include <entt/entt.hpp>

using CFEntity = entt::registry::entity_type;
class EntityManager : public QObject{
    Q_OBJECT
public:
    
    EntityManager();

    static void createEntity(int id);

    static void deleteEntity(int id);

    static CFEntity& getRoot();

public:
    static CFEntity root_;
    static entt::registry m_registry;
    static std::vector<CFEntity> children;
};

#endif // ENTITY_H
