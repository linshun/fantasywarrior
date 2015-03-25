(function(_G){
    var stage = 0;
    var logicFrq = 1.0; //tick per second
    var battleSiteX = [-2800,-1800,-800];
    var monsterCount = {dragon:1, slime:7, piglet:2, rat:0}

    var frontDistanceWithHeroX = 600
    var backwardDistanceWithHeroX = 800
    var distanceWithHeroX = 150
    var distanceWithHeroY = 150

    var EXIST_MIN_MONSTER = 4

    var GameMaster = function(layer){
        this._totaltime = 0;
        this._layer = layer;
        _G.HeroManager = [];
        _G.MonsterManager = [];
        this.init();

    };
    _G.GameMaster = GameMaster;

    GameMaster.prototype = {
        init:function(){
            this.addHeroes();
            this.addMonsters();

            for(var i=0; i < 4; ++i)
                this.randomshowMonster(true);

            stage=1;
        },

        addHeroes:function(){
            var knight = new Knight();
            knight.setPosition(battleSiteX[0], 270);
            this._layer.addChild(knight);
            knight.idleMode();
            knight.setAIEnabled(true);
            HeroManager.push(knight);

            var mage = new Mage();
            mage.setPosition(battleSiteX[0], 400);
            this._layer.addChild(mage);
            mage.idleMode();
            mage.setAIEnabled(true);
            HeroManager.push(mage);

            var archer = new Archer();
            archer.setPosition(battleSiteX[0], 150);
            this._layer.addChild(archer);
            archer.idleMode();
            archer.setAIEnabled(true);
            HeroManager.push(archer);
        },

        addMonsters:function(){
            this.addDragon();
            this.addSlime();
            this.addPiglet();
            this.addRat();
        },

        addDragon:function(){
            for(var i = 0; i < monsterCount.dragon; ++i){
                var dragon = new Dragon();
                dragon.setVisible(false);
                // dragon.setAIEnabled(false);
                this._layer.addChild(dragon);
                cc.pool.putInPool(dragon);
            }
        },

        addSlime:function(){
            for (var i = 0; i < monsterCount.slime; ++i) {
                var slime = new Slime();
                slime.setVisible(false);
                this._layer.addChild(slime);
                cc.pool.putInPool(slime);
            };
        },

        addPiglet:function(){
            for(var i = 0; i < monsterCount.piglet; ++i){
                var pig = new Piglet();
                pig.setVisible(false);
                this._layer.addChild(pig);
                cc.pool.putInPool(pig);
            }
        },

        addRat:function(){
            for(var i = 0; i < monsterCount.rat; ++i){
                var rat = new Rat();
                rat.setVisible(false);
                this._layer.addChild(rat);
                cc.pool.putInPool(rat);
            }
        },

        randomshowMonster:function(isFront){
            var rand = Math.random();
            
            if(rand < 0.15){
                if(cc.pool.hasObject(Dragon))
                    this.showDragon(isFront);
                else
                    this.randomshowMonster(isFront);
            }else if(rand < 0.3){
                if(cc.pool.hasObject(Rat))
                    this.showRat(isFront);
                else
                    this.randomshowMonster(isFront);
            }else if(rand < 0.6){
                if(cc.pool.hasObject(Piglet))
                    this.showPiglet(isFront);
                else
                    this.randomshowMonster(isFront);
            }else{
                this.showSlime(isFront);
            }
        },

        showDragon:function(isFront){
            var dragon = cc.pool.getFromPool(Dragon);

            dragon.reset();
            var appearPos = this.getFocusPointOfHeros();
            var random = Math.random()*0.2+1;
            if(stage == 0){
                appearPos.x += frontDistanceWithHeroX*random;
                dragon.setFacing(90);
            }else{
                if(isFront){
                    appearPos.x += frontDistanceWithHeroX*1.8*random;
                    dragon.setFacing(90);
                }else{
                    appearPos.x -= backwardDistanceWithHeroX*1.8*random;
                    dragon.setFacing(-90);
                }
            }

            randomY = 2*Math.random()-1;
            appearPos.y = appearPos.y + randomY*distanceWithHeroY;
            dragon.setPosition(appearPos);
            dragon._myPos = appearPos;
            dragon.setVisible(true);
            dragon._goRight = false;
            dragon.setAIEnabled(true);
            MonsterManager.push(dragon);
        },

        showPiglet:function(isFront){
            var piglet = cc.pool.getFromPool(Piglet);
            piglet.reset();
            var appearPos = this.getFocusPointOfHeros();
            var randomX = Math.random()*0.2+1;
            if(stage == 0){
                appearPos.x += frontDistanceWithHeroX*randomX;
                piglet.setFacing(90);
            }else{
                if(isFront){
                    appearPos.x += frontDistanceWithHeroX*1.8*randomX;
                    piglet.setFacing(90);
                }else{
                    appearPos.x -= backwardDistanceWithHeroX*1.8*randomX;
                    piglet.setFacing(-90)
                }
            }
            var randomY = 2*Math.random()-1;
            appearPos.y -= randomY*distanceWithHeroY;
            piglet.setPosition(appearPos);
            piglet._myPos = appearPos;
            piglet.setVisible(true);
            piglet._goRight = false;
            piglet.setAIEnabled(true);
            MonsterManager.push(piglet);
        },

        showRat:function(isFront){
            var rat = cc.pool.getFromPool(Rat);
            rat.reset();
            rat._goRight = false;
            this.jumpInto(rat, isFront);
            MonsterManager.push(rat);
        },

        showSlime:function(isFront){
            var slime = cc.pool.getFromPool(Slime);
            slime.reset();
            slime._goRight = false;
            this.jumpInto(slime, isFront);
            MonsterManager.push(slime);
        },

        jumpInto:function(obj, isFront){
            var appearPos = this.getFocusPointOfHeros();
            var random = 2*Math.random()-1;
            if(isFront)
                appearPos.x += frontDistanceWithHeroX + random*distanceWithHeroX;
            else
                appearPos.x -= frontDistanceWithHeroX + random*distanceWithHeroX;

            appearPos.y += 1500;
            obj.setPosition(appearPos);
            obj._myPos = appearPos;

            if(stage == 0){
                obj.runAction(cc.sequence(
                        cc.delayTime(Math.random()),
                        cc.callFunc(function(){obj.setVisible(true);}),
                        cc.JumpBy3D.create(0.5, cc.math.vec3(-200*(Math.random()*0.6+0.7), -1700 + 300*Math.random(), 0),150, 1),
                        cc.callFunc(function(){obj.setAIEnabled(true); obj._myPos = obj.getPosition()})
                    ));
                obj.setFacing(135);
            }else{
                if(isFront){
                    obj.runAction(cc.sequence(
                        cc.delayTime(Math.random()),
                        cc.callFunc(function(){obj.setVisible(true);}),
                        cc.JumpBy3D.create(0.5, cc.math.vec3(0, -1700 + 300*Math.random(), 0),150, 1),
                        cc.callFunc(function(){obj.setAIEnabled(true); obj._myPos = obj.getPosition()})
                    ));
                    obj.setFacing(135);
                }else{
                    obj.runAction(cc.sequence(
                        cc.delayTime(Math.random()),
                        cc.callFunc(function(){obj.setVisible(true);}),
                        cc.JumpBy3D.create(0.5, cc.math.vec3(200*(Math.random()*0.6+0.7), -1700 + 300*Math.random(), 0),150, 1),
                        cc.callFunc(function(){obj.setAIEnabled(true); obj._myPos = obj.getPosition()})
                    ));
                    obj.setFacing(45);
                }
            }
        },

        update:function(dt){
            this._totaltime += dt;
            if(this._totaltime > logicFrq){
                this._totaltime -= logicFrq;
                this.logicUpdate();
            }
        },

        logicUpdate:function(){
            if(stage === 1){
                if(MonsterManager.length < EXIST_MIN_MONSTER){

                    for(let i = 0; i < 4; ++i)
                        this.randomshowMonster(true);

                    stage = 2;
                }
            }else if(stage === 2){
                if(MonsterManager.length < EXIST_MIN_MONSTER){
                    for(let i = 0; i < 4; ++i)
                        this.randomshowMonster(true);

                    stage = 3;
                }
            }else if(stage === 3){
                if(MonsterManager.length == 0){
                    for(let i = 0; i < HeroManager.length; ++i){
                        HeroManager[i]._goRight = true;
                    }
                    stage = 4;
                }
            }else if(stage === 4){
                if(this.getFocusPointOfHeros().x > battleSiteX[1]){
                    for(let i = 0; i < 3; ++i)
                        this.randomshowMonster(true);
                    for(let i = 0; i < 4; ++i)
                        this.randomshowMonster(false)

                    stage = 5;
                }
            }else if(stage == 5){
                if(MonsterManager.length < EXIST_MIN_MONSTER){
                    for(let i = 0; i < 4; ++i)
                        this.randomshowMonster(true);

                    stage = 6;
                }
            }else if(stage === 6){
                if(MonsterManager.length < EXIST_MIN_MONSTER){
                    for(let i = 0; i < 4; ++i)
                        this.randomshowMonster(false);

                    stage = 7;
                }
            }else if(stage === 7){
                if(MonsterManager.length == 0){
                    for(let i = 0; i < HeroManager.length; ++i){
                        let hero = HeroManager[i];
                        if(hero)
                            hero._goRight = true;
                    }


                    var d = cc.pool.getFromPool(Dragon);
                    if(d)
                        d.removeFromParent();
                    
                    for(let i = 0; i < monsterCount.piglet; ++i){
                        var p = cc.pool.getFromPool(Piglet);
                        if(p)
                            p.removeFromParent();
                    }

                    for(let i = 0; i < monsterCount.slime; ++i){
                        var s = cc.pool.getFromPool(Slime);
                        if(s)
                            s.removeFromParent();
                    }

                    stage = 8;
                }
            }else if(stage === 8){
                if(this.getFocusPointOfHeros().x > battleSiteX[2]){
                    this.showWarning();
                    stage = 9;
                }
            }

        },

        showWarning:function(){
            cc.Texture2D.setDefaultAlphaPixelFormat(0);//AUTO
            var waring = new cc.Layer();
            var waring_logo = new cc.Sprite("#caution.png");
            cc.Texture2D.setDefaultAlphaPixelFormat(4);//RGB565
            waring_logo.setPosition(cc.winSize.width*0.5, cc.winSize.height*0.5);
            waring_logo.setVertexZ(1);
            waring_logo.setGlobalZOrder(UIZorder);

            var self = this;
            function showdialog(){
                waring.removeFromParent();
                self.showDialog();
                cc.audioEngine.playEffect("audios/effects/boss/boss.mp3");
            }

            waring_logo.runAction(cc.sequence(
                    cc.delayTime(0.5),
                    cc.blink(1.5, 3).easing(cc.easeSineOut()),
                    cc.callFunc(showdialog)
                ));
            waring.addChild(waring_logo);
            waring.setScale(0.5);
            waring.setVertexZ(-cc.director.getZEye()/2);
            waring.ignoreAnchorPointForPosition(false);
            waring.setLocalZOrder(999);
            this._layer._camera.addChild(waring);
        },

        showDialog:function(){
            cc.Texture2D.setDefaultAlphaPixelFormat(0);//AUTO
            var colorLayer = new cc.LayerColor(cc.color(10, 10, 10, 150));
            colorLayer.ignoreAnchorPointForPosition(false);
            colorLayer.setVertexZ(-cc.director.getZEye()/5);
            colorLayer.setGlobalZOrder(0);
            this._layer._camera.addChild(colorLayer);

            //create dialog
            var dialog = new cc.Layer();
            dialog.x = -cc.winSize.width*0.025;

            var outframe = new cc.Sprite("#outframe.png");
            outframe.setPosition(cc.winSize.width*0.55, cc.winSize.height*0.27);
            outframe.setScale(0.6*resolutionRate);
            outframe.setGlobalZOrder(UIZorder+1);
            dialog.addChild(outframe);

            var inframe = new cc.Sprite("#inframe.png");
            inframe.setPosition(cc.winSize.width*0.67, cc.winSize.height*0.27);
            inframe.setScale(0.5*resolutionRate);
            inframe.setGlobalZOrder(UIZorder);
            dialog.addChild(inframe);

            var bossicon = new cc.Sprite("#bossicon.png");
            bossicon.setPosition(cc.winSize.width*0.42, cc.winSize.height*0.46);
            bossicon.setScale(0.75*resolutionRate);
            bossicon.setFlippedX(true);
            bossicon.setGlobalZOrder(UIZorder);
            dialog.addChild(bossicon);

            var bosslogo = new cc.Sprite("#bosslogo.png");
            bosslogo.setPosition(cc.winSize.width*0.417, cc.winSize.height*0.265);
            bosslogo.setScale(0.74*resolutionRate);
            dialog.addChild(bosslogo);

            var ttfconf = {outlineSize:0, fontSize:24, glyphs:0, fontFilePath:"fonts/britanic bold.ttf"};
            var text = cc.Label.createWithTTF(ttfconf, "How dare you???");
            text.setPosition(cc.winSize.width*0.68, cc.winSize.height*0.27);
            text.setGlobalZOrder(UIZorder+1);
            dialog.addChild(text);

            // dialog.setScale
            dialog.setScale(0.1);
            dialog.ignoreAnchorPointForPosition(false);
            dialog.setVertexZ(-cc.director.getZEye()/3);
            dialog.setGlobalZOrder(UIZorder);
            this._layer._camera.addChild(dialog);

            function pausegame(){
                for(let i = 0; i < HeroManager.length; ++i){
                    HeroManager[i].idleMode();
                    HeroManager[i].setAIEnabled(false);
                }
            }
            dialog.runAction(cc.sequence(
                cc.scaleTo(0.5, 0.5), 
                cc.callFunc(pausegame)
                ))
            this._layer._uiLayer.setVisible(false);

            var self = this;
            function removeDialog(){
                dialog.removeFromParent();
                colorLayer.removeFromParent();
                self._layer._uiLayer.setVisible(true);
                for(let i = 0; i < HeroManager.length; ++i){
                    HeroManager[i].setAIEnabled(true);
                }
                self.showBoss();
            }
            dialog.runAction(cc.sequence(
                cc.delayTime(3),
                cc.callFunc(removeDialog)
                ));

            cc.Texture2D.setDefaultAlphaPixelFormat(4);//RGB565
        },

        showBoss:function(){
            var boss = new Rat();
            this._layer.addChild(boss);
            boss.reset();
            var appearPos = cc.math.vec3(500, 200, 300);
            boss.setPosition3D(appearPos);
            boss._myPos = appearPos;
            boss.setFacing(180);
            boss.runAction(cc.sequence(
                cc.moveBy(0.5, cc.math.vec3(0, 0, -300)).easing(cc.easeBounceOut()),
                cc.callFunc(function(){boss.setAIEnabled(true);})
                ));
            MonsterManager.push(boss);
        },

        getFocusPointOfHeros:function(){
            var ptFocus = cc.p(0, 0);
            for(var i = 0; i < HeroManager.length; ++i){
                ptFocus.x += HeroManager[i].x;
                ptFocus.y += HeroManager[i].y;
            }
            ptFocus.x /= HeroManager.length;
            ptFocus.y /= HeroManager.length;
            return ptFocus;
        }
    };

})(this);