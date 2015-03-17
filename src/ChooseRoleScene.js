var ChooseRoleLayer = (function(){

    var TAG_knight = 2, TAG_archer = 1, TAG_mage = 3;

    return  cc.Layer.extend({
        ctor:function(){
            this._super();
            cc.Texture2D.setDefaultAlphaPixelFormat(0);// AUTO
            this.addBackground();
            this.addHeroes();
            this.addButton();
            this.addBag();
            cc.audioEngine.playMusic(BGM_RES.CHOOSEROLESCENEBGM, true);
        },

        addBackground:function(){
            //holder for background
            var node3d = new cc.Sprite3D();

            var bg = new cc.Sprite("chooseRole/cr_bk.jpg");
            bg.setAnchorPoint(0.5, 0.5);
            bg.setPosition(cc.winSize.width/2, cc.winSize.height/2);
            bg.setVertexZ(-250);
            bg.setScale(1.5);
            bg.setGlobalZOrder(-1);
            node3d.addChild(bg);
            this.addChild(node3d);
        },

        addHeroes:function(){
            var knight = new Knight();
            var knight.setTag(TAG_knight);
            knight.setRotation3D(rtt[2]);
            knight.setPosition3D(pos[2]);
            // knight.setAIEnabled(false);
            knight.setScale(1.3);
            this.addChild(knight);
        },

        addButton:function(){

        },

        addBag:function(){

        }
    });
})();

var ChooseRoleScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new ChooseRoleLayer();
        this.addChild(layer);
    }
});