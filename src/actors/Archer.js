var Archer = Actor.extend({
    ctor:function(){
        this._super("model/archer/archer.c3b");
        this.setScale(1.6);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.vec3(90, 0, 0));
        this.setRotation(-90);
        this.setDefaultEqt();
    },

    setDefaultEqt:function(){
        
    }
});