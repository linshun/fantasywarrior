var BattleLayer = cc.Layer.extend({
    uiLayer:null,

    ctor:function(){
        this._super();
        this.setCascadeColorEnabled(true);

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            onTouchBegan:this.onTouchBegan.bind(this),
            onTouchMoved:this.onTouchMoved.bind(this),
            onTouchEnded:this.onTouchEnded.bind(this)
        }, this);

        //create background
        var spriteBg = new cc.Sprite3D("model/scene/changing.c3b");
        this.addChild(spriteBg);
        spriteBg.setScale(2.65);
        spriteBg.setPosition3D(cc.vec3(-2300, -1000, 0));
        spriteBg.setRotation3D(cc.vec3(90, 0, 0));
        spriteBg.setGlobalZOrder(-10);

        var water = cc.Water.create("shader3D/water.png", "shader3D/wave1.jpg", "shader3D/18.jpg", cc.size(5500, 400), 0.77, 0.3797, 1.2);
        this.addChild(water);
        water.setPosition3D(cc.vec3(-3500, -580, -110));
        water.setAnchorPoint(0, 0);
        water.setGlobalZOrder(-10);

        //init ui layer
        var uiLayer = new BattleFieldUI();
        uiLayer.setVertexZ(-cc.director.getZEye()/4);
        uiLayer.setScale(0.25);
        uiLayer.ignoreAnchorPointForPosition(false);
        uiLayer.setGlobalZOrder(3000);
        this.uiLayer = uiLayer;

        //set camera
    },

    onTouchBegan:function(touch, event){
        return true;
    },

    onTouchMoved:function(touch, event){

    },

    onTouchEnded:function(touch, event){

    }
});

var BattleScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        cc.Texture2D.setDefaultAlphaPixelFormat(4);//RGB565
        var layer = new BattleLayer();
        this.addChild(layer);
    }
});