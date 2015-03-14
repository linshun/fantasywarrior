var Slime = Actor.extend({
    ctor:function(){
        this._super("model/slime/slime.c3b");
        this.setTexture("model/slime/baozi.jpg");
        this.setScale(17);
        //TODO addEffect
        this.setRotation3D(cc.vec3(90, 0, 0));
        this.setRotation(-90);
    }
});