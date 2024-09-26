#pragma once

#include <bitset>
#include <cstdint>


//削除されたエンティティからの不正アクセスを防止するため、下位ビットにバージョン情報を入れる
using EntityIndex = uint32_t;						//エンティティインデクス
using EntityVersion = uint32_t;                     //バージョン情報
using EntityID = uint64_t;                          //エンティティID

const EntityID MAX_ENTITIES = 5000;					//エンティティ数上限
using ComponentType = std::uint8_t;					//コンポーネントID
const ComponentType MAX_COMPONENTS = 32;			//コンポーネント数上限
using ComponentMask = std::bitset<MAX_COMPONENTS>;	//Bitset様式使用

//ComponentのIDを用いて、使ってるコンポーネントを確定する仕組み
//例：Transform= 0, RigidBody=1...
//TransformとRigidBodyを持つEntityのSignatureは0b11

namespace Entity
{

    // 上位ビットインデクス　下位ビットバージョン情報
    inline static EntityID CreateEntityID(EntityIndex index, EntityVersion version)
    {
        return ((EntityID)index << 32) | ((EntityID)version);
    }

    inline static EntityIndex GetIndex(EntityID id)
    {
        return id >> 32;
    }

    inline static EntityVersion GetVersion(EntityID id)
    {
        return (EntityVersion)id;
    }

    inline static bool IsEntityValid(EntityID id)
    {
        return (id >> 32) != EntityIndex(-1);
    }
}

namespace Component
{
    //ComponentTypeごとにComponentIDを生成
    static uint32_t GenerateID()
    {
        static uint32_t value = 0;
        return value++;
    }

    // テンプレ―ト特殊化でコンポーネントのタイプごとに個別のIDを生成
    // 関数インスタンスごとにComponenntID静的変数が初期化されるため、
    // 外部関数の静的変数として保存する
    template<class T>
    static uint32_t TypeID()
    {
        static uint32_t ComponenntID = GenerateID();
        return ComponenntID;
    }
}