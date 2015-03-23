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
                        let angle = radNormalize(cc.pToAngleSelf(cc.pSub(mpos, apos)));
                        let afacing = radNormalize(attack.facing);

                        if((afacing + attack.angle/2)>angle && angle >(afacing-attack.angle/2)){
                            attack.onCollide(monster);
                        }
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

    var BasicCollider = cc.Sprite3D.extend({
        ctor:function(pos, facing, attackInfo){
            this._super();
            this.setCascadeColorEnabled(true);

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
            cc.audioEngine.playEffect(CommonAudios.hit);
        },

        hurtEffect:function(target){
            var hurtAction = cc.Animate.create(cc.animationCache.getAnimation("hurtAnimation"));
            var hurtEffect = new cc.BillBoard();
            
            hurtEffect.setScale(1.2);
            hurtEffect.runAction(cc.sequence(
                hurtAction,
                cc.callFunc(function(){hurtEffect.removeFromParent();})));
            var pos = target.getPosition3D();
            hurtEffect.setPosition3D(cc.vec3(pos.x, pos.y, pos.z + 50)); 
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
    
})(this);