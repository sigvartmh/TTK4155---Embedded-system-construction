var app = require('http').createServer(handler)
  , fs = require('fs')
  , io = require('socket.io').listen(app)

app.listen(80);

function handler (req, res) {
  fs.readFile(__dirname + '/game.html',
  function (err, data) {
    if (err) {
      res.writeHead(500);
      return res.end('Error loading game.html');
    }

    res.writeHead(200);
    res.end(data);
  });
}

io.sockets.on('connection', function (socket) {
  socket.emit('news', { hello: 'world' });
  
  socket.on('my other event', function (data) {
    console.log(data);
  });
  
  socket.on('position',function(data){
    console.log(data);
    console.log('position detected')
  });

  socket.on('change', function(){
    console.log('Emitting new pos');
    var pos = Array(0);
    var string;
    for(var i = 0; i<351;i++){
      pos[0] = i;
      string = pos.join('') + 'px';
      socket.emit('newpos', string);
    }
  });
});

