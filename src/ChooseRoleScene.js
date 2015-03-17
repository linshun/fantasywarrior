var ChooseRoleLayer = (function(){

    var TAG_knight = 2, TAG_archer = 1, TAG_mage = 3;
    var rtt = [cc.vec3(-90, -60, 0), cc.vec3(-90, -70, 0), cc.vec3(-90, -60, 0)];
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
            cc.log(Knight);
            var knight = new Knight();
            knight.setTag(TAG_knight);
            knight.setRotation3D(rtt[2]);
            knight.setPosition3D(pos[2]);
            // knight.setAIEnabled(false);
            // knight.setScale(1.3);
            this.addChild(knight);

            var archer = new Archer();
            archer.setTag(TAG_archer);
            archer.setRotation3D(rtt[1]);
            archer.setPosition3D(pos[1]);
            // archer.setAIEnabled(false);
            this.addChild(archer);

            var mage = new Mage();
            mage.setTag(TAG_mage);
            mage.setRotation3D(rtt[3]);
            mage.setPosition3D(pos[3]);
            // mage.setAIEnabled(false);
            mage.setScale(1.3);
            this.addChild(mage);
            this.schedule(this._hero_rotate, 0);
        },

        _hero_rotate:function(dt){

        },

        addButton:function(){
            var button = new ccui.Button("button1.png", "button2.png", "", ccui.Widget.PLIST_TEXTURE);
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