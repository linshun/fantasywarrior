var Actor = cc.EffectSprite3D.extend({
    _stateMachine:null,
    _curAnimation:"",
    _curAnimation3d:null,
    _circle:null,
    _effectNode:null,
    puff:null,

    ctor:function(modelpath){
        this._super(modelpath);
        // this._stateMachine = new StateMachine(this);

        copyObject(ActorDefaultValues, this);
        copyObject(ActorCommonValues, this);

        //todo HPCounter

        this._effectNode = new cc.Node();
        if(currentLayer != null)
            currentLayer.addChild(this._effectNode);

    },

    update:function(dt){
        //baseUpdate
        this._myPos = this.getPosition();
        this._aliveTime += dt;
        if(this._AIEnabled){
            this._AITimer += dt;
            if(this._AITimer > this._AIFrequency){
                this._AITimer -= this._AIFrequency;
                this.AI(); //AI function does not run every tick
            }
        }
        // this._stateMachine.update(dt);
        this.stateMachineUpdate(dt);
        this.movementUpdate(dt);
    },

    AI:function(){
        cc.log(this._name + " update ai")
        if(!this._isalive)
            return;

        this._target = this._findEnemy(this._racetype);
        if(this._target != null){//if i can find a target
            var p1 = this._myPos;
            var p2 = this._target._myPos;
            this._targetFacing = cc.pToAngleSelf(cc.pSub(p2, p1));
            var isInRange = this._inRange();
            if((!this._cooldown || this._statetype != EnumStateType.WALKING) && !isInRange){
                cc.log(this._name + " walk")
                this.walkMode();
                return;
            }else if(isInRange && this._statetype != EnumStateType.ATTACKING){
                cc.log(this._name + " attack")
                this.attackMode();
                return;
            }
        }else if(this._statetype != EnumStateType.WALKING && this._goRight == true){
            cc.log(this._name + "walk right")
            this.walkMode();
            return;
        }else if(this._cooldown || this._statetype != EnumStateType.IDLE){
            cc.log(this._name + "idle")
            this.idleMode();
            return;
        }
    },

    stateMachineUpdate:function(dt){
        var state = this._statetype;
        if(state == EnumStateType.WALKING)
            this.walkUpdate(dt);
        else if(state == EnumStateType.KNOCKING)
            this.knockingUpdate(dt);
        else if(state == EnumStateType.ATTACKING)
            this.attackUpdate(dt);
    },

    walkUpdate:function(dt){
        cc.log()
        if(this._target && this._target._isalive){
            if(this._inRange())
                this.attackMode();
        }else{
            if(this._goRight)
                this._targetFacing = 0;
            else
                this.idleMode();
        }
    },

    knockingUpdate:function(dt){

    },

    attackUpdate:function(dt){
        cc.log("attack update")
    },

    movementUpdate:function(dt){
        cc.log("movementUpdate")
        //facing
        if(this._curFacing != this._targetFacing){
            var angleDt = this._curFacing - this._targetFacing;
            angleDt %= Math.PI*2;
            var turnleft = (angleDt - Math.PI) < 0;
            var turnby = this._turnSpeed*dt;

            //right
            if(turnby > angleDt)
                this._curFacing = this._targetFacing;
            else if(turnleft)
                this._curFacing = this._curFacing - turnby;
            else
                this._curFacing = this._curFacing + turnby;
            cc.log("face : " + this._curFacing)
            this.setRotation(-cc.radiansToDegrees(this._curFacing));
        }
        //position
        cc.log(this._curSpeed)
        cc.log(this._speed)
        if(this._statetype != EnumStateType.WALKING)
            this._curSpeed = cc.clampf(this._curSpeed - this._decceleration*dt, 0, this._speed)
        else if(this._curSpeed < this._speed)
            this._curSpeed = cc.clampf(this._curSpeed + this._acceleration*dt, 0, this._speed);

        cc.log(this._curSpeed)
        if(this._curSpeed > 0){
            var targetPostion = cc.pRotateByAngle(cc.pAdd(cc.p(this._curSpeed*dt, 0), this._myPos), this._myPos, this._curFacing);
            cc.log("target position " +targetPostion.x + "," +targetPostion.y)
            this.setPosition(targetPostion);
        }
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

    setStateType:function(type){
        this._statetype = type;
        if(this._puff){
            if(type == EnumStateType.WALKING)
                this._puff.setEmissionRate(5);
            else
                this._puff.setEmissionRate(0);
        }
    },

    idleMode:function(){
        this.setStateType(EnumStateType.IDLE)
        this.playAnimation("idle", true);
    },

    walkMode:function(){
        this.setStateType(EnumStateType.WALKING)
        this.playAnimation("walk", true);
    },

    attackMode:function(){
        this.setStateType(EnumStateType.ATTACKING)
        this.playAnimation("idle", true); // idle? not attack?
        self._attackTimer = self._attackFrequency*3/4
    },

    knockMode:function(){
        //todo
    },

    dyingMode:function(){
        //todo
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
    },

    _findEnemy:function(heroOrMonster){
        var shortest = this._searchDistance,
            target = null, allDead = true;
        var list;
        if(heroOrMonster == EnumRaceType.MONSTER)
            list = HeroManager;
        else
            list = MonsterManager;
        cc.log(list.length)
        for(var i = 0; i < list.length; ++i){
            var temp = list[i];
            var dis = cc.pDistance(this._myPos, temp._myPos)
            cc.log("distance"+dis)
            if(temp._isalive){
                if(dis < shortest){
                    shortest = dis;
                    target = temp;
                }
                allDead = false;
            }
        }
        return target;//{target:target, allDead:allDead};
    },

    _inRange:function(){
        if(!this._target)
            return;

        if(this._target._isalive){
            var attackDistance = this._attackRange + this._target._radius -1;
            return (cc.pDistance(this._myPos, this._target._myPos) < attackDistance);
        }
    },

    setAIEnabled:function(b){
        this._AIEnabled = b;
    },

    setFacing:function(degrees){
        this._curFacing = cc.degreesToRadians(degrees);
        this._targetFacing = this._curFacing;
        this.setRotation(degrees);
    },

    //cc.pool will invoke this when put into pool
    unuse:function(){
        this.setVisible(false);
    },

    //cc.pool will invoke this when get from pool
    reuse:function(){
        this.setVisible(true);
    }
});