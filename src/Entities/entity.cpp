#include "entity.h"

Entity::Entity(){

}

Entity::Entity(const Entity& e){
    this->id = e.id;
    this->children.clear();
    for(auto& item: e.children){
           this->children.push_back(item);
    }

}

std::shared_ptr<Entity> Entity::getRoot(){
    std::shared_ptr<Entity> root = std::make_shared<Entity>(1);
    root->children.emplace_back(Entity(2));
    root->children.emplace_back(Entity(3));
    root->children.emplace_back(Entity(4));

    Entity ent(5);
    ent.children.emplace_back(Entity(6));
    ent.children.emplace_back(Entity(7));

    root->children.push_back(ent);
    return root;
}
