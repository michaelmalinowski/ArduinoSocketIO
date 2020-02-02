var app = require('express')();
var server = require('http').Server(app);
var io = require('socket.io')(server);

server.listen(80);
// WARNING: app.listen(80) will NOT work here!

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function (socket) {
  console.log("New User");
  
  socket.on('arduino', function (data) {
    console.log(data);
  });

  socket.on('hello', function (data) {
    socket.broadcast.emit('hello', 'helloss')
    console.log(data);
  });
});
