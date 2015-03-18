var Mage = Actor.extend({
    _type:"Mage",
    
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