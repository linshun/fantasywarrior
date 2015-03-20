var Piglet = Actor.extend({
    ctor:function(){
        this._super("model/piglet/piglet.c3b");

        this.setTexture("model/piglet/zhu0928.jpg");
        this.setScale(1.3);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.initShadow();
    }
})

Piglet.Actions = {
    idle : createAnimation("res/model/piglet/piglet.c3b",0,40,0.7,true),
    walk : createAnimation("res/model/piglet/piglet.c3b",135,147,1.5,true),
    attack1 : createAnimation("res/model/piglet/piglet.c3b",45,60,0.7,true),
    attack2 : createAnimation("res/model/piglet/piglet.c3b",60,75,0.7,true),
    defend : createAnimation("res/model/piglet/piglet.c3b",92,96,0.7,true),
    knocked : createAnimation("res/model/piglet/piglet.c3b",81,87,0.7,true),
    dead : createAnimation("res/model/piglet/piglet.c3b",95,127,1,true)
}