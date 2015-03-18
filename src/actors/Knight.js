var Knight = Actor.extend({
    _type:"Knight",

    ctor:function(){
        this._super("model/knight/knight.c3b");
        this.setScale(25);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.setDefaultEqt();
        this.idleMode();
    },

    //set default equipment
    setDefaultEqt:function(){

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