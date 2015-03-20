var Dragon = Actor.extend({
    ctor:function(){
        this._super("model/dragon/dragon.c3b");

        copyObject(ActorCommonValues, this);
        copyObject(DragonValues, this);

        this.setScale(10);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
    },

    reset:function(){
        copyObject(ActorCommonValues, this);
        copyObject(DragonValues, this);
        this.walkMode();
        this.setVertexZ(0);
    }
});

Dragon.Actions = {
    idle : createAnimation("res/model/dragon/dragon.c3b",0,24,0.7,true),
    knocked : createAnimation("res/model/dragon/dragon.c3b",30,37,0.7,true),
    dead : createAnimation("res/model/dragon/dragon.c3b",42,80,1,true),
    attack1 : createAnimation("res/model/dragon/dragon.c3b",85,100,0.7,true),
    attack2 : createAnimation("res/model/dragon/dragon.c3b",100,115,0.7,true),
    walk : createAnimation("res/model/dragon/dragon.c3b",120,140,1,true),
};