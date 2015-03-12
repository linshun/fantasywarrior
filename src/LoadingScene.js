var LoadingLayer = cc.Layer.extend({
    ctor:function () {
        this._super();
        this.init();
    },

    init:function(){
        var size = cc.winSize;
        //add background
        var background = new cc.Sprite("loadingscene/bg.jpg");
        background.setPosition(size.width / 2, size.height / 2);
        background.setScale(1.5);
        this.addChild(background);

        //add loadingbar
        var loadingbar = new ccui.LoadingBar("loadingscene/sliderProgress.png");
        loadingbar.setDirection(ccui.LoadingBar.TYPE_LEFT);
        loadingbar.setPosition(size.width / 2, size.height * 0.2);
        loadingbar.setScale(3, 2);
        loadingbar.setColor(cc.color(0, 0, 0));
        loadingbar.setOpacity(70);
        loadingbar.setPercent(0);
        this.addChild(loadingbar);

        //add label
        this.addLoadingText();

        //add slime
        this.slimeAction();

        this.scheduleUpdate();
        return true;
    },

    update:function(dt){

    },

    addLoadingText:function(){

    },

    slimeAction:function(){

    }
});

var LoadingScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new LoadingLayer();
        this.addChild(layer);
    }
});
