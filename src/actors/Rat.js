var Rat = Actor.extend({
    ctor:function(){
        this._super("model/rat/rat.c3b");

        copyObject(ActorCommonValues, this);
        copyObject(RatValues, this);

        this.setScale(20);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.vec3(90, 0, 0));
        this.setRotation(-90);
        this.initShadow();

        this.scheduleUpdate();
    },

    reset:function(){
        copyObject(ActorCommonValues, this);
        copyObject(RatValues, this);
        this.walkMode();
        this.setVertexZ(0);
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