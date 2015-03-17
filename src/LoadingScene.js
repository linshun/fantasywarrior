var particleRes = {
    "iceTrail" : "FX/iceTrail.plist",
    "magic" : "FX/magic.plist",
    "pixi" : "FX/pixi.plist",
    "puffRing" : "FX/puffRing.plist",
    "puffRing2" : "FX/puffRing2.plist",
    "walkpuff" : "FX/walkingPuff.plist"
}

var spriteFrameRes = [
    "FX/FX.plist",
    "chooseRole/chooserole.plist",
    "battlefieldUI/battleFieldUI.plist",
    "mainmenuscene/mainmenuscene.plist",
];

var LoadingLayer = cc.Layer.extend({
    _loading:[],

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
        slime.setRotation3D(cc.vec3(-90, -90, 0));
        this.addChild(slime, 33);
        slime.setPosition(cc.winSize.width/2, cc.winSize.height/2 - 100);
        //todo
    }
});

var LoadingScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new LoadingLayer();
        this.addChild(layer);
    }
});
