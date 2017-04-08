(function(){

  var BOX_SIZE = 50

  function box(x, y, size){
    ctx.rect(x,y,size,size);
    ctx.fillStyle = '#7B94B4';
    ctx.fillRect(x,y,size,size);

    ctx.stroke();
  }

  function redbox(x, y, size){
    ctx.rect(x,y,size,size);
    ctx.fillStyle = '#A31919';
    ctx.fillRect(x,y,size,size);

    ctx.stroke();
  }

  var rnd = (s) => s * (Math.floor((Math.random() * 10) + 1));

  function make_map(data, stride, step){

    var posx = step, posy = step;
    var grid = [];


    for(var i =0; i<data.length; i++){
        var tile = data[i]
        var margin = BOX_SIZE + step;
        var type = 'empty';

        if((i % stride) === 0 && i !== 0) {
          posx  = step;
          posy += margin;
        }

        if(tile === 'X'){
          setTimeout(
            function(x, y){
              return ()=>{ box(x, y, BOX_SIZE); }
            }(posx, posy),
           rnd(50));
           type = 'block';
        }

        if(tile === '@')type = 'marker';

        grid.push({x:posx, y: posy, type:type});

        posx += margin;
    }

    return grid
  }

  function Grid(grid, stride){

    this.get = (x,y) => {
      return grid[x + (y * stride)];
    }
  }

  function isUndefined(obj){ return typeof obj === 'undefined'}


  var new_parasite = function() {
    var infected = [];
    var incrementalAnim = 100;

    var discardThisOne = (blk) => {
      if(isUndefined(blk)) return true;
      if( blk.type  === 'block' ) return true;

      var ret = infected.find((obj)=>(blk.x === obj.x && blk.y === obj.y));
    //  debugger;
      if(!isUndefined(ret)) return true;

      return false;
    }

    return function search(loc, x, y) {
      var blk = loc.get(x,y);
      if(discardThisOne(blk)) return;

      setTimeout(function(){
        return function(x,y){redbox(x, y, BOX_SIZE)}(blk.x, blk.y)
      }, incrementalAnim += 200);
      infected.push(blk);
//debugger;
      //check up
      search(loc, x, y+1);

      //check down
      search(loc, x, y-1);

      //check left
      search(loc, x-1, y);

      //check right
      search(loc, x+1, y);

    };
  }();

  function updown(loc, x, y, vec){
    var blk  = loc.get(x,y);
    if(isUndefined(blk)) return;

    if( blk.type !== 'block' ) {
      leftright(loc, x, y, -1);
      leftright(loc, x, y,  1);
      updown(loc, x, (y + vec), vec);
    }

    return;
  }

  function leftright(loc, x, y, vec){
    var blk  = loc.get(x,y);
    if(isUndefined(blk)) return;

    if( blk.type !== 'block' ) {
      redbox(blk.x, blk.y, BOX_SIZE);
      leftright( loc, (x + vec), y, vec );
    }

    return;
  }

  function findMarker(map,step){

    for(var i=0; i<map.length; i++){

      if(map[i] === '@'){
        var y = Math.floor(i/step);
        var x = i - (y*step);
        return {x:x, y:y}
      }
    }
  }


  var ctx = document.getElementById("myCanvas").getContext("2d");

  var map ='XXXXXXXXXX'
      map+='X00XXX000X'
      map+='X000000X0X'
      map+='X0XXXX0X0X'
      map+='X00X0X0X0X'
      map+='XX0X0X0X0X'
      map+='X00X@0000X'
      map+='XXXXXXXXXX'

  var _grid = make_map(map, 10, 5);
  var _marker = findMarker(map, 10);
  var loc = new Grid(_grid, 10);

  var x = _marker.x, y = _marker.y;

  new_parasite(loc, x, y);
  //updown(loc, x, y, 1)
  //updown(loc, x, y, -1);
  console.log(loc.get(5,5));




})();
