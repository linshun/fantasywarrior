var Knight = Actor.extend({

    ctor:function(){
        this._super("model/knight/knight.c3b");

        copyObject(ActorCommonValues, this);
        copyObject(KnightValues, this);

        this._useWeaponId = ReSkin.knight.weapon;
        this._useArmourId = ReSkin.knight.armour;
        this._useHelmetId = ReSkin.knight.helmet;

        this.setScale(25);
        this.addEffect(cc.math.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.math.vec3(90, 0, 0));
        this.setRotation(-90);
        this.setDefaultEqt();
        this.idleMode();
        this.initShadow();
        this.initPuff();

        this.initAttackEffect();

        this.schedule(this.update, 0);

        MessageDispatcher.registerMessage(MessageDispatcher.MessageType.SPECIAL_KNIGHT, function(){
            if(this._specialAttackChance == 1) return;
            this._specialAttackChance = 1;
        }, this);
    },

    playDyingEffects:function(){
        cc.audioEngine.playEffect(WarriorProperty.dead);
    },

    hurtSoundEffects:function(){
        cc.audioEngine.playEffect(WarriorProperty.wounded);
    },

    normalAttack:function(){
        cc.audioEngine.playEffect(WarriorProperty.normalAttackShout);

        currentLayer.addChild(new KnightNormalAttack(this.getPosition(), this._curFacing, this._normalAttack, this));
    },

    specialAttack:function(){
        this._specialAttackChance = 0;
        this._angry = ActorCommonValues._angry;
        MessageDispatcher.dispatchMessage(MessageDispatcher.MessageType.ANGRY_CHANGE, [this]);

        //knight will create 2 attacks one by one
        var attack = this._specialAttack;
        attack.knock = 0;
        cc.audioEngine.playEffect(WarriorProperty.specialAttackShout);

        currentLayer.addChild(new KnightNormalAttack(this.getPosition(), this._curFacing, attack, this));
        this._sprite.runAction(this.attackEffect.clone());

        var pos = this.getPosition();
        pos.x += 50;
        pos = cc.pRotateByAngle(pos, this._myPos, this._curFacing);

        cc.audioEngine.playEffect(WarriorProperty.specialAttack1);

        var self = this;
        function punch(){
            currentLayer.addChild(new KnightNormalAttack(pos, self._curFacing, self));
            self._sprite.runAction(self.attackEffect.clone())
        }
        delayExecute(this, punch, 0.2);
    },

    initAttackEffect:function(){
        var speed = 0.15,
            startRotate = 145,
            rotate = -60,
            scale = 0.01,
            sprite = new cc.Sprite("#specialAttack.jpg");

        sprite.setVisible(false);
        sprite.setBlendFunc(cc.ONE, cc.ONE);
        sprite.setScaleX(scale);
        sprite.setRotation(startRotate);
        sprite.setOpacity(0);
        sprite.setAnchorPoint(cc.p(0.5, -0.5));
        sprite.setPosition3D(cc.math.vec3(10, 0, 50));
        this.addChild(sprite);
        this._sprite = sprite;

        var attack = cc.spawn(
            cc.scaleTo(speed, 2.5, 2.5),
            cc.rotateBy(speed, rotate),
            cc.fadeIn(0)
            );
        var restore = cc.sequence(
            cc.fadeOut(0.5),
            cc.scaleTo(0, scale, 2.5),
            cc.rotateTo(0, startRotate)
            );
        this.attackEffect = cc.sequence(cc.show(), attack, restore);
        this.attackEffect.retain();
    },

    hurt : function(collider, dirKnockMode){
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
            this.addBloodEffect(blood);

            //blood
            MessageDispatcher.dispatchMessage(MessageDispatcher.MessageType.BLOOD_MINUS, [this]);

            //angry
            MessageDispatcher.dispatchMessage(MessageDispatcher.MessageType.ANGRY_CHANGE, [this]);
            this._angry += damage;

            return damage;
        }
    },


    //set default equipment
    setDefaultEqt:function(){
        this.updateWeapon();
        this.updateHelmet();
        this.updateArmour();
    },

    updateWeapon:function(){
        if(this._useWeaponId === 0){
            this.getMeshByName("zhanshi_wuqi01").setVisible(true);
            this.getMeshByName("zhanshi_wuqi02").setVisible(false);
        }else{
            this.getMeshByName("zhanshi_wuqi01").setVisible(false);
            this.getMeshByName("zhanshi_wuqi02").setVisible(true);
        }
    },

    updateHelmet:function(){
        if(this._useHelmetId === 0){
            this.getMeshByName("zhanshi_tou01").setVisible(true);
            this.getMeshByName("zhanshi_tou02").setVisible(false);
        }else{
            this.getMeshByName("zhanshi_tou01").setVisible(false);
            this.getMeshByName("zhanshi_tou02").setVisible(true);
        }
    },

    updateArmour:function(){
        if(this._useArmourId === 0){
            this.getMeshByName("zhanshi_shenti01").setVisible(true);
            this.getMeshByName("zhanshi_shenti02").setVisible(false);
        }else{
            this.getMeshByName("zhanshi_shenti01").setVisible(false);
            this.getMeshByName("zhanshi_shenti02").setVisible(true);
        }
    },

    switchWeapon:function(){
        this._useWeaponId = (this._useWeaponId + 1) % 2;
        this.updateWeapon();
    },

    switchHelmet:function(){
        this._useHelmetId = (this._useHelmetId + 1) % 2;
        this.updateHelmet();
    },

    switchArmour:function(){
        this._useArmourId = (this._useArmourId + 1) % 2;
        this.updateArmour();
    }
});

Knight.Actions = {
    idle : createAnimation("res/model/knight/knight.c3b", 267, 283, 0.7, true),
    walk : createAnimation("res/model/knight/knight.c3b",227,246,0.7, true),
    attack1 : createAnimation("res/model/knight/knight.c3b",103,129,0.7, true),
    attack2 : createAnimation("res/model/knight/knight.c3b",130,154,0.7, true),
    specialattack1 : createAnimation("res/model/knight/knight.c3b",160,190,1, true),
    specialattack2 : createAnimation("res/model/knight/knight.c3b",191,220,1, true),
    defend : createAnimation("res/model/knight/knight.c3b",92,96,0.7, true),
    knocked : createAnimation("res/model/knight/knight.c3b",254,260,0.7, true),
    dead : createAnimation("res/model/knight/knight.c3b",0,77,1, true)
};