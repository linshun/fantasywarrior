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

    _G.copyObject = function(o1, o2){
        for(var i in o1)
            o2[i] = o1[i];
    }
    
    _G.radNormalize = function(rad){
        var pi2 = 2 * Math.PI;
        rad %= pi2;
        rand = (rad + pi2) % pi2;
        if(rad > Math.PI)
            rad = rad - Math.PI;
        return rad;
    }

    _G.delayExecute = function(target, func, delay){
        var wait = cc.delayTime(delay);
        target.runAction(cc.sequence(wait, cc.callFunc(func, target)));
    }

    cc.pGetClampPoint = function(pt1, pt2, pt3){
        return cc.p(cc.clampf(pt1.x, pt2.x, pt3.x), cc.clampf(pt1.y, pt2.y, pt3.y));
    }

    cc.pToAngleSelf = function(self){
        return Math.atan2(self.y, self.x)    
    }
    

})(this);