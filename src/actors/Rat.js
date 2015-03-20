var Rat = Actor.extend({
    ctor:function(){
        this._super("model/rat/rat.c3b");

        this.setScale(20);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.initShadow();
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