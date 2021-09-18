//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_VERTEXBUFFER_H
#define CFRENDERENGINE_VERTEXBUFFER_H

#include <cstdint>
#include "GLResource.h"

CFENGINE_RENDER_START
struct Attribute{
    enum Enum{
        Position,
        TextureCoord,
        Color,
    };
};
struct AttribType // 顶点属性数据类型
{
    /// Attribute types:
    enum Enum
    {
        Int8 = 0x1400,
        Uint8 = 0x1401,  //!< Uint8
        Int16 = 0x1402,
        Uint16 = 0x1403,
        Int = 0x1404,
        Uint = 0x1405,  //!< Int16
        Float = 0x1406,

        Count
    };
};
class VertexLayout{
public:
    struct AttribInfo{
        Attribute::Enum attrib;
        AttribType::Enum type;
        unsigned char typeSize;
        unsigned int num;
        unsigned int offset;
    };
    VertexLayout& begin(){
        return *this;
    }

    void end(){

    }

    VertexLayout& add(Attribute::Enum attrib, uint8_t num, AttribType::Enum type)
    {
        m_attribute.push_back({attrib,type,attribTypeSize(type),num,m_stride}) ;
        m_stride += num;

        return *this;
    }

private:
    unsigned char attribTypeSize(AttribType::Enum attrib){
        switch (attrib) {
            case AttribType::Enum::Int8:
                return sizeof(char);
            case AttribType::Enum::Uint8:
                return sizeof(unsigned char);
            case AttribType::Enum::Int16:
                return sizeof(short);
            case AttribType::Enum::Uint16:
                return sizeof(unsigned short);
            case AttribType::Enum::Int:
                return sizeof(int);
            case AttribType::Enum::Uint:
                return sizeof(unsigned int);
            case AttribType::Enum::Float:
                return sizeof(float);
        }
    }

public:
    unsigned int m_stride = 0;
    std::vector<AttribInfo> m_attribute;
};
class VertexBuffer: public GLResource {
public:
    VertexBuffer(std::vector<float>& vertices, std::shared_ptr<VertexLayout> layout);

    ~VertexBuffer();



};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_VERTEXBUFFER_H
