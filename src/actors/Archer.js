var Archer = Actor.extend({
    _type:"Archer",
    
    ctor:function(){
        this._super("model/archer/archer.c3b");
        this.setScale(1.6);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.vec3(0, 0, 0));
        // this.setRotation(-90);
        this.setDefaultEqt();
        this.idleMode();
    },

    setDefaultEqt:function(){
        
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