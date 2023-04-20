const express = require("express");
const cors = require('cors');
const bodyParser = require('body-parser');
const { WebSocketServer, WebSocket } = require("ws");

const app = express();
const port = 3000;
const jsonParser = bodyParser.json();

let communication = {};
let messages = {};
let ids = new Set();
let socketServers = {};
let sockets = {};

app.use(cors());

app.post("/", jsonParser, (req, res) => {
  const data = req.body;
  console.log("Received message:");
  console.log(data);

  ids.add(data.id);
  for(const key of ids.keys()) {
    if(key === data.id) continue;
    console.log(Object.keys(sockets));
    if(sockets[key]) {
      ws = sockets[key];
      ws.send(JSON.stringify({message: data.message}));
    }else if(messages[key]) {
      messages[key].push(data.message);
    }else{
      messages[key] = [data.message]
    }
  }

  console.log("Messages are:");
  console.log(messages);
  

  res.sendStatus(200);
});

app.get("/", (req, res) => {
  const id = req.query.id;
  console.log(`Request by id ${id}`);
  if(!(id in communication)) {
    res.sendStatus(418)
    return;
  }else if(communication[id] === "poll") {
    const data = messages[id];
    
    if(data) {
      messages[id] = null;
      res.send({messages: data})
    } else {
      res.sendStatus(204);
    }
    return;
  }else if(communication[id] === "long-poll") {
    const data = messages[id];

    if(data) {
      messages[id] = null;
      res.send({messages: data})
    } else {
      setTimeout(() => longPool(id, res), 500);
    }
    return;
  }
});

function longPool(id, res) {
  if(messages[id]) res.send({messages: messages[id]});
  else setTimeout( () => { longPool(id, res); }, 500);
}

app.post("/communication", jsonParser, (req, res) => {
  const data = req.body;
  console.log("Received communication type change:");
  console.log(data);

  ids.add(data.id);;
  
  communication[data.id] = data.communication;

  if(socketServers[data.id]) {
    const wss = socketServers[data.id];
    wss.close();
    delete socketServers[data.id];
  }
  if(data.communication === "websocket") {
    const wss = new WebSocketServer({
      port: data.id % 65536 < 10024 ? (data.id + 10024)%65536 : data.id%65536
    });
    wss.on("connection", (ws, req) => {
      sockets[data.id] = ws;
      ws.on("message", data => {});
      ws.on("close", () => {
        delete sockets[data.id];
      });
      ws.onerror = () => {};
    });
    socketServers[data.id] = wss;
  }

  console.log("Communication is:")
  console.log(communication);

  res.sendStatus(200);
});

app.listen(port, () => {
  console.log(`Started on port ${port}`);
});