var BattleFieldUI = cc.Layer.extend({
    ctor:function(){
        this._super();
        this.avatarInit();
        this.bloodbarInit();
        this.angrybarInit();
        this.touchButtonInit();
        this.timeInit();

        cc.audioEngine.playMusic(BGM_RES.BATTLEFIELDBGM);
    },

    avatarInit:function(){
        var offset = 8, scale = 0.7;

        this.magePng = new cc.Sprite("#UI-1136-640_18.png");
        this.magePng.setPosition3D(cc.vec3(1070/1136*cc.winSize.width, 70/640*cc.winSize.height, 3));
        this.magePng.setScale(scale);
        this.addChild(this.magePng, 2);
        this.magePngFrame = new cc.Sprite("#UI-2.png");
        this.magePngFrame.setScale(scale);
        this.magePngFrame.setPosition3D(cc.vec3(this.magePng.x + 1, this.magePng.y - offset, 1));
        this.addChild(this.magePngFrame);
    },

    bloodbarInit:function(){

    },

    angrybarInit:function(){

    },

    touchButtonInit:function(){

    },

    timeInit:function(){

    }
});