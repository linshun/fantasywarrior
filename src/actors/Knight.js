var Knight = Actor.extend({
    _type:"Knight",
    _useWeaponId:ReSkin.knight.weapon,
    _useArmourId:ReSkin.knight.armour,
    _useHelmetId:ReSkin.knight.helmet,

    ctor:function(){
        this._super("model/knight/knight.c3b");
        this.setScale(25);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.setDefaultEqt();
        this.idleMode();
        this.initShadow();
        this.initPuff();
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