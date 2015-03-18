var ChooseRoleLayer = (function(){

    var TAG_knight = 2, TAG_archer = 1, TAG_mage = 3,
        TAG_bag = 10, TAG_weapon = 11, TAG_armour = 12, TAG_helmet = 13;
    // var rtt = [cc.vec3(-90, -60, 0), cc.vec3(0, 30, 0), cc.vec3(-90, -60, 0)];
    var visibleSize = cc.director.getVisibleSize();
    var pos = [cc.vec3(visibleSize.width*0.14, visibleSize.height*0.35, -180),
               cc.vec3(visibleSize.width*0.34, visibleSize.height*0.25, -40),
               cc.vec3(visibleSize.width*0.5, visibleSize.height*0.35, -180)];

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
            knight.setTag(TAG_knight);
            knight.setPosition3D(pos[1]);
            knight.setRotation3D(cc.vec3(0, 30, 0));
            // knight.setAIEnabled(false);
            this.addChild(knight);

            var archer = new Archer();
            archer.setTag(TAG_archer);
            archer.setPosition3D(pos[0]);
            archer.setRotation3D(cc.vec3(0, 30, 0));
            // archer.setAIEnabled(false);
            this.addChild(archer);

            var mage = new Mage();
            mage.setTag(TAG_mage);
            mage.setPosition3D(pos[2]);
            // mage.setAIEnabled(false);
            this.addChild(mage);
            this.schedule(this._hero_rotate, 0);
        },

        _hero_rotate:function(dt){

        },

        addButton:function(){
            var button = new ccui.Button("button1.png", "", "", ccui.Widget.PLIST_TEXTURE);
            button.setNormalizedPosition(cc.p(0.34, 0.13));
            this.addChild(button);
            button.addTouchEventListener(function(sender, type){
                cc.log("battle");
            }, this);
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