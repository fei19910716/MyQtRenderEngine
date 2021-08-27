#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <vector>
#include <memory>

class Entity : public QObject{
    Q_OBJECT
public:
    Entity(int _id):id(_id){}
    int id;
    std::vector<Entity> children;

    Entity();
    Entity(const Entity&);


    static std::shared_ptr<Entity> getRoot();
};

#endif // ENTITY_H
