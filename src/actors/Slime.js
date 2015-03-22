var Slime = Actor.extend({
    
    ctor:function(){
        copyObject(ActorCommonValues, this);
        copyObject(SlimeValues, this);

        this._angryFace = false;

        this._super("model/slime/slime.c3b");
        this.setTexture("model/slime/baozi.jpg");
        this.setScale(17);
        this.addEffect(cc.vec3(0, 0, 0), CelLine, -1);
        this.setRotation3D(cc.vec3(90, 0, 0));
        this.setRotation(-90);

        this.runAction(cc.repeatForever(createAnimation("model/slime/slime.c3b", 0, 22, 0.7)));

        // this.schedule(this.update, 0);
    },

    reset:function(){
        copyObject(ActorCommonValues, this);
        copyObject(SlimeValues, this);

        this._target = this._findEnemy(this._racetype);
        this.walkMode();
        this.setVertexZ(0);
    },

    walkMode:function(){
        this.angryFace(false);
        this._super();
    },

    attackMode:function(){
        this.angryFace(true);
        this._super();
    },

    idleMode:function(){
        this.angryFace(false);
        this._super();
    },

    knockMode:function(collider, dirKnockMode){
        this.angryFace(false);
        this._super(this, collider, dirKnockMode);
    },

    angryFace:function(angry){
        if(this._angryFace != angry){
            this._angryFace = angry;
            if(angry)
                this.setTexture("model/slime/baozi2.jpg");
            else
                this.setTexture("model/slime/baozi.jpg");
        }
    }

});

(function(){
    var dur = 0.6, bsc = 17;
    var walk = cc.spawn(
            cc.sequence(
                    cc.delayTime(dur/8),
                    cc.JumpBy3D.create(dur*7/8, cc.vec3(0, 0, 0), 30, 1)
                ),
            cc.sequence(
                    cc.scaleTo(dur/8, bsc*1.4, bsc*1.4, bsc*0.75).easing(cc.easeSineOut())
                )
        );
    walk.retain();
    
    var idle = cc.sequence(
        cc.scaleTo(dur/2, bsc*1.1, bsc*1.1, bsc*0.8),
        cc.scaleTo(dur/2, bsc, bsc, bsc)
        );
    idle.retain();
    
    var attack1 = cc.spawn(
        cc.moveBy(dur/2, cc.vec3(0, 0, 20)),
        cc.rotateBy(dur/2, cc.vec3(70, 0, 0)),
        cc.moveTo(dur/2, cc.p(40, 0)).easing(cc.easeBounceOut())
        );
    attack1.retain();

    var attack2 = cc.spawn(
        cc.moveTo(dur, cc.vec3(0, 0, 0)),
        cc.rotateBy(dur*3/4, cc.vec3(-70, 0, 0)),
        cc.moveTo(dur, cc.p(0, 0)).easing(cc.easeBackOut())
        );
    attack2.retain();

    var die = cc.spawn(
        cc.sequence(
                cc.JumpBy3D.create(dur/2, cc.vec3(0, 0, 0), 30, 1),
                cc.scaleBy(dur, 2, 2, 0.1)
            ),
        cc.rotateBy(dur, cc.vec3(-90, 0, 0))
        );
    die.retain();

    var knock = cc.sequence(
        cc.rotateBy(dur/3, cc.vec3(-60, 0, 0)).easing(cc.easeBackInOut()),
        cc.rotateBy(dur/2, cc.vec3(60, 0, 0))
        );
    knock.retain();


    Slime.Actions={
        walk:walk,
        idle:idle,
        attack1:attack1,
        attack2:attack2,
        dead:die,
        knocked:knock
    }
})()
