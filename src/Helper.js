(function(_G){

    cc.EffectSprite3D.extend = cc.Class.extend;
    cc.EffectSprite3D._ctor = function(file){
        this.initWithFile(file);
    };

    _G.createAnimation = function(file, begin, finish, speed, retain=false){
        var animation3d = cc.Animation3D.create(file);
        var animate3d = cc.Animate3D.create(animation3d, begin/30, (finish-begin)/30);
        animate3d.setSpeed(speed);
        if(retain)
            animate3d.retain();
        return animate3d;
    }
})(this);