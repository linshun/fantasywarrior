var Archer = Actor.extend({
    
    ctor:function(){
        this._super("model/archer/archer.c3b");
        copyObject(ActorCommonValues, this);
        copyObject(ArcherValues, this);

        this._useWeaponId = ReSkin.archer.weapon;
        this._useArmourId = ReSkin.archer.armour;
        this._useHelmetId = ReSkin.archer.helmet;
        
        this.setScale(1.6);
        this.addEffect(cc.math.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.math.vec3(90, 0, 0));
        this.setRotation(-90);

        this.setDefaultEqt();
        this.idleMode();
        this.initShadow();
        this.initPuff();

        MessageDispatcher.registerMessage(MessageDispatcher.MessageType.SPECIAL_ARCHER, function(){
            if(this._specialAttackChance == 1) return;
            this._specialAttackChance = 1;
        }, this);

        this.scheduleUpdate();
    },

    playDyingEffects:function(){
        cc.audioEngine.playEffect(Archerproperty.dead);
    },

    hurtSoundEffects:function(){
        cc.audioEngine.playEffect(Archerproperty.wounded);
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
        cc.audioEngine.playEffect(Archerproperty.normalAttackShout);

        currentLayer.addChild(new ArcherNormalAttack(this.getPosition(), this._curFacing, this._normalAttack, this));
    },

    setDefaultEqt:function(){
        this.updateWeapon();
        this.updateHelmet();
        this.updateArmour();
        this.showOrHideArrow(false, 0);
    },

    specialAttack:function(){
        this._specialAttackChance = ArcherValues._specialAttackChance;
        this._angry = ActorCommonValues._angry;
        MessageDispatcher.dispatchMessage(MessageDispatcher.MessageType.ANGRY_CHANGE, [this]);

        cc.audioEngine.playEffect(Archerproperty.specialAttackShout);

        var attack = this._specialAttack;
        attack.knock = 80;

        var pos = this.getPosition();
        var pos1 = cc.pRotateByAngle(pos, this._myPos, this._curFacing);

        currentLayer.addChild(new ArcherSpecialAttack(pos1, this._curFacing, attack, this));

        var self = this;
        function spike(){
            currentLayer.addChild(new ArcherSpecialAttack(pos1, self._curFacing, attack, self));
            cc.audioEngine.playEffect(Archerproperty.attack1);
        }
        delayExecute(this, spike, 0.2);
        delayExecute(this, spike, 0.4);
    },

    updateWeapon:function(){
        if(this._useWeaponId === 0){
            this.getMeshByName("gongjianshou_gong01").setVisible(true);
            this.getMeshByName("gongjianshou_gong02").setVisible(false);
        }else{
            this.getMeshByName("gongjianshou_gong01").setVisible(false);
            this.getMeshByName("gongjianshou_gong02").setVisible(true);
        }
    },

    updateHelmet:function(){
        if(this._useHelmetId === 0){
            this.getMeshByName("gongjianshou_tou01").setVisible(true);
            this.getMeshByName("gonajingshou_tou02").setVisible(false);
        }else{
            this.getMeshByName("gongjianshou_tou01").setVisible(false);
            this.getMeshByName("gonajingshou_tou02").setVisible(true);
        }
    },

    updateArmour:function(){
        if(this._useArmourId === 0){
            this.getMeshByName("gongjianshou_shenti01").setVisible(true);
            this.getMeshByName("gonjianshou_shenti02").setVisible(false);
        }else{
            this.getMeshByName("gongjianshou_shenti01").setVisible(false);
            this.getMeshByName("gonjianshou_shenti02").setVisible(true);
        }
    },

    //show/hide arrow
    //isShow: true:Show false:Hide
    //type: 0:show/hide all 1:show/hide 1 2:show/hide 2
    showOrHideArrow:function(isShow, arrowType){
        if(arrowType === 0){
            this.getMeshByName("gongjiashou_jian01").setVisible(isShow);
            this.getMeshByName("gongjianshou_jian02").setVisible(isShow);  
        }else if(arrowType === 1){
            this.getMeshByName("gongjiashou_jian01").setVisible(isShow);
        }else if(arrowType === 2){
            this.getMeshByName("gongjianshou_jian02").setVisible(isShow);
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

Archer.createArrow = function(){
    var sprite3d = new cc.Sprite3D("model/archer/arrow.obj");
    sprite3d.setTexture("model/archer/hunter01_tex_head.jpg");
    sprite3d.setScale(2);
    sprite3d.setRotation3D(cc.math.vec3(-90, 0, 0));
    sprite3d.setPosition3D(cc.math.vec3(0, 0, 50));
    return sprite3d;
}

Archer.Actions = {
    idle : createAnimation("res/model/archer/archer.c3b",208,253,0.7,true),
    walk : createAnimation("res/model/archer/archer.c3b",110,130,0.7,true),
    attack1 : createAnimation("res/model/archer/archer.c3b",0,12,0.7,true),
    attack2 : createAnimation("res/model/archer/archer.c3b",12,24,0.7,true),
    specialattack1 : createAnimation("res/model/archer/archer.c3b",30,43,1,true),
    specialattack2 : createAnimation("res/model/archer/archer.c3b",44,56,1,true),
    defend : createAnimation("res/model/archer/archer.c3b",70,95,0.7,true),
    knocked : createAnimation("res/model/archer/archer.c3b",135,145,0.7,true),
    dead : createAnimation("res/model/archer/archer.c3b",150,196,0.7,true)
};