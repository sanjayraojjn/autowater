/**
 * ----------------------------------------------------------------------------
 * ESP32 Remote Control with WebSocket
 * ----------------------------------------------------------------------------
 * © 2020 Stéphane Calderoni
 * ----------------------------------------------------------------------------
 */

var gateway = 'ws://' + window.location.hostname + '/ws';
var websocket;

//********************
// Initialization
//*********************

window.addEventListener('load', onLoad);

function onLoad(event){
    initWebSocket();
    initButton();
}

function initWebSocket(){
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('Connection opened');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function onMessage(event){
    console.log("recieved a notification from " + event.origin);
    //change the class of led
    let data = JSON.parse(event.data);
    if(data.status){
        document.getElementById("led").className = data["status"];
    }
    if(data.dryness_level){
        document.getElementById("soil_dryness_level").innerHTML = data.dryness_level;
    }
    if(data.required_dryness_level){
        document.getElementById("required_soil_dryness").innerHTML = data.required_dryness_level;
    }
    
    console.log(event);
}

function initButton(){
    document.getElementById("toggle").addEventListener("click", onToggle);
    document.getElementById("refresh").addEventListener("click", onRefresh);
}

function onToggle(evt){
    console.log("toggle called");
    //websocket.send('toggle');
    websocket.send( JSON.stringify({"action":"toggle"}) );
}
function onRefresh(evt){
    console.log("refresh called");
    //websocket.send('toggle');
    websocket.send( JSON.stringify({"action":"get_sensor_params"}) );
}

function getSensorParams(evt){
    console.log("update fields called");
    websocket.send( JSON.stringify({"action":"get_sensor_params"}) );
}

