var Mage = Actor.extend({
    
    ctor:function(){
        this._super("model/mage/mage.c3b");

        copyObject(ActorCommonValues, this);
        copyObject(MageValues, this);
        
        this._useWeaponId = ReSkin.mage.weapon;
        this._useArmourId = ReSkin.mage.armour;
        this._useHelmetId = ReSkin.mage.helmet;

        this.setScale(1.9);
        this.addEffect(cc.math.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.math.vec3(90, 0, 0));
        this.setRotation(-90);

        this.setDefaultEqt();
        this.idleMode();
        this.initShadow();
        this.initPuff();

        MessageDispatcher.registerMessage(MessageDispatcher.MessageType.SPECIAL_MAGE, function(){
            if(this._specialAttackChance == 1) return;
            this._specialAttackChance = 1;
        }, this);

        this.scheduleUpdate();
    },

    playDyingEffects:function(){
        cc.audioEngine.playEffect(MageProperty.dead);
    },

    hurtSoundEffects:function(){
        cc.audioEngine.playEffect(MageProperty.wounded);
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

    normalAttack:function(){
        cc.audioEngine.playEffect(MageProperty.normalAttackShout);
        currentLayer.addChild(new MageNormalAttack(this.getPosition(), this._curFacing, this._normalAttack, this._target, this));
    },

    specialAttack:function(){
        this._specialAttackChance = 0;
        this._angry = ActorCommonValues._angry;
        MessageDispatcher.dispatchMessage(MessageDispatcher.MessageType.ANGRY_CHANGE, [this])

        //mage will create 3 ice spikes on the ground
        cc.audioEngine.playEffect(MageProperty.specialAttackShout);
        cc.audioEngine.playEffect(MageProperty.ice_special)

        var pos1 = this.getPosition();
        var pos2 = this.getPosition();
        var pos3 = this.getPosition();
        pos1.x += 130;
        pos2.x += 330;
        pos3.x += 530;
        pos1 = cc.pRotateByAngle(pos1, this._myPos, this._curFacing);
        pos2 = cc.pRotateByAngle(pos2, this._myPos, this._curFacing);
        pos3 = cc.pRotateByAngle(pos3, this._myPos, this._curFacing);
        currentLayer.addChild(new MageIceSpikes(pos1, this._curFacing, this._specialAttack, this));

        var self = this;
        function spike2(){
            currentLayer.addChild(new MageIceSpikes(pos2, self._curFacing, self._specialAttack, self));
        }

        function spike3(){
            currentLayer.addChild(new MageIceSpikes(pos3, self._curFacing, self._specialAttack, self));
        }

        delayExecute(this, spike2, 0.25);
        delayExecute(this, spike3, 0.5);
    },

    setDefaultEqt:function(){
        this.updateWeapon();
        this.updateHelmet();
        this.updateArmour();
    },

    updateWeapon:function(){
        if(this._useWeaponId === 0){
            this.getMeshByName("fashi_wuqi01").setVisible(true);
            this.getMeshByName("fashi_wuqi2").setVisible(false);
        }else{
            this.getMeshByName("fashi_wuqi01").setVisible(false);
            this.getMeshByName("fashi_wuqi2").setVisible(true);
        }
    },

    updateHelmet:function(){
        if(this._useHelmetId === 0){
            this.getMeshByName("fashi_tou01").setVisible(true);
            this.getMeshByName("fashi_tou2").setVisible(false);
        }else{
            this.getMeshByName("fashi_tou01").setVisible(false);
            this.getMeshByName("fashi_tou2").setVisible(true);
        }
    },

    updateArmour:function(){
        if(this._useArmourId === 0){
            this.getMeshByName("fashi_shenti01").setVisible(true);
            this.getMeshByName("fashi_shenti2").setVisible(false);
        }else{
            this.getMeshByName("fashi_shenti01").setVisible(false);
            this.getMeshByName("fashi_shenti2").setVisible(true);
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

Mage.Actions = {
    idle : createAnimation("res/model/mage/mage.c3b",206,229,0.7,true),
    walk : createAnimation("res/model/mage/mage.c3b",99,119,0.7,true),
    attack1 : createAnimation("res/model/mage/mage.c3b",12,30,0.7,true),
    attack2 : createAnimation("res/model/mage/mage.c3b",31,49,0.7,true),
    specialattack1 : createAnimation("res/model/mage/mage.c3b",56,74,1,true),
    specialattack2 : createAnimation("res/model/mage/mage.c3b",75,92,1,true),
    defend : createAnimation("res/model/mage/mage.c3b",1,5,0.7,true),
    knocked : createAnimation("res/model/mage/mage.c3b",126,132,0.7,true),
    dead : createAnimation("res/model/mage/mage.c3b",139,199,0.7,true)
}