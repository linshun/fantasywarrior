var Rat = Actor.extend({
    ctor:function(){
        this._super("model/rat/rat.c3b");

        copyObject(ActorCommonValues, this);
        copyObject(RatValues, this);

        this.setScale(20);
        this.addEffect(cc.math.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.math.vec3(90, 0, 0));
        this.setRotation(-90);
        this.initShadow();

        this.scheduleUpdate();
    },

    reset:function(){
        copyObject(ActorCommonValues, this);
        copyObject(RatValues, this);
        this.walkMode();
        this.setVertexZ(0);
    },

    normalAttackSoundEffects:function(){
        cc.audioEngine.playEffect(MonsterRatValues.attack);
    },

    hurtSoundEffects:function(){
        cc.audioEngine.playEffect(MonsterRatValues.wounded);
    },

    playDyingEffects:function(){
        cc.audioEngine.playEffect(MonsterRatValues.dead);
    },

    dyingMode:function(knockSource, knockAmount){
        this.setStateType(EnumStateType.DYING);
        this.playAnimation("dead");
        this.playDyingEffects();
        //remove from MonsterManager
        for(let i = 0; i < MonsterManager.length; ++i){
            if(this == MonsterManager[i]){
                MonsterManager.splice(i, 1);
                break;
            }
        }

        var self = this;
        function recycle(){
            self.removeFromParent();
            currentLayer._uiLayer.showVictoryUI();
        }

        function disableHeroAI(){
            for(let i = 0; i < HeroManager.length; ++i){
                HeroManager[i].setAIEnabled(false);
                HeroManager[i].idleMode();
                HeroManager[i]._goRight = false;
            }
        }

        this.runAction(cc.sequence(
            cc.delayTime(3),
            cc.callFunc(disableHeroAI),
            cc.moveBy(1.0, cc.math.vec3(0, 0, -50)),
            cc.callFunc(recycle)
            ));

        if(knockAmount){
            var p = this._myPos;
            var angle = cc.pToAngleSelf(cc.pSub(p, knockSource));
            var newPos = cc.pRotateByAngle(cc.pAdd(cc.p(knockAmount, 0), p), p, angle);
            this.runAction(cc.moveTo(Rat.Actions.knocked.getDuration()*3, newPos).easing(cc.easeCubicActionOut()));
        }

    },

    hurt:function(collider, dirKnockMode){
        if(this._isalive == true){
            var damage = collider.damage;
            var critical = false;
            var knock = collider.knock;
            if(Math.random() < collider.criticalChance){
                damage *= 1.5;
                critical = true;
                knock *= 2;
            }
            damage = damage + damage * cc.randomMinus1To1() * 0.15;
            damage -= this._defense;
            damage = Math.floor(damage);

            if(damage <= 0)
                damage = 1;

            this._hp -= damage;

            if(this._hp > 0){
                if(critical == true){
                    this.knockMode(collider, dirKnockMode);
                }
                this.hurtSoundEffects();
            }else{
                this._hp = 0;
                this._isalive = false;
                this.dyingMode(collider.getPosition(), knock);
            }

            var blood = this._hpCounter.showBloodLossNum(damage, this, critical);
            blood.setVertexZ(cc.winSize.height*0.25);
            this.addBloodEffect(blood);

            return damage;
        }
    }
});

Rat.Actions = {
    idle : createAnimation("res/model/rat/rat.c3b",0,23,1,true),
    knocked : createAnimation("res/model/rat/rat.c3b",30,37,0.5,true),
    dead : createAnimation("res/model/rat/rat.c3b",41,76,0.2,true),
    attack1 : createAnimation("res/model/rat/rat.c3b",81,99,0.7,true),
    attack2 : createAnimation("res/model/rat/rat.c3b",99,117,0.7,true),
    walk : createAnimation("res/model/rat/rat.c3b",122,142,0.4,true)
}