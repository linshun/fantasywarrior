var Archer = Actor.extend({
    
    ctor:function(){
        copyObject(ActorCommonValues, this);
        copyObject(ArcherValues, this);
        this._super("model/archer/archer.c3b");

        this._useWeaponId = ReSkin.archer.weapon;
        this._useArmourId = ReSkin.archer.armour;
        this._useHelmetId = ReSkin.archer.helmet;
        
        this.setScale(1.6);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.setDefaultEqt();
        this.idleMode();
        this.initShadow();
        this.initPuff();

    },

    setDefaultEqt:function(){
        this.updateWeapon();
        this.updateHelmet();
        this.updateArmour();
        this.showOrHideArrow(false, 0);
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