#pragma once

#include <bitset>
#include <cstdint>


//�폜���ꂽ�G���e�B�e�B����̕s���A�N�Z�X��h�~���邽�߁A���ʃr�b�g�Ƀo�[�W������������
using EntityIndex = uint32_t;						//�G���e�B�e�B�C���f�N�X
using EntityVersion = uint32_t;                     //�o�[�W�������
using EntityID = uint64_t;                          //�G���e�B�e�BID

const EntityID MAX_ENTITIES = 5000;					//�G���e�B�e�B�����
using ComponentType = std::uint8_t;					//�R���|�[�l���gID
const ComponentType MAX_COMPONENTS = 32;			//�R���|�[�l���g�����
using ComponentMask = std::bitset<MAX_COMPONENTS>;	//Bitset�l���g�p

//Component��ID��p���āA�g���Ă�R���|�[�l���g���m�肷��d�g��
//��FTransform= 0, RigidBody=1...
//Transform��RigidBody������Entity��Signature��0b11

namespace Entity
{

    // ��ʃr�b�g�C���f�N�X�@���ʃr�b�g�o�[�W�������
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
    //ComponentType���Ƃ�ComponentID�𐶐�
    static uint32_t GenerateID()
    {
        static uint32_t value = 0;
        return value++;
    }

    // �e���v���\�g���ꉻ�ŃR���|�[�l���g�̃^�C�v���ƂɌʂ�ID�𐶐�
    // �֐��C���X�^���X���Ƃ�ComponenntID�ÓI�ϐ�������������邽�߁A
    // �O���֐��̐ÓI�ϐ��Ƃ��ĕۑ�����
    template<class T>
    static uint32_t TypeID()
    {
        static uint32_t ComponenntID = GenerateID();
        return ComponenntID;
    }
}