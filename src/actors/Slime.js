var Slime = Actor.extend({
    _type:"Slime",
    
    ctor:function(){
        this._super("model/slime/slime.c3b");
        this.setTexture("model/slime/baozi.jpg");
        this.setScale(17);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.vec3(90, 0, 0));
        this.setRotation(-90);

        this.runAction(cc.repeatForever(createAnimation("model/slime/slime.c3b", 0, 22, 0.7)));
    }
});