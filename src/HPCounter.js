var HPCounter = cc.Node.extend({
    _isBlooding:false,
    _num:0,

    ctor:function(){
        this._super();
    },

    showBloodLossNum:function(damage,actor,attack){
        var time = 1;
        var self = this;

        function getRandomXYZ(){
            var randx = 20*Math.sin(cc.degreesToRadians(time*0.5+4356)),
                randy = 20*Math.sin(cc.degreesToRadians(time*0.37+5436)),
                randz = 20*Math.sin(cc.degreesToRadians(time*0.2+54325));
            return cc.math.vec3(randx, randy, randz);
        }

        function getBlood(){
            var num = self._num;
            var tm = 0.5;
            var pointZ = 50;

            var effect = new cc.BillBoard();
            var ttfconfig = {outlineSize:7, fontSize:50, glyphs:0, fontFilePath:"fonts/britanic bold.ttf"};
            var blood = cc.Label.createWithTTF(ttfconfig, "-"+num, cc.TEXT_ALIGNMENT_CENTER, 400);
            blood.enableOutline(cc.color(0, 0, 0, 255));
            blood.setScale(0.1);
            blood.setGlobalZOrder(FXZorder);

            var targetScale = 0.6;
            if(num > 1000)
                blood.setColor(cc.color(254, 58, 19));
            else if(num > 300)
                blood.setColor(cc.color(255, 247, 153));
            else{
                targetScale = 0.55;
                blood.setColor(cc.color(189, 0, 0));
            }

            if(actor._racetype != EnumRaceType.MONSTER)
                blood.setColor(cc.color(0, 180, 255));

            function getAction(){
                var seq = cc.sequence(
                    cc.scaleTo(tm/2, targetScale).easing(cc.easeElasticOut()),
                    cc.fadeOut(tm/2),
                    cc.callFunc(function(){blood.removeFromParent(); self._isBlooding = false;self._num=0;})
                    );
                var spawn = cc.spawn(
                    seq,
                    cc.moveBy(tm, cc.math.vec3(0, 0, pointZ)),
                    cc.rotateBy(tm, cc.randomMinus1To1()*40)
                    );
                return spawn;
            }

            if(attack){
                var criticalAttack = new cc.Sprite("#hpcounter.png");
                criticalAttack.setGlobalZOrder(FXZorder);
                tm = 1;
                criticalAttack.runAction(getAction());
                if(actor._name == "Rat")
                    criticalAttack.setVertexZ(cc.winSize.height*0.25);

                effect.addChild(criticalAttack);
                pointZ = 80;
                targetScale *= 2;
            }

            self._blood = blood;
            self._blood.runAction(getAction());
            effect.addChild(blood);

            return effect;
        }

        if(self._isBlooding == false){
            self._isBlooding = true;
            self._num = damage;
        }else{
            self._blood.stopAllActions();
            self._blood.removeFromParent();
            self._num += damage;
        }

        return getBlood();
    }
});