var MainMenuLayer = cc.Layer.extend({
    ctor:function(){
        this._super();
    }
});

var MainMenuScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new MainMenuLayer();
        this.addChild(layer);
    }
});