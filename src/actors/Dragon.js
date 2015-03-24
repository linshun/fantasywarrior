var Dragon = Actor.extend({
    ctor:function(){
        this._super("model/dragon/dragon.c3b");

        copyObject(ActorCommonValues, this);
        copyObject(DragonValues, this);

        this.setScale(10);
        this.addEffect(cc.math.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.math.vec3(90, 0, 0));
        this.setRotation(-90);

        this.scheduleUpdate();
    },

    reset:function(){
        copyObject(ActorCommonValues, this);
        copyObject(DragonValues, this);
        this.walkMode();
        this.setVertexZ(0);
    },

    normalAttackSoundEffects:function(){
        cc.audioEngine.playEffect(MonsterDragonValues.attack);
    },

    playDyingEffects:function(){
        cc.audioEngine.playEffect(MonsterDragonValues.dead);
    },

    hurtSoundEffects:function(){
        cc.audioEngine.playEffect(MonsterDragonValues.wounded);
    },

    normalAttack:function(){
        this.normalAttackSoundEffects();
        currentLayer.addChild(new DragonAttack(this.getPosition(), this._curFacing, this._normalAttack));
    },

    dyingMode:function(knockSource, knockAmount){
        this.setStateType(EnumStateType.DYING);
        this.playAnimation("dead");

        if(knockAmount){
            var p = this.getPosition();
            var angle = cc.pToAngleSelf(cc.pSub(p, knockSource));
            var newPos = cc.pRotateByAngle(cc.pAdd(cc.p(knockAmount, 0), p), p, angle);
            this.runAction(cc.moveTo(Dragon.Actions.knocked.getDuration()*3, newPos).easing(cc.easeCubicActionOut()));
        }
        this._AIEnabled = false;
        //remove from HeroManager
        for(let i = 0; i < HeroManager.length; ++i){
            if(this == HeroManager[i]){
                HeroManager.splice(i, 1);
                break;
            }
        }

        this.runAction(cc.sequence(
                cc.delayTime(3),
                cc.moveBy(1.0, cc.math.vec3(0, 0, -50)),
                cc.callFunc(function(){
                    this.setVisible(false);
                    cc.pool.putInPool(this);
                }, this)
            ));
    }
});

Dragon.Actions = {
    idle : createAnimation("res/model/dragon/dragon.c3b",0,24,0.7,true),
    knocked : createAnimation("res/model/dragon/dragon.c3b",30,37,0.7,true),
    dead : createAnimation("res/model/dragon/dragon.c3b",42,80,1,true),
    attack1 : createAnimation("res/model/dragon/dragon.c3b",85,100,0.7,true),
    attack2 : createAnimation("res/model/dragon/dragon.c3b",100,115,0.7,true),
    walk : createAnimation("res/model/dragon/dragon.c3b",120,140,1,true),
};