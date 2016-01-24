//
//  CharacterSprite.cpp
//  DayFantazyPj
//
//  Created by YuichiNishioka on 2014/04/06.
//
//
#include "CharacterSprite.h"

using namespace cocos2d;

CharacterSprite::CharacterSprite()
{
    
}

CharacterSprite::~CharacterSprite()
{
    
}

bool CharacterSprite::initWithCharacterDto(CharacterDto pCharacterDto)
{
    m_characterDto = pCharacterDto;
    
    // CharacterのSpriteFrameのplistをキャッシュ
    auto spriteFramePlistName = StringUtils::format("%s%d.plist", m_characterDto.charaFileName.c_str(), m_characterDto.id);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(spriteFramePlistName);
    
    // Spriteを生成
    auto spriteFrameName = StringUtils::format("%s%d_%s_%d.jpg", m_characterDto.charaFileName.c_str(), m_characterDto.id, "bottom", 1);
    if ( !Sprite::initWithSpriteFrameName(spriteFrameName) )
    {
        return false;
    }
    return true;
}

CharacterSprite* CharacterSprite::createWithCharacterDto(CharacterDto pCharacterDto)
{
    auto *pRet = new CharacterSprite();
    if (pRet && pRet->initWithCharacterDto(pCharacterDto))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void CharacterSprite::setCharacterMapItem(CharacterMapItem characterMapItem)
{
    m_characterMapItem = characterMapItem;
}

CharacterMapItem* CharacterSprite::getCharacterMapItem()
{
    return &m_characterMapItem;
}

//キャラクター情報取得
CharacterSprite::CharacterDto* CharacterSprite::getCharacterDto()
{
    return &m_characterDto;
}

void CharacterSprite::runMoveAction(MapIndex moveMapIndex)
{
    if (moveMapIndex.x == 0 && moveMapIndex.y == 0)
    {
        CCLOG("移動なし");
        return;
    }
    // キャラ向きを設定
    m_characterDto.dictType = moveMapIndex.moveDictType;

    // キャラの向きを変更
    if (moveMapIndex.moveDictType == MOVE_DOWN)
    {
        this->runBottomAction();
    }
    else if (moveMapIndex.moveDictType == MOVE_LEFT)
    {
        this->runLeftAction();
    }
    else if (moveMapIndex.moveDictType == MOVE_RIGHT)
    {
        this->runRightAction();
    }
    else if (moveMapIndex.moveDictType == MOVE_UP)
    {
        this->runTopAction();
    }

}

void CharacterSprite::runTypeAnimation(MapIndex fromMove, MapIndex toMove)
{
    int targetBaseTag = CharacterSprite::animateTag::kMoveTag;
    if (this->isRunning() && this->getActionByTag(targetBaseTag))
    {
        return;
    }
    //move animation
    auto animation = this->createMoveAnimation(fromMove, toMove);
    animation->setTag(targetBaseTag);
    this->runAction(animation);
}

void CharacterSprite::attackTypeAnimation(MapIndex fromMove, MapIndex toMove)
{
    int targetBaseTag = CharacterSprite::animateTag::kMoveTag;
    if (this->isRunning() && this->getActionByTag(targetBaseTag))
    {
        return;
    }
    //move animation
    auto animation = this->createAttackAnimation(fromMove, toMove);
    animation->setTag(targetBaseTag);
    this->runAction(animation);
}

void CharacterSprite::runBottomAction()
{
    int targetBaseTag = CharacterSprite::kBottomTag;
    if (this->isRunning() && this->getActionByTag(targetBaseTag))
    {
        return;
    }
    CharacterSprite::stopAllActions();
    auto action = createBottomActorAnimate();
    action->setTag(targetBaseTag);
    this->runAction(action);
}

void CharacterSprite::runLeftAction()
{
    int targetBaseTag = CharacterSprite::kLeftTag;
    if (this->isRunning() && this->getActionByTag(targetBaseTag))
    {
        return;
    }
    CharacterSprite::stopAllActions();
    auto action = createLeftActorAnimate();
    action->setTag(targetBaseTag);
    this->runAction(action);
}

void CharacterSprite::runRightAction()
{
    int targetBaseTag = CharacterSprite::kRightTag;
    if (this->isRunning() && this->getActionByTag(targetBaseTag))
    {
        return;
    }
    CharacterSprite::stopAllActions();
    auto action = createRightActorAnimate();
    action->setTag(targetBaseTag);
    this->runAction(action);
}

void CharacterSprite::runTopAction()
{
    int targetBaseTag = CharacterSprite::kTopTag;
    if (this->isRunning() && this->getActionByTag(targetBaseTag))
    {
        return;
    }
    CharacterSprite::stopAllActions();
    auto action = createTopActorAnimate();
    action->setTag(targetBaseTag);
    this->runAction(action);
}

bool CharacterSprite::runAttackAction()
{
    int targetBaseTag = CharacterSprite::kAttackTag;
    if (this->isRunning() && this->getActionByTag(targetBaseTag))
    {
        return true;
    }
    //CharacterSprite::stopAllActions();
    auto action = createAttackActorAnimate();
    action->setTag(targetBaseTag);
    this->runAction(action);
    return false;
}


FiniteTimeAction* CharacterSprite::createBottomActorAnimate()
{
    return createCharacterAnimate(m_characterDto.charaFileName, m_characterDto.id, "bottom");
}

FiniteTimeAction* CharacterSprite::createLeftActorAnimate()
{
    return createCharacterAnimate(m_characterDto.charaFileName, m_characterDto.id, "left");
}

FiniteTimeAction* CharacterSprite::createRightActorAnimate()
{
    return createCharacterAnimate(m_characterDto.charaFileName, m_characterDto.id, "right");
}

FiniteTimeAction* CharacterSprite::createTopActorAnimate()
{
    return createCharacterAnimate(m_characterDto.charaFileName, m_characterDto.id, "top");
}

FiniteTimeAction* CharacterSprite::createAttackActorAnimate()
{
    return createAttackAnimate(m_characterDto.charaFileName, m_characterDto.id, "attack");
}

FiniteTimeAction* CharacterSprite::createCharacterAnimate(std::string fileName, int characterId, std::string frameName)
{
    auto pAnimation = Animation::create();
    auto startSpriteFrameName = StringUtils::format("%s%d_%s_%d.jpg", fileName.c_str(), characterId, frameName.c_str(), 2);
    auto pStartFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(startSpriteFrameName);
    pAnimation->addSpriteFrame(pStartFrame);
    for (int i = 0; i < 3; i++)
    {
        auto spriteFrameName = StringUtils::format("%s%d_%s_%d.jpg", fileName.c_str(), characterId, frameName.c_str(), (i + 1));
        auto pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
        pAnimation->addSpriteFrame(pFrame);
    }
    pAnimation->setDelayPerUnit(0.1);
    //無限loop
    pAnimation->setLoops(-1);
    return Animate::create(pAnimation);
}

FiniteTimeAction* CharacterSprite::createAttackAnimate(std::string fileName, int characterId, std::string frameName)
{
    auto pAnimation = Animation::create();
    auto startSpriteFrameName = StringUtils::format("%s%d_%s_%d.jpg", fileName.c_str(), characterId, frameName.c_str(), 2);
    auto pStartFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(startSpriteFrameName);
    pAnimation->addSpriteFrame(pStartFrame);
    for (int i = 0; i < 3; i++)
    {
        auto spriteFrameName = StringUtils::format("%s%d_%s_%d.jpg", fileName.c_str(), characterId, frameName.c_str(), (i + 1));
        auto pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
        pAnimation->addSpriteFrame(pFrame);
    }
    pAnimation->setDelayPerUnit(0.05);
    return Animate::create(pAnimation);
}


//move methodfs
FiniteTimeAction* CharacterSprite::createMoveAnimation(MapIndex fromMove, MapIndex toMove)
{
    //moving distance
    float distance = sqrtf(abs(fromMove.x - toMove.x) + abs(fromMove.y - toMove.y));
    return MoveTo::create(distance / 8, Point(toMove.x,toMove.y));
}

FiniteTimeAction* CharacterSprite::createAttackAnimation(MapIndex fromMove, MapIndex toMove)
{
    //moving distance
    float distance = sqrtf(abs(fromMove.x - toMove.x) + abs(fromMove.y - toMove.y));
    return Sequence::create(MoveTo::create(0.05f, Point(toMove.x,toMove.y)), MoveTo::create(0.05f, Point(fromMove.x,fromMove.y)),NULL);
}