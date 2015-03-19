var Mage = Actor.extend({
    _type:"Mage",
    _useWeaponId:ReSkin.mage.weapon,
    _useArmourId:ReSkin.mage.armour,
    _useHelmetId:ReSkin.mage.helmet,
    
    ctor:function(){
        this._super("model/mage/mage.c3b");
        this.setScale(1.9);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.vec3(0, 0, 0));
        // this.setRotation(-90);
        this.setDefaultEqt();
        this.idleMode();
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