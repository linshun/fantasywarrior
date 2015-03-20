var State = function(){
    this._type = "Base state";
}

State.prototype = {
    onEnter:function(actor){
        cc.log(actor._name + " enter state : " + this._type);
    },

    execute:function(actor, dt){

    },

    onExit:function(actor){
        cc.log(actor._name + " exit state : " + this._type);
    }
}

var StateIDLE = function(){
    State.call(this);
    this._type = "Idle State";
};

StateIDLE.prototype = Object.create(State.prototype);
StateIDLE.prototype.constructor = StateIDLE;

StateIDLE.prototype.execute = function(actor, dt){
    //todo
}

var StateWalk = function(){
    State.call(this);
    this._type = "Walk State";
};
StateWalk.prototype = Object.create(State.prototype);
StateWalk.prototype.constructor = StateWalk;
StateWalk.prototype.execute = function(actor, dt){

}

var StateAttack = function(){
    State.call(this);
    this._type = "Attack State";
}
StateAttack.prototype = Object.create(State.prototype);
StateAttack.prototype.constructor = StateAttack;
StateAttack.prototype.execute = function(actor, dt){

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
        // this._owner._myPos = this._owner.getPosition();
        // this._owner._aliveTime += dt;
        // if(this._AIEnabled){
        //     this._AITimer += dt;
        //     if(this._AITimer > this._AIFrequency){
        //         this._AITimer -= this._AIFrequency;
        //         this.AI(); //AI function does not run every tick
        //     }
        // }
        if(this._state)
            this._state.execute(this._owner, dt);
    }
}

