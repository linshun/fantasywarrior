var Actor = cc.Sprite3D.extend({
    _stateMachine:null,

    ctor:function(modelpath){
        this._super(modelpath);
        this._stateMachine = new StateMachine(this);
    },

    update:function(dt){
        this._stateMachine.update(dt);
    },

    getFSM:function(){
        return this._stateMachine;
    }
});