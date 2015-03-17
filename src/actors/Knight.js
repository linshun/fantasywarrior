var Knight = Actor.extend({
    ctor:function(){
        this._super("model/knight/knight.c3b");
        this.setScale(25);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.vec3(90, 0, 0));
        this.setRotation(-90);
    }
});