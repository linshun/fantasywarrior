var Actor = cc.EffectSprite3D.extend({
    _stateMachine:null,
    _type:"Actor",
    _curAnimation:"",
    _curAnimation3d:null,
    _circle:null,
    _effectNode:null,
    puff:null,

    ctor:function(modelpath){
        this._super(modelpath);
        this._stateMachine = new StateMachine(this);

        //todo HPCounter

        this._effectNode = new cc.Node();
        if(currentLayer != null)
            currentLayer.addChild(this._effectNode);

    },

    update:function(dt){
        this._stateMachine.update(dt);
    },

    getFSM:function(){
        return this._stateMachine;
    },

    isHero:function(){

    },

    isMonster:function(){

    },

    playAnimation:function(name, loop){
        if(name == this._curAnimation)
            return;

        this.stopAllActions();
        if(loop)
            this._curAnimation3d = cc.repeatForever(this.__proto__.constructor.Actions[name].clone());
        else
            this._curAnimation3d = this.__proto__.constructor.Actions[name].clone();
        this.runAction(this._curAnimation3d);
        this._curAnimation = name;
    },

    idleMode:function(){
        this._stateMachine.changeState(new StateIDLE);
        this.playAnimation("idle", true);
    },

    walkMode:function(){
        this._stateMachine.changeState(new StateWalk);
        this.playAnimation("walk", true);
    },

    attackMode:function(){
        this._stateMachine.changeState(new StateAttack);
        this.playAnimation("idle", true); // idle? not attack?
        // self._attackTimer = self._attackFrequency*3/4
    },

    initShadow:function(){
        this._circle = new cc.Sprite(
            "#shadow.png");
        //use Shadow size for aesthetic, use radius to see collision size
        this._circle.setScale(25/this.getScale()*0.2)
        this._circle.setOpacity(255*0.7);
        this._circle.setRotation3D(cc.vec3(90, 0, 0));
        this.addChild(this._circle);
    },

    initPuff:function(){
        var puff = cc.BillboardParticleSystem.create(ParticleManager.getPlistData("walkpuff"));
        var puffFrame = cc.spriteFrameCache.getSpriteFrame("walkingPuff.png");
        puff.setTextureWithRect(puffFrame.getTexture(), puffFrame.getRect());
        puff.setScale(1.5);
        puff.setGlobalZOrder(0);
        this._puff = puff;
        this._effectNode.addChild(puff);
    }
});