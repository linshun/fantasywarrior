(function(_G){
    var stage = 0;
    var battleSiteX = [-2800,-1800,-800];

    var GameMaster = function(layer){
        this._totaltime = 0;
        this._logicFrq = 1.0;
        this._layer = layer;
        this.heroes = [];
        this.init();
    };
    _G.GameMaster = GameMaster;

    GameMaster.prototype = {
        init:function(){
            this.addHeroes();
            this.addMonsters();

            for(var i=0; i < 3; ++i)
                this.randomshowMonster();

            stage=1;
        },

        addHeroes:function(){
            var knight = new Knight();
            knight.setPosition(battleSiteX[0], 270);
            knight.setRotation3D(cc.vec3(90, 0, -90));
            this._layer.addChild(knight);
            knight.idleMode();
            this.heroes.push(knight);

            var mage = new Mage();
            mage.setPosition(battleSiteX[0], 400);
            mage.setRotation3D(cc.vec3(90, 0, -90));
            this._layer.addChild(mage);
            mage.idleMode();
            this.heroes.push(mage);

            var archer = new Archer();
            archer.setPosition(battleSiteX[0], 150);
            archer.setRotation3D(cc.vec3(90, 0, -90));
            this._layer.addChild(archer);
            archer.idleMode();
            this.heroes.push(archer);
        },

        addMonsters:function(){

        },

        randomshowMonster:function(){

        },

        update:function(dt){

        },

        getFocusPointOfHeros:function(){
            var ptFocus = cc.p(0, 0);
            for(var i = 0; i < this.heroes.length; ++i){
                ptFocus.x += this.heroes[i].x;
                ptFocus.y += this.heroes[i].y;
            }
            ptFocus.x /= this.heroes.length;
            ptFocus.y /= this.heroes.length;
            return ptFocus;
        }
    };

})(this);