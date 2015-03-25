var BattleFieldUI = cc.Layer.extend({
    ctor:function(){
        this._super();
        this.avatarInit();
        this.bloodbarInit();
        this.angrybarInit();
        this.touchButtonInit();
        this.timeInit();

        cc.audioEngine.playMusic(BGM_RES.BATTLEFIELDBGM, true);

        MessageDispatcher.registerMessage(MessageDispatcher.MessageType.BLOOD_MINUS, this.bloodMinus, this);
        MessageDispatcher.registerMessage(MessageDispatcher.MessageType.ANGRY_CHANGE, this.angryChange, this);
    },

    shakeAvatar:function(){
        return cc.Repeat.create(cc.Spawn.create(
                cc.sequence(
                    cc.scaleTo(0.075, 0.75),
                    cc.scaleTo(0.075, 0.7)
                ),
                cc.sequence(
                    cc.moveBy(0.05, cc.p(6.5, 0)),
                    cc.moveBy(0.05, cc.p(-13, 0)),
                    cc.moveBy(0.05, cc.p(6.5, 0))
                )

            ),2);
    },

    bloodMinus:function(hero){
        var progressTo, progressToClone, tintTo,
            percent = hero._hp/hero._maxhp*100;

        var bloodBar, bloodBarClone, avatar;
        if(hero._name == "Knight"){
            bloodBar = this.knightBlood;
            bloodBarClone = this.knightBloodClone;
            avatar = this.knightPng;
        }else if(hero._name == "Archer"){
            bloodBar = this.archerBlood;
            bloodBarClone = this.archerBloodClone;
            avatar = this.archerPng;
        }else{
            bloodBar = this.mageBlood;
            bloodBarClone = this.mageBloodClone;
            avatar = this.magePng;
        }

        bloodBar.stopAllActions();
        bloodBarClone.stopAllActions();
        avatar.runAction(this.shakeAvatar());

        if(hero._hp > 0 && percent > 50){
            progressTo = cc.progressTo(0.3, percent);
            progressToClone = cc.progressTo(1, percent);
            bloodBar.runAction(progressTo);
            bloodBarClone.runAction(progressToClone);
        }else if(hero._hp > 0 && percent <= 50){
            progressTo = cc.progressTo(0.3, percent);
            progressToClone = cc.progressTo(1, percent);
            tintTo = cc.tintTo(0.5, 254, 225, 26);

            bloodBar.runAction(cc.spawn(progressTo, tintTo));
            bloodBarClone.runAction(progressToClone);
        }else if(hero._hp > 0 && percent <= 30){
            progressTo = cc.progressTo(0.3, percent);
            progressToClone = cc.progressTo(1, percent);
            tintTo = cc.tintTo(0.5, 254, 26, 69);

            bloodBar.runAction(cc.spawn(progressTo, tintTo));
            bloodBarClone.runAction(progressToClone);
        }else if(hero._hp <= 0){
            progressTo = cc.progressTo(0.3, 0.1);
            progressToClone = cc.progressTo(1, 2);
            bloodBar.runAction(progressTo);
            bloodBarClone.runAction(progressToClone);
        }

    },

    angryChange:function(hero){
        var percent = hero._angry / hero._angryMax * 100;
        var progressTo = cc.progressTo(0.3, percent);

        var bar;
        if(hero._name == "Knight"){
            bar = this.knightAngry;
            if(percent >= 100)
                this.knightAngryFullSignal.setVisible(true);
            else
                this.knightAngryFullSignal.setVisible(false);
        }else if(hero._name == "Archer"){
            bar = this.archerAngry;
            if(percent >= 100)
                this.archerAngryFullSignal.setVisible(true);
            else
                this.archerAngryFullSignal.setVisible(false);
        }else{
            bar = this.mageAngry;
            if(percent >= 100)
                this.mageAngryFullSignal.setVisible(true);
            else
                this.mageAngryFullSignal.setVisible(false);
        }

        bar.runAction(progressTo);
    },

    avatarInit:function(){
        var offset = 8, scale = 0.7;

        this.magePng = new cc.Sprite("#UI-1136-640_18.png");
        this.magePng.setPosition3D(cc.math.vec3(1070/1136*cc.winSize.width, 70/640*cc.winSize.height, 3));
        this.magePng.setScale(scale);
        this.addChild(this.magePng, 2);
        this.magePngFrame = new cc.Sprite("#UI-2.png");
        this.magePngFrame.setScale(scale);
        this.magePngFrame.setPosition3D(cc.math.vec3(this.magePng.x + 1, this.magePng.y - offset, 1));
        this.addChild(this.magePngFrame);

        this.knightPng = new cc.Sprite("#UI-1136-640_03.png");
        this.knightPng.setPosition3D(cc.math.vec3(-this.magePng.getContentSize().width*2 + this.magePng.x+40, 70/640*cc.winSize.height, 2));
        this.knightPng.setScale(scale);
        this.addChild(this.knightPng, 2);
        this.knightPngFrame = new cc.Sprite("#UI-2.png")
        this.knightPngFrame.setScale(scale);
        this.knightPngFrame.setPosition3D(cc.math.vec3(this.knightPng.x+1, this.knightPng.y-offset, 1));
        this.addChild(this.knightPngFrame, 1);

        this.archerPng = new cc.Sprite("#UI-1136-640_11.png");
        this.archerPng.setPosition3D(cc.math.vec3(-this.magePng.getContentSize().width+this.magePng.x+20, 70/640*cc.winSize.height, 2));
        this.archerPng.setScale(scale);
        this.addChild(this.archerPng, 2);
        this.archerPngFrame = new cc.Sprite("#UI-2.png");
        this.archerPngFrame.setScale(scale);
        this.archerPngFrame.setPosition3D(cc.math.vec3(this.archerPng.x+1, this.archerPng.y-offset, 1));
        this.addChild(this.archerPngFrame);
    },

    bloodbarInit:function(){
        var offset = 45, scale = 0.7;
        this.knightBlood = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.knightBlood.setColor(cc.color(149, 254, 26));
        this.knightBlood.setType(cc.ProgressTimer.TYPE_BAR);
        this.knightBlood.setBarChangeRate(cc.p(1, 0));
        this.knightBlood.setMidpoint(cc.p(0, 0));
        this.knightBlood.setPercentage(100);
        this.knightBlood.setPosition3D(cc.math.vec3(this.knightPng.x-1, this.knightPng.y-offset, 4));
        this.knightBlood.setScale(scale);
        this.addChild(this.knightBlood, 4);

        this.knightBloodClone = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.knightBloodClone.setColor(cc.color(255, 83, 23));
        this.knightBloodClone.setType(cc.ProgressTimer.TYPE_BAR);
        this.knightBloodClone.setBarChangeRate(cc.p(1, 0));
        this.knightBloodClone.setMidpoint(cc.p(0, 0));
        this.knightBloodClone.setPercentage(100);
        this.knightBloodClone.setPosition3D(cc.math.vec3(this.knightPng.x-1, this.knightPng.y-offset, 3));
        this.knightBloodClone.setScale(scale);
        this.addChild(this.knightBloodClone, 3);

        this.archerBlood = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.archerBlood.setColor(cc.color(149, 254, 26));
        this.archerBlood.setType(cc.ProgressTimer.TYPE_BAR);
        this.archerBlood.setMidpoint(cc.p(0, 0));
        this.archerBlood.setBarChangeRate(cc.p(1, 0));
        this.archerBlood.setPercentage(100);
        this.archerBlood.setPosition3D(cc.math.vec3(this.archerPng.x-1,this.archerPng.y-offset, 4));
        this.archerBlood.setScale(scale);
        this.addChild(this.archerBlood, 4);

        this.archerBloodClone = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.archerBloodClone.setColor(cc.color(255,83,23));
        this.archerBloodClone.setType(cc.ProgressTimer.TYPE_BAR);
        this.archerBloodClone.setBarChangeRate(cc.p(1,0));
        this.archerBloodClone.setMidpoint(cc.p(0,0));
        this.archerBloodClone.setPercentage(100);
        this.archerBloodClone.setPosition3D(cc.math.vec3(this.archerPng.getPositionX()-1, this.archerPng.getPositionY()-offset,3));
        this.archerBloodClone.setScale(scale);
        this.addChild(this.archerBloodClone,3);

        this.mageBlood = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.mageBlood.setColor(cc.color(149, 254, 26));
        this.mageBlood.setType(cc.ProgressTimer.TYPE_BAR);
        this.mageBlood.setMidpoint(cc.p(0, 0));
        this.mageBlood.setBarChangeRate(cc.p(1, 0));
        this.mageBlood.setPercentage(100);
        this.mageBlood.setPosition3D(cc.math.vec3(this.magePng.x-1, this.magePng.y-offset, 4));
        this.mageBlood.setScale(scale);
        this.addChild(this.mageBlood, 4);

        this.mageBloodClone = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.mageBloodClone.setColor(cc.color(255, 83, 23));
        this.mageBloodClone.setType(cc.ProgressTimer.TYPE_BAR);
        this.mageBloodClone.setBarChangeRate(cc.p(1, 0));
        this.mageBloodClone.setMidpoint(cc.p(0, 0));
        this.mageBloodClone.setPercentage(100);
        this.mageBloodClone.setPosition3D(cc.math.vec3(this.magePng.x-1, this.magePng.y-offset, 3));
        this.mageBloodClone.setScale(scale);
        this.addChild(this.mageBloodClone, 3);
    },

    angrybarInit:function(){
        var offset = 53, fullAngerStarOffset = 70, yellow = cc.color(255, 255, 0), grey = cc.color(113, 103, 76);
        var action = cc.rotateBy(1, cc.math.vec3(0, 0, 360)).repeatForever();

        this.knightAngry = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.knightAngry.setColor(yellow);
        this.knightAngry.setType(cc.ProgressTimer.TYPE_BAR);
        this.knightAngry.setBarChangeRate(cc.p(1, 0));
        this.knightAngry.setMidpoint(cc.p(0, 0));
        this.knightAngry.setPercentage(0);
        this.knightAngry.setPosition3D(cc.math.vec3(this.knightPng.x-1, this.knightPng.y-offset, 4));
        this.knightAngry.setScale(0.7);
        this.addChild(this.knightAngry, 4);

        this.knightAngryClone = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.knightAngryClone.setColor(grey);
        this.knightAngryClone.setType(cc.ProgressTimer.TYPE_BAR);
        this.knightAngryClone.setBarChangeRate(cc.p(1, 0));
        this.knightAngryClone.setMidpoint(cc.p(0, 0));
        this.knightAngryClone.setPercentage(100);
        this.knightAngryClone.setPosition3D(cc.math.vec3(this.knightPng.x-1, this.knightPng.y-offset, 3));
        this.knightAngryClone.setScaleX(0.7);
        this.knightAngryClone.setScaleY(0.75);
        this.addChild(this.knightAngryClone, 3);

        this.knightAngryFullSignal = new cc.Sprite("#specialLight.png");
        this.knightAngryFullSignal.setPosition3D(cc.math.vec3(this.knightPng.x, this.knightPng.y+fullAngerStarOffset, 4));
        this.knightAngryFullSignal.runAction(action);
        this.knightAngryFullSignal.setScale(1);
        this.knightAngryFullSignal.setVisible(false);
        this.addChild(this.knightAngryFullSignal, 4);

        this.archerAngry = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.archerAngry.setColor(yellow);
        this.archerAngry.setType(cc.ProgressTimer.TYPE_BAR);
        this.archerAngry.setMidpoint(cc.p(0, 0));
        this.archerAngry.setBarChangeRate(cc.p(1, 0));
        this.archerAngry.setPercentage(0);
        this.archerAngry.setPosition3D(cc.math.vec3(this.archerPng.x-1, this.archerPng.y-offset, 4));
        this.archerAngry.setScale(0.7);
        this.addChild(this.archerAngry, 4);

        this.archerAngryClone = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.archerAngryClone.setColor(grey);
        this.archerAngryClone.setType(cc.ProgressTimer.TYPE_BAR);
        this.archerAngryClone.setBarChangeRate(cc.p(1, 0));
        this.archerAngryClone.setMidpoint(cc.p(0, 0));
        this.archerAngryClone.setPercentage(100);
        this.archerAngryClone.setPosition3D(cc.math.vec3(this.archerPng.x-1, this.archerPng.y-offset,3));
        this.archerAngryClone.setScaleX(0.7);
        this.archerAngryClone.setScaleY(0.75);
        this.addChild(this.archerAngryClone, 3);

        this.archerAngryFullSignal = new cc.Sprite("#specialLight.png");
        this.archerAngryFullSignal.setPosition3D(cc.math.vec3(this.archerPng.x, this.archerPng.y+fullAngerStarOffset, 4));
        this.archerAngryFullSignal.runAction(action.clone());
        this.archerAngryFullSignal.setScale(1);
        this.archerAngryFullSignal.setVisible(false);
        this.addChild(this.archerAngryFullSignal);

        this.mageAngry = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.mageAngry.setColor(yellow);
        this.mageAngry.setType(cc.ProgressTimer.TYPE_BAR);
        this.mageAngry.setMidpoint(cc.p(0, 0));
        this.mageAngry.setBarChangeRate(cc.p(1, 0));
        this.mageAngry.setPercentage(0);
        this.mageAngry.setPosition3D(cc.math.vec3(this.magePng.x-1, this.magePng.y-offset, 4));
        this.mageAngry.setScale(0.7);
        this.addChild(this.mageAngry, 4);

        this.mageAngryClone = new cc.ProgressTimer(new cc.Sprite("#UI-1136-640_36_clone.png"));
        this.mageAngryClone.setColor(grey);
        this.mageAngryClone.setType(cc.ProgressTimer.TYPE_BAR);
        this.mageAngryClone.setBarChangeRate(cc.p(1, 0));
        this.mageAngryClone.setMidpoint(cc.p(0, 0));
        this.mageAngryClone.setPercentage(100);
        this.mageAngryClone.setPosition3D(cc.math.vec3(this.magePng.x-1, this.magePng.y-offset, 3));
        this.mageAngryClone.setScaleX(0.7);
        this.mageAngryClone.setScaleY(0.75);
        this.addChild(this.mageAngryClone, 3);

        this.mageAngryFullSignal = new cc.Sprite("#specialLight.png");
        this.mageAngryFullSignal.setPosition3D(cc.math.vec3(this.magePng.x, this.magePng.y+fullAngerStarOffset, 4));
        this.addChild(this.mageAngryFullSignal, 4);
        this.mageAngryFullSignal.runAction(action.clone());
        this.mageAngryFullSignal.setScale(1);
        this.mageAngryFullSignal.setVisible(false);
    },

    touchButtonInit:function(){
        var setBtn = new cc.Sprite("#UI-1136-640_06.png");
        setBtn.setPosition3D(cc.math.vec3(1093/1136*cc.winSize.width, 591/640*cc.winSize.height, 3));
        setBtn.setScale(0.8);
        this.addChild(setBtn, 3);

        var chest = new cc.Sprite("#chest.png");
        chest.setPosition3D(cc.math.vec3(861/1136*cc.winSize.width, 595/640*cc.winSize.height, 3));
        chest.setScale(0.8);
        this.addChild(chest, 3);

        var coin = new cc.Sprite("#coins.png");
        coin.setPosition3D(cc.math.vec3(1028.49/1136*cc.winSize.width, 593/640*cc.winSize.height, 3));
        coin.setScale(0.8);
        this.addChild(coin, 3);

        var chestAmout = new cc.Sprite("#UI-1.png");
        chestAmout.setPosition3D(cc.math.vec3(785/1136*cc.winSize.width, 590/640*cc.winSize.height, 2));
        chestAmout.setScaleX(0.8);
        chestAmout.setScaleY(0.7);
        this.addChild(chestAmout, 2);

        var coinAmount = new cc.Sprite("#UI-1.png");
        coinAmount.setPosition3D(cc.math.vec3(957/1136*cc.winSize.width, 590/640*cc.winSize.height, 2));
        coinAmount.setScaleX(0.8);
        coinAmount.setScaleY(0.7);
        this.addChild(coinAmount, 2);
    },

    timeInit:function(){
        var ttfconfig = {outlineSize:1, fontSize:25, glyphs:0, fontFilePath:"fonts/britanic bold.ttf"};
        var label = cc.Label.createWithTTF(ttfconfig, "00:00");
        label.setAnchorPoint(0, 0);
        label.setPosition3D(cc.math.vec3(cc.winSize.width*0.02, cc.winSize.height*0.915, 2));
        label.enableOutline(cc.color(0, 0, 0, 255));
        this._tmlabel = label;
        this.addChild(label, 5);

        var self = this, time = 0;
        this.schedule(function(){
            time++;
            if(time >= 3600)
                time = 0;

            var min = Math.floor(time/60);
            var sec = time%60;
            if(min < 10)
                min = "0" + min;
            if(sec < 10)
                sec = "0" + sec;
            label.setString(min+":"+sec);
        }, 1);
    },

    heroDead:function(hero){
        if(hero._name == "Knight"){
            cc.GreyShader.setGreyShader(this.knightPng)
            cc.GreyShader.setGreyShader(this.knightPngFrame)    
            this.knightAngryFullSignal.setVisible(false)   
            this.knightAngryClone.setVisible(false)
        }else if(hero._name == "Mage"){
            cc.GreyShader.setGreyShader(this.magePng)
            cc.GreyShader.setGreyShader(this.magePngFrame)    
            this.mageAngryFullSignal.setVisible(false)   
            this.mageAngryClone.setVisible(false)
        }else{
            cc.GreyShader.setGreyShader(this.archerPng)
            cc.GreyShader.setGreyShader(this.archerPngFrame)    
            this.archerAngryFullSignal.setVisible(false)   
            this.archerAngryClone.setVisible(false)
        }
    },

    showVictoryUI:function(){
        var layer = new cc.LayerColor(cc.color(10, 10, 10, 150));
        layer.ignoreAnchorPointForPosition(false);
        layer.setPosition3D(cc.math.vec3(cc.winSize.width*0.5, cc.winSize.height*0.5, 0));
        var victory = new cc.Sprite("#victory.png");
        victory.setPosition3D(cc.math.vec3(cc.winSize.width*0.5, cc.winSize.height*0.5, 3));
        victory.setScale(0.1);
        victory.setGlobalZOrder(UIZorder);
        layer.addChild(victory, 1);
        this.addChild(layer);
        victory.runAction(cc.scaleTo(1.5, 1).easing(cc.easeElasticOut()));

        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ONE_BY_ONE,
            onTouchBegan:function(){return true;},
            onTouchEnded:function(){
                cc.audioEngine.stopMusic();
                cc.audioEngine.stopAllEffects();

                cc.director.replaceScene(new MainMenuScene);
                currentLayer = null;
            }
        }, this);
    }
});