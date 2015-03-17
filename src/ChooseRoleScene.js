var ChooseRoleLayer = cc.Layer.extend({
    ctor:function(){
        this._super();
    }
});

var ChooseRoleScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new ChooseRoleLayer();
        this.addChild(layer);
    }
});