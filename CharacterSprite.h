//
//  CharacterSprite.h
//  DayFantazyPj
//
//  Created by YuichiNishioka on 2014/04/06.
//
//

#ifndef __DayFantazyPj__CharacterSprite__
#define __DayFantazyPj__CharacterSprite__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class CharacterSprite  : public cocos2d::Sprite
{
public:
    typedef struct _CharacterDto {
        /** プレイヤーを一意に識別するID. */
        int id;
        /** キャラのタイプ(1:player,2:enemy,3:other */
        int characterType;
        // キャラファイル名
        std::string charaFileName;
        /** キャラ名. */
        std::string name;
        /** キャライメージのID. */
        int imageResId;
        /** 顔画像のデフォルトID. */
        int faceImgId;
        /** 攻撃力. */
        int attackPoint;
        /** 防御力. */
        int defencePoint;
        /** レベル. */
        int lv;
        /** 経験値. */
        int exp;
        /** 次のレベルまでの経験値 */
        int nextExp;
        /** HP. */
        int hitPoint;
        /** HP最大値. */
        int hitPointLimit;
        /** MP. */
        int magicPoint;
        /** MP最大値. */
        int magicPointLimit;
        /** 移動力(ステータス表示用). */
        int movePoint;
        /** 攻撃範囲(ステータス表示用). */
        int attackRange;
        /** tag用. */
        long seqNo;
        // キャラ向き
        int dictType;
        // お金
        int gold;
    } CharacterDto;

    // コンストラクタ、デストラクタ
    CharacterSprite();
    ~CharacterSprite();

    // character Create Init method
    virtual bool initWithCharacterDto(CharacterDto characterDto);
    static CharacterSprite* createWithCharacterDto(CharacterDto characterDto);

    void setCharacterMapItem(CharacterMapItem characterMapItem);
    CharacterMapItem* getCharacterMapItem();

    CharacterDto* getCharacterDto();

    void runMoveAction(MapIndex moveMapIndex);
    void runTypeAnimation(MapIndex fromMove, MapIndex toMove);
    void runBottomAction();
    void runLeftAction();
    void runRightAction();
    void runTopAction();
    bool runAttackAction();
    // attack
    void attackTypeAnimation(MapIndex fromMove, MapIndex toMove);

private:

    // animation Tags
    enum animateTag {
        kBottomTag = 1,
        kLeftTag   = 2,
        kRightTag  = 3,
        kTopTag    = 4,
        kMoveTag   = 5,
        kAttackTag = 6,
    };
    CharacterMapItem m_characterMapItem;
    
    CharacterDto m_characterDto;
    
    FiniteTimeAction* createBottomActorAnimate();
    FiniteTimeAction* createLeftActorAnimate();
    FiniteTimeAction* createRightActorAnimate();
    FiniteTimeAction* createTopActorAnimate();
    
    FiniteTimeAction* createAttackActorAnimate();

    FiniteTimeAction* createCharacterAnimate(std::string fileName, int characterId, std::string frameName);
    FiniteTimeAction* createAttackAnimate(std::string fileName, int characterId, std::string frameName);
    // moving animation
    FiniteTimeAction* createMoveAnimation(MapIndex fromMove, MapIndex toMove);
    // attack animation
    FiniteTimeAction* createAttackAnimation(MapIndex fromMove, MapIndex toMove);
};
#endif /* defined(__DayFantazyPj__CharacterSprite__) */
