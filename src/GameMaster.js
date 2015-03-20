(function(_G){
    var stage = 0;
    var logicFrq = 1.0; //tick per second
    var battleSiteX = [-2800,-1800,-800];
    var monsterCount = {dragon:1, slime:7, piglet:2, rat:0}

    var frontDistanceWithHeroX = 600
    var backwardDistanceWithHeroX = 800
    var distanceWithHeroX = 150
    var distanceWithHeroY = 150

    var GameMaster = function(layer){
        this._totaltime = 0;
        this._layer = layer;
        _G.HeroManager = [];
        _G.MonsterManager = [];

        this.init();
    };
    _G.GameMaster = GameMaster;

    GameMaster.prototype = {
        init:function(){
            this.addHeroes();
            this.addMonsters();

            for(var i=0; i < 4; ++i)
                this.randomshowMonster(true);

            stage=1;
        },

        addHeroes:function(){
            var knight = new Knight();
            knight.setPosition(battleSiteX[0], 270);
            knight.setRotation3D(cc.vec3(90, 0, -90));
            this._layer.addChild(knight);
            knight.idleMode();
            HeroManager.push(knight);

            var mage = new Mage();
            mage.setPosition(battleSiteX[0], 400);
            mage.setRotation3D(cc.vec3(90, 0, -90));
            this._layer.addChild(mage);
            mage.idleMode();
            HeroManager.push(mage);

            var archer = new Archer();
            archer.setPosition(battleSiteX[0], 150);
            archer.setRotation3D(cc.vec3(90, 0, -90));
            this._layer.addChild(archer);
            archer.idleMode();
            HeroManager.push(archer);
        },

        addMonsters:function(){
            this.addDragon();
            this.addSlime();
            // this.addPiglet();
            // this.addRat();
        },

        addDragon:function(){
            for(var i = 0; i < monsterCount.dragon; ++i){
                var dragon = new Dragon();
                dragon.setVisible(false);
                // dragon.setAIEnabled(false);
                this._layer.addChild(dragon);
                cc.pool.putInPool(dragon);
            }
        },

        addSlime:function(){
            for (var i = 0; i < monsterCount.slime; ++i) {
                var slime = new Slime();
                slime.setVisible(false);
                this._layer.addChild(slime);
                cc.pool.putInPool(slime);
            };
        },

        addPiglet:function(){
            for(var i = 0; i < monsterCount.piglet; ++i){
                var pig = new Piglet();
                pig.setVisible(false);
                this._layer.addChild(pig);
                cc.pool.putInPool(pig);
            }
        },

        addRat:function(){
            for(var i = 0; i < monsterCount.rat; ++i){
                var rat = new Rat();
                rat.setVisible(false);
                this._layer.addChild(rat);
                cc.pool.putInPool(rat);
            }
        },

        randomshowMonster:function(isFront){
            var rand = Math.random();

            rand = 0.9;
            
            if(rand < 0.15){
                if(cc.pool.hasObject(Dragon))
                    this.showDragon(isFront);
                else
                    this.randomshowMonster(isFront);
            }else if(rand < 0.3){
                if(cc.pool.hasObject(Rat))
                    this.showRat(isFront);
                else
                    this.randomshowMonster(isFront);
            }else if(rand < 0.6){
                if(cc.pool.hasObject(Piglet))
                    this.showPiglet(isFront);
                else
                    this.randomshowMonster(isFront);
            }else{
                this.showSlime(isFront);
            }
        },

        showDragon:function(isFront){
            var dragon = cc.pool.getFromPool(Dragon);
            cc.log("show dragon" + dragon);

            dragon.reset();
            //todo
        },

        showPiglet:function(isFront){
            var pig = cc.pool.getFromPool(Piglet);
            cc.log("show piglet" + piglet);
        },

        showRat:function(isFront){
            var rat = cc.pool.getFromPool(Rat);
            cc.log("show rat" + rat);
        },

        showSlime:function(isFront){
            var slime = cc.pool.getFromPool(Slime);
            cc.log("show slime" + slime);
            slime.reset();
            slime._goRight = false;
            this.jumpInto(slime, isFront);
            MonsterManager.push(slime);
        },

        jumpInto:function(obj, isFront){
            var appearPos = this.getFocusPointOfHeros();
            var random = 2*Math.random()-1;
            if(isFront)
                appearPos.x += frontDistanceWithHeroX + random*distanceWithHeroX;
            else
                appearPos.x -= frontDistanceWithHeroX + random*distanceWithHeroX;

            appearPos.y += 1500;
            obj.setPosition(appearPos);
            obj._myPos = appearPos;

            if(stage == 0){
                obj.runAction(cc.sequence(
                        cc.delayTime(Math.random()),
                        cc.callFunc(function(){obj.setVisible(true);}),
                        cc.JumpBy3D.create(0.5, cc.vec3(-200*(Math.random()*0.6+0.7), -1700 + 300*Math.random(), 0),150, 1),
                        cc.callFunc(function(){cc.log(obj.y);obj.setAIEnabled(true);})
                    ));
                obj.setFacing(135);
            }else{
                //todo
            }
        },

        update:function(dt){
            this._totaltime += dt;
            if(this._totaltime > logicFrq){
                this._totaltime -= logicFrq;
                this.logicUpdate();
            }
        },

        logicUpdate:function(){

        },

        getFocusPointOfHeros:function(){
            var ptFocus = cc.p(0, 0);
            for(var i = 0; i < HeroManager.length; ++i){
                ptFocus.x += HeroManager[i].x;
                ptFocus.y += HeroManager[i].y;
            }
            ptFocus.x /= HeroManager.length;
            ptFocus.y /= HeroManager.length;
            return ptFocus;
        }
    };

})(this);