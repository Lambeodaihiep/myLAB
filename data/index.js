var slider0 = document.getElementById("servoSlider0");
    var servoP0 = document.getElementById("servoPos0");
    servoP0.innerHTML = slider0.value;
    slider0.oninput = function() {
      slider0.value = this.value;
      servoP0.innerHTML = this.value;
    }

var slider1 = document.getElementById("servoSlider1");
    var servoP1 = document.getElementById("servoPos1");
    servoP1.innerHTML = slider1.value;
    slider1.oninput = function() {
      slider1.value = this.value;
      servoP1.innerHTML = this.value;
    }

var slider2 = document.getElementById("servoSlider2");
    var servoP2 = document.getElementById("servoPos2");
    servoP2.innerHTML = slider2.value;
    slider2.oninput = function() {
      slider2.value = this.value;
      servoP2.innerHTML = this.value;
    }

var slider3 = document.getElementById("servoSlider3");
    var servoP3 = document.getElementById("servoPos3");
    servoP3.innerHTML = slider3.value;
    slider3.oninput = function() {
      slider3.value = this.value;
      servoP3.innerHTML = this.value;
    }

var slider4 = document.getElementById("servoSlider4");
    var servoP4 = document.getElementById("servoPos4");
    servoP4.innerHTML = slider4.value;
    slider4.oninput = function() {
      slider4.value = this.value;
      servoP4.innerHTML = this.value;
    }

var slider5 = document.getElementById("servoSlider5");
    var servoP5 = document.getElementById("servoPos5");
    servoP5.innerHTML = slider5.value;
    slider5.oninput = function() {
      slider5.value = this.value;
      servoP5.innerHTML = this.value;
    }

var slider6 = document.getElementById("servoSlider6");
    var servoP6 = document.getElementById("servoPos6");
    servoP6.innerHTML = slider6.value;
    slider6.oninput = function() {
      slider6.value = this.value;
      servoP6.innerHTML = this.value;
    }

var slider7 = document.getElementById("servoSlider7");
    var servoP7 = document.getElementById("servoPos7");
    servoP7.innerHTML = slider7.value;
    slider7.oninput = function() {
      slider7.value = this.value;
      servoP7.innerHTML = this.value;
    }

var slider8 = document.getElementById("servoSlider8");
    var servoP8 = document.getElementById("servoPos8");
    servoP8.innerHTML = slider8.value;
    slider8.oninput = function() {
      slider8.value = this.value;
      servoP8.innerHTML = this.value;
    }

var slider9 = document.getElementById("servoSlider9");
    var servoP9 = document.getElementById("servoPos9");
    servoP9.innerHTML = slider9.value;
    slider9.oninput = function() {
      slider9.value = this.value;
      servoP9.innerHTML = this.value;
    }

var slider10 = document.getElementById("servoSlider10");
    var servoP10 = document.getElementById("servoPos10");
    servoP10.innerHTML = slider10.value;
    slider10.oninput = function() {
      slider10.value = this.value;
      servoP10.innerHTML = this.value;
    }

var slider11 = document.getElementById("servoSlider11");
    var servoP11 = document.getElementById("servoPos11");
    servoP11.innerHTML = slider11.value;
    slider11.oninput = function() {
      slider11.value = this.value;
      servoP11.innerHTML = this.value;
    }

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
window.addEventListener('load', onLoad);

function onLoad(event) {
  initWebSocket();
}

function initWebSocket() {
  console.log('Trying to open a WebSocket connection...');
  websocket = new WebSocket(gateway);
  websocket.onopen    = onOpen;
  websocket.onclose   = onClose;
  websocket.onmessage = onMessage; // <-- add this line
}
function onOpen(event) {
  console.log('Connection opened');
}
function onClose(event) {
  console.log('Connection closed');
  setTimeout(initWebSocket, 2000);
}

var message;
var servoP, slider;
function onMessage(event) {
  console.log(event.data);
  message = event.data;
  slider = message.substring(0, message.indexOf("&"));
  servoP = message.substring(message.indexOf("&") + 1, message.length);
  document.getElementById("servoPos" + slider).innerHTML = servoP;
  document.getElementById("servoSlider" + slider).value = servoP;
  // window.onload = function what(){
    
  // };
}

function submitForm0(){
  websocket.send("0&" + slider0.value);
}
function submitForm1(){
  websocket.send("1&" + slider1.value);
}
function submitForm2(){
  websocket.send("2&" + slider2.value);
}
function submitForm3(){
  websocket.send("3&" + slider3.value);
}
function submitForm4(){
  websocket.send("4&" + slider4.value);
}
function submitForm5(){
  websocket.send("5&" + slider5.value);
}
function submitForm6(){
  websocket.send("6&" + slider6.value);
}
function submitForm7(){
  websocket.send("7&" + slider7.value);
}
function submitForm8(){
  websocket.send("8&" + slider8.value);
}
function submitForm9(){
  websocket.send("9&" + slider9.value);
}
function submitForm10(){
  websocket.send("10&" + slider10.value);
}
function submitForm11(){
  websocket.send("11&" + slider11.value);
}