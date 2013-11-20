var app = require('http').createServer(handler)
  , fs = require('fs')
  , io = require('socket.io').listen(app)
  , serial = require('serialport')
  , SerialPort = serial.SerialPort; // localize object constructor

var sp = new SerialPort("COM2", { 
	parser: serial.parsers.readline("\n"),
	baudrate: 19200,
	databits: 8,
	stopbits: 1,
	parity: 'none'
});

app.listen(123,'127.0.0.1');

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
    
sp.on("open", function () {
    console.log('open');
    io.sockets.on('connection', function (socket) {
        socket.emit('news', { hello: 'world' });
        socket.on('my other event', function (data) {
            console.log(data);
        });
    
    socket.on('update', function(){
        //console.log('update: received');
        sp.write('\n');
    });
  
    socket.on('position',function(data){
        console.log(data);
        console.log('position detected');
    //serialPort.write(data+"\n");
        var x = 1;
        var y = null;

        sp.write('p'+parseInt(data)+'q');
        setTimeout(function() {
         x = x * 3 + 2;
          y = x / 2;
        }, 100); //concider sending 0-100 in ascii 0 = 0; 100 = 'd';
        console.log("Wrote to serialport: "+"p"+parseInt(data)+"\0");
    });
    setInterval(function(){sp.write('u')},500);

        
    sp.on('data', function(data) {
            var string = data.split(":");
            var number = Array(string[1]);
            if(string[0] == "Encoder"){
                for(var i= 0; i<string[1].length; i++){
                    number[i] = string[1][i];
                }
                
                number = parseInt(number.join(''));
                //string = number + 'px';
                if (number>100){
                  number=100;
                }
                else if(number<=0){
                  number = 0;
                }
                number = (100-number)*4

                console.log('data received: ' + string);
                console.log('Number out:' + number);
                string = number + 'px';
                console.log("string sent: " + string);
                socket.emit('newpos', string);
            }
            if(string[0] == "Score"){
              for(var i= 0; i<string[1].length; i++){
                    number[i] = string[1][i];
              }
              number = parseInt(number.join(''));
              socket.emit("update_score",number);
            }
            console.log(data);
        
    });
  	
	
    socket.on('change', function(){
        console.log("change triggered wrote to uart")
        sp.write('s');
        sp.write('q');
        }); 
    });
});



