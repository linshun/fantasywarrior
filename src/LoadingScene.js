var LoadingLayer = cc.Layer.extend({
    _loading:[],
    _slime:null,
    _slimeOriginX:0,
    _slimeOriginY:0,
    _loadingbar:null,
    _num:0,
    _totalResource:0,


    ctor:function () {
        this._super();
        this.init();
    },

    init:function(){
        this._totalResource = spriteFrameRes.length + Object.keys(particleRes).length;
        var size = cc.winSize;
        //add background
        var background = new cc.Sprite("loadingscene/bg.jpg");
        background.setPosition(size.width / 2, size.height / 2);
        background.setScale(1.5);
        background.setVertexZ(-250);
        background.setGlobalZOrder(-1);
        this.addChild(background);

        //add loadingbar
        var loadingbar = new ccui.LoadingBar("loadingscene/sliderProgress.png");
        loadingbar.setDirection(ccui.LoadingBar.TYPE_LEFT);
        loadingbar.setPosition(size.width / 2, size.height * 0.2);
        loadingbar.setScale(3, 2);
        loadingbar.setColor(cc.color(0, 0, 0));
        loadingbar.setOpacity(70);
        loadingbar.setPercent(0);
        this._loadingbarSize = loadingbar.getContentSize().width*3;
        this.addChild(loadingbar);

        this._loadingbar = loadingbar;

        //add label
        this.addLoadingText();

        //add slime
        this.slimeAction();

        this.scheduleUpdate();

        return true;
    },

    update:function(dt){
        this._num++;
        if(this._num > this._totalResource){
            this.unscheduleUpdate();
            //replace scene
            cc.director.replaceScene(new MainMenuScene());
            return;
        }

        this._loadingbar.setPercent(this._num/this._totalResource * 100);

        //loading text action
        var loadingAction = cc.jumpBy(0.016, cc.p(0, 0), 50, 1);
        var loadingIndex = this._num%this._loading.length;
        this._loading[loadingIndex].runAction(loadingAction);

        //slime action
        this._slime.runAction(cc.moveTo(dt, cc.p(this._slimeOriginX+this._loadingbarSize*this._loadingbar.getPercent()/100, this._slimeOriginY)))

        //loading resource
        if(this._num < spriteFrameRes.length)
            this.cacheTexture(this._num);
        else
            this.cacheParticle(this._num - spriteFrameRes.length);
    },

    addLoadingText:function(){
        var loading = ['l', 'o', 'a', 'd', 'i', 'n', 'g'];
        var ttfconfig = {outlineSize:5, fontSize:55, glyphs:0, fontFilePath:"chooseRole/actor_param.ttf"};
        var size = cc.winSize;
        for(var i = 0; i < loading.length; ++i){
            var l = cc.Label.createWithTTF(ttfconfig, loading[i]);
            l.enableOutline(cc.color(104, 151, 161));
            l.setPosition(size.width * (0.13 + 0.1 * (i + 1)), size.height * 0.6);
            this.addChild(l);
            this._loading.push(l);
        }
    },

    slimeAction:function(){
        var slime = new Slime();
        // slime.setAIEnabled(false);
        slime.setRotation3D(cc.vec3(0, 30, 0));
        this.addChild(slime, 33);
        this._slimeOriginX = cc.winSize.width * 0.2;
        this._slimeOriginY = cc.winSize.height * 0.3;
        slime.setPosition(this._slimeOriginX, this._slimeOriginY);
        this._slime = slime;
        
        var dur = 0.6, bsc = 27;
        slime.runAction(cc.spawn(
            cc.sequence(cc.delayTime(dur/8), cc.JumpBy3D.create(dur*7/8, cc.vec3(0, 0, 0), 30, 1)),

            cc.sequence(
                cc.scaleTo(dur/8, bsc*1.4, bsc*1.4, bsc*0.75).easing(cc.easeSineOut()),
                cc.scaleTo(dur/8, bsc*0.85, bsc*0.85, bsc*1.3).easing(cc.easeSineOut()),
                cc.scaleTo(dur/8, bsc*1.2, bsc*1.2, bsc*0.9).easing(cc.easeSineOut()),
                cc.scaleTo(dur/8, bsc*0.95, bsc*0.95, bsc*1.1).easing(cc.easeSineOut()),
                cc.scaleTo(dur*4/8, bsc, bsc, bsc).easing(cc.easeSineOut())
            )
        ).repeatForever());
    },

    cacheParticle:function(index){
        var keys = Object.keys(particleRes);
        ParticleManager.addPlistData(keys[index], particleRes[keys[index]]);
    },

    cacheTexture:function(index){
        cc.spriteFrameCache.addSpriteFrames(spriteFrameRes[index]);
    }
});

var LoadingScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new LoadingLayer();
        this.addChild(layer);
    }
});
