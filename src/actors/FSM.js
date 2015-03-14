var State = function(){

}

State.prototype = {
    onEnter:function(actor){

    },

    execute:function(actor, dt){

    },

    onExit:function(actor){

    }
}

var StateMachine = function(owner){
    this._state = null;
    this._owner = owner;
};

StateMachine.prototype = {
    changeState:function(state){
        this.state && this._state.onExit(this._owner);
        this._state = state;
        this._state.onEnter(this._owner);
    },

    update:function(dt){
        if(this._state)
            this._state.execute(this._owner, dt);
    }
}