var serialport = require("serialport");
var SerialPort = serialport.SerialPort; // localize object constructor

var sp = new SerialPort("/dev/ttyACM0", { 
	parser: serialport.parsers.readline("\n"),
	baudrate: 9600,
	databits: 8,
	stopbits: 1,
	parity: 'none'
});

sp.on("open", function () {
	console.log('open');
	sp.on('data', function(data) {
   		console.log('data received: ' + data);
	});
});
