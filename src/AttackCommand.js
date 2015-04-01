(function(_G){
    var AttackManager = [];
    
    _G.solveAttacks = function(dt){
        for(let i = 0; i < AttackManager.length; ++i){
            let attack = AttackManager[i];
            let apos = attack.getPosition();
            if(attack.mask == EnumRaceType.HERO){
                for(let j = 0; j < MonsterManager.length; ++j){
                    let monster = MonsterManager[j];
                    let mpos = monster._myPos;
                    let dist = cc.pDistance(apos, mpos);
                    if(dist < (attack.maxRange + monster._radius) && dist > attack.minRange){
                        // let angle = radNormalize(cc.pToAngleSelf(cc.pSub(mpos, apos)));
                        // let afacing = radNormalize(attack.facing - 90);

                        // if((afacing + attack.angle/2)>angle && angle >(afacing-attack.angle/2)){
                            attack.onCollide(monster);
                        // }
                    }
                }
            }else{
                for(let k = 0; k < HeroManager.length; ++k){
                    let hero = HeroManager[k];
                    let hpos = hero._myPos;
                    let dist = cc.pDistance(attack.getPosition(), hpos);
                    if(dist < (attack.maxRange+hero._radius) && dist > attack.minRange){
                        let angle = cc.pToAngleSelf(cc.pSub(hpos, attack.getPosition()));
                        if((attack.facing+attack.angle/2)>angle && angle>(attack.facing-attack.angle/2)){
                            attack.onCollide(hero);
                        }
                    }
                }
            }
            attack.curDuration += dt;
            if(attack.curDuration > attack.duration){
                attack.onTimeOut();
                AttackManager.splice(i, 1);
                i--;
            }else{
                attack.onUpdate(dt);
            }
        }
    };

    var BasicCollider = jsb.Sprite3D.extend({
        ctor:function(pos, facing, attackInfo){
            this._super();
            this.setCascadeColorEnabled(true);
            this.setCameraMask(cc.CameraFlag.USER1, true);

            this.minRange = 0   //the min radius of the fan
            this.maxRange = 150 //the max radius of the fan
            this.angle    = 120 //arc of attack, in radians
            this.knock    = 150 //default knock, knocks 150 units 
            this.mask     = 1   //1 is Heroes, 2 is enemy, 3 ??
            this.damage   = 100
            this.facing    = 0 //this is radians
            this.duration = 0
            this.curDuration = 0
            this.speed = 0 //traveling speed}
            this.criticalChance = 0

            this.initData(pos, facing, attackInfo);

            AttackManager.push(this);
        },

        initData:function(pos, facing, attackInfo){
            copyObject(attackInfo, this);
            this.facing = facing||this.facing;
            this.setPosition(pos);
        },

        onTimeOut:function(){
            this.removeFromParent();
        },

        playHitAudio:function(){
            // cc.audioEngine.playEffect(CommonAudios.hit);
        },

        hurtEffect:function(target){
            var hurtAction = cc.Animate.create(cc.animationCache.getAnimation("hurtAnimation"));
            var hurtEffect = new jsb.BillBoard();
            
            hurtEffect.setScale(1.2);
            hurtEffect.runAction(cc.sequence(
                hurtAction,
                cc.callFunc(function(){hurtEffect.removeFromParent();})));
            var pos = target.getPosition3D();
            hurtEffect.setPosition3D(cc.math.vec3(pos.x, pos.y, pos.z + 50)); 
            currentLayer.addChild(hurtEffect);           
        },

        onCollide:function(target){
            this.hurtEffect(target);
            this.playHitAudio();
            target.hurt(this);
        },

        onUpdate:function(){

        }
    });

    _G.BasicCollider = BasicCollider;

    var KnightNormalAttack = BasicCollider.extend({
        ctor:function(pos, facing, attackInfo, knight){
            this._super(pos, facing, attackInfo);
            this.owner = knight;
        }
    });
    _G.KnightNormalAttack = KnightNormalAttack;

    var ArcherNormalAttack = BasicCollider.extend({
        ctor:function(pos, facing, attackInfo, owner){
            this._super(pos, facing, attackInfo);
            this.owner = owner;

            this.sp = Archer.createArrow();
            this.sp.setRotation(cc.radiansToDegrees(-facing)-90);
            this.sp.setCameraMask(cc.CameraFlag.USER1);
            this.addChild(this.sp);
        },

        onCollide:function(target){
            this.hurtEffect(target);
            this.playHitAudio();
            this.owner._angry += target.hurt(this, true)*0.3;
            MessageDispatcher.dispatchMessage(MessageDispatcher.MessageType.ANGRY_CHANGE, [target]);
            this.curDuration = this.duration + 1;
        },

        onUpdate:function(dt){
            var selfPos = this.getPosition();
            var nextPos = cc.pRotateByAngle(cc.pAdd(cc.p(this.speed*dt, 0), selfPos), selfPos, this.facing);
            this.setPosition(nextPos);
        }
    });
    _G.ArcherNormalAttack = ArcherNormalAttack;
    

    var ArcherSpecialAttack = BasicCollider.extend({
        ctor:function(pos,facing,attackInfo, owner){
            this._super(pos,facing,attackInfo);

            this.owner = owner;
            this.sp = Archer.createArrow();
            this.sp.setRotation(cc.radiansToDegrees(-facing)-90);
            this.sp.setCameraMask(cc.CameraFlag.USER1);
            this.addChild(this.sp);
        },

        onCollide:function(target){
            if(this.curDOTTime >= this.DOTTimer){
                this.hurtEffect(target);
                this.playHitAudio();
                this.owner._angry += target.hurt(this, true)*0.3;
                MessageDispatcher.dispatchMessage(MessageDispatcher.MessageType.ANGRY_CHANGE, [target]);
                this.DOTApplied = true;
            }
        },

        onUpdate:function(dt){
            var selfPos = this.getPosition();
            var nextPos = cc.pRotateByAngle(cc.pAdd(cc.p(this.speed*dt, 0), selfPos), selfPos, this.facing);
            this.setPosition(nextPos);

            this.curDOTTime += dt;
            if(this.DOTApplied){
                this.DOTApplied = false;
                this.curDOTTime = 0;
            }
        }
    });
    _G.ArcherSpecialAttack = ArcherSpecialAttack;

    var MageNormalAttack = BasicCollider.extend({
        ctor:function(pos,facing,attackInfo, target, owner){
            this._super(pos,facing,attackInfo);
            this._target = target;
            this.owner = owner;

            this.sp = jsb.BillBoard.create("FX/FX.png", RECTS.iceBolt, 0);
            this.sp.setPosition3D(cc.math.vec3(0, 0, 50));
            this.sp.setScale(2);
            this.addChild(this.sp);

            var smoke = cc.ParticleSystem.create(ParticleManager.getPlistData("iceTrail"));
            var magicf = cc.spriteFrameCache.getSpriteFrame("puff.png");
            smoke.setTextureWithRect(magicf.getTexture(), magicf.getRect());
            smoke.setScale(2);
            this.addChild(smoke);
            smoke.setRotation3D(cc.math.vec3(90, 0, 0));
            smoke.setGlobalZOrder(0);
            smoke.setVertexZ(50);

            var pixi = cc.ParticleSystem.create(ParticleManager.getPlistData("pixi"));
            var pixif = cc.spriteFrameCache.getSpriteFrame("particle.png");
            pixi.setTextureWithRect(pixif.getTexture(), pixif.getRect());
            pixi.setScale(2);
            this.addChild(pixi);
            pixi.setRotation3D(cc.math.vec3(90, 0, 0));
            pixi.setGlobalZOrder(0);
            pixi.setVertexZ(50);

            this.setCameraMask(cc.CameraFlag.USER1, true);

            this.part1 = smoke;
            this.part2 = pixi;
        },

        onTimeOut:function(){
            this.part1.stopSystem();
            this.part2.stopSystem();
            var self = this;
            this.runAction(cc.sequence(cc.delayTime(1), cc.callFunc(function(){self.removeFromParent()})))

            var magic = cc.ParticleSystem.create(ParticleManager.getPlistData("magic"));
            var magicf = cc.spriteFrameCache.getSpriteFrame("particle.png");
            magic.setTextureWithRect(magicf.getTexture(), magicf.getRect());
            magic.setScale(1.5);
            magic.setRotation3D(cc.math.vec3(90, 0, 0));
            this.addChild(magic);
            magic.setGlobalZOrder(0);
            magic.setVertexZ(0);
            magic.setCameraMask(cc.CameraFlag.USER1);

            this.sp.setTextureRect(RECTS.iceSpike);
            this.sp.runAction(cc.fadeOut(1));
            this.sp.setScale(4);
        },

        playHitAudio:function(){
            cc.audioEngine.playEffect(MageProperty.ice_normalAttackHit);
        },

        onCollide:function(target){
            this.hurtEffect(target);
            this.playHitAudio();
            this.owner._angry += target.hurt(this)*0.3;
            MessageDispatcher.dispatchMessage(MessageDispatcher.MessageType.ANGRY_CHANGE, [this.owner])
            this.curDuration = this.duration + 1;
        },

        onUpdate:function(dt){
            var nextPos
            if(!!this._target && this._target._isalive){
                let selfPos = this.getPosition();
                var tpos = this._target._myPos;
                var angle = cc.pToAngleSelf(cc.pSub(tpos, selfPos));
                nextPos = cc.pRotateByAngle(cc.pAdd(cc.p(this.speed*dt, 0), selfPos), selfPos, angle);
                this.setPosition(nextPos);
            }else{
                let selfPos = this.getPosition();
                nextPos = cc.pRotateByAngle(cc.pAdd(cc.p(this.speed*dt, 0), selfPos), selfPos, this.facing);
            }
            this.setPosition(nextPos);
        }
    });
    _G.MageNormalAttack = MageNormalAttack;

    var MageIceSpikes = BasicCollider.extend({
        ctor:function(pos, facing, attackInfo, owner){
            this._super(pos, facing, attackInfo);

            this.sp = cc.ShadowSprite.createWithSpriteFrameName("shadow.png");
            this.sp.setGlobalZOrder(-this.getPositionY()+FXZorder);
            this.sp.setOpacity(100);
            this.sp.setPosition3D(cc.math.vec3(0, 0, 1));
            this.sp.setScale(this.maxRange/12);
            this.sp.setGlobalZOrder(-1);
            this.addChild(this.sp);
            this.owner = owner;

            //create 3 spikes
            var x = new cc.Node();
            this.spikes = x;
            this.addChild(x);
            for(let i = 0; i < 10; ++i){
                let rand = Math.ceil(Math.random()*3);
                let frameName = "#iceSpike"+rand+".png";
                var spike = new cc.Sprite(frameName);
                spike.setAnchorPoint(0.5, 0);
                spike.setRotation3D(cc.math.vec3(90, 0, 0));
                x.addChild(spike);
                if(rand == 3)
                    spike.setScale(1.5);
                else
                    spike.setScale(2);
                spike.setOpacity(165);
                spike.setFlippedX(!Math.floor(Math.random()*2));
                spike.setPosition3D(cc.math.vec3(cc.randomMinus1To1()*100,cc.randomMinus1To1()*100,1));
                spike.setGlobalZOrder(0);
                x.setScale(0);
                x.setVertexZ(-210);
            }
            x.runAction(cc.moveBy(0.3, cc.math.vec3()).easing(cc.easeBackOut()));
            x.runAction(cc.scaleTo(0.4, 1).easing(cc.easeBounceOut()));

            var magic = cc.BillboardParticleSystem.create(ParticleManager.getPlistData("magic"));
            var magicf = cc.spriteFrameCache.getSpriteFrame("particle.png");
            magic.setTextureWithRect(magicf.getTexture(), magicf.getRect());
            magic.setCamera(currentLayer._camera);
            magic.setScale(1.5);
            this.addChild(magic);
            magic.setGlobalZOrder(-this.getPositionY()*2+FXZorder);
            magic.setVertexZ(0);

            this.setCameraMask(cc.CameraFlag.USER1, true)
        },

        onTimeOut:function(){
            this.spikes.setVisible(false);
            var puff = cc.BillboardParticleSystem.create(ParticleManager.getPlistData("puffRing"));
            var puffFrame = cc.spriteFrameCache.getSpriteFrame("puff.png");
            puff.setTextureWithRect(puffFrame.getTexture(), puffFrame.getRect());
            puff.setCamera(currentLayer._camera);
            puff.setScale(3);
            this.addChild(puff);
            puff.setGlobalZOrder(-this.getPositionY()+FXZorder);
            puff.setVertexZ(20);
            puff.setCameraMask(cc.CameraFlag.USER1);

            var magic = cc.BillboardParticleSystem.create(ParticleManager.getPlistData("magic"));
            var magicf = cc.spriteFrameCache.getSpriteFrame("particle.png");
            magic.setTextureWithRect(magicf.getTexture(), magicf.getRect());
            magic.setCamera(currentLayer._camera);
            magic.setScale(1.5);
            this.addChild(magic);
            magic.setGlobalZOrder(-this.getPositionY()+FXZorder);
            magic.setVertexZ(0);
            magic.setCameraMask(cc.CameraFlag.USER1);

            this.sp.runAction(cc.fadeOut(1));
            var self = this;
            this.runAction(cc.sequence(
                cc.delayTime(1),
                cc.callFunc(function(){self.removeFromParent()})
                ));
        },

        onCollide:function(target){
            if(this.curDOTTime > this.DOTTimer){
                this.hurtEffect(target);
                this.playHitAudio();
                this.owner._angry += target.hurt(this)*0.1;
                MessageDispatcher.dispatchMessage(MessageDispatcher.MessageType.ANGRY_CHANGE, [target]);
                this.DOTApplied = true;
            }
        },

        onUpdate:function(dt){
            this.curDOTTime += dt;
            if(this.DOTApplied){
                this.DOTApplied = false;
                this.curDOTTime = 0;
            }
        }
    });
    _G.MageIceSpikes = MageIceSpikes;

    var DragonAttack = BasicCollider.extend({
        ctor:function(pos,facing,attackInfo){
            this._super(pos,facing,attackInfo);

            this.sp = jsb.BillBoard.create("FX/FX.png", RECTS.fireBall);
            this.sp.setPosition3D(cc.math.vec3(0, 0, 48));
            this.sp.setScale(1.7);
            this.sp.setCameraMask(cc.CameraFlag.USER1);
            this.addChild(this.sp);
        },

        onTimeOut:function(){
            this.runAction(cc.sequence(
                    cc.delayTime(0.5),
                    cc.callFunc(function(){this.removeFromParent()}, this)
                ));

            var magic = cc.ParticleSystem.create(ParticleManager.getPlistData("magic"));
            var magicf = cc.spriteFrameCache.getSpriteFrame("particle.png");
            magic.setTextureWithRect(magicf.getTexture(), magicf.getRect());
            magic.setScale(1.5);
            magic.setRotation3D(cc.math.vec3(90, 0, 0));
            this.addChild(magic);
            magic.setGlobalZOrder(-this.y*2+FXZorder);
            magic.setVertexZ(0);
            magic.setEndColor(cc.color(255, 128, 0));
            magic.setCameraMask(cc.CameraFlag.USER1);

            var fireBallAction = new cc.Animate(cc.animationCache.getAnimation("fireBallAnim"));
            this.sp.runAction(fireBallAction);
            this.sp.setScale(2);
        },

        playHitAudio:function(){
            cc.audioEngine.playEffect(MonsterDragonValues.fireHit);
        },

        onCollide:function(target){
            this.hurtEffect(target);
            this.playHitAudio();
            target.hurt(this);
            this.curDuration = this.duration + 1;
        },

        onUpdate:function(dt){
            var selfPos = this.getPosition();
            var nextPos = cc.pRotateByAngle(cc.pAdd(cc.p(this.speed*dt, 0), selfPos), selfPos, this.facing);
            this.setPosition(nextPos);
        }
    });
    _G.DragonAttack = DragonAttack;
})(this);
