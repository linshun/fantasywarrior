var Actor = cc.EffectSprite3D.extend({
    _stateMachine:null,
    _type:"Actor",
    _curAnimation:"",
    _curAnimation3d:null,

    ctor:function(modelpath){
        this._super(modelpath);
        this._stateMachine = new StateMachine(this);
    },

    update:function(dt){
        this._stateMachine.update(dt);
    },

    getFSM:function(){
        return this._stateMachine;
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
    }
});